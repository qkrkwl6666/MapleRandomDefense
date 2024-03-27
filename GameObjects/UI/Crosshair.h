#pragma once
#include "SpriteAnimatorGo.h"
class Crosshair : public SpriteAnimatorGo
{
public:
	Crosshair(const std::string& name = "crosshair");
	~Crosshair() override = default;
	Crosshair(const Crosshair&) = delete;
	Crosshair(Crosshair&&) = delete;
	Crosshair& operator=(const Crosshair&) = delete;
	Crosshair& operator=(Crosshair&&) = delete;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);	
	bool isCursorsCollision = false;
	bool isCursorsMoving = false;

	sf::Vector2f GetPosition() const
	{
		return position;
	}



};

