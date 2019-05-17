#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

#include "Sphere.h"
#include "Colors.h"

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;
Sphere *sun = new Sphere(&program);

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;
float eyeZ = 4; // for view matrix (zoom)
int n = 0;
int gRadius = 100;

int s = 4;


// For rotating the sphere per axis
int xAngle = 0;
int yAngle = 0;
int zAngle = 0;


bool mode = false;
float radius = 1.0f;

/*
Struct to hold data for object rendering.
*/
class Object
{
public:
  inline Object ()
    : vao(0),
      positionBuffer(0),
      colorBuffer(0),
      indexBuffer(0)
  {}

  inline ~Object () { // GL context must exist on destruction
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &positionBuffer);
  }

  GLuint vao;        // vertex-array-object ID
  
  GLuint positionBuffer; // ID of vertex-buffer: position
  GLuint colorBuffer;    // ID of vertex-buffer: color
  
  GLuint indexBuffer;    // ID of index-buffer
  
  glm::mat4x4 model; // model matrix
};

Object triangle;
Object quad;
Object sphere;

/*
 * Calc the amount of triangles of one qadrant in recursive way.
 * Example returns are 1 for n=0, 4 for n=1, 9 for n=2, 16 for n=3
 */
/*int calcAmountTriangles(int n) {
	if (n == 0) {
		return 1;
	}
	return calcAmountTriangles(n - 1) + (n * 2 + 1);
}


void renderSphere()
{
	glm::mat4x4 mvp = projection * view * sphere.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the n triangles.
	glBindVertexArray(sphere.vao);
	glDrawElements(GL_TRIANGLES, 8 * calcAmountTriangles(n) * 3, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}*/

void renderCoord()
{
  // Create mvp.
  glm::mat4x4 mvp = projection * view * quad.model;
  
  // Bind the shader program and set uniform(s).
  program.use();
  program.setUniform("mvp", mvp);
  
  // Bind vertex array object so we can render the 2 triangles.
  glBindVertexArray(quad.vao);
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(0);
}

/*
 * Init the coordination system and set its vertices to construct the axis-lines
 */
void initCoord()
{
	glm::vec3 center= glm::vec3( 0.0f, 0.0f, 0.0f );
	glm::vec3 xAxis = glm::vec3( 3.0f, 0.0f, 0.0f );
	glm::vec3 yAxis = glm::vec3( 0.0f, 3.0f, 0.0f );
	glm::vec3 zAxis = glm::vec3( 0.0f, 0.001f, 3.0f );
	std::vector<glm::vec3> vertices;
	vertices.push_back(center);
	vertices.push_back(xAxis);
	vertices.push_back(yAxis);
	vertices.push_back(zAxis);
	// set all 4 colors to green
	const std::vector<glm::vec3> colors = { { 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } };
	const std::vector<GLushort>  indices = { 0, 1, 0, 0, 2, 0, 0, 3, 0 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &quad.vao);
	glBindVertexArray(quad.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &quad.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &quad.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &quad.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
	-
	// Modify model matrix.
	quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, 0.0f, 0.0f));
}


/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
  // OpenGL: Set "background" color and enable depth testing.
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  
  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  // Construct view matrix.
  glm::vec3 eye(0.0f, 0.0f, eyeZ); // zoom closer if eyeZ is greater
  glm::vec3 center(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);
  
  view = glm::lookAt(eye, center, up);
  
  // Create a shader program and set light direction.
  if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX)) {
    std::cerr << program.log();
    return false;
  }
  
  if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT)) {
    std::cerr << program.log();
    return false;
  }
  
  if (!program.link()) {
    std::cerr << program.log();
    return false;
  }

  // Create all objects.
  sun->init();
  initCoord();
  
  return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mode) { // when c was pressed
		glDisable(GL_CULL_FACE);
		renderCoord();
	}
	glEnable(GL_CULL_FACE);
	sun->draw(projection * view * quad.model);
}

void glutDisplay ()
{
   render();
   glutSwapBuffers();
}

/*
 Resize callback.
 */
void glutResize (int width, int height)
{
  // Division by zero is bad...
  height = height < 1 ? 1 : height;
  glViewport(0, 0, width, height);
  
  // Construct projection matrix.
  //projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
  projection = glm::ortho(-5.0F * width / height, 5.0F * width / height, -5.0F, 5.0F, zNear, zFar);
}

/*
 Callback for char input.
 */
void glutKeyboard (unsigned char keycode, int x, int y)
{
  switch (keycode) {
  case 27: // ESC
    glutDestroyWindow ( glutID );
    return;
    
  case '+':
	  if (n < 4) {
	  n++;
	  init();
	  glutDisplay();
	  }
    break;
  case '-':
	  if (n > 0) {
	  n--;
	  init();
	  glutDisplay();
	  }
    break;
  case 'x':
	  sun->setAngleX(sun->getAngleX() + 3);
	  init();
	  glutDisplay();
	  break;
  case 'r':
	  if (gRadius > 10) {
		  gRadius--;
		  std::cout << n << std::endl;
		  init();
		  glutDisplay();
	  }
	  break;
  case 'R':
	  if (gRadius < 100) {
		  gRadius++;
		  init();
		  glutDisplay();
	  }
	  break;
  case 'y':
	  sun->setAngleY(sun->getAngleY() + 3);
	  init();
	  glutDisplay();
	  break;
  case 'z':
	  sun->setAngleZ(sun->getAngleZ() + 3);
	  init();
	  glutDisplay();
	  break;
  case 'c':
	  mode = !mode;
	  glutDisplay();
    break;
  case 'a':
	  if (eyeZ < 50) {
		  eyeZ+=0.5;
		  init();
		  glutDisplay();
	  }
    break;
  case 's':
	  if (eyeZ > 1) {
		  eyeZ-=0.5;
		  init();
		  glutDisplay();
	  }
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  // GLUT: Initialize freeglut library (window toolkit).
  glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(40,40);
  glutInit(&argc, argv);


  
  // GLUT: Create a window and opengl context (version 4.3 core profile).
  glutInitContextVersion(4, 3);
  glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
  glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
  
  glutCreateWindow("Aufgabenblatt 03");
  glutID = glutGetWindow();
  


  // GLEW: Load opengl extensions
  //glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    return -1;
  }
#if _DEBUG
  if (glDebugMessageCallback) {
    std::cout << "Register OpenGL debug callback " << std::endl;
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(cg::glErrorVerboseCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE,
			  GL_DONT_CARE,
			  GL_DONT_CARE,
			  0,
			  nullptr,
			  true); // get all debug messages
  } else {
    std::cout << "glDebugMessageCallback not available" << std::endl;
  }
#endif

  // GLUT: Set callbacks for events.
  glutReshapeFunc(glutResize);
  glutDisplayFunc(glutDisplay);
  //glutIdleFunc   (glutDisplay); // redisplay when idle
  
  glutKeyboardFunc(glutKeyboard);
  
  // init vertex-array-objects.
  bool result = init();
  if (!result) {
    return -2;
  }

  // GLUT: Loop until the user closes the window
  // rendering & event handling
  glutMainLoop ();
  
  // Cleanup in destructors:
  // Objects will be released in ~Object
  // Shader program will be released in ~GLSLProgram
  
  return 0;
}
