#pragma once
#include <vector>
#include <list>

class ForceGenerator
{
public:
	ForceGenerator(struct Body* body = nullptr) : m_body{ body } {}

	virtual void Apply(std::vector<struct Body*> bodies) = 0;
	virtual void Draw(class Graphics* graphics);

protected:
	struct Body* m_body{ nullptr };
};