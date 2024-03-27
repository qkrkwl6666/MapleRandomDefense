#include "pch.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TileSet.h"
#include "ShapeGo.h"
#include "TextGo.h"
#include <Windows.h>
#include "Crosshair.h"
#include "Interface.h"
#include "UpgradeBuilding.h"
#include "SellBuilding.h"
#include "SCUnit.h"
#include "Hydralisk.h"
#include "Dragoon.h"
#include "Ghost.h"
#include "Enemy.h"
#include "Zergling.h"
#include "Spawner.h"
#include "Civilian.h"
#include "RichText.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}


void SceneGame::Init()
{
	tileSet = new TileSet();
	AddGo(tileSet, Scene::World);

	mouse = FRAMEWORK.GetMouse();

	leftFiller = new ShapeGo<sf::RectangleShape>("leftFiller");
	rightFiller = new ShapeGo<sf::RectangleShape>("rightFiller");

	leftFiller->SetSize({
		((float)FRAMEWORK.GetWindowSize().x / 8),
		(float)FRAMEWORK.GetWindowSize().y });

	rightFiller->SetSize({
		((float)FRAMEWORK.GetWindowSize().x / 8),
		(float)FRAMEWORK.GetWindowSize().y });

	leftFiller->SetPosition({ 0,0 });
	rightFiller->SetPosition({ FRAMEWORK.GetWindowSize().x - rightFiller->GetSize().x, 0 });
	leftFiller->SetColor(sf::Color::Black);
	rightFiller->SetColor(sf::Color::Black);
	AddGo(leftFiller, Layers::Ui);
	AddGo(rightFiller, Layers::Ui);

	basePosition = { 16 * 32 , 16 * 32 };
	basePosition += offset;
	UnitSummonLocation.setSize(sf::Vector2f(25, 25));
	UnitSummonLocation.setOrigin(UnitSummonLocation.getSize() / 2.f);
	UnitSummonLocation.setPosition(basePosition);

	buildings["TerranBuilding"] = new UpgradeBuilding("terranBuilding", Building::Races::Terran);
	buildings["TerranBuilding"]->SetPosition({ 12 * 32 , 27 * 32 });
	AddGo(buildings["TerranBuilding"], Layers::World);

	buildings["ZergBuilding"] = new UpgradeBuilding("zergBuilding", Building::Races::Zerg);
	buildings["ZergBuilding"]->SetPosition({ 16 * 32 , 27 * 32 });
	AddGo(buildings["ZergBuilding"], Layers::World);

	buildings["ProtossBuilding"] = new UpgradeBuilding("protossBuilding", Building::Races::Protoss);
	buildings["ProtossBuilding"]->SetPosition({ 19 * 32 , 27 * 32 });
	AddGo(buildings["ProtossBuilding"], Layers::World);

	buildings["Sellbuilding"] = new SellBuilding("sellBuilding");
	buildings["Sellbuilding"]->SetPosition({ 26 * 32 , 24 * 32 });
	buildings["Sellbuilding"]->SetScale({ 0.25, 0.23 });
	AddGo(buildings["Sellbuilding"], Layers::World);

	mainInterface = new Interface("Interface");
	mainInterface->sortLayer = 10;
	AddGo(mainInterface, Layers::Ui);

	mineralText = new TextGo("mineral");
	mineralText->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), std::to_string(mineral), 20, sf::Color::Green);
	mineralText->SetOrigin(Origins::TL);
	mineralText->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.70f , FRAMEWORK.GetWindowSize().y * 0.005f });
	mineralText->sortLayer = 10;
	AddGo(mineralText, Layers::Ui);

	gasText = new TextGo("gas");
	gasText->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), std::to_string(gas), 20, sf::Color::Green);
	gasText->SetOrigin(Origins::TL);
	gasText->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.80f , FRAMEWORK.GetWindowSize().y * 0.005f });
	gasText->sortLayer = 10;
	AddGo(gasText, Layers::Ui);

	spawner = new Spawner("Spawner");
	AddGo(spawner, Layers::World);

	Scene::Init();

	tileSet->LoadTileMap("tilejson/Map.json", 0.5f);
	tileSet->VaSet();

	civilian = new Civilian();
	AddGo(civilian, Layers::World);
	civilian->Init();
	civilian->SetPosition({ 27.f * 32.f + 16.f, 29.f * 32.f + 16.f });
	AllUnitList.push_back(civilian);

	EnemyList = spawner->GetEnemys();

	mineral = 25; // 초기자금

	
}

