#include "World.h"
#include "Body.h"
#include "Forces/ForceGenerator.h"
#include "Constraints/Joint.h"
#include "Collision/Collision.h"

glm::vec2 World::gravity{ 0, -9.8f };

World::~World()
{
	for (auto& body : m_bodies)
	{
		delete body;
	}

	m_bodies.clear();
}

void World::Step(float dt)
{
	//apply joint force
	for (auto joint : m_joints) joint->Step(dt);

	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
	if (!m_bodies.empty() && !m_forceGenerators.empty())
	{
		for (auto forceGenerator : m_forceGenerators)
		{
			forceGenerator->Apply(bodies);
		}
	}
	
	//integrate
	for (auto& body : bodies) body->Step(dt);

	// collision
	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);
}

void World::Draw(Graphics* graphics)
{
	for (auto joint : m_joints) joint->Draw(graphics);
	for (auto forceGenerator : m_forceGenerators) forceGenerator->Draw(graphics);
	for (auto body : m_bodies)	body->Draw(graphics);
}

void World::AddBody(Body* po)
{
	m_bodies.push_back(po);
}

void World::RemoveBody(Body* po)
{
	m_bodies.remove(po);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}

void World::AddForceGenerator(ForceGenerator* forceGenerator)
{
	m_forceGenerators.push_back(forceGenerator);
}
