#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(Vector2 position, Vector2 direction, std::vector<std::vector<int>> grid);
	~Player() {};

	virtual void Update(float deltaTime) override;

private:
	std::vector<std::vector<int>> grid;
};
