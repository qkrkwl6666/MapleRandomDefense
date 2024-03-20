#include "pch.h"
#include "UIAnimatorEditer.h"
#include "SpriteGo.h"
#include "Crosshair.h"
#include "TextGo.h"
#include "SpriteAnimatorGo.h"
#include <ostream>
#include <fstream>

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
		- (texts["SpritesCountText"]->GetGlobalBounds().width)
		, 50.f });

	texts["SpritesCountText"]->sortLayer = 2;

	NewSpriteGo("SaveSprite", "graphics/UI/save.png");
	sprites["SaveSprite"]->SetOrigin(Origins::TL);
	sprites["SaveSprite"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- sprites["SaveSprite"]->GetGlobalBounds().width, 
		FRAMEWORK.GetWindowSize().y * 0.2f, });
	sprites["SaveSprite"]->sortLayer = 1;

	NewSpriteGo("ChangeXY", "graphics/UI/button.png");
	sprites["ChangeXY"]->SetOrigin(Origins::TL);
	sprites["ChangeXY"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- sprites["ChangeXY"]->GetGlobalBounds().width,
		FRAMEWORK.GetWindowSize().y * 0.4f, });
	sprites["ChangeXY"]->sortLayer = 1;

	texts.insert({ "XYText", new TextGo("XYText") });
	texts["XYText"]->SetFont(font);
	texts["XYText"]->SetString("X");
	texts["XYText"]->SetCharacterSize(30);
	texts["XYText"]->SetColor(sf::Color::Black);
	texts["XYText"]->SetOrigin(Origins::MC);
	texts["XYText"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- ((sprites["ChangeXY"]->GetGlobalBounds().width / 2))
		, FRAMEWORK.GetWindowSize().y * 0.45f });

	NewSpriteGo("AnimationView", "graphics/UI/button.png");
	sprites["AnimationView"]->SetOrigin(Origins::TL);
	sprites["AnimationView"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- sprites["AnimationView"]->GetGlobalBounds().width,
		FRAMEWORK.GetWindowSize().y * 0.6f, });
	sprites["AnimationView"]->sortLayer = 1;

	texts.insert({ "AnimationViewText", new TextGo("AnimationViewText") });
	texts["AnimationViewText"]->SetFont(font);
	texts["AnimationViewText"]->SetString(L"애니메이션 미리보기");
	texts["AnimationViewText"]->SetCharacterSize(30);
	texts["AnimationViewText"]->SetColor(sf::Color::Black);
	texts["AnimationViewText"]->SetOrigin(Origins::MC);
	texts["AnimationViewText"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- ((sprites["ChangeXY"]->GetGlobalBounds().width / 2))
		, FRAMEWORK.GetWindowSize().y * 0.65f });

	NewSpriteGo("SpriteAngleCount", "graphics/UI/button.png");
	sprites["SpriteAngleCount"]->SetOrigin(Origins::TL);
	sprites["SpriteAngleCount"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- sprites["SpriteAngleCount"]->GetGlobalBounds().width,
		FRAMEWORK.GetWindowSize().y * 0.8f, });
	sprites["SpriteAngleCount"]->sortLayer = 1;

	texts.insert({ "AngleCountText", new TextGo("AngleCountText") });
	texts["AngleCountText"]->SetFont(font);
	texts["AngleCountText"]->SetString(L"스프라이트 시트 개수");
	texts["AngleCountText"]->SetCharacterSize(30);
	texts["AngleCountText"]->SetColor(sf::Color::Black);
	texts["AngleCountText"]->SetOrigin(Origins::MC);
	texts["AngleCountText"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		- ((sprites["SpriteAngleCount"]->GetGlobalBounds().width / 2))
		, FRAMEWORK.GetWindowSize().y * 0.85f });

	animator = std::make_shared<Animator>();
	preViewSprite = new SpriteAnimatorGo();
	preViewSprite->sortLayer = 5;
	preViewSprite->SetScale({ 3.f , 3.f });

	SCENE_MGR.GetScene(SceneIds::SceneAnimatorEditer)->AddGo(preViewSprite, Scene::Ui);

	animator->SetTarget(preViewSprite->GetSprite());
	preViewSprite->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f
		, FRAMEWORK.GetWindowSize().y * 0.5f });

	SplitSpriteSheet();

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

	animator->Update(dt);
}

