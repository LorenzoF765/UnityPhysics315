//#define POINT_FORCE
//#define AREA_FORCE
#define DRAG_FORCE

#include "ForceTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shapes/CircleShape.h"
#include "../Physics/Forces/GravitationalGenerator.h"
#include "../Physics/Forces/PointForce.h"
#include "../Physics/Forces/AreaForce.h"
#include "../Physics/Forces/DragForce.h"

void ForceTest::Initialize()
{
	Test::Initialize();

#if defined(POINT_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new PointForce(body, 2000);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
	m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
	auto body = new Body(new CircleShape(200, { 1, 1, 1, 0.2f }), { 400, 300 }, { 0, 0 }, 0, Body::STATIC)
		;
	ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
	m_world->AddForceGenerator(forceGenerator);
#endif

	m_user = new Body(new CircleShape(1, { 0, 0, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::KINEMATIC);
	m_world->AddBody(m_user);

	/*auto forceGenerator = new GravitationalGenerator(400);
	m_world->AddForceGenerator(forceGenerator);*/
}

void ForceTest::Update()
{
	Test::Update();

	glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	m_user->velocity = position - m_user->position;
	m_user->position = position;

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

		float size = randomf(1, 8);
		auto body = new Body(new CircleShape(randomf(0.1f, 1.0f), { randomf(), randomf(), randomf(), 1 }), position, velocity);
		body->damping = 1;
		body->gravityScale = 30;

		m_world->AddBody(body);
	}
}

void ForceTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
	m_world->Draw(m_graphics);
	//m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
}
