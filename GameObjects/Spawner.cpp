#include "pch.h"
#include "Spawner.h"
#include "Enemy.h"
#include "Zergling.h"
#include "SceneGame.h"
#include "Interface.h"
#include "Ultralisk.h"
#include "Scourge.h"
#include "DarkTemplar.h"
#include "Queen.h"
#include "Overlord.h"
#include "Mutalisk.h"
#include "Lurker.h"
#include "InfestedTerran.h"
#include "Guardian.h"
#include "Devourer.h"
#include "Defiler.h"
#include "Zealot.h"
#include "TerranBoss.h"

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
	mainInterface = sceneGame->GetInterface();
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
		case 4:
			SpawnEnemys(new DarkTemplar());
			break;
		case 5:
			SpawnEnemys(new Queen());
			break;
		case 6:
			SpawnEnemys(new Overlord());
			break;
		case 7:
			SpawnEnemys(new Mutalisk());
			break;
		case 8:
			SpawnEnemys(new Lurker());
			break;
		case 9:
			SpawnEnemys(new InfestedTerran());
			break;
		case 10:
			SpawnEnemys(new Guardian());
			break;
		case 11:
			SpawnEnemys(new Devourer());
			break;
		case 12:
			SpawnEnemys(new Defiler());
			break;
		case 13:
			SpawnEnemys(new Zealot());
			break;
		// 보스 스테이지
		case 14:
			if (!isBoss)
			{
				TerranBoss* enemy = new TerranBoss();
				enemy->Init();
				Enemys.push_back(enemy);
				isBoss = true;
			}
			// 클리어
			if (Enemys.size() == 0 && isBoss)
			{
				isBoss = false;
				mainInterface->ClearText(true);
				FRAMEWORK.SetTimeScale(0.f);
			}
			break;
		case 15:
			if (Enemys.size() != 0)
			{
				isBoss = false;
				mainInterface->LoseText(true);
				FRAMEWORK.SetTimeScale(0.f);
			}
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
			killCount++;
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

	if (Enemys.size() >= 150)
	{
		mainInterface->LoseText(true);
		FRAMEWORK.SetTimeScale(0.f);
	}
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

void Spawner::AllRemove()
{
	auto it = Enemys.begin();
	while (it != Enemys.end())
	{
		removeEnemys.push_back(*it);
		it = Enemys.erase(it);
	}


}
