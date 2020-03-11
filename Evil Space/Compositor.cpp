#include "stdafx.h"
#include "Compositor.h"
#include "InteractiveObject.h"
#include "Ammunition.h"
#include "Effect.h"

Compositor::Compositor(void): 
						Objects(*new GameList())
					  , Effects(*new GameList())
					  , Ammunitions(*new GameList())
{}

void Compositor::RemoveDeadObjects() 
{
	for (int i = 0; i < Objects.Count(); i++)
	{
		InteractiveObject* aliveObj = dynamic_cast<InteractiveObject*>(Objects[i]);

		if (!aliveObj->IsAlive())
			Objects.Remove(aliveObj);
	}
}

void Compositor::RemoveDoneEffects() 
{
	for (int i = 0; i < Effects.Count(); i++)
	{
		Effect* workingEffect = dynamic_cast<Effect*>(Effects[i]);

		if (workingEffect->IsDone())
			Effects.Remove(workingEffect);
	}
}

void Compositor::RemoveDoneAmmunitions() 
{
	for (int i = 0; i < Ammunitions.Count(); i++)
	{
		Ammunition* ammo = dynamic_cast<Ammunition*>(Ammunitions[i]);

		if (!ammo->IsAlive())
			Ammunitions.Remove(ammo);
	}
}

void Compositor::Update(GameList& list)
{
	for (int i = 0; i < list.Count(); i++)
		list[i]->Update();
}

void Compositor::Draw(Graphics* g, GameList& list) 
{
	for (int i = 0; i < list.Count(); i++)
		list[i]->Draw(g);
}

void Compositor::Draw(Graphics* g) try
{
	Draw(g, Objects);
	Draw(g, Effects);
	Draw(g, Ammunitions);
}
catch (...)
{
	int a;
	a= 5;
}

void Compositor::Update() 
{
	Update(Ammunitions);
	Update(Effects);
	Update(Objects);

	RemoveDeadObjects();
	RemoveDoneEffects();
	RemoveDoneAmmunitions();
}

void Compositor::AddGameObject(InteractiveObject* obj) 
{
	Objects.Add(obj);
}

void Compositor::AddGameObject(Ammunition* obj) 
{
	Ammunitions.Add(obj);
}

void Compositor::AddGameObject(Effect* obj) 
{
	Effects.Add(obj);
}

Compositor::~Compositor()
{
	delete &Ammunitions;
	delete &Effects;
	delete &Objects;
}