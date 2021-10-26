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

			targetBug = bug;
		}
	}

	return targetBug;

}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{

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

	return newTargetPosition - position;
}
