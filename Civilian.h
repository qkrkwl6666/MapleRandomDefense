#pragma once
#include "SCUnit.h"
class Civilian : public SCUnit
{
protected:
	Civilian(const Civilian&) = delete;
	Civilian(Civilian&&) = delete;
	Civilian& operator=(const Civilian&) = delete;
	Civilian& operator=(Civilian&&) = delete;

public:
	Civilian(const std::string& name = "",
		const std::string& animationName = "");
	~Civilian() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

