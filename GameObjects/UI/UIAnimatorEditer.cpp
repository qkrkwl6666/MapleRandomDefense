﻿#include "pch.h"
#include "UIAnimatorEditer.h"
#include "SpriteGo.h"
#include "Crosshair.h"
#include "TextGo.h"

UIAnimatorEditer::UIAnimatorEditer(const std::string& name)
{

}

UIAnimatorEditer::~UIAnimatorEditer()
{

}

void UIAnimatorEditer::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf");

	NewSpriteGo("MainBG", "graphics/UI/Bg.png");
	sprites["MainBG"]->SetOrigin(Origins::MC);
	sprites["MainBG"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["MainBG"]->SetScale({ 1.0f , 1.0f });
	sprites["MainBG"]->sortLayer = 1;

	NewSpriteGo("TextuerLoad", "graphics/UI/button.png");
	sprites["TextuerLoad"]->SetOrigin(Origins::TL);
	sprites["TextuerLoad"]->SetPosition({ 0, 0});
	sprites["TextuerLoad"]->sortLayer = 1;

	texts.insert({ "TextureText", new TextGo("TextureText") });
	texts["TextureText"]->SetFont(font);
	texts["TextureText"]->SetString("TextureLoad");
	texts["TextureText"]->SetCharacterSize(30);
	texts["TextureText"]->SetColor(sf::Color::Black);
	texts["TextureText"]->SetOrigin(Origins::MC);
	texts["TextureText"]->SetPosition({ 150.f , 50});
	texts["TextureText"]->sortLayer = 2;

	NewSpriteGo("IdSprite", "graphics/UI/button.png");
	sprites["IdSprite"]->SetOrigin(Origins::TL);
	sprites["IdSprite"]->SetPosition({ 0, FRAMEWORK.GetWindowSize().y * 0.4f, });
	sprites["IdSprite"]->sortLayer = 1;

	texts.insert({ "IdText", new TextGo("IdText") });
	texts["IdText"]->SetFont(font);
	texts["IdText"]->SetString("ID");
	texts["IdText"]->SetCharacterSize(30);
	texts["IdText"]->SetColor(sf::Color::Black);
	texts["IdText"]->SetOrigin(Origins::MC);
	texts["IdText"]->SetPosition({ 150.f , FRAMEWORK.GetWindowSize().y * 0.45f });
	texts["IdText"]->sortLayer = 2;

	NewSpriteGo("FpsSprite", "graphics/UI/button.png");
	sprites["FpsSprite"]->SetOrigin(Origins::TL);
	sprites["FpsSprite"]->SetPosition({ 0, FRAMEWORK.GetWindowSize().y * 0.6f, });
	sprites["FpsSprite"]->sortLayer = 1;

	texts.insert({ "FpsText", new TextGo("FpsText") });
	texts["FpsText"]->SetFont(font);
	texts["FpsText"]->SetString("Fps");
	texts["FpsText"]->SetCharacterSize(30);
	texts["FpsText"]->SetColor(sf::Color::Black);
	texts["FpsText"]->SetOrigin(Origins::MC);
	texts["FpsText"]->SetPosition({ 150.f , FRAMEWORK.GetWindowSize().y * 0.65f });
	texts["FpsText"]->sortLayer = 2;

	NewSpriteGo("LoopSprite", "graphics/UI/button.png");
	sprites["LoopSprite"]->SetOrigin(Origins::TL);
	sprites["LoopSprite"]->SetPosition({ 0, FRAMEWORK.GetWindowSize().y * 0.8f, });
	sprites["LoopSprite"]->sortLayer = 1;

	texts.insert({ "LoopText", new TextGo("LoopText") });
	texts["LoopText"]->SetFont(font);
	texts["LoopText"]->SetString("0 : SINGLE , 1: LOOP");
	texts["LoopText"]->SetCharacterSize(30);
	texts["LoopText"]->SetColor(sf::Color::Black);
	texts["LoopText"]->SetOrigin(Origins::MC);
	texts["LoopText"]->SetPosition({ 150.f , FRAMEWORK.GetWindowSize().y * 0.85f });
	texts["LoopText"]->sortLayer = 2;

	NewSpriteGo("SpritesCount", "graphics/UI/button.png");
	sprites["SpritesCount"]->SetOrigin(Origins::TL);
	sprites["SpritesCount"]->SetPosition({ FRAMEWORK.GetWindowSize().x 
		- sprites["SpritesCount"]->GetGlobalBounds().width, 0,});
	sprites["SpritesCount"]->sortLayer = 1;

	texts.insert({ "SpritesCountText", new TextGo("SpritesCountText") });
	texts["SpritesCountText"]->SetFont(font);
	texts["SpritesCountText"]->SetString("SpritesCount");
	texts["SpritesCountText"]->SetCharacterSize(30);
	texts["SpritesCountText"]->SetColor(sf::Color::Black);
	texts["SpritesCountText"]->SetOrigin(Origins::MC);
	texts["SpritesCountText"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- (sprites["SpritesCount"]->GetGlobalBounds().width / 2)
		, 50.f });

	texts["SpritesCountText"]->sortLayer = 2;

	NewSpriteGo("SaveSprite", "graphics/UI/save.png");
	sprites["SaveSprite"]->SetOrigin(Origins::TL);
	sprites["SaveSprite"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- sprites["SaveSprite"]->GetGlobalBounds().width, 
		FRAMEWORK.GetWindowSize().y * 0.2f, });
	sprites["SaveSprite"]->sortLayer = 1;

	std::vector<Animation> animations = 
	{
	   {"texture1.png", 0, 0, 100, 100},
	   {"texture2.png", 100, 100, 200, 200},
	   {"texture3.png", 200, 200, 150, 150}
	};

	std::string filename = "animations.csv";

	SaveToCSV();

	UiInit();
	ObjectsSort();
}

