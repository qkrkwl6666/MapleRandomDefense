#pragma once
#include "UIGo.h"
#include "ShapeGo.h"

class SCUnit;
class Building;


class Interface : public UIGo
{
protected:
	Interface(const Interface&) = delete;
	Interface(Interface&&) = delete;
	Interface& operator=(const Interface&) = delete;
	Interface& operator=(Interface&&) = delete;

	ShapeGo<sf::RectangleShape>* selectBox;
	sf::Vector2f selectStartPos;
	bool isSelecting = false;
	bool noUnits = true;
	
	std::list<SCUnit*> isSelectList;

	sf::Vector2f worldMousePos;
	
	std::unordered_map<std::string, Building*> buildings;

public:
	Interface(const std::string& name = "");
	~Interface() override;


	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void SetActiveUpgrade(bool active);

	void Upgrade();
};

