#pragma once
#include "SpriteAnimatorGo.h"

class SCUnit : public SpriteAnimatorGo
{
protected:
	Angle currentAngle = Angle::TOP;

public:
	SCUnit(const std::string& name = "");
	~SCUnit() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const Angle& GetCurrentAngle() { return currentAngle; }
};

