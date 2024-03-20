#pragma once

#include "pch.h"
#include "UIGo.h"

class SpriteAnimatorGo;

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
		SPRITE_ANGLE_COUNT,
	};

	struct Animation
	{
		int x;
		int y;
		int width;
		int height;
		int Angle;
	};

protected:
	std::string SpriteSheetFilePath = "";
	std::string CsvFilePath = "";
	std::vector<Animation> animations;
	SpriteAnimatorGo* preViewSprite;

	std::shared_ptr<Animator> animator;

	bool isIdInput = false;
	std::wstring idWstring = L"";
	std::wstring fpsWstring = L"";
	std::wstring loopWstring = L"";
	std::wstring countWstring = L"";
	std::wstring spriteAngleCountWstring = L"";

	Types currentType = Types::NONE;
	
	bool isX = true;


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

	bool MouseSpriteMouseLeftEvent(const std::string& id);
	void SaveToCSV();

	void SplitSpriteSheet();

	std::string removeNewline(std::string str)
	{
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		return str;
	}
};

