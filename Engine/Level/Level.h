#pragma once

#include "Core.h"
#include "RTTI.h"

// ���� ����(Forward Declaration).
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�.
	void AddActor(Actor* newActor);

	void DestroyActor();

	// ���� ó�� �Լ�.
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭.
	std::vector<Actor*> actors;
};