void SceneGame::SellUnit(SCUnit::Type t, SCUnit::Rarity r)
{
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		for (auto it = HydraliskList.begin(); it != HydraliskList.end();)
		{
			SCUnit* hydralisk = *it;
			if (hydralisk && hydralisk->GetRarity() == r)
			{
				it = HydraliskList.erase(it);
				for (auto* data : AllUnitList)
				{
					if (data == hydralisk)
					{
						AllUnitList.remove(data);
						break;
					}
				}
				hydralisk->SellThis();
				return;
			}
			else
			{
				it++;
			}
		}

		break;
	case SCUnit::Type::Dragoon:
		for (auto it = DragoonList.begin(); it != DragoonList.end();)
		{
			SCUnit* dragoon = *it;
			if (dragoon && dragoon->GetRarity() == r)
			{
				it = DragoonList.erase(it);
				for (auto* data : AllUnitList)
				{
					if (data == dragoon)
					{
						AllUnitList.remove(data);
						break;
					}
				}
				dragoon->SellThis();
				return;
			}

			else
			{
				it++;
			}
		}
		break;
	case SCUnit::Type::Ghost:
		for (auto it = GhostList.begin(); it != GhostList.end();)
		{
			SCUnit* ghost = *it;
			if (ghost && ghost->GetRarity() == r)
			{
				it = GhostList.erase(it);
				for (auto* data : AllUnitList)
				{
					if (data == ghost)
					{
						AllUnitList.remove(data);
						break;
					}
				}
				ghost->SellThis();
				return;
			}
			else
			{
				it++;
			}
		}
		break;
	default:
		break;
	}
}

Enemy* SceneGame::FindEnemy(sf::Vector2f pos, float range)
{
	float distance = 0.f;
	for (auto* go : *EnemyList)
	{
		distance = Utils::Distance(pos, go->GetPosition());
		if (distance < range * 32)
		{
			return go;
		}
	}
	return nullptr;
}

void SceneGame::message(MessageType m)
{
	switch (m)
	{
	case SceneGame::MessageType::NONE:
		break;
	case SceneGame::MessageType::NotEnoughMinerals:
		std::cout << "미네랄이 부족합니다!!" << std::endl;
		break;
	case SceneGame::MessageType::NoMoreSpace:
		std::cout << "자리가 가득 찼습니다!" << std::endl;
		break;
	case SceneGame::MessageType::count:
		break;
	default:
		break;
	}
}

void SceneGame::message(MessageType m, SCUnit::Type t, SCUnit::Rarity r)
{	
	std::wstring messageDisplayText;
	std::wstring type;
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		type = L"Hydralisk ";
		break;
	case SCUnit::Type::Dragoon:
		type = L"Dragoon ";
		break;
	case SCUnit::Type::Ghost:
		type = L"Ghost ";
		break;
	default:
		break;
	}

	std::wstring rarity;
	std::wstring rarityUpperLegend = L"1 플레이어[가] ";
	std::wstring rarityUpperLegendPer;
	std::wstring empty = L"";
	std::wstring line = L"---------------------------------------------";
	switch (r)
	{
	case SCUnit::Rarity::Common:
		rarity = L"[일반] 50.0%";
		break;
	case SCUnit::Rarity::Rare:
		rarity = L"[레어] 33.1%";
		break;
	case SCUnit::Rarity::Ancient:
		rarity = L"고대] 10.2%";
		break;
	case SCUnit::Rarity::Artifact:
		rarity = L"유물] 5.1% ★";
		break;
	case SCUnit::Rarity::Saga:
		rarity = L"서사] 0.8% ★★★";
		break;
	case SCUnit::Rarity::Legendary:
		rarityUpperLegendPer = L"0.5% 확률로 ";
		rarity = L"[전설] 을 획득하였습니다.";
		break;
	case SCUnit::Rarity::Mythic:
		rarityUpperLegendPer = L"0.08% 확률로 ";
		rarity = L"[신화] 를 획득하였습니다.";
		break;
	case SCUnit::Rarity::Primeval:
		rarityUpperLegendPer = L"0.019% 확률로 ";
		rarity = L"[태초] 를 획득하였습니다.";
		break;
	}

	switch (m)
	{
	case SceneGame::MessageType::BuyUnit:
	{
		switch (r)
		{
		case SCUnit::Rarity::Common:
		case SCUnit::Rarity::Rare:
		case SCUnit::Rarity::Ancient:
		case SCUnit::Rarity::Artifact:
		case SCUnit::Rarity::Saga:
		{
			messageDisplayText = type + rarity;
			SystemMessage message;
			message.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), messageDisplayText, 20, sf::Color::White);
			message.systemMessage->sortLayer = 10;
			AddGo(message.systemMessage, Layers::Ui);
			messageContainer.push_front(message);
		}
		break;
		case SCUnit::Rarity::Legendary:
		case SCUnit::Rarity::Mythic:
		case SCUnit::Rarity::Primeval:
		{
			messageDisplayText = rarityUpperLegend + rarityUpperLegendPer + type + rarity;

			SystemMessage messageLine1;
			messageLine1.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), line, 20, sf::Color::White);
			messageLine1.systemMessage->sortLayer = 10;
			AddGo(messageLine1.systemMessage, Layers::Ui);
			messageContainer.push_front(messageLine1);

			SystemMessage empty1;
			empty1.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), empty, 20, sf::Color::White);
			empty1.systemMessage->sortLayer = 10;
			AddGo(empty1.systemMessage, Layers::Ui);
			messageContainer.push_front(empty1);

			SystemMessage empty2;
			empty2.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), empty, 20, sf::Color::White);
			empty2.systemMessage->sortLayer = 10;
			AddGo(empty2.systemMessage, Layers::Ui);
			messageContainer.push_front(empty2);

			SystemMessage message;
			message.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), messageDisplayText, 20, sf::Color::White);
			message.systemMessage->sortLayer = 10;
			AddGo(message.systemMessage, Layers::Ui);
			messageContainer.push_front(message);

			SystemMessage empty3;
			empty3.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), empty, 20, sf::Color::White);
			empty3.systemMessage->sortLayer = 10;
			AddGo(empty3.systemMessage, Layers::Ui);
			messageContainer.push_front(empty3);

			SystemMessage empty4;
			empty4.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), empty, 20, sf::Color::White);
			empty4.systemMessage->sortLayer = 10;
			AddGo(empty4.systemMessage, Layers::Ui);
			messageContainer.push_front(empty4);

			SystemMessage messageLine2;
			messageLine2.systemMessage->Set(RES_MGR_FONT.Get("font/Kostar.ttf"), line, 20, sf::Color::White);
			messageLine2.systemMessage->sortLayer = 10;
			AddGo(messageLine2.systemMessage, Layers::Ui);
			messageContainer.push_front(messageLine2);
		}
		break;
		}
	}
	break;
	case SceneGame::MessageType::SellUnit:
		//std::cout << "[유닛을 판매했습니다 : " << type << rarity << std::endl;
		break;
	default:
		break;
	}
}

