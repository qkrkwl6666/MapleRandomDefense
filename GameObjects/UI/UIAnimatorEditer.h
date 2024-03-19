#pragma once

#include "pch.h"
#include "UIGo.h"

class UIAnimatorEditer : public UIGo
{
public:
	UIAnimatorEditer(const std::string& name = "");
	~UIAnimatorEditer() override;
	UIAnimatorEditer(const UIAnimatorEditer&) = delete;
	UIAnimatorEditer(UIAnimatorEditer&&) = delete;
	UIAnimatorEditer& operator=(const UIAnimatorEditer&) = delete;
	UIAnimatorEditer& operator=(UIAnimatorEditer&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

