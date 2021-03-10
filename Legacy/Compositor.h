#pragma once

class InteractiveObject;
class Ammunition;
class Effect;

class Compositor
{
public:
	GameList& Ammunitions;
	GameList& Objects;
	GameList& Effects;

	Compositor(void);
	void Draw(Gdiplus::Graphics*);
	void Update();
	void AddGameObject(InteractiveObject*);
	void AddGameObject(Ammunition*);
	void AddGameObject(Effect*);
	virtual ~Compositor(void);

private:
	void RemoveDeadObjects();
	void RemoveDoneEffects();
	void RemoveDoneAmmunitions();
	void Update(GameList&);
	void Draw(Gdiplus::Graphics*, GameList&);
};