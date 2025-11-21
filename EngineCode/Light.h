#pragma once
#include "Mesh.h"



class Light: public Mesh{
protected:
	glm::vec3 mcolor = glm::vec3(1.0f);
	glm::vec3 mdirection = glm::vec3(0.01, 0.01f, 0.01f);
	glm::vec3 mdiffuse = mcolor * glm::vec3(0.5f);
	glm::vec3 mambient = mdiffuse * glm::vec3(0.2f); 
	glm::vec3 mspecular = glm::vec3(1.0f); 

public:
	Light() = default;
	Light(glm::vec3 col,glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);
	
	glm::vec3 GetDirection() { return mdirection; };
	glm::vec3 GetAmbient() { return mambient; };
	glm::vec3 GetDiffuse() { return mdiffuse; };
	glm::vec3 GetSpecular() { return mspecular; };

	void SetDirection(glm::vec3 dir) { mdirection = dir; };
	void SetAmbient(glm::vec3 ambient) { mambient = ambient; };
	void SetDiffuse(glm::vec3 diffuse) { mdiffuse = diffuse; };
	void SetSpecular(glm::vec3 specular) { mspecular = specular; };
};




class PointLight : public Light {
protected:

	float mconstant;
	float mlinear;
	float mquadratic;

	glm::vec3 color = glm::vec3(1.0f, 1.0f,1.0f);

public:
	PointLight() = default;
	PointLight(float constant, float linear, float quadratic);

	float GetConstant() { return mconstant; };
	float GetLinear() { return mlinear; };
	float GetQuadratic() { return mquadratic; };

	void SetConstant(float constant) { mconstant = constant; };
	void SetLinear(float linear) { mlinear = linear; };
	void SetQuadratic(float quad) { mquadratic = quad; };
};


class SpotLight : public PointLight {
private:
	float mInnercutOff;
	float mOuterCutOff;

public:
	SpotLight(float inner, float outer);

	float GetInnerCutOff() { return mInnercutOff; };
	float GetOuterCutOff() { return mOuterCutOff; };

	void SetInnerCutOffonstant(float inner) { mInnercutOff = inner; };
	void SetOuterCutOff(float outer) { mOuterCutOff= outer; };
};