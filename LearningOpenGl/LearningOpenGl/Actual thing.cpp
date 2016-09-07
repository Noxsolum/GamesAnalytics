#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

// GLEW
#define GLEW_STATIC
#include <GLFW\glew.h>

// GLFW
#include <GLFW\glfw3.h>
#include "ReadingData.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\string_cast.hpp>

using namespace std;

// ========================
// --- Shader Creation ---
// ========================
GLuint VBOs[3], VAOs[3];
GLuint shaderProgram;
GLint vertexColorLocation;

// ==========================
// --- Window Dimensions ---
// ==========================
const GLuint WIDTH = 900, HEIGHT = 900;

// =======================
// --- Input Function ---
// =======================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();
void switchPlayer();

// ===============
// --- Camera ---
// ===============
glm::vec3 cameraPos = glm::vec3(415.0f, 754.0f, 2526.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
bool keys[1024];

// ==================
// --- Deltatime ---
// ==================
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// ================
// --- HeatMap ---
// ================
void CheckWithin(glm::vec3 SquaresArray[], glm::vec3 PlayerPos[], int ColourArray[]);
void CreateSquareArray(glm::vec3 SquaresArray[]);
void CheckDeath(glm::vec3 SquaresArray[], glm::vec3 PlayerPos[], int ColourArray[]);
void CreateDeathArray(glm::vec3 SquaresArrayTwo[]);
void colourpicker(int NoOfInts);
void deathcolourpicker(int noOfIntTwo);

// =================
// --- Creation ---
// =================
void Trajection();
void HeatMap();
void DeathMap();

// =========================
// --- Player Variables ---
// =========================
const int ColorArray = 60000;
const int DeathArray = 8100;
glm::vec3 HeatMapSquares[ColorArray];
glm::vec3 DeathMapSquares[DeathArray];
int ColorPickerFull[ColorArray];
int ColorPickerDeath[DeathArray];
const int PosArray = 200000;
glm::vec3 playerPos0[PosArray];
glm::vec3 playerPos1[PosArray];
glm::vec3 playerPos2[PosArray];
glm::vec3 playerPos3[PosArray];
glm::vec3 playerPos4[PosArray];
glm::vec3 playerPos5[PosArray];
glm::vec3 playerPos6[PosArray];
glm::vec3 playerPos7[PosArray];
glm::vec3 playerPos8[PosArray];
glm::vec3 playerPos9[PosArray];
glm::vec3 playerPosFull[PosArray];
glm::vec3 playerPosDeath[PosArray];
int WhichTrajectory = 0;
int WhichHeatMap = 0;
int allTrajectories = 0;

// ================
// --- Colours ---
// ================
GLfloat colorBlue = 0.0f;
GLfloat colorRed = 0.0f;
GLfloat colorGreen = 0.0f;

/* --- GLSL Shaders ---
- THe shaders are, very simply, nothing more than programs that transform inputs to outputs -
- We use GLSL for this because it is specifically tailored to vector and matrix manipulation -

-- A Shader always begins with the version declaration --
#version version_number

-- Followed by the Inputs, Outputs and Uniforms --
in type in_varible_name;
in type in_varible_name;

out type out_varible_name;
out type out_varible_name;

uniform type uniform_name;

-- Followed by it's main function where we process all of the input varibles and output them in the output varibles --
void main()
{
// Process the inputs and do weird graphics stuff
...
//Output the processed stuff to output variable
output_variable_name = weird_stuff_we_processed;
}

--- Types ---
- GLSL has all the basic types we know (int, float, double, uint, bool) -
- It also introduces two container types which are vectors and matrices -

--- Vectors ---
- vecn: Default number of n floats
- bvecn: a vector of n booleans.
- ivecn: a vector of n integers.
- uvecn: a vector of n unsigned integers.
- dvecn: a vector of n double components.

- To access the individual componants of these vecs we will use .x, .y, .z and .w
- e.g. vec3 someVec;
- e.g. someVec.x;
- e.g. someVec = (1.0f, 1.0f, 1.0f)
- e.g. vec4 otherVec = (someVec.xyz, 1.0f)

- GLSL uses the keyword 'in' and 'out' to move things about within the shaders
*/
// ======================
// --- Vertex Shader ---
// ======================
const GLchar* vertexShaderSource = "#version 330 core\n"

"layout (location = 0) in vec3 position;\n"

"out vec4 vertexColor;\n"

"uniform mat4 transform;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"gl_Position = projection * view * transform * vec4(position, 1.0f);\n"
"}\n";

// ========================
// --- Fragment Shader ---
// ========================
const GLchar* fragmentShaderSource = "#version 330 core\n"

"out vec4 color;\n"

"uniform vec4 ourColor;\n"

"void main()\n"
"{\n"

"color = ourColor;\n"

"}\n\0";


int main()
{
	// =====================
	// --- Instructions ---
	// =====================
	cout << "Start Program!\n";
	cout << "Use the WASD keys to pan the scene!\n";
	cout << "Use Page Up and Page Down to Zoom!\n";
	cout << "Use the '1', '2' and '3' keys to change the the individual trajectories!\n";
	cout << "Use the '4', '5' and '6' keys to change the the heat maps!\n";
	cout << "Use the '-' and '=' keys to turn on and off the full trajectories!\n";

	// =====================
	// --- Reading Data ---
	// =====================
	CreateSquareArray(HeatMapSquares);
	CreateDeathArray(DeathMapSquares);
	
	ReadingData(playerPos0, playerPos1, playerPos2, playerPos3, playerPos4, playerPos5, playerPos6, playerPos7, playerPos8, playerPos9, playerPosFull);
	ReadingDeath(playerPosDeath);

	CheckWithin(HeatMapSquares, playerPosFull, ColorPickerFull);
	CheckDeath(DeathMapSquares, playerPosDeath, ColorPickerDeath);

	// ===================
	// --- Attributes ---
	// ===================
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// ========================
	// --- INITIALIZE GLFW ---
	// ========================
	glfwInit();

	// --- Configure GLFW ---
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // --- Width - Height - Title - Window? - Unknown ---
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// ========================
	// --- INITIALIZE GLEW ---
	//=========================
	glewExperimental = GL_TRUE; // - Activates Modern Versions of GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// ======================================
	// --- Call The KeyCallBack Function ---
	// ======================================
	glfwSetKeyCallback(window, key_callback);

	// =========================================
	// --- Initialize the Viewport (Camera) ---
	// =========================================
	glViewport(0, 0, WIDTH, HEIGHT);

	// ======================
	// --- Vertex Shader ---
	// ======================

	GLuint vertexShader; // - Creates the shader object -
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // - Defines what kind of shader we want -

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // - The shader object, How many strings we want to pass, The source code(GLSL), length of the array - 
	glCompileShader(vertexShader); // - Compiles the shader -

								   // --- Testing to see if the vertex shader properly compiled ---
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ========================
	// --- Fragment Shader ---
	// ========================

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// --- Testing to see if the fragment shader properly compiles ---
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ========================
	// --- Program Shaders ---
	// ========================
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ==================================================
	// --- Delete the shaders once they are finished ---
	// ==================================================
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// =====================
	// --- VERTEX INPUT ---
	// =====================
	GLfloat SquareForTrajectory[] = {
		-3.0f, -3.0f, 0.0f,
		3.0f, -3.0f, 0.0f,
		3.0f, 3.0f, 0.0f,

		-3.0f, -3.0f, 0.0f,
		-3.0f, 3.0f, 0.0f,
		3.0f, 3.0f, 0.0f,
	};
	
	GLfloat SquareForHeatMap[] = {
		-5.0f, -5.0f, 0.0f,
		5.0f, -5.0f, 0.0f,
		5.0f, 5.0f, 0.0f,

		-5.0f, -5.0f, 0.0f,
		-5.0f, 5.0f, 0.0f,
		5.0f, 5.0f, 0.0f
	};

	GLfloat SquareForDeathMap[] = {
		-12.5f, -12.5f, 0.0f,
		12.5f, -12.5f, 0.0f,
		12.5f, 12.5f, 0.0f,

		-12.5f, -12.5f, 0.0f,
		-12.5f, 12.5f, 0.0f,
		12.5f, 12.5f, 0.0f
	};

	// =================================
	// --- Setting Up The Triangles ---
	// =================================
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);

	// ============================
	// --- Trajectory Squares ---
	// ============================
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareForTrajectory), SquareForTrajectory, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); 

	// ======================================
	// --- HeatMap Squares For Positions ---
	// ======================================
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareForHeatMap), SquareForHeatMap, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// ===================================
	// --- HeatMap Squares For Deaths ---
	// ===================================
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareForDeathMap), SquareForDeathMap, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// ======================
	// --- The Game Loop ---
	// ======================
	cout << "Begins the While Loop!" << endl;
	while (!glfwWindowShouldClose(window))
	{
		// =================================================
		// --- Calculate deltatime of the current frame ---
		// =================================================
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ===================
		// --- Key Inputs ---
		// ===================
		glfwPollEvents();
		do_movement();
		switchPlayer();
		
		//=================================
		// --- Background Color Buffer ---
		// ================================
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// --- Drawing Our First Triangle ---
		glUseProgram(shaderProgram);

		// ===============
		// --- Camera ---
		// ===============
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		cout << glm::to_string(cameraPos) << endl;

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 7000.0f);

		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ================
		// --- Colours ---
		// ================
		vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // gets the uniforms location
		colorRed = 1.0f;
		colorBlue = 0.0f;
		colorGreen = 1.0f;
		glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);

		// ==============================
		// --- Spawning the HeatMaps ---
		// ==============================
		switch (WhichHeatMap)
		{
		case 1:
			glBindVertexArray(VAOs[1]);
			HeatMap();	
			break;
		case 2:
			glBindVertexArray(VAOs[2]);
			DeathMap();
			break;
		default:
			break;
		}

		// ==============================
		// --- Spawning the Trajectories ---
		// ==============================
		glBindVertexArray(VAOs[0]);
		Trajection();
		
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	// ========================
	// --- Deletes the VAO ---
	// ========================
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	// =================
	// --- End Main --- 
	// =================
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 500.0f * deltaTime;

	if (cameraPos.z < 500.0f)
	{
		cameraSpeed = 100 * deltaTime;
	}

	if (keys[GLFW_KEY_PAGE_UP])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_PAGE_DOWN])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_W])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;
	if (keys[GLFW_KEY_S])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void switchPlayer()
{
	if (WhichTrajectory < 10)
	{
		if (keys[GLFW_KEY_1])
		{
			WhichTrajectory = WhichTrajectory + 1;
			if (WhichTrajectory > -1 && WhichTrajectory < 11)
			{
				cout << "Player: " << WhichTrajectory << endl;
			}
		}
	}
	if (WhichTrajectory > 0)
	{
		if (keys[GLFW_KEY_2])
		{
			WhichTrajectory = WhichTrajectory - 1;
			if (WhichTrajectory > -1 && WhichTrajectory < 11)
			{
				cout << "Player: " << WhichTrajectory << endl;
			}
		}
	}
	if (keys[GLFW_KEY_3])
	{
		WhichTrajectory = -1;
		cout << "Trajectories Off!" << endl;
	}

	if (keys[GLFW_KEY_4])
	{
		WhichHeatMap = 1;
		if (WhichHeatMap > -1 && WhichHeatMap < 11)
		{
			cout << "Player Position Heat Map!" << endl;
		}
	}

	if (keys[GLFW_KEY_5])
	{
		WhichHeatMap = 2;
		if (WhichHeatMap > -1 && WhichHeatMap < 11)
		{
			cout << "Player Deaths Heat Map!" << endl;
		}
	}

	if (keys[GLFW_KEY_6])
	{
		WhichHeatMap = 0;
		cout << "Heat Maps Off!" << endl;
	}
	if (keys[GLFW_KEY_MINUS])
	{
		WhichTrajectory = -1;
		allTrajectories = 1;
		cout << "Full Player Trajectories On!";
	}
	if (keys[GLFW_KEY_EQUAL])
	{
		WhichTrajectory = -1;
		allTrajectories = 0;
		cout << "Full Player Trajectories Off!";
	}
}

