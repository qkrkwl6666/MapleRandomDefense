#pragma once
#include "UIGo.h"
#include "ShapeGo.h"

class SCUnit;

class Interface : public UIGo
{
protected:
	ShapeGo<sf::RectangleShape>* selectBox;
	sf::Vector2f selectStartPos;
	bool isSelecting = false;
	
	std::list<SCUnit*> isSelectList;

	sf::Vector2f worldMousePos;
	

public:
	Interface(const std::string& name = "");
	~Interface() override;
	Interface(const Interface&) = delete;
	Interface(Interface&&) = delete;
	Interface& operator=(const Interface&) = delete;
	Interface& operator=(Interface&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

