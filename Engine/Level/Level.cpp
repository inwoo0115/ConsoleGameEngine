#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	//actors.push_back(newActor);
	addRequestedActor = newActor;
}

void Level::ProcessAddedAndDestroyedActor()
{
	//Actor ���� ó��
	for (int ix = 0;ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			actors.erase(actors.begin() + ix); 
			continue;
		}
		++ix;
	}
	// �߰� ��û�� ���� ó��
	if (addRequestedActor)
	{
		actors.push_back(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		actor->Draw();
	}
}