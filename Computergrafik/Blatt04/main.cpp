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

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;
constexpr auto PI = 3.14159265358979323846;

cg::GLSLProgram program;

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
int calcAmountTriangles(int n) {
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
}

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

glm::vec3 rgbToCMY(glm::vec3 rgbColors)
{
	float c = 1.0f - rgbColors[0];
	float m = 1.0f - rgbColors[1];
	float y = 1.0f - rgbColors[2];
	return { c, m, y };
}

glm::vec3 rgbToHSV(glm::vec3 rgbColors)
{
	float cMax = 0.0f;
	float cMin = 1.0f;

	// Calc max and min color values
	for (size_t i = 0; i < 3; i++)
	{
		if (rgbColors[i] > cMax)
		{
			cMax = rgbColors[i];
		}
		if (rgbColors[i] < cMin)
		{
			cMin = rgbColors[i];
		}
	}

	float delta = cMax - cMin;


	// Calc hue
	float hue = 60;
	float mult = 0.0f;

	// Calc mult which is used for the hue
	if (cMax == rgbColors[0]) // red
	{
		mult = fmodf(((rgbColors[1] - rgbColors[2]) / delta), 6.0f);
	}
	else if (cMax == rgbColors[1]) // green
	{
		mult = (rgbColors[2] - rgbColors[0]) / delta + 2;
	}
	else // blue
	{
		mult = (rgbColors[0] - rgbColors[1]) / delta + 4;
	}

	hue *= mult;


	// Calc saturation
	float saturation = 0.0f;

	if (cMax != 0)
	{
		saturation = delta / cMax;
	}


	// Calc value
	float value = cMax;
	return { hue, saturation, value };
}

glm::vec3 cmyToRGB(glm::vec3 cmyColors)
{
	return{ rgbToCMY(cmyColors) };
}

glm::vec3 cmyToHSV(glm::vec3 cmyColors)
{
	return{ rgbToHSV(cmyToRGB(cmyColors)) };
}

glm::vec3 hsvToRGB(glm::vec3 hsvColors)
{
	//Formel auf: https://www.rapidtables.com/convert/color/hsv-to-rgb.html

	float h = hsvColors[0];
	float s = hsvColors[1];
	float v = hsvColors[2];

	float c = v * s;
	float x = c * (1 - abs(fmodf((h / 60), 2) - 1));
	float m = v - c;

	float r = 0.0f, g = 0.0f, b = 0.0f;
	if (h >= 0 && h < 60)
	{
		r = c;
		g = x;
		b = 0.0f;
	}
	else if (h >= 60 && h < 120)
	{
		r = x;
		g = c;
		b = 0.0f;
	}
	else if (h >= 120 && h < 180)
	{
		r = 0.0f;
		g = c;
		b = x;
	}
	else if (h >= 180 && h < 240)
	{
		r = 0.0f;
		g = x;
		b = c;
	}
	else if (h >= 240 && h < 300)
	{
		r = x;
		g = 0;
		b = c;
	}
	else if (h >= 300 && h < 360)
	{
		r = c;
		g = 0;
		b = x;
	}
	else {
		//Error!;
	}

	r = (r + m);
	g = (g + m);
	b = (b + m);

	return { r, g, b };
}

glm::vec3 hsvToCMY(glm::vec3 hsvColors)
{
	return{ rgbToCMY(hsvToRGB(hsvColors)) };
}


int sumVerticesForN(int n) {
	int sum = 0;
	for (int i = n; i > 0; i--) {
		sum += i;
	}
	return sum;
}

int sumVerticesForNUntil(int n, int limit) {
	int sum = 0;
	for (int i = n; i > limit - 1; i--) {
		sum += i;
	}
	return sum;
}


/*
 * Rotate a vertice on the X axis
 */
glm::vec3 rotateX(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {1, 0, 0}, {0, cos(rad), -sin(rad) }, {0, sin(rad), cos(rad)} };
	return rotationMatrix * vertice;
}

/*
 * Rotate a vertice on the Y axis
 */
glm::vec3 rotateY(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {cos(rad), 0, sin(rad)}, {0, 1, 0}, {-sin(rad), 0, cos(rad)} };
	return rotationMatrix * vertice;
}

/*
 * Rotate a vertice on the Z axis
 */
glm::vec3 rotateZ(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {cos(rad), -sin(rad), 0}, {sin(rad), cos(rad), 0 }, {0, 0, 1} };
	return rotationMatrix * vertice;
}

/*
 * Mirror a vertice on the XZ-pane
 */
glm::vec3 mirrorXZ(glm::vec3 vertice) {
	glm::mat3x3 mirrorMatrix = { {1, 0, 0}, {0, -1, 0}, {0, 0, 1} };
	return mirrorMatrix * vertice;
}

