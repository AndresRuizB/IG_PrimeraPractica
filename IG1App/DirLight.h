#pragma once
#include "Light.h"

class DirLight : public Light {
public:
	DirLight():Light() {};
	~DirLight() {};

	virtual void upload(glm::dmat4 const& modelViewMat) const;

	void setPosDir(glm::fvec3 dir);

};