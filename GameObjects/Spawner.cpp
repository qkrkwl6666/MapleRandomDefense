#include "pch.h"
#include "Spawner.h"
#include "Enemy.h"
#include "Zergling.h"

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
