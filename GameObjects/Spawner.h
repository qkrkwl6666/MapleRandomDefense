#pragma once

#include "GameObject.h"

class Enemy;

class Spawner : public GameObject
{
protected:
	Spawner(const Spawner&) = delete;
	Spawner(Spawner&&) = delete;
	Spawner& operator=(const Spawner&) = delete;
	Spawner& operator=(Spawner&&) = delete;

	std::list<Enemy*> Enemys;
public:
	Spawner(const std::string& name = "");
	~Spawner() override;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void LateUpdate(float dt) override;
};
