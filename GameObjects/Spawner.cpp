#include "pch.h"
#include "Spawner.h"
#include "Enemy.h"
#include "Zergling.h"
#include "SceneGame.h"
#include "Interface.h"
#include "Ultralisk.h"
#include "Scourge.h"

Spawner::Spawner(const std::string& name): GameObject(name)
{

}

Spawner::~Spawner()
{
	for (auto& data : Enemys)
	{
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}
	}
}

void Spawner::Init()
{
	GameObject::Init();

	SetPosition({ 16 * 32 + 16.f , 10 * 32 + 16.f });

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));
}

void Spawner::Release()
{
	GameObject::Release();
}

void Spawner::Reset()
{
	GameObject::Reset();
}

void Spawner::Update(float dt)
{
	GameObject::Update(dt);

	spawnTimer += dt;

	// TODO : 공격 탐지 테스트 코드
	Enemys.reverse();

	switch (sceneGame->GetInterface()->GetStage())
	{
		case 0:
			if (spawnTimer > 0.8f)
			{
				spawnTimer = 0.f;
			}
			break;
		case 1:
			SpawnEnemys(new Zergling());
			break;
		case 2:
			SpawnEnemys(new Scourge());
			break;
		case 3:
			SpawnEnemys(new Ultralisk());
			break;
	}


	for (auto* data : Enemys)
	{
		if (data == nullptr)
		{
			continue;
		}

		if (!data->GetActive())
		{
			Enemys.remove(data);
			removeEnemys.push_back(data);
			break;
		}
		else
		{
			data->Update(dt);
		}
	}

	for (auto* data : removeEnemys)
	{
		removeEnemys.remove(data);
		delete data;
		data = nullptr;
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::L))
	{
		Zergling* zergling = new Zergling();
		zergling->Init();
		Enemys.push_back(zergling);
	}
}

void Spawner::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	for (auto& data : Enemys)
	{
		if (data == nullptr || !data->GetActive())
		{
			continue;
		}

		data->Draw(window);
	}
}

void Spawner::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void Spawner::SpawnEnemys(Enemy* enemy)
{
	if (spawnTimer > 0.8f)
	{
		enemy->Init();
		Enemys.push_back(enemy);
		spawnTimer = 0.f;
	}
}