void Trajection()
{
	switch (allTrajectories)
	{
	case 1:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPosFull[i].x != 0 && playerPosFull[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPosFull[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	default:
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;
	}
	switch (WhichTrajectory)
	{
	case 0:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos0[i].x != 0 && playerPos0[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos0[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 1:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos1[i].x != 0 && playerPos1[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos1[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 2:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos2[i].x != 0 && playerPos2[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos2[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 3:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos3[i].x != 0 && playerPos3[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos3[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 4:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos4[i].x != 0 && playerPos4[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 1.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos4[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 5:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos5[i].x != 0 && playerPos5[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.5f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos5[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 6:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos6[i].x != 0 && playerPos6[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.5f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos6[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 7:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos7[i].x != 0 && playerPos7[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos7[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 8:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos8[i].x != 0 && playerPos8[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos8[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	case 9:
		for (GLuint i = 0; i < PosArray; i++)
		{
			if (playerPos9[i].x != 0 && playerPos9[i].y != 0)
			{
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glm::mat4 trans;
				trans = glm::translate(trans, playerPos9[i]);
				GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
		break;
	default:
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		break;
	}
}

void CreateSquareArray(glm::vec3 SquaresArray[])
{
	//Spawn squares every 10 points along the coords
	// Max Point: (1230, 1750), Min Point: (-490, -250)
	// 1750
		int k = 0;

		int x = 1755;
		for (int i = 0; i < 225; i++)
		{
			x = x - 10;
			int y = 1755;
			for (int j = 0; j < 225; j++)
			{
				y = y - 10;
				SquaresArray[k] = glm::vec3(x, y, 1.0f);
				k++;
			}
		}
		k = 0;
}

void CreateDeathArray(glm::vec3 SquaresArrayTwo[])
{
	int k = 0;
	float x = 1762.5;

	for (int i = 0; i < 90; i++)
	{
		x = x - 25;
		float y = 1762.5;
		for (int j = 0; j < 90; j++)
		{
			y = y - 25;
			SquaresArrayTwo[k] = glm::vec3(x, y, 1.0f);
			k++;
		}
	}
	k = 0;
}

void CheckWithin(glm::vec3 Square[], glm::vec3 PlayerPos[], int ColourArray[])
{
		int ColorNum = 0;
		for (int i = 0; i < ColorArray; i++)
		{
			for (int j = 0; j < PosArray; j++)
			{
				if ((PlayerPos[j].x != 0) && (PlayerPos[j].y != 0))
				{
					if ((PlayerPos[j].x < (Square[i].x + 5)) && (PlayerPos[j].x >(Square[i].x - 5)) && (PlayerPos[j].y < (Square[i].y + 5)) && (PlayerPos[j].y >(Square[i].y - 5)))
					{
						ColorNum++;
					}
				}
			}
			ColourArray[i] = ColorNum;
			if (ColourArray[i] < 0)
			{
				ColourArray[i] = 0;
			}
			ColorNum = 0;
		}
}

void CheckDeath(glm::vec3 Square[], glm::vec3 PlayerPos[], int ColourArray[])
{
	int ColorNum = 0;
	for (int i = 0; i < DeathArray; i++)
	{
		for (int j = 0; j < PosArray; j++)
		{
			if ((PlayerPos[j].x != 0) && (PlayerPos[j].y != 0))
			{
				if ((PlayerPos[j].x < (Square[i].x + 12.5)) && (PlayerPos[j].x >(Square[i].x - 12.5)) && (PlayerPos[j].y < (Square[i].y + 12.5)) && (PlayerPos[j].y >(Square[i].y - 12.5)))
				{
					ColorNum++;
				}
			}
		}
		ColourArray[i] = ColorNum;
		if (ColourArray[i] < 0)
		{
			ColourArray[i] = 0;
		}
		ColorNum = 0;
	}
}

void colourpicker(int noOfInts)
{
	switch (noOfInts) {
	case 0:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
		break;
	case 1:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.2f;
		break;
	case 2:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.4f;
	case 3:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.6f;
		break;
	case 4:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.8f;
		break;
	case 5:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 1.0f;
		break;
	case 6:
		colorRed = 0.0f;
		colorGreen = 0.2f;
		colorBlue = 1.0f;
		break;
	case 7:
		colorRed = 0.0f;
		colorGreen = 0.4f;
		colorBlue = 1.0f;
		break;
	case 8:
		colorRed = 0.0f;
		colorGreen = 0.6f;
		colorBlue = 1.0f;
		break;
	case 9:
		colorRed = 0.0f;
		colorGreen = 0.8f;
		colorBlue = 1.0f;
		break;
	case 10:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 1.0f;
		break;
	case 11:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.8f;
		break;
	case 12:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.6f;
		break;
	case 13:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.4f;
		break;
	case 14:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.2f;
		break;
	case 15:
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 16:
		colorRed = 0.2f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 17:
		colorRed = 0.4f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 18:
		colorRed = 0.6f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 19:
		colorRed = 0.8f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 20:
		colorRed = 1.0f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
		break;
	case 21:
		colorRed = 1.0f;
		colorGreen = 0.8f;
		colorBlue = 0.0f;
		break;
	case 22:
		colorRed = 1.0f;
		colorGreen = 0.6f;
		colorBlue = 0.0f;
		break;
	case 23:
		colorRed = 1.0f;
		colorGreen = 0.4f;
		colorBlue = 0.0f;
		break;
	case 24:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 25:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 26:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 27:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 28:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 29:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 30:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 31:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 32:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 33:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 34:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	case 35:
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
		break;
	default:
		colorRed = 1.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
	}
}

void deathcolourpicker(int noOfIntsTwo)
{
	if (noOfIntsTwo > -1 && noOfIntsTwo < 10)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 9 && noOfIntsTwo < 20)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.2f;
	}
	if (noOfIntsTwo > 19 && noOfIntsTwo < 30)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.4f;
	}
	if (noOfIntsTwo > 29 && noOfIntsTwo < 40)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.6f;
	}
	if (noOfIntsTwo > 39 && noOfIntsTwo < 50)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.8f;
	}
	if (noOfIntsTwo > 49 && noOfIntsTwo < 60)
	{
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 59 && noOfIntsTwo < 70)
	{
		colorRed = 0.0f;
		colorGreen = 0.2f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 69 && noOfIntsTwo < 80)
	{
		colorRed = 0.0f;
		colorGreen = 0.4f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 79 && noOfIntsTwo < 90)
	{
		colorRed = 0.0f;
		colorGreen = 0.6f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 89 && noOfIntsTwo < 100)
	{
		colorRed = 0.0f;
		colorGreen = 0.8f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 99 && noOfIntsTwo < 110)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 1.0f;
	}
	if (noOfIntsTwo > 109 && noOfIntsTwo < 120)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.8f;
	}
	if (noOfIntsTwo > 119 && noOfIntsTwo < 130)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.6f;
	}
	if (noOfIntsTwo > 129 && noOfIntsTwo < 140)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.4f;
	}
	if (noOfIntsTwo > 139 && noOfIntsTwo < 150)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.2f;
	}
	if (noOfIntsTwo > 149 && noOfIntsTwo < 160)
	{
		colorRed = 0.0f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 159 && noOfIntsTwo < 170)
	{
		colorRed = 0.2f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 169 && noOfIntsTwo < 180)
	{
		colorRed = 0.4f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 179 && noOfIntsTwo < 190)
	{
		colorRed = 0.6f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 189 && noOfIntsTwo < 200)
	{
		colorRed = 0.8f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 199 && noOfIntsTwo < 210)
	{
		colorRed = 1.0f;
		colorGreen = 1.0f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 209 && noOfIntsTwo < 220)
	{
		colorRed = 1.0f;
		colorGreen = 0.8f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 219 && noOfIntsTwo < 230)
	{
		colorRed = 1.0f;
		colorGreen = 0.6f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 229 && noOfIntsTwo < 240)
	{
		colorRed = 1.0f;
		colorGreen = 0.4f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 239 && noOfIntsTwo < 250)
	{
		colorRed = 1.0f;
		colorGreen = 0.2f;
		colorBlue = 0.0f;
	}
	if (noOfIntsTwo > 249 && noOfIntsTwo < 260)
	{
		colorRed = 1.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
	}
	if(noOfIntsTwo > 260)
	{
		colorRed = 1.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
	}
}

void HeatMap()
{

		for (GLuint i = 0; i < ColorArray; i++)
		{
			colourpicker(ColorPickerFull[i]);
			glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);
			glm::mat4 trans;
			trans = glm::translate(trans, HeatMapSquares[i]);
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		//for (GLuint i = 0; i < ColorArray; i++)
		//{
		//	colourpicker(ColorPickerDeath[i]);
		//	glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);
		//	glm::mat4 trans;
		//	trans = glm::translate(trans, HeatMapSquares[i]);
		//	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		//	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		//	glDrawArrays(GL_TRIANGLES, 0, 6);
		//}
}

void DeathMap()
{
	for (GLuint i = 0; i < DeathArray; i++)
	{
		deathcolourpicker(ColorPickerDeath[i]);
		glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, DeathMapSquares[i]);
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}