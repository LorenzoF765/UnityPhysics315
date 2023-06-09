#pragma once
#include "Test.h"

class ParticleTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

protected:
	struct Body* m_user{ nullptr };
};