#pragma once
#include "Test.h"

#define SPRING_STIFFNESS	100
#define SPRING_LENGTH		2
#define BODY_DAMPING		10
#define CHAIN_SIZE			3

class JointTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

private:
	struct Body* m_anchor{ nullptr };
};