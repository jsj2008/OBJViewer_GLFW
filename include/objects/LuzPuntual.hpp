/*
 * LuzPuntual.hpp
 *
 *  Created on: 19/7/2015
 *      Author: Javier
 */

#pragma once

#include <glm/glm/vec3.hpp>
#include <libs/lib/glew.h>
//#include "glew.h"

struct LuzPuntual {
	glm::vec3 position;
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	struct Attenuation {
		GLfloat constant;
		GLfloat linear;
		GLfloat exponential;
		Attenuation();
	} attenuation;
	GLuint positionAttrib, colorAttrib, ambientIntensityAttrib,
			diffuseIntensityAttrib, attenuationConstantAttrib,
			attenuationLinearAttrib, attenuationExponentialAttrib;
	LuzPuntual();
	void linkLuzAttrib(GLuint shader);
	void loadLuzAttrib();
};