void UIAnimatorEditer::Release()
{
	GameObject::Release();

	UiDelete();
}

void UIAnimatorEditer::Reset()
{
	GameObject::Reset();
}

void UIAnimatorEditer::Update(float dt)
{
	GameObject::Update(dt);
}

void UIAnimatorEditer::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);

	switch (currentType)
	{
		case UIAnimatorEditer::Types::NONE:
			if (sprites["TextuerLoad"]->GetGlobalBounds().intersects
			(FRAMEWORK.GetMouse()->GetGlobalBounds()) &&
				InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				SpriteSheetFilePath = Utils::WSTRINGToString(Utils::OpenSaveFileDialog());

				std::cout << SpriteSheetFilePath << std::endl;
			}

			if (sprites["SaveSprite"]->GetGlobalBounds().intersects
			(FRAMEWORK.GetMouse()->GetGlobalBounds()) &&
				InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				SaveToCSV();
			}

			MouseHandle("IdSprite", Types::ID_INPUT);
			MouseHandle("FpsSprite", Types::FPS_INPUT);
			MouseHandle("LoopSprite", Types::LOOPTYPE_INPUT);
			MouseHandle("SpritesCount", Types::COUNT_INPUT);
			break;

		case UIAnimatorEditer::Types::ID_INPUT:
			InputString("IdText", idWstring);
			break;
		case UIAnimatorEditer::Types::FPS_INPUT:
			InputString("FpsText", fpsWstring);
			break;
		case UIAnimatorEditer::Types::LOOPTYPE_INPUT:
			InputString("LoopText", loopWstring);
			break;

		case UIAnimatorEditer::Types::COUNT_INPUT:
			InputString("SpritesCountText", countWstring);
			break;

		default:
			break;
	}




}

void UIAnimatorEditer::MouseHandle(const std::string& id, 
	Types type)
{
	if (sprites[id]->GetGlobalBounds().intersects
	(FRAMEWORK.GetMouse()->GetGlobalBounds()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		currentType = type;
		InputMgr::SetIsInput(true);
	}
}

void UIAnimatorEditer::InputString(const std::string& id,
	std::wstring& isWstring)
{
	texts[id]->SetString(InputMgr::GetInputText());

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		isWstring = InputMgr::GetInputText();
		
		std::wcout << isWstring << std::endl;

		InputMgr::SetIsInput(false);

		currentType = Types::NONE;
	}

}

void UIAnimatorEditer::SaveToCSV()
{
	std::wcout << idWstring << std::endl;

	std::ofstream file("animations.csv", std::ios::out);

	if (file.is_open())
	{
		// CSV 파일 헤더 작성
		file << "ID,FPS,LOOPTYPE\n"; // \n\n
		file << removeNewline(Utils::WSTRINGToString(idWstring)) << ","
			<< removeNewline(Utils::WSTRINGToString(fpsWstring)) << ","
			<< removeNewline(Utils::WSTRINGToString(loopWstring)) << "\n";

		std::wcout << idWstring << fpsWstring << loopWstring;

		file << "TEXTURE,X,Y,WIDTH,HEIGHT\n";

		// 애니메이션 데이터 작성
		//for (const auto& animation : animations)
		//{
		//	file << animation.texture << ","
		//		<< animation.x << ","
		//		<< animation.y << ","
		//		<< animation.width << ","
		//		<< animation.height << "\n";
		//}

		file.close();
		std::cout << "CSV file saved successfully." << std::endl;
	}
	else
	{
		std::cout << "Unable to open file." << std::endl;
	}
}

