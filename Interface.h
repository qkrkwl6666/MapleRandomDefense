#pragma once
#include "UIGo.h"
class Interface : public UIGo
{
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

