#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "shader.h"
using namespace glm;


class Light
{
public:
	glm::vec3 position;


	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	Light(){}
	void Init(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int distance = 100) {
		this->position = position;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;

		switch (distance)
		{
		case 3250:
			linear = 0.0014f;
			quadratic = 0.000007f;
			break;
		case 600:
			linear = 0.007f;
			quadratic = 0.0002f;
			break;
		case 325:
			linear = 0.014f;
			quadratic = 0.0007f;
			break;
		case 200:
			linear = 0.022f;
			quadratic = 0.0019f;
			break;
		case 160:
			linear = 0.027f;
			quadratic = 0.0028f;
			break;
		case 100:
			linear = 0.045f;
			quadratic = 0.0075f;
			break;
		case 65:
			linear = 0.07f;
			quadratic = 0.017f;
			break;
		case 50:
			linear = 0.09f;
			quadratic = 0.032f;
			break;
		case 32:
			linear = 0.14f;
			quadratic = 0.07f;
			break;
		case 20:
			linear = 0.22f;
			quadratic = 0.20f;
			break;
		case 13:
			linear = 0.35f;
			quadratic = 0.44f;
			break;
		case 7:
			linear = 0.7f;
			quadratic = 1.8f;
			break;
		default:
			linear = 0.7f;
			quadratic = 1.8f;
		}
	}


	void Draw(Shader shader,int index) {
		
		shader.setVec3("Lights[" + std::to_string(index) + "].position", position);
		shader.setVec3("Lights[" + std::to_string(index) + "].ambient", ambient);
		shader.setVec3("Lights[" + std::to_string(index) + "].diffuse", diffuse);
		shader.setVec3("Lights[" + std::to_string(index) + "].specular", specular);
		shader.setFloat("Lights[" + std::to_string(index) + "].linear", linear);
		shader.setFloat("Lights[" + std::to_string(index) + "].quadratic", quadratic);
	}

};

#endif 

