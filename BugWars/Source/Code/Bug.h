#pragma once
#include "GameBase/BugBase.h"

struct Bug : public BugBase
{
	virtual void OnUpdate(float dt) override;
	virtual BugBase* FindBugToEat() const override;
	virtual void OnEat(BugBase& first, BugBase& second) override;

	bool inUpdatePool = false;
};