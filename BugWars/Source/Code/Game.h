#pragma once
#include "GameBase/GameBase.h"
#include "Globals.h"
#include "Bug.h"

struct Tank;

struct Game : public GameBase
{
	Game();
	~Game();

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() const override;
	virtual void AddObject(GameObject* object) override;

	virtual void OnBugsSpawned() override;

	

	std::vector<GameObject*> objects;

	std::vector<Bug*> nearestBugPool;

	Tank* player;
	const float renderDistance = 900;
	const float updateDistance = 1400;
};