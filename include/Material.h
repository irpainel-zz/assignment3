/*
 * Material.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "glm/vec4.hpp"
class Material {
public:
	Material();
	virtual ~Material();

	glm::vec4 emission;    // Ecm
	glm::vec4 ambient;     // Acm
	glm::vec4 diffuse;     // Dcm
	glm::vec4 specular;    // Scm
	float shininess;  // Srm
};

#endif /* MATERIAL_H_ */
