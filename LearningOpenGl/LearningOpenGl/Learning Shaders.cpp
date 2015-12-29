#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

// --- Window Dimensions 
const GLuint WIDTH = 800, HEIGHT = 600;

// --- Input Function ---
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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
// --- Vertex Shader ---
// - The vertex shade uses the co-ordinates from one 3D vertex and turns them into different 3D co-ordinates -
const GLchar* vertexShaderSource = "#version 330 core\n"

"layout (location = 0) in vec3 position;\n"

"out vec4 vertexColor;\n" // Specify a color output to the fragment shader
//"out vec3 ourColor;\n"

"void main()\n"
"{\n"

"gl_Position = vec4(position, 1.0);\n"
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
//"ourColor = color;\n"

"}\n";

// --- Fragment Shader ---
// - The fragement shader is basically the thing that calulates the final colour of a pixal, it's where the advanced OpenGL Effects occur -
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n" // Recieves the output data from the vertex shader

//"in vec3 ourColor;\n"

"out vec4 color;\n"

"void main()\n"
"{\n"

"color = vertexColor;\n"

"}\n";


int main()
{

	
	cout << "Start Program\n";
	
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
	glViewport(0, 0, 800, 600); // --- Location of bottom left corner of the window - width - height ---
	
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

	GLuint shaderProgram;
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

	// --- VERTEX INPUT ---
	GLfloat vertices[] = {
		-0.01f, -0.01f, 0.0f,
		0.01f, -0.01f, 0.0f,
		0.0f, 0.01f, 0.0f
	};

	
	// --- Player Positions ---
	const int ArraySize = 50000;
	glm::vec2 playerPositions[ArraySize];
	ReadingPlayer0(playerPositions);
	for (int i = 0; i < 50000; i++)
	{
		cout << glm::to_string(playerPositions[i]) << endl;
	}


	// --- Buffer Objects ---
	GLuint VBO, VAO;

	// --- Buffers ---
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// - Binds the Vertex Array OBject first and then set the Vertex Buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// - Copys the user-defined data (Vertices) to the currently bound buffer -
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // - The buffer we want to copy, the size of the data we want to pass through the buffer, the actual data we want to send, How we want the GPU to process the given data -
	// GL_STATIC_DRAW - Basic / GL_DYNAMIC_DRAW and GL_STREAM_DRAW - Advanced

	// - Tells OpenGL how to interpret the the vertex data - 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // - Specifies which vertex attribute we want to configure (Location = 0), Size of the vertex attribute, Type of data, Normalized data or not?, The stride (Explained later), The offset of where the position data begins in the buffer - 
	glEnableVertexAttribArray(0); // - Enables the vertex attribute since it is disabled by default -

	// - Color Attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // - Unbind the VAO - 

	// - Uncommenting this line will make the wireframe triangle -
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// --- The Game Loop ---		
	
	// - Stops the Windows Closing until the User is finished -
	while (!glfwWindowShouldClose(window))
	{
		// --- Checks if any events have been activated e.g. key press ---
		glfwPollEvents();

		// --- Rendering Commands ---
			// --- Background Color Buffer ---
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // --- Red, Green, Blue, Alpha ---
			glClear(GL_COLOR_BUFFER_BIT);

			// --- Drawing Our First Triangle ---
			glUseProgram(shaderProgram);

			// --- Lets us change colour over time ---
			GLfloat timeValue = glfwGetTime(); // Run time in seconds
			GLfloat greenValue = ((sin(timeValue)/4) + 0.5); // Vary the colour based on sin/cos
			GLfloat redValue = ((cos(timeValue)/2) + 0.5); // Vary the colour based on sin/cos
			GLfloat blueValue = ((cos(timeValue)/2) + 0.5); // Vary the colour based on sin/cos
			GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // gets the uniforms location
			glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f); // Lastly we set the uniform value using this

			glBindVertexArray(VAO); // Binds the VAO
			glDrawArrays(GL_TRIANGLES, 0, 3); // Draws the Triangle (Type of drawing, Unknown, number of vertices)
			glBindVertexArray(0); // Unbinds the VAO

		// --- Once the back buffer is done rendering anything to display it is transfered to the front buffer as a complete image hence swap buffers ---
		glfwSwapBuffers(window);  
	}

	// --- Deletes the VAO ---
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
		//data.ReadingData();

	// --- End Main ---
	glfwTerminate();
	return 0;
}	

// --- User Input Function ---
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		cout << "Enter Pressed";
}