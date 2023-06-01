#pragma once
#include "Body.h"

namespace Integrator
{
	void ExplicitEuler(Body& body, float dt)
	{
		body.position += body.velocity * dt;
		body.velocity *= (1.0f / (1.0f + (2.0f * dt)));
	}

	void SemiImplicitEuler(Body& body, float dt)
	{
		glm::vec2 acceleration = (body.force * body.invMass);

		body.velocity += acceleration * dt;
		body.position += body.velocity * dt;
	}
}