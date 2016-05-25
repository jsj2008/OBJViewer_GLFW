/*
 * Luz.cpp
 *
 *  Created on: 20/7/2015
 *      Author: Javier
 */

#include "LuzPuntual.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <stdio.h>

LuzPuntual::Attenuation::Attenuation() :
		constant(0), linear(0.01f), exponential(0) {
}

LuzPuntual::LuzPuntual() :
		position(0, 0, 100), color(1, 1, 1), ambientIntensity(0), diffuseIntensity(
				1), attenuation(), positionAttrib(0), colorAttrib(0), ambientIntensityAttrib(
				0), diffuseIntensityAttrib(0), attenuationConstantAttrib(0), attenuationLinearAttrib(
				0), attenuationExponentialAttrib(0) {
}

void LuzPuntual::linkLuzAttrib(GLuint shader) {
	positionAttrib = glGetUniformLocation(shader, "pointLight.position");
	if (positionAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	colorAttrib = glGetUniformLocation(shader, "pointLight.color");
	if (colorAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	ambientIntensityAttrib = glGetUniformLocation(shader,
			"pointLight.ambientIntensity");
	if (ambientIntensityAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	diffuseIntensityAttrib = glGetUniformLocation(shader,
			"pointLight.diffuseIntensity");
	if (diffuseIntensityAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	attenuationConstantAttrib = glGetUniformLocation(shader,
			"pointLight.attenuation.constant");
	if (attenuationConstantAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	attenuationLinearAttrib = glGetUniformLocation(shader,
			"pointLight.attenuation.linear");
	if (attenuationLinearAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
	attenuationExponentialAttrib = glGetUniformLocation(shader,
			"pointLight.attenuation.exponential");
	if (attenuationExponentialAttrib < 0) {
		printf("Shader did not contain the 'pointLight.position' uniform.");
	}
}

void LuzPuntual::loadLuzAttrib() {
	glUniform3fv(positionAttrib, 1, value_ptr(position));
	glUniform3fv(colorAttrib, 1, value_ptr(color));
	glUniform1f(ambientIntensityAttrib, ambientIntensity);
	glUniform1f(diffuseIntensityAttrib, diffuseIntensity);
	glUniform1f(attenuationConstantAttrib, attenuation.constant);
	glUniform1f(attenuationLinearAttrib, attenuation.linear);
	glUniform1f(attenuationExponentialAttrib, attenuation.exponential);

}

