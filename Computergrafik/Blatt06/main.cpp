#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "header/GLSLProgram.h"
#include "header/GLTools.h"
#include "header/SunSystem.h"

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;
cg::GLSLProgram programShaded;

glm::mat4x4 view;
glm::mat4x4 projection;

SunSystem *sunSystem = new SunSystem(&program, &programShaded);

float zNear = 0.1f;
float zFar  = 100.0f;
float eyeX = 0.0f;
float eyeY = 20.0f;
float eyeZ = 12.0f; // for view matrix (zoom)

glm::vec3 eye(eyeX, eyeY, eyeZ);
glm::vec3 center(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);


/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
  // OpenGL: Set "background" color and enable depth testing.
  glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  //glEnable(GL_CULL_FACE);
  
  // Construct view matrix.
  
  view = glm::lookAt(eye, center, up);
  
  // Create all objects.
  sunSystem->init(eye);
  sunSystem->setView(view);
  
  return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sunSystem->draw();
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
  projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
  //projection = glm::ortho(-5.0F * width / height, 5.0F * width / height, -5.0F, 5.0F, zNear, zFar);

  sunSystem->setProjection(projection);
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
  case 'q':
	  sunSystem->increaseAlpha();
	  break;
  case 'w':
	  sunSystem->decreaseAlpha();
	  break;
  case 'o':
	  sunSystem->increaseBeta();
	  break;
  case 'p':
	  sunSystem->decreaseBeta();
	  break;
  case 'u':
	  sunSystem->liftUpPlanetOne();
    break;
  case 'i':
	  sunSystem->liftDownPlanetOne();
    break;
  case 'd':
	  sunSystem->increaseSpeed();
	  break;
  case 'f':
	  sunSystem->decreaseSpeed();
	  break;
  case 'n':
	  sunSystem->toggleNormals();
	  break;
  case 'm':
	  sunSystem->toggleWireframe();	  
	  break;
  case 'l':
	  sunSystem->toggleLightsource();
	  break;
  case 'k':
	  sunSystem->toggleShading();
	  break;
  case 'j':
	  sunSystem->toggleNormalMode();
	  break;
  case '+':
	  sunSystem->scaleUp();
	  break;
  case '-':
	  sunSystem->scaleDown();
	  break;
  case 'b':
	  sunSystem->toggleBoundingBox();
	  break;
  case ',':
		sunSystem->toggleMeshNormals();
	  break;
  case '.':
	  sunSystem->toggleMeshFaceNormals();
	  break;
  case 'x':
	  sunSystem->rotateExSunX();
	  break;
  case 'y':
	  sunSystem->rotateExSunY();
	  break;
  case 'z':
	  sunSystem->rotateExSunZ();
	  break;
  }

  init();
  glutDisplay();
  glutPostRedisplay();
}

void endProgram() {
	delete sunSystem;
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
  
  glutCreateWindow("Aufgabenblatt 06");
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
  glutIdleFunc   (glutDisplay); // redisplay when idle
  
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
  
  endProgram();

  return 0;
}
