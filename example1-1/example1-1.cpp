///////////////////////////////////////////////////////////////////////
//
// triangles.cpp
//
///////////////////////////////////////////////////////////////////////
#include <iostream> 
using namespace std;

#include "vgl.h"
#include "LoadShaders.h" 

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers }; 
enum Attrib_IDs { vPosition = 0 };

static bool spin = false;
static GLfloat spinFactor = 0.0;

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;

//---------------------------------------------------------------------
//
// init
//
void init(void) 
{
	glewExperimental = GL_TRUE;
	glewInit();
	glGenVertexArrays(NumVAOs, VAOs);
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

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
			vertices, GL_STATIC_DRAW);
	ShaderInfo  shaders[] = 
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT,GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

//---------------------------------------------------------------------
//
// display
//
void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush(); 
}

void showEmpty(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void showTriangle(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Mais sobre os comandos de push e pop matrices aqui: 
	//http://www.opengl.org/sdk/docs/man2/xhtml/glPushMatrix.xml
	glPushMatrix();

	glRotatef(spinFactor, 1.0, 1.0, 0.0);
	glColor3f (0.7, 0.7, 0.7);

	//Mecanismo similar ao glPushMatrix
	//no topo da pilha é colocada uma cópia de um conjunto de atributos,
	//incluindo a cor
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f (1.0, 1.0, 1.0);
	glVertex3f (-0.5, -0.5, 0.0);

	glColor3f (1.0, 0.0, 0.0);
	glVertex3f (0.5, -0.5, 0.0);

	glColor3f (0.0, 1.0, 0.0);
	glVertex3f (0.5, 0.5, 0.0);

	glColor3f (0.0, 0.0, 1.0);
	glVertex3f (-0.5, 0.5, 0.0);

	glEnd();

	//retira cabeça da pilha de atributos
	glPopAttrib();

	//retira a matriz de transformação da cabeça da pilha
	glPopMatrix();
}

//função que incrementa o ângulo de rotação
void spinDisplay(void)
{
	spinFactor = spinFactor + 2.0;
	if (spinFactor > 360.0)
		spinFactor = spinFactor - 360.0;
}

//função chamada quando a tela é redimensionada 
void reshape(GLFWwindow* window, int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//evento que trata clique do mouse
void mouse(GLFWwindow* window, int button, int action, int mods) 
{
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_PRESS)
				spin = true;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			if (action == GLFW_PRESS)
				spin = false;
			break;
		default:
			break;
	}
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(512, 512, "Hello World", NULL, NULL);
	if (!window)
	{
		printf("Error while creating window");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, reshape);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSwapInterval(1);

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//showEmpty();
		//showTriangle();
		//if (spin)
		//	spinDisplay();
		display();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
