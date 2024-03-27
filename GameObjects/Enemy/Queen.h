#pragma once
#include "Enemy.h"
class Queen : public Enemy
{
protected:
	Queen(const Queen&) = delete;
	Queen(Queen&&) = delete;
	Queen& operator=(const Queen&) = delete;
	Queen& operator=(Queen&&) = delete;

public:
	Queen(const std::string& name = "", const std::string& animationName = "");
	~Queen() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

