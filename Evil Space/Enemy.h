#pragma once
#include "ship.h"

class Player;

class Enemy abstract:
	public Ship
{
public:
	const float DetectionRadius;
	Enemy(Map*, Compositor*);
	virtual void Draw(Graphics*) override;
	virtual void Update() override;
	virtual ~Enemy(void);
protected:
	int decision;

	void Attack(GameObject*);
	void Flee(GameObject*);
	void CheckObstruction();
	void Wander();
	void Think();
	int CalcAngle(PointF&);
	Player* FindPlayer();
};
