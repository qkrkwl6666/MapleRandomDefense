#pragma once

#include "GameObject.h"

class Enemy;
class SceneGame;
class Interface;

class Spawner : public GameObject
{
protected:
	Spawner(const Spawner&) = delete;
	Spawner(Spawner&&) = delete;
	Spawner& operator=(const Spawner&) = delete;
	Spawner& operator=(Spawner&&) = delete;

	std::list<Enemy*> Enemys;
	std::list<Enemy*> removeEnemys;

	float spawnTimer = 0;

	SceneGame* sceneGame = nullptr;
	Interface* mainInterface = nullptr;
	
	bool isBoss = false;
	bool isDead = false;
	bool isClear = false;
	int killCount = 0;

public:
	Spawner(const std::string& name = "");
	~Spawner() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void LateUpdate(float dt) override;

	std::list<Enemy*>* GetEnemys() { return &Enemys; }

	void SpawnEnemys(Enemy* enemy);
	void AllRemove();

	int& GetKillCount() { return killCount; }


};

