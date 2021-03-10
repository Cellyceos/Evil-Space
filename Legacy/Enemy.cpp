#include "stdafx.h"
#include "Enemy.h"
#include "GDIBitmap.h"
#include "Player.h"
#include "Compositor.h"
#include "Map.h"

Enemy::Enemy(Map* map, Compositor* compositor) : Ship(map, compositor)
										, DetectionRadius(600.0f)
										, decision(0)
{
	direction = Randomizer.Next(0.0f, MaxDirections);

	RectF& rect = Maps->MapRectangle();

	do {
		Rects.X = Randomizer.Next(0.0f, rect.Width + 1.0f);
		Rects.Y = Randomizer.Next(0.0f, rect.Height + 1.0f);
	} while (rect.Contains(MiddlePoint()));

	delete &rect;
}

Player* Enemy::FindPlayer()
{
	Player* player = NULL;
	RectF& area = *new RectF(MiddlePoint().X - DetectionRadius, MiddlePoint().Y - DetectionRadius, DetectionRadius*2.0f, DetectionRadius*2.0f);

	for (int i = 0; i < Compositors->Objects.Count(); i++)
	{
		player = dynamic_cast<Player*>(Compositors->Objects[i]);

		if (player != NULL && player->Rects.IntersectsWith(area))
			break;
	}

	delete &area;

	return player;
}

int Enemy::CalcAngle(PointF& player)
{
	PointF& enemy = MiddlePoint();

	auto co = fabs(atan2(enemy.X - player.X, enemy.Y - player.Y) * 180.0f / M_PI);

	if (enemy.X > player.X)
		co = 360 - co;
	else
		co = 0 + co;

	delete &player;
	delete &enemy;
	return (int)co;
}

void Enemy::Think()
{
	Player* player = FindPlayer();

	if (player != NULL)
		Attack(player);
	else
		Wander();
}

void Enemy::Wander()
{
	if (5 < speed)
		SlowSpeed();
	else if (speed < 5)
		IncreaseSpeed();

	int rnd = Randomizer.Next(0, 101);

	if (rnd > 90)
		MoveLeft();
	else if (rnd > 80)
		MoveRight();
}

void Enemy::Attack(GameObject* player)
{
	int angle = CalcAngle(player->MiddlePoint());

	if (angle + (360 - direction) < direction - angle)
	{
		Direction(direction + 2);
		return;
	}

	if (direction + (360 - angle) < angle - direction)
	{
		Direction(direction - 2);
		return;
	}

	if (angle - direction > direction - angle) 
		Direction(direction + 1);
	else 
		Direction(direction - 1);

	if (fabs(angle - direction) < 5.0f)
		Fire();
}

void Enemy::Draw(Graphics* g)
{
	Bitmap* image = RotateImage(_image->GetFrame(currentFrame));
	GameObject::Draw(g, image);

	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}

void Enemy::Update()
{
	Ship::Update();
	Think();
}

Enemy::~Enemy(void)
{
}
