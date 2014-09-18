/*
 * Material.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Iury Roger Painelli
 */

#include "Material.h"

Material::Material() {
	emission = glm::vec4();
	ambient = glm::vec4();
	diffuse = glm::vec4();
	specular = glm::vec4();
	shininess = 0.0;

}

Material::~Material() {
	// TODO Auto-generated destructor stub
}

