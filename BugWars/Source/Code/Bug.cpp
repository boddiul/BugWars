#include "pch.h"
#include "Bug.h"
#include "Game.h"



#include "GameBase/Log.h"


void Bug::OnUpdate(float dt)
{
}

BugBase* Bug::FindBugToEat() const
{

	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();




	for (auto bug : g_Game->nearestBugPool)
	{
		if (bug->id == id)
			continue;

		if (bug->disabled)
			continue;

		if (bug->id > id)
			continue; // Can't eat that

		{
			

			float dist = (bug->position - position).Length2();//position.Distance(bug->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = bug;
			}
		}
	}

	return target;
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	if (first.id > second.id)
	{
		second.disabled = true;
		second.visible = false;
	}
	else
	{
		first.disabled = true;
		first.visible = false;
	}
}