void UIAnimatorEditer::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);

	switch (currentType)
	{
		case UIAnimatorEditer::Types::NONE:
			
			if(MouseSpriteMouseLeftEvent("TextuerLoad"))
			{
				SpriteSheetFilePath = Utils::WSTRINGToString(Utils::OpenSaveFileDialog());
				Utils::RemoveStringBeforeKeyWord(SpriteSheetFilePath , "graphics");
				std::cout << SpriteSheetFilePath << std::endl;
			}

			if (MouseSpriteMouseLeftEvent("SaveSprite"))
			{
				SaveToCSV();
			}

			if (MouseSpriteMouseLeftEvent("ChangeXY"))
			{
				if (isX)
				{
					isX = false;
					texts["XYText"]->SetString("Y");
				}
				else
				{
					isX = true;
					texts["XYText"]->SetString("X");
				}
			}

			if (MouseSpriteMouseLeftEvent("AnimationView"))
			{
				animator->AddClip(RES_MGR_ANIMATIONCLIP.Get(CsvFilePath));
				animator->Play(Utils::WSTRINGToString(idWstring));
			}

			MouseHandle("IdSprite", Types::ID_INPUT);
			MouseHandle("FpsSprite", Types::FPS_INPUT);
			MouseHandle("LoopSprite", Types::LOOPTYPE_INPUT);
			MouseHandle("SpritesCount", Types::COUNT_INPUT);
			MouseHandle("SpriteAngleCount", Types::SPRITE_ANGLE_COUNT);
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

		case UIAnimatorEditer::Types::SPRITE_ANGLE_COUNT:
			InputString("AngleCountText", spriteAngleCountWstring);
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

bool UIAnimatorEditer::MouseSpriteMouseLeftEvent(const std::string& id)
{
	if (sprites[id]->GetGlobalBounds().intersects
	(FRAMEWORK.GetMouse()->GetGlobalBounds()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UIAnimatorEditer::SaveToCSV()
{
	std::wcout << idWstring << std::endl;

	// TODO : 예외 처리 아직 안함

	std::ofstream file("Animation/AnimatorEditer/" + 
		Utils::WSTRINGToString(idWstring) + ".csv", std::ios::out);

	if (file.is_open())
	{
		// CSV 파일 헤더 작성
		file << "ID,FPS,LOOPTYPE\n"; // \n\n
		file << Utils::WSTRINGToString(idWstring) << ","
			<< Utils::WSTRINGToString(fpsWstring) << ","
			<< Utils::WSTRINGToString(loopWstring) << "\n\n";

		std::wcout << idWstring << fpsWstring << loopWstring;

		file << "TEXTURE,X,Y,WIDTH,HEIGHT,ANGLE,ORIGIN\n";

		sf::Image spriteSheet;
		spriteSheet.loadFromFile(SpriteSheetFilePath);
		sf::Vector2u imgSize = spriteSheet.getSize();
	
		for (int j = 0; j < std::stoi(spriteAngleCountWstring); j++)
		{
			animations.clear();

			for (int i = 0; i < std::stoi(countWstring); i++)
			{
				Animation ani;

				if (isX)
				{
					ani.width = imgSize.x / std::stoi(countWstring);
					ani.height = imgSize.y;
					ani.x = i * ani.width;
					ani.y = 0;
				}

				else
				{
					ani.width = imgSize.x / std::stoi(spriteAngleCountWstring);
					ani.height = imgSize.y / std::stoi(countWstring);
					ani.x = j * ani.width;
					ani.y = i * ani.height;
					ani.Angle = j;
				}

				animations.push_back(ani);
			}

			//애니메이션 데이터 작성
			for (const auto& animation : animations)
			{
				file << SpriteSheetFilePath << ","
					<< animation.x << ","
					<< animation.y << ","
					<< animation.width << ","
					<< animation.height << ","
					<< animation.Angle << ","
					<< "\n";
			}

			file << "\n\n";
		}
		
		file.close();

		std::cout << "CSV file saved successfully." << std::endl;
		CsvFilePath = "Animation/AnimatorEditer/" + 
			Utils::WSTRINGToString(idWstring) + ".csv";
	}
	else
	{
		std::cout << "Unable to open file." << std::endl;
	}
}

void UIAnimatorEditer::SplitSpriteSheet()
{
	/*sf::Image image;
	image.loadFromFile("graphics/Hydralisk.png");
	
	SpriteGo* previewImg;
	previewImg = new SpriteGo();

	previewImg->SetTexture("graphics/Hydralisk.png");
	previewImg->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f,
		FRAMEWORK.GetWindowSize().y * 0.5f });

	SCENE_MGR.GetScene(SceneIds::SceneAnimatorEditer)->AddGo(previewImg, Scene::Ui);*/
}

