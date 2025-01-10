#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(Vector2 position, Vector2 direction);
	~Player() {};

	virtual void Update(float deltaTime) override;
};
