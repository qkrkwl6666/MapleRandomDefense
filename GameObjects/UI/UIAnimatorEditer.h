#pragma once

#include "pch.h"
#include "UIGo.h"
#include <ostream>
#include <fstream>

class UIAnimatorEditer : public UIGo
{
public:
	enum class Types
	{
		NONE,
		ID_INPUT,
		FPS_INPUT,
		LOOPTYPE_INPUT,
		COUNT_INPUT,
	};

	struct Animation
	{
		std::string texture;
		int x;
		int y;
		int width;
		int height;
	};

protected:
	std::string SpriteSheetFilePath = "";
	std::vector<Animation> animations;

	bool isIdInput = false;
	std::wstring idWstring = L"";
	std::wstring fpsWstring = L"";
	std::wstring loopWstring = L"";
	std::wstring countWstring = L"";

	Types currentType = Types::NONE;

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

	void MouseHandle(const std::string& id, Types type);
	void InputString(const std::string& id , std::wstring& isWstring);

	void SaveToCSV();

	std::string removeNewline(std::string str)
	{
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		return str;
	}
};