void SceneGame::message(int i)
{
	std::cout << "+ " << i << "원" << std::endl;
}

void SceneGame::MessageUpdate(float dt)
{
	float yOffset = 0.f;
	for (auto& message : messageContainer)
	{
		message.Update(dt);
		message.systemMessage->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.14f , FRAMEWORK.GetWindowSize().y * 0.56f - yOffset });
		yOffset += 25.f;
	}
	for (auto message = messageContainer.begin(); message != messageContainer.end();)
	{
		if (message->messageTimer > message->messageInterval)
		{
			message->systemMessage->SetActive(false);
			DeleteGo(message->systemMessage);
			message = messageContainer.erase(message);
		}
		else
		{
			++message;
		}
	}

	if (messageContainer.size() > 8)
	{
		messageContainer.back().systemMessage->SetActive(false);
		DeleteGo(messageContainer.back().systemMessage);
		messageContainer.pop_back();
	}
}

void SceneGame::UpgradeUpdate()
{
	for (auto go : HydraliskList)
	{
		SCUnit* hydralisk = go;
		hydralisk->SetUpgrade(hydraliskUpgrade);
		hydralisk->SetDamage();
	}

	for (auto go : GhostList)
	{
		SCUnit* ghost = go;
		ghost->SetUpgrade(ghostUpgrade);
		ghost->SetDamage();
	}

	for (auto go : DragoonList)
	{
		SCUnit* dragoon = go;
		dragoon->SetUpgrade(dragoonUpgrade);
		dragoon->SetDamage();
	}
}

void SceneGame::Release()
{
	Scene::Release();

}

void SceneGame::Reset()
{
	hydraliskUpgrade = 0;
	dragoonUpgrade = 0;
	ghostUpgrade = 0;
}

