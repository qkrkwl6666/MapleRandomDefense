#pragma once

#include "pch.h"

class UIAnimatorEditer;

class SceneAnimatorEditer : public Scene
{
protected:
	SceneAnimatorEditer(const SceneAnimatorEditer&) = delete;
	SceneAnimatorEditer(SceneAnimatorEditer&&) = delete;
	SceneAnimatorEditer& operator=(const SceneAnimatorEditer&) = delete;
	SceneAnimatorEditer& operator=(SceneAnimatorEditer&&) = delete;

	UIAnimatorEditer* uiAnimatorEditer = nullptr;
	

public:
	SceneAnimatorEditer(SceneIds id);
	~SceneAnimatorEditer() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;
};

