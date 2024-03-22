#pragma once
#include "SpriteGo.h"
class SceneGame;

class Building :
    public SpriteGo
{
public:

	enum class Races
	{
		NONE = -1,
		Zerg,
		Protoss,
		Terran,
		count,
	};

protected:

	SceneGame* sceneGame = nullptr;

public:
	Building(const std::string& name = "");
	~Building() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

};

