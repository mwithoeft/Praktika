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

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;
float eyeZ = 4;
int nigger = 1;
int s = 100;
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

void renderSphere()
{
  // Create mvp.
  glm::mat4x4 mvp = projection * view * quad.model;
  
  // Bind the shader program and set uniform(s).
  program.use();
  program.setUniform("mvp", mvp);
  
  // Bind vertex array object so we can render the 1 triangle.
  glBindVertexArray(triangle.vao);
  glDrawElements(GL_TRIANGLES, 8 * ((nigger + 1) ^ 2), GL_UNSIGNED_SHORT, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

void initCoord()
{
	glm::vec3 center= glm::vec3( 0.0f, 0.0f, 0.0f );
	glm::vec3 xAxis = glm::vec3( 1.0f, 0.0f, 0.0f );
	glm::vec3 yAxis = glm::vec3( 0.0f, 1.0f, 0.0f );
	glm::vec3 zAxis = glm::vec3( 0.0f, 0.0f, 1.0f );
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

std::vector<GLushort> setIndices() {
	/*
	n=1:
	6 Eckpunkte
	4up 4*n
	4mid
	4down

	1. p1=0 p2= p1[]+Eckpunkte p3= p2[]+up | p1=0 p2=6 p3=10
	2. p1=1 p2= p1[]+Eckpunkte p3= p2[]+up | p1=1 p2=7 p3=11
	n=2:
	6 Eckpunkte
	8 up 4*n
	8 mid
	8 down

	1. p1=0 p2= p1+Eckpunkte p3= p2[]+up | p1=0 p2=6 p3=14
	
	*/
	int layer = 4 * nigger;
	const int points = 6;
	std::vector<GLushort> indices;
	for (int i = 0; i < points;i++){
		int p1 = i;
		indices.push_back(p1);
		indices.push_back(p1 + points);
		indices.push_back(p1 + points + layer);
	}
	

	for (int k = 0; k <= nigger; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8 * ((nigger + 1) ^ 2); j++) {
				
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < (nigger + 1); j++) {
			for (int k = 0; k < (nigger + 1); k++) {
				

			}
		}
	}
	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);
	
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(0);
	indices.push_back(4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(5);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(5);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(3);
	indices.push_back(0);
	indices.push_back(5);
	indices.;

	return indices;
}

std::vector<glm::vec3> setColors() {
	std::vector<glm::vec3> colors;
	for (int i = 0; i < 8 * ((nigger + 1) ^ 2); i++) {
		colors.push_back({ 1.0f, 1.0f, 0.0f });//Gelb
	}
	return colors;
}

std::vector<glm::vec3> tessellate(glm::vec3 p0, glm::vec3 p1) {

	std::vector<glm::vec3> points;
	for (float i = 0; i < nigger; i++) {
		glm::vec3 vecp0p1 = p1 - p0;
		glm::vec3 pn = glm::vec3((i+1 / ((float)nigger + 1.0f)) * vecp0p1[0] + p0[0],
			(i+1 / ((float)nigger + 1.0f)) * vecp0p1[1] + p0[1],
			(i+1 / ((float)nigger + 1.0f)) * vecp0p1[2] + p0[2]);
		points.push_back(pn);

		

	}
	return points;
}

std::vector<glm::vec3> setVertices()
{
	std::vector<glm::vec3> vertices;

	glm::vec3 p0 = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 p1 = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 p2 = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 p3 = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 p4 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 p5 = glm::vec3(0.0f, -1.0f, 0.0f);
	vertices.push_back(p0);
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);
	vertices.push_back(p4);
	vertices.push_back(p5);

	//up
	for (int i = 0; i < 4; i++) {
		std::vector<glm::vec3> tmp(tessellate(vertices[i], vertices[4]));
		for (int j = 0; j < nigger; j++) {
			vertices.push_back(tmp[j]);
		}
	}
	//solo mid 5k easy
	for (int i = 0; i < 4; i++) {
		std::vector<glm::vec3> tmp(tessellate(vertices[i], vertices[i+1]));
		for (int j = 0; j < nigger; j++) {
			vertices.push_back(tmp[j]);
		}
	}
	//down
	for (int i = 0; i < 4; i++) {
		std::vector<glm::vec3> tmp(tessellate(vertices[i], vertices[5]));
		for (int j = 0; j < nigger; j++) {
			vertices.push_back(tmp[j]);	
		}
	}
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << i << "(" << vertices[i][0] << "|" << vertices[i][1] << "|" << vertices[i][2] << ")" << std::endl;
	}
	return vertices;
}

void initSphere()
{
  // Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
  //const std::vector<glm::vec3> vertices = { glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) };
  //const std::vector<glm::vec3> vertices = { p0, p1, p2, p3, p3, p4, p5};
  // set colors to yellow
  const std::vector<glm::vec3> vertices = setVertices();
  const std::vector<glm::vec3> colors = setColors();
  const std::vector<GLushort>  indices  = setIndices();

  GLuint programId = program.getHandle();
  GLuint pos;

  // Step 0: Create vertex array object.
  glGenVertexArrays(1, &triangle.vao);
  glBindVertexArray(triangle.vao);
  
  // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
  glGenBuffers(1, &triangle.positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
  
  // Bind it to position.
  pos = glGetAttribLocation(programId, "position");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  // Step 2: Create vertex buffer object for color attribute and bind it to...
  glGenBuffers(1, &triangle.colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
  
  // Bind it to color.
  pos = glGetAttribLocation(programId, "color");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  // Step 3: Create vertex buffer object for indices. No binding needed here.
  glGenBuffers(1, &triangle.indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle.indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
  
  // Unbind vertex array object (back to default).
  glBindVertexArray(0);
  
  // Modify model matrix.
  triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.0f, 0.0f));
}

glm::vec3 rota(glm::vec3 p, float angle)
{
	float p1 = p[0];
	float p2 = p[1];
	glm::vec3 rp = glm::vec3(p1*cos(angle) - p2 * sin(angle), p2 * cos(angle) + p1 * sin(angle), 0.0f);
	return rp;
}


/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
  // OpenGL: Set "background" color and enable depth testing.
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  
  // Construct view matrix.
  glm::vec3 eye(eyeZ / 2, eyeZ/2, eyeZ);
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
	if (mode) {
		renderCoord();
	}
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
  projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
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
	  if (nigger < 30) {
	  nigger++;
	  std::cout << nigger << std::endl;
	  //initCircle();
	  glutDisplay();
	  }
    break;
  case '-':
	  if (nigger > 3) {
	  nigger--;
	  std::cout << nigger << std::endl;
	  //initCircle();
	  glutDisplay();
	  }
    break;
  case 'q':
	  break;
  case 'w':
	  break;
  case 'c':
	  mode = !mode;
	  glutDisplay();
    break;
  case 'a':
	  if (eyeZ < 20) {
		  eyeZ+=0.5;
		  init();
		  glutDisplay();
	  }
    break;
  case 's':
	  if (eyeZ > 2) {
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
  
  glutCreateWindow("Aufgabenblatt 02");
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
