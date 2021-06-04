#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <stack>
#include <cmath>
#include <assimp/texture.h>
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "EditorManager.h"


int width = 700;
int height = 700;
int rows = 50;
int columns = 50;


// ------------ camera and shader -------------------
Shader shader;
Camera camera(glm::vec3(0, 3, 30));
EditorManager editor;


void init()
{
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4, 0.0f, 1.0f, 0.4f);

	glewInit();

	shader.init("vertex.vert", "fragment.frag");
	
	editor.initModel("C:/Users/Andreea/Desktop/SPG_Proiect/ProiectPrincipal/SPGOpenGL/obj/grass_field/grass_field.obj");
	editor.initModel("C:/Users/Andreea/Desktop/SPG_Proiect/ProiectPrincipal/SPGOpenGL/obj/house/house/house.obj");
	editor.initModel("C:/Users/Andreea/Desktop/SPG_Proiect/ProiectPrincipal/SPGOpenGL/obj/tree/tree.obj");
	editor.initModel("C:/Users/Andreea/Desktop/SPG_Proiect/ProiectPrincipal/SPGOpenGL/obj/field/field.obj");
}


void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.use();
	shader.setVec3("viewPos", camera.Position);
	shader.setFloat("shininess", 60.0f);

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);


	editor.Draw(shader);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	camera.SetWandH(w, h);
}


bool edit_on = true;
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'c') edit_on = !edit_on;

	if (edit_on) {
		switch (key)
		{
			// =================== add objects in scenes to be render ======================
		case '1':
			editor.addObject(object,1);
			break;
		case '2':
			editor.addObject(object,2);
			break;
		case '3':
			editor.addObject(object,3);
			break;

		case '4':
			editor.addObject(object, 4);
			break;

		case '0':
			editor.addObject(light, 0);
			break;

			// =================== move selected object added ==============================

		case 'z':
			editor.Moveobject(DOWN);
			break;
		case 'x':
			editor.Moveobject(UP);
			break;

		case 'w':
			editor.Moveobject(FORWARD);
			break;
		case 's':
			editor.Moveobject(BACKWARD);
			break;
		case 'a':
			editor.Moveobject(LEFT);
			break;
		case 'd':
			editor.Moveobject(RIGHT);
			break;

			// ===================== rotate selected object ===============================

		case 'i':
			editor.Moveobject(RotateLY);
			break;
		case 'o':
			editor.Moveobject(RotateRY);
			break;
		case 'j':
			editor.Moveobject(RotateLX);
			break;
		case 'k':
			editor.Moveobject(RotateRX);
			break;
		case 'n':
			editor.Moveobject(RotateLZ);
			break;
		case 'm':
			editor.Moveobject(RotateRZ);
			break;


			// ============================ change the selection =============================
		case ',':
			editor.ChangeSelected(LEFT);
			break;
		case '.':
			editor.ChangeSelected(RIGHT);
			break;

		case '/':
			editor.DeleteInstance();
			break;
		}
	}
	else {
		switch (key) {
			// ========================= moving the camera =================================
		case 'w':
			camera.ProcessMove(FORWARD);
			break;
		case 's':
			camera.ProcessMove(BACKWARD);
			break;
		case 'a':
			camera.ProcessMove(LEFT);
			break;
		case 'd':
			camera.ProcessMove(RIGHT);
			break;
		case 'q':
			camera.ProcessRotate(RotateLY);
			break;
		case 'e':
			camera.ProcessRotate(RotateRY);
			break;

		};
	}

	glutPostRedisplay(); // cauzeaza redesenarea ferestrei
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(width, height);
	camera.SetWandH(width, height);
	glutCreateWindow("SPG");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	

	glutMainLoop();

	return 0;
}
