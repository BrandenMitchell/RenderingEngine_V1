#include "Light.h"


Light::Light(glm::vec3 col, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {
	mcolor = col;
	mdirection = dir;
	mdiffuse = diff;
	mambient = amb;
	mspecular = spec;
}


PointLight::PointLight(float constant, float linear, float quadratic) {
	mconstant = constant;
	mlinear = linear;
	mquadratic = quadratic;
	isLight = true;
}


SpotLight::SpotLight(float inner, float outer) {
	mInnercutOff = inner;
	mOuterCutOff = outer;
}



