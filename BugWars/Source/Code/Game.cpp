#include "pch.h"
#include "Game.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"


#include "GameBase/Log.h"


Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;



}

// Make it work (Утечки памяти)
Game::~Game()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();


	nearestBugPool.clear();
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);



	//LogZA("Arr Size: %zu", objects.size());
	//LogZA("Pool Size: %zu", nearestBugPool.size());



	float uds = updateDistance * updateDistance;

	int sz = objects.size();

	// Make it work (Краш в auto loop в дебаг)
	for (int i = 0; i < sz; i++)
	{

		// Make it fast (Оптимизация для поиска ближайших жуков)

		Bug* bug;
		bool isBug = (bug = dynamic_cast<Bug*>(objects[i]));
		bool inUpdateZone = (objects[i]->position - player->position).Length2() < uds;


		if (isBug)
		{
			if ((bug->disabled && bug->inUpdatePool) || (!bug->disabled && !inUpdateZone && bug->inUpdatePool))
			{
				nearestBugPool.erase(remove(nearestBugPool.begin(), nearestBugPool.end(), bug), nearestBugPool.end());
				bug->inUpdatePool = false;
			}
		}

		if (!objects[i]->disabled)
		{

			if (isBug && inUpdateZone && !bug->inUpdatePool)
				{
					nearestBugPool.push_back(bug);
					bug->inUpdatePool = true;
				}
			
			
			if (!isBug || inUpdateZone)
				objects[i]->Update(dt);

		}
			
	}
		
}

void Game::OnRender() const
{
	float rds = renderDistance * renderDistance;

	for (auto obj : objects)
		if (obj->visible)
			if ((obj->position-player->position).Length2()< rds)
				DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	if (auto tank = dynamic_cast<Tank*>(object))
		player = tank;



	// Make it right (Поведение жуков и танков)
	object->disabled = false;


	/*int sz = objects.size();
	for (int i = 0; i < sz; i++)
	{
		if (objects[i]->disabled)
		{
			delete objects[i];

			objects[i] = object;
			return;
		}
	}*/
	objects.push_back(object);
}

void Game::OnBugsSpawned()
{
}
