#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <Cunt\glew.h>

// GLFW
#include <Cunt\glfw3.h>
#include "ReadingData.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\string_cast.hpp>

using namespace std;

// --- Shader Creation ---
GLuint shaderProgram;
GLint vertexColorLocation;

// --- Window Dimensions ---
const GLuint WIDTH = 800, HEIGHT = 800;

// --- Input Function ---
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();

// --- Camera ---
glm::vec3 cameraPos = glm::vec3(325.0f, 754.0f, 2526.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
bool keys[1024];

// --- Deltatimte ---
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// --- HeatMap ---
void CheckWithin(glm::vec3 SquaresArray[], glm::vec3 PlayerPos[], int ColourArray[]);
void CreateSquareArray(glm::vec3 SquaresArray[]);
void colourpicker(int ColourArray[]);

// --- Creation ---
void Trajection();
void HeatMap();

// --- Player Variables ---
const int ColorArray = 40000;
glm::vec3 HeatMapSquares[ColorArray];
int ColorPicker[ColorArray];
const int PosArray = 150000;
glm::vec3 playerPos0[PosArray];
glm::vec3 playerPos1[PosArray];
glm::vec3 playerPos2[PosArray];
glm::vec3 playerPos3[PosArray];
glm::vec3 playerPosFull[PosArray];

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
"layout(location = 1) in vec2 texCoord;\n"

"out vec4 vertexColor;\n" // Specify a color output to the fragment shader
"out vec2 TexCoord;\n"

"uniform mat4 transform;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"

//"gl_Position = projection * view * vec4(position, 1.0f);\n" // Default
"gl_Position = projection * view * transform * vec4(position, 1.0f);\n" // With Translations
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"

"}\n";

// ========================
// --- Fragment Shader ---
// ========================
const GLchar* fragmentShaderSource = "#version 330 core\n"
// "in vec4 vertexColor;\n" // Recieves the output data from the vertex shader

"out vec4 color;\n"

"uniform vec4 ourColor;\n"

"void main()\n"
"{\n"

"color = ourColor;\n"

"}\n\0";


int main()
{
	cout << "Start Program\n";

	// --- Getting Player Data ---
	fileOpen();

	CreateSquareArray(HeatMapSquares);
	//ReadingPlayer0(playerPos0);
	//ReadingPlayerFull(playerPosFull);

	//CheckWithin(HeatMapSquares, playerPosFull, ColorPicker);


	// - With the vertex shader, each input variable is know as a "Vertex Attribute" -
	// - We are limited by the hardware to how many of these we can declare by we are guaranted at least 16 4-Component Vertex Attributes -
	// - Checks how many vertex attributes my hardware allows for -
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// --- Iniitialize GLFW ---
	glfwInit();

	// --- Configure GLFW ---
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // - Not Resizable by the user

											  // --- CREATING A WINDOW ---
											  // FULL SCREEN??? glfwGetPrimaryMonitor() for first nullptr
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // --- Width - Height - Title - Window? - Unknown ---
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// --- INITIALIZE GLEW ---
	glewExperimental = GL_TRUE; // - Activates Modern Versions of GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// --- Call The KeyCallBack Function ---
	glfwSetKeyCallback(window, key_callback);

	// --- Initialize the Viewport (Camera) ---
	glViewport(0, 0, WIDTH, HEIGHT); // --- Location of bottom left corner of the window - width - height ---

								// --- glViewport is basically a worldpoint to screenpoint transformer ---

								// --- SHADER COMPILER ---
								// -- Vertex Shader -- 

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

	// -- Fragment Shader --

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

	// -- Program Shaders --
	// - To actually use the shaders we just made, we need to link them together to form the pipeline -

	shaderProgram = glCreateProgram(); // - Creates a programa and returns an ID to the program object (shaderProgram) -

	glAttachShader(shaderProgram, vertexShader); // - attaches the vertex shador to the program -
	glAttachShader(shaderProgram, fragmentShader); // - attaches the fragment shador to the program -
	glLinkProgram(shaderProgram); // - Links all of the above together -

								  // --- Testing to see if the program shader properly compiles ---
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// -- Delete the shaders once they are finished --
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// =====================
	// --- VERTEX INPUT ---
	// =====================
	GLfloat TriangleForTrajectory[] = {
		-2.5f, -2.5f, 0.0f,
		2.4f, -2.5f, 0.0f,
		0.0f, 2.5f, 0.0f,
	};
	
	GLfloat SquareForHeatMap[] = {
		-5.0f, -5.0f, 0.0f,
		5.0f, -5.0f, 0.0f,
		5.0f, 5.0f, 0.0f,

		-5.0f, -5.0f, 0.0f,
		-5.0f, 5.0f, 0.0f,
		5.0f, 5.0f, 0.0f
	};

	// --- Testing the Positions ---
	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f,  0.0f,  0.0f),
	//	glm::vec3(2.0f,  5.0f, 0.0f),
	//	glm::vec3(-1.5f, -2.2f, 0.0f),
	//	glm::vec3(-3.8f, -2.0f, 0.0f),
	//	glm::vec3(2.4f, -0.4f, 0.0f),
	//	glm::vec3(-1.7f,  3.0f, 0.0f),
	//	glm::vec3(1.3f, -2.0f, 0.0f),
	//	glm::vec3(1.5f,  2.0f, 0.0f),
	//	glm::vec3(1.5f,  0.2f, 0.0f),
	//	glm::vec3(-1.3f,  1.0f, 0.0f)
	//};

	// =================================
	// --- Setting Up The Triangles ---
	// =================================
	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// ============================
	// --- Trajectory Triangle ---
	// ============================
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleForTrajectory), TriangleForTrajectory, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); 

	// ========================
	// --- HeatMap Squares ---
	// ========================
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareForHeatMap), SquareForHeatMap, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// - Uncommenting this line will make the wireframe triangle -
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ======================
	// --- The Game Loop ---
	// ======================

	while (!glfwWindowShouldClose(window))
	{
		// --- Calculate deltatime of the current frame ---
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// --- Checks if any events have been activated e.g. key press ---
		glfwPollEvents();
		do_movement();

		// --- Rendering Commands ---
		// --- Background Color Buffer ---
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // --- Red, Green, Blue, Alpha ---
		glClear(GL_COLOR_BUFFER_BIT);

		// --- Drawing Our First Triangle ---
		glUseProgram(shaderProgram);

		// --- Camera ---
		glm::mat4 view;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		cout << glm::to_string(cameraPos) << endl;

		// --- View and projection ---
		glm::mat4 projection;
		
		//view = glm::translate(view, glm::vec3(-300.0f, -700.0f, -4000.0f)); // the view we are alligned too
		projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 7000.0f); // the Max and Min we set to be able to see

		// Get their uniform location
		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// --- Colours ---

		//GLfloat timeValue = glfwGetTime(); // Run time in seconds
		//GLfloat greenValue = ((sin(timeValue) / 2) + 0.5); // Vary the colour based on sin/cos
		//GLfloat redValue = ((sin(timeValue) / 2) + 0.5); // Vary the colour based on sin/cos
		//GLfloat blueValue = ((sin(timeValue) / 2) + 0.5); // Vary the colour based on sin/cos

		vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // gets the uniforms location
		colorRed = 1.0f;
		colorBlue = 0.0f;
		colorGreen = 1.0f;
		glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);

		// ===============================
		// --- Spawning the triangles ---
		// ===============================
		glBindVertexArray(VAOs[1]);
		HeatMap();
		//glDrawArrays(GL_TRIANGLES, 0, 6); // --- Default ---

		glBindVertexArray(VAOs[0]);
		//Trajection();
		//glDrawArrays(GL_TRIANGLES, 0, 3); // --- Default ---
		
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
	fileClose();
	return 0;
}