void SceneGame::Enter()
{
	Scene::Enter();

}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(screenPos);

	mineralText->SetString(std::to_string(mineral));
	gasText->SetString(std::to_string(gas));
	if (gas >= 10)
	{
		gas -= 10;
		mineral += 5;
	}

	MessageUpdate(dt);

	// *************** 개발자 모드
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		if (!modeDeveloper)
		{
			modeDeveloper = true;
			return;
		}
		if (modeDeveloper)
		{
			modeDeveloper = false;
			return;
		}
	}

	if (modeDeveloper)
	{
		std::cout << (int)worldPos.x / 32 << " " << (int)worldPos.y / 32 << std::endl;
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			mineral += 20;
		}
	}
	// *************** 개발자 모드

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos;
	}

	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos;

		GetWorldView().move(delta);
	}

}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

	if (civilian->GetPosition().x >= 900)
	{
		civilian->SetPosition({ 27.f * 32.f + 16.f, 29.f * 32.f + 16.f });
		civilian->SetIsAster(false);
		civilian->SetStatus(SCUnit::Status::IDLE);
		BuyUnit();
	}

}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::DebugUpdate(float dt)
{
	Scene::DebugUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::BuyUnit()
{
	if (mineral < 10)
	{
		message(MessageType::NotEnoughMinerals);
		return;
	}
	mineral -= 10;
	UnitSummonLocation.setPosition(basePosition);
	std::vector<sf::Vector2f> directions = {
	{32, 0},
	{32, 32},
	{0, 32},
	{0, -32},
	{32, -32},
	{64, -32},
	{64, 0},
	{64, 32},
	{64, 64},
	{32, 64},
	{0, 64},
	{-32, 64},
	{-32, 32},
	{-32, 0},
	{-32, -32},
	{-32,-64}
	};
	int directionIndex = 0;

	while (directionIndex < 16)
	{
		SummonStuck = false;
		for (auto go : AllUnitList)
		{
			if (go->GetHitBox().getGlobalBounds().contains(UnitSummonLocation.getPosition()))
			{
				SummonStuck = true;
				break;
			}
		}

		if (!SummonStuck)
		{
			break;
		}
		UnitSummonLocation.setPosition(basePosition + directions[directionIndex]);
		directionIndex++;
	}

	if (directionIndex == 16)
	{
		message(MessageType::NoMoreSpace);
		return;
	}

	int randomUnit = -1;
	randomUnit = Utils::RandomRange(0, 3);
	int randomint = -1;
	randomint = Utils::RandomRange(0, 10000);
	SCUnit::Rarity randomrarity = SCUnit::Rarity::NONE;
	if (randomint < 5000)
	{
		randomrarity = SCUnit::Rarity::Common;
	}
	if (randomint >= 5000 && randomint < 8310)
	{
		randomrarity = SCUnit::Rarity::Rare;
	}
	if (randomint >= 8310 && randomint < 9330)
	{
		randomrarity = SCUnit::Rarity::Ancient;
	}
	if (randomint >= 9330 && randomint < 9840)
	{
		randomrarity = SCUnit::Rarity::Artifact;
	}
	if (randomint >= 9840 && randomint < 9920)
	{
		randomrarity = SCUnit::Rarity::Saga;
	}
	if (randomint >= 9920 && randomint < 9970)
	{
		randomrarity = SCUnit::Rarity::Legendary;
	}
	if (randomint >= 9970 && randomint < 9988)
	{
		randomrarity = SCUnit::Rarity::Mythic;
	}
	if (randomint >= 9988 && randomint < 10000)
	{
		randomrarity = SCUnit::Rarity::Primeval;
	}

	switch (randomUnit)
	{
	case 0:
	{
		Hydralisk* hydralisk = new Hydralisk("hydralisk", randomrarity);
		hydralisk->Init();
		hydralisk->SetPosition(UnitSummonLocation.getPosition());
		AddGo(hydralisk, Layers::World);
		HydraliskList.push_back(hydralisk);
		AllUnitList.push_back(hydralisk);
		UpgradeUpdate();
		hydralisk->SetDamage();
		message(MessageType::BuyUnit, SCUnit::Type::Hydralisk, randomrarity);
	}
	break;
	case 1:
	{
		Dragoon* dragoon = new Dragoon("dragoon", randomrarity);
		dragoon->Init();
		dragoon->SetPosition(UnitSummonLocation.getPosition());
		AddGo(dragoon, Layers::World);
		DragoonList.push_back(dragoon);
		AllUnitList.push_back(dragoon);
		UpgradeUpdate();
		dragoon->SetDamage();
		message(MessageType::BuyUnit, SCUnit::Type::Dragoon, randomrarity);
	}
	break;
	case 2:
	{
		Ghost* ghost = new Ghost("ghost", randomrarity);
		ghost->Init();
		ghost->SetPosition(UnitSummonLocation.getPosition());
		AddGo(ghost, Layers::World);
		GhostList.push_back(ghost);
		AllUnitList.push_back(ghost);
		UpgradeUpdate();
		ghost->SetDamage();
		message(MessageType::BuyUnit, SCUnit::Type::Ghost, randomrarity);
	}
	break;
	default:
		break;
	}
}
