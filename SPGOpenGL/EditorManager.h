#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <vector>
#include <string>
#include "model.h"
#include "light.h"
#define PI glm::pi<float>()

using namespace glm;

// posibile miscari 
enum MOVE {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RotateLX,
	RotateRX,
	RotateLY,
	RotateRY,
	RotateLZ,
	RotateRZ
};

enum typeInstance {
	light, object
};

struct instance {
	typeInstance type;

	mat4 move;
	mat4 rotate;
	int index;

	Light light;
	int nrlight;

	instance(typeInstance t) {
		type = t;
	}

	void initObject(int i, mat4 m = mat4(1.0f), mat4 r = mat4(1.0f)) {
		index = i;
	}
	void initLight(int nr) {
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		light.Init(glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(x, y, z),
			glm::vec3(x, y, z),
			glm::vec3(x, y, z),200);
		nrlight = nr;
	}

};


class EditorManager {
public:

	// vectorul cu modele folosit pt desena un tip de obiect incarcat 
	vector<Model> models;
	// vector cu struct care retine ce model a fost pus ,si matricile de transformare
	vector<instance> displayObjs;

	float speed = 0.5f;
	int selected;

	EditorManager() {
	}

	// folosit pt a adauga  modele (clasa care se ocupa de citirea .obj) in vector
	void initModel(string path){
		Model model;
		model.init(path);
		models.push_back(model);
	}

	int nrlight = 0;
	// cand se apasa 1 ,2,3 ... se adauga in vector structul de instanta 
	void addObject(typeInstance type,int index) {
		instance in(type);
		if (type== object && models.size() > index-1) {
			in.initObject(index - 1);
			displayObjs.push_back(in);
			selected = displayObjs.size()-1;
		}
		else if (type == light) {
			in.initLight(nrlight++);
			displayObjs.push_back(in);
			selected = displayObjs.size() - 1;
		}
	}

	
	// se seteaza matricea de rasformare din vertex numita "mvp", si se deseneaza modelele
	void Draw(Shader& shader) {
		for (int i = 0; i < displayObjs.size(); i++) {
			
			if (displayObjs[i].type == object) {
				shader.setMat4("mvp", displayObjs[i].move * displayObjs[i].rotate);
				models[displayObjs[i].index].Draw(shader);
			}
			else if (displayObjs[i].type == light)
			{
				displayObjs[i].light.Draw(shader, displayObjs[i].nrlight);
			}
		}
	}


	// schimbare selected pt a muta obiectele 
	void ChangeSelected(MOVE dir) {
		if (dir == LEFT && selected > 0) {
			selected--;
		}
		else if (dir == RIGHT && selected < (displayObjs.size() - 1)) {
			selected++;
		}

	}

	void DeleteInstance() {
		if (selected >=0 )
			displayObjs.erase(displayObjs.begin()+selected);
			selected--;
		
	}
		

	// primeste o directie si seteaza matricea de trasnformare a obiectului selectat
	void Moveobject(MOVE direction) {
		if (displayObjs[selected].type == object) {

			if (direction == FORWARD) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(0.0f, 0.0f, -speed));
			}
			else if (direction == BACKWARD) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(0.0f, 0.0f, speed));
			}
			else if (direction == LEFT) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(-speed, 0.0f, 0.0f));
			}
			else if (direction == RIGHT) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(speed, 0.0f, 0.0f));
			}
			else if (direction == UP) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(0.0f, speed, 0.0f));
			}
			else if (direction == DOWN) {
				displayObjs[selected].move = translate(displayObjs[selected].move, vec3(0.0f, -speed, 0.0f));
			}
			else if (direction == RotateLY) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(-5.0f), vec3(0.0f, 1.0f, 0.0f));
			}
			else if (direction == RotateRY) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(5.0f), vec3(0.0f, 1.0f, 0.0f));
			}
			else if (direction == RotateLX) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(-5.0f), vec3(1.0f, 0.0f, 0.0f));
			}
			else if (direction == RotateRX) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(5.0f), vec3(1.0f, 0.0f, 0.0f));
			}
			else if (direction == RotateLZ) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(-5.0f), vec3(0.0f, 0.0f, 1.0f));
			}
			else if (direction == RotateRZ) {
				displayObjs[selected].rotate = rotate(displayObjs[selected].rotate, radians(5.0f), vec3(0.0f, 0.0f, 1.0f));
			}
		}
		else{
			if (direction == FORWARD) {
				displayObjs[selected].light.position +=  vec3(0.0f, 0.0f, -speed);
			}
			else if (direction == BACKWARD) {
				displayObjs[selected].light.position += vec3(0.0f, 0.0f, speed);
			}
			else if (direction == LEFT) {
				displayObjs[selected].light.position += vec3(-speed, 0.0f, 0.0f);
			}
			else if (direction == RIGHT) {
				displayObjs[selected].light.position += vec3(speed, 0.0f, 0.0f);
			}
			else if (direction == UP) {
				displayObjs[selected].light.position += vec3(0.0f, speed, 0.0f);
			}
			else if (direction == DOWN) {
				displayObjs[selected].light.position += vec3(0.0f, -speed, 0.0f);
			}
		}
	}

};



#endif