// --- User Input Function ---
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

void CheckWithin(glm::vec3 Square[], glm::vec3 PlayerPos[], int ColourArray[])
{
	int MaxNum = 0;
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
					ColourArray[i] = ColorNum;
					if (ColorNum > MaxNum)
					{
						MaxNum = ColorNum;
					}
				}
			}
		}
		ColorNum = 0;	
		if (ColourArray[i] < 0)
		{
			ColourArray[i] = 0;
		}
	}
	cout << ColorNum << endl;
}

void CreateSquareArray(glm::vec3 SquareList[])
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
			SquareList[k] = glm::vec3(x, y, 1.0f);
			k++;
		}
	}
	k = 0;
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
	default:
		colorRed = 0.0f;
		colorGreen = 0.0f;
		colorBlue = 0.0f;
	}
}

void Trajection()
{
	for (GLuint i = 0; i < PosArray; i++)
	{
		if (playerPos0[i].x != 0 && playerPos0[i].y != 0)
		{
			glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
			glm::mat4 trans;
			trans = glm::translate(trans, playerPos0[i]);
			//trans = glm::translate(trans, cubePositions[i]);
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glDrawArrays(GL_TRIANGLES, 0, 3); // Draws the Triangle (Type of drawing, Unknown, number of vertices)
		}
	}

	//glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);

	//for (GLuint i = 0; i < ArraySize; i++)
	//{
	//	if (player1Positions[i].x != 0 && player1Positions[i].y != 0)
	//	{
	//		glm::mat4 trans;
	//		trans = glm::translate(trans, player1Positions[i]);
	//		//trans = glm::translate(trans, cubePositions[i]);
	//		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	//		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	//		glDrawArrays(GL_TRIANGLES, 0, 3); // Draws the Triangle (Type of drawing, Unknown, number of vertices)
	//	}
	//}

}

void HeatMap() 
{
	for (GLuint i = 0; i < 34400; i++)
	{
		//colourpicker(ColorPicker[i]);
		glUniform4f(vertexColorLocation, colorRed, colorGreen, colorBlue, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, HeatMapSquares[i]);
		//trans = glm::translate(trans, cubePositions[i]);
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawArrays(GL_TRIANGLES, 0, 6); // Draws the Triangle (Type of drawing, Unknown, number of verticess 
	}
}