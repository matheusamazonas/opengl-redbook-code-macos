///////////////////////////////////////////////////////////////////////
//
// triangles.cpp
//
///////////////////////////////////////////////////////////////////////
#include <iostream> 
using namespace std;

#include "vgl.h"
#include "LoadShaders.h" 

// NumVAOs is used as an element count
enum VAO_IDs { Triangles, NumVAOs };
// NumBuffers is used as an element count
enum Buffer_IDs { ArrayBuffer, NumBuffers }; 
enum Attrib_IDs { vPosition = 0 };

// VAOs stores all Vertex Array Objects
GLuint  VAOs[NumVAOs];
// Stores all buffers used. In this example, we use only
// ArrayBuffers (Buffer_ID = 0)
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;

//---------------------------------------------------------------------
//
// init
//
void init(void) 
{
	// Generates 1 Vertex Array. Here we use the enum's
	// last element to alocate as many as Vertex Arrays
	// as are in the enum (NumVAOs = 1)
	glGenVertexArrays(NumVAOs, VAOs);
	// Binds the triangles Vertex Array (VAOs[0])
	glBindVertexArray(VAOs[Triangles]);
	GLfloat  vertices[NumVertices][2] = 
	{
		{ -0.90, -0.90 },  // Triangle 1
		{  0.85, -0.90 },
		{ -0.90,  0.85 },
		{  0.90, -0.85 },  // Triangle 2
		{  0.90,  0.90 },
		{ -0.85,  0.90 }
	}; 

	// Creates the buffer's name
	glGenBuffers(NumBuffers, Buffers);
	// Binds the buffer (Buffers[0])
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); 
	// Copy the data from the buffer object to OpenGL's server buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
			vertices, GL_STATIC_DRAW);
	// Set the shaders info
	// The ShaderINfo array end with a GL_NONE-type shader
	// ShaderInfo has basically a type and the path to the shader source code
	ShaderInfo  shaders[] = 
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	// Load the shaders and "run" them
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	// Connects the shader "in" variables to a vertex-attribute array
	// vPosition = 0 (declared before)
	glVertexAttribPointer(vPosition, 2, GL_FLOAT,GL_FALSE, 0, BUFFER_OFFSET(0));
	// Enable the vertex-attribute array passing the inde xof the attribute
	//  array pointer we just initialized
	glEnableVertexAttribArray(vPosition);
}

//---------------------------------------------------------------------
//
// display
//
void display(void) 
{
	// Clear the Color Buffer with the current color
	glClear(GL_COLOR_BUFFER_BIT);
	// Select the collection of vertives we want to draw
	glBindVertexArray(VAOs[Triangles]);
	// Actually draws
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush(); 
}

//---------------------------------------------------------------------
//
// main
//

int main (int argc, char** argv) 
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Forcing the applicaiton to run OpenGL 4.0 or higher
	// The RedBook is based on OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(512, 512, "Example 1-1", NULL, NULL);
	if (!window)
	{
		printf("Error while creating window");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initializes the GLEW library
	glewExperimental = GL_TRUE;
	glewInit();

	// Prints the OpenGL Version on the terminal
	//printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		display();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
