#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

#include <cmath>



#include "GameBase/Log.h"

void Tank::OnUpdate(float dt)
{
}


BugBase* Tank::GetBugToShoot() const
{
	BugBase* targetBug = nullptr;


	float minDist = std::numeric_limits<float>::max();



	for (auto bug : g_Game->nearestBugPool)
	{

		float dist = (bug->position - position).Length2();
		if (dist < minDist)
		{
			minDist = dist;

			targetBug = bug;
		}
	}

	return targetBug;

}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	/*
	Point newTargetPosition = target_pos;
	float minBulletDistance = std::numeric_limits<float>::max();

	int bestStep = -1;
	for (int step = 0; step < 30; step++)
	{

		Point bugPosition = target_pos + target_dir.Normalized() * target_vel * step * 0.5;
		Point bulletPosition = position + (bugPosition - position).Normalized() * bullet_vel * step * 0.5;

		float bulletDistance = (bugPosition - bulletPosition).Length2();
		if (bulletDistance < minBulletDistance)
		{
			newTargetPosition = bugPosition;
			minBulletDistance = bulletDistance;
			bestStep = step;
		}
	}

	return newTargetPosition - position;*/


	float Vox = target_dir.Normalized().x * target_vel;
	float Voy = target_dir.Normalized().y * target_vel;
	
	float Xo = target_pos.x - position.x;
	float Yo = target_pos.y - position.y;


	double quadA = (double)(Vox* Vox+ Voy * Voy)  -((double)bullet_vel * (double)bullet_vel);
	double quadB = (2 * Xo * Vox + 2 * Yo * Voy);
	double quadC = (Xo* Xo+Yo*Yo);

	double d = quadB * quadB - quadA * quadC * 4.0;

	float t = d >= 0 ? (-quadB-sqrt(d))/(2.0* quadA) : 0;

	

	return (target_pos + target_dir.Normalized() * target_vel * t)-position;


}
