#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"

#include <cmath>



#include "GameBase/Log.h"

void Tank::OnUpdate(float dt)
{
}

// Make it right (Стрельба танка)
Point Tank::CalcShootDirection() const
{

	Point targetDirection = Point{ 1, 1 };



	// Ближайший жук к игроку в данный момент. Выстрел в позицию жука тогда, когда он будет ближе к пуле


	float minDist = std::numeric_limits<float>::max();



	for (auto bug : g_Game->nearestBugPool)
	{





		float dist = (bug->position - position).Length2();
		if (dist < minDist)
		{
			minDist = dist;
			Point targetPosition = bug->position;

			float minBulletDistance = std::numeric_limits<float>::max();



			float aa = (bug->angle - 90.0f) * std::numbers::pi_v<float> / 180.0f;



			int bestStep = -1;
			for (int step = 0; step < 30; step++)
			{

				Point bugPosition = bug->position + Point(cos(aa), sin(aa)) * BugBase::s_Velocity * step * 0.5;
				Point bulletPosition = position + (bugPosition - position).Normalized() * BulletBase::s_Velocity * step * 0.5;

				float bulletDistance = (bugPosition - bulletPosition).Length2();
				if (bulletDistance < minBulletDistance)
				{
					targetPosition = bugPosition;
					minBulletDistance = bulletDistance;
					bestStep = step;
				}
			}

			targetDirection = targetPosition - position;
		}
	}


	// Ближайший жук к пуле во все моменты. Выстрел в позицию жука тогда, когда он будет ближе к пуле
	/*
	float minDist = std::numeric_limits<float>::max();


	for (auto bug : g_Game->nearestBugPool)
	{


		float minBulletDistance = std::numeric_limits<float>::max();

		float aa =  (bug->angle- 90.0f) * std::numbers::pi_v<float> / 180.0f;
		Point targetPosition = bug->position;


		int bestStep = -1;
		for (int step = 0; step < 20; step++)
		{

			Point bugPosition = bug->position + Point(cos(aa), sin(aa)) * BugBase::s_Velocity * step;
			Point bulletPosition = position + (bugPosition - position).Normalized() * BulletBase::s_Velocity * step;
			float bulletDistance = (bugPosition - bulletPosition).Length();
			//LogZA("Step: %zu", step);

			//LogZA("bulletDistance: %f", bulletDistance);
			if (bulletDistance < minBulletDistance)
			{
				targetPosition = bulletPosition;
				minBulletDistance = bulletDistance;
				bestStep = step;
			}


		}
		LogZA("Best step: %zu", bestStep);


		if (minBulletDistance<minDist)
		{
			targetDirection = (targetPosition - position);
			minDist = minBulletDistance;
		}
	}
	LogZA("Best distance: %f", minDist);*/





	



	// Ближайший жук к игроку через X шагов. Выстрел в позицию жука через X шагов, когда он будет ближе к пуле
	
	/*
	float minDist = std::numeric_limits<float>::max();


	for (auto bug : g_Game->nearestBugPool)
	{


		float minBulletDistance = std::numeric_limits<float>::max();
		float minPlayerDistance = std::numeric_limits<float>::max();

		float aa = (bug->angle- 90.0f) * std::numbers::pi_v<float> / 180.0f;
		Point targetPosition = bug->position;


		for (int step = 0; step < 20; step++)
		{

			Point bugPosition = bug->position + Point(cos(aa), sin(aa)) * BugBase::s_Velocity * step;
			Point bulletPosition = position + (bugPosition - position).Normalized() * BulletBase::s_Velocity * step;
			float bulletDistance = (bugPosition - bulletPosition).Length();
			if (bulletDistance < minBulletDistance)
			{
				targetPosition = bugPosition;
				minBulletDistance = bulletDistance;
				

				minPlayerDistance = (bugPosition - position).Length();
			}


		}
		


		if (minPlayerDistance < minDist)
		{
			targetDirection = (targetPosition - position);
			minDist = minPlayerDistance;
		}
	}*/


	return targetDirection;
}
