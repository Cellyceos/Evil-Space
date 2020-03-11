#include "stdafx.h"
#include "Effect.h"

wstring Effect::EffectPath = L"Effects\\";

Effect::Effect(Map* map, Compositor* compositor) : GameObject(map, compositor)
{
	//scale = 0.5f;
}

void Effect::Update()
{
	GameObject::Update();
}

bool Effect::IsDone()
{
	return frames <= currentFrame;
}

Effect::~Effect(void)
{

}