/*
 * Rotate the sphere on the X axis
 */
glm::vec3 rotateSphereX(glm::vec3 vertice) {
	float x = vertice[0];
	float y = vertice[1];
	float z = vertice[2];


	vertice[0] - x;
	vertice = rotateX(xAngle, vertice);
	vertice[0] + x;

	return vertice;
}

/*
 * Rotate the sphere on the Y axis
 */
glm::vec3 rotateSphereY(glm::vec3 vertice) {
	float x = vertice[0];
	float y = vertice[1];
	float z = vertice[2];

	vertice[1] - y;
	vertice = rotateY(yAngle, vertice);
	vertice[1] + y;

	return vertice;
}

/*
 * Rotate the sphere on the Z axis
 */
glm::vec3 rotateSphereZ(glm::vec3 vertice) {
	float x = vertice[0];
	float y = vertice[1];
	float z = vertice[2];

	vertice[2] - z;
	vertice = rotateZ(zAngle, vertice);
	vertice[2] + z;

	return vertice;
}

/*
 * Inits the Sphere.
 * Calcs and sets vertices and its indices for connecting them.
 */
void initSphere()
{
	std::vector<glm::vec3> vertices = {};
	std::vector<glm::vec3> colors = {};
	std::vector<GLushort>  indices = {};

	float angleStep = 90 / (n + 1);
	float angleEighth = 90; // degrees

	int indicesEighth = sumVerticesForN(n + 2);
	int indicesOffset = 0;

	int verticesCounter = n + 2;


	for (int sphereEighth = 0; sphereEighth < 8; sphereEighth++) {
		for (int i = 0; i < verticesCounter; i++) {

			float angleRight = 90 / (float)(verticesCounter - i - 1);

			for (int j = 0; j < verticesCounter - i; j++) {

				glm::vec3 point = { 0.0f, 0.0f, 1.0f * ((float)gRadius / 100) };
				glm::vec3 rotatedAngle = rotateX(-angleStep * i, point);

				if (verticesCounter - i != 1) {
					rotatedAngle = rotateY(angleRight * j, rotatedAngle);
				}

				float angle = angleEighth * (float)(sphereEighth % 4);
				rotatedAngle = rotateY(angle, rotatedAngle);

				if (sphereEighth >= 4) {
					rotatedAngle = mirrorXZ(rotatedAngle);
				}

				vertices.push_back(rotatedAngle);
				colors.push_back({ 0.0f, 1.0f, 1.0f }); // yellow

				if (i != verticesCounter - 1 && j != verticesCounter - i - 1) {
					int left = indicesOffset + sumVerticesForNUntil(verticesCounter, verticesCounter - i + 1) + j;
					int top = left + (verticesCounter - i);
					int right = left + 1;

					if (sphereEighth >= 4) {
						indices.push_back(top);
						indices.push_back(right);
						indices.push_back(left);
					}
					else {
						indices.push_back(top);
						indices.push_back(left);
						indices.push_back(right);
					}

					if (sphereEighth >= 4) {
						if (i > 0) {
							int bottom = right - (verticesCounter - i + 1);
							indices.push_back(bottom);
							indices.push_back(left);
							indices.push_back(right);
						}
					}
					else {
						if (i > 0) {
							int bottom = right - (verticesCounter - i + 1);
							indices.push_back(right);
							indices.push_back(left);
							indices.push_back(bottom);
						}
					}

					
				}
			}
		}
		indicesOffset += indicesEighth;
	}

	// if Sphere has a rotation (default all 0.0), rotate it
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] = rotateSphereX(vertices[i]);
		vertices[i] = rotateSphereY(vertices[i]);
		vertices[i] = rotateSphereZ(vertices[i]);
	}





	GLuint programId = program.getHandle();
	GLuint pos;


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &sphere.vao);
	glBindVertexArray(sphere.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &sphere.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sphere.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &sphere.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sphere.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &sphere.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	//quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, 0.0f, 0.0f));
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
  initSphere();
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
	renderSphere();
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
	  std::cout << n << std::endl;
	  init();
	  glutDisplay();
	  }
    break;
  case '-':
	  if (n > 0) {
	  n--;
	  std::cout << n << std::endl;
	  init();
	  glutDisplay();
	  }
    break;
  case 'x':
	  xAngle += 3;
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
		  std::cout << gRadius << "y\n" << yAngle << "x\n" << xAngle << "z\n" << zAngle << std::endl;
		  init();
		  glutDisplay();
	  }
	  break;
  case 'y':
	  printf("rotay \n \n \n \n \n rota y");
	  yAngle += 3;
	  init();
	  glutDisplay();
	  break;
  case 'z':
	  zAngle+=3;
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
