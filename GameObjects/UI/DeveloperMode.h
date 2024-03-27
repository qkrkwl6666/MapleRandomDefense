#pragma once
#include "UIGo.h"

class SceneGame;
class Enemy;

class DeveloperMode : public UIGo
{
protected:
	DeveloperMode(const DeveloperMode&) = delete;
	DeveloperMode(DeveloperMode&&) = delete;
	DeveloperMode& operator=(const DeveloperMode&) = delete;
	DeveloperMode& operator=(DeveloperMode&&) = delete;

	SceneGame* sceneGame = nullptr;
	std::list<Enemy*>* enemyList = nullptr;
	

public:
	DeveloperMode(const std::string& name = "");
	~DeveloperMode() override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

