#include "pch.h"
#include "SCUnit.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"
#include "Enemy.h"

SCUnit::SCUnit(const std::string& name , const std::string& animationName)
	: SpriteAnimatorGo(name) , animationName(animationName)
{

}

SCUnit::~SCUnit()
{
	
}

void SCUnit::Init()
{
	SpriteAnimatorGo::Init();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));

	float aniangle = -157.5;

	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

	// ���� ��������Ʈ

	isSelectSprite = std::make_shared<SpriteGo>();
	isSelectSprite->SetTexture("graphics/UI/cursorsSelect.png");
	isSelectSprite->SetOrigin(Origins::MC);
	isSelectSprite->SetScale({ 2.f , 2.f });
	isSelectSprite->SetActive(false);

}

void SCUnit::Reset()
{
	SpriteAnimatorGo::Reset();
}

void SCUnit::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyUp(sf::Keyboard::Space))
	{
		if (isSelectSprite->GetActive() && isSelect)
		{
			SetSelect(false);
		}
		else
		{
			SetSelect(true);
		}
	}

	if (isSelectSprite->GetActive() && isSelect)
	{
		isSelectSprite->SetPosition({ GetPosition().x + 5.f, GetPosition().y + 30.f });
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		direction = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos() - GetPosition();

		Utils::Normalize(direction);
	
		float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));
		//std::cout << aniAngle << std::endl;
		currentAngle = angleMap[aniAngle];
		if (aniAngle < -90 || aniAngle > 90)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
	}

	switch (currentStatus)
	{
		case SCUnit::Status::NONE:
			SetStatus(Status::IDLE);
			break;
		case SCUnit::Status::IDLE:
			animator->PlayIdle(animationName + "Move", true, currentAngle);

			if (isAster == true)
			{
				SetStatus(Status::MOVE);
				isAster = false;
			}

			//animator->Update(dt, currentAngle);
			break;
		case SCUnit::Status::MOVE:
			if (!animator->IsPlaying())
			{
				animator->Play(animationName + "Move", true, true);
			}

			if (!path.empty())
			{
				if (pathIndex < path.size())
				{
					sf::Vector2f targetPosition = sf::Vector2f(path[pathIndex].x * 32, path[pathIndex].y * 32);

					sf::Vector2f direction = Utils::GetNormalize(targetPosition - GetPosition());

					float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));

					float distance = Utils::Distance(targetPosition, GetPosition());

					currentAngle = angleMap[aniAngle];
					if (aniAngle < -90 || aniAngle > 90)
					{
						SetFlipX(true);
					}
					else
					{
						SetFlipX(false);
					}

					if (distance > 0.1f)
					{
						Translate(direction * moveSpeed * dt);
					}
					else
					{
						pathIndex++;
					}
				}
				else
				{
					pathIndex = 0;
					isAster = false;
					SetStatus(Status::IDLE);
				}
			}

			animator->Update(dt, currentAngle);
			break;
		case SCUnit::Status::ATTACK:
			if (!animator->IsPlaying())
			{
				animator->Play(animationName + "Attack", true, true);
			}
			animator->Update(dt, currentAngle);
			break;
		default:
			break;
	}

	if (target == nullptr)
	{
		target = sceneGame->FindEnemy(GetPosition(), attackRange);
	}
	else
	{
		direction = target->GetPosition() - GetPosition();
		Utils::Normalize(direction);
		float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));
		currentAngle = angleMap[aniAngle];
		if (aniAngle < -90 || aniAngle > 90)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
		if ((Utils::Distance(GetPosition(), target->GetPosition()) > attackRange * 32))
		{
			target = nullptr;
		}
	}

}

void SCUnit::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);
}

void SCUnit::Draw(sf::RenderWindow& window)
{
	if (isSelectSprite->GetActive() && isSelect == true)
	{
		isSelectSprite->Draw(window);
	}

	SpriteAnimatorGo::Draw(window);
}

void SCUnit::SellThis()
{
	//TO-DO ������ ���� �ִϸ��̼� ���
	sceneGame->SetMineral(sceneGame->GetMineral() + sellingValue); // �ڽ��� �ǸŰ���
	sceneGame->message(SceneGame::MessageType::SellUnit);
	sceneGame->message(sellingValue);

	sceneGame->RemoveGo(this);
}

void SCUnit::SetStatus(Status status)
{
	currentStatus = status;
	if (status == Status::ATTACK)
	{
		animator->Stop();
	}
}

void SCUnit::SetSelect(bool isSelect)
{
	this->isSelect = isSelect;
	isSelectSprite->SetActive(isSelect);
}

void SCUnit::Astar(sf::Vector2f dest)
{
	// BEST f 점수
	std::vector<std::vector<int>> best
		(size, std::vector<int>(size, INT32_MAX));

	// 부모 노드 추적 기본값 -1 ,-1
	std::vector<std::vector<sf::Vector2i>> parent
		(size, std::vector<sf::Vector2i>(size, {-1, -1}));

	// CLOSED LIST 방문 여부 [x][y] = 방문 했는지
	std::vector<std::vector<bool>> closed
		(size, std::vector<bool>(size, false));

	// OPEN LIST
	std::priority_queue<Node> openList;

	// 목적지 인덱스 변환
	sf::Vector2i destIndex = { (int)dest.x / 32 , (int)dest.y / 32 };
	sf::Vector2i startIndex = { (int)GetPosition().x / 32 ,(int)GetPosition().y / 32 };

	// 초기값 
	{
		int g = 0;
		int h = { std::abs((destIndex.x - startIndex.x)) + 
			std::abs((destIndex.y - startIndex.y)) };

		openList.push(Node(g + h , g , startIndex));
		best[startIndex.x][startIndex.y] = g + h;
		parent[startIndex.x][startIndex.y] = startIndex;
	}

	while (!openList.empty())
	{
		Node node = openList.top();
		openList.pop();

		// 이미 방문햇을경우
		if (closed[node.pos.x][node.pos.y])
			continue;

		// 이미 더좋은 cost 가 있을경우
		if (best[node.pos.x][node.pos.y] < node.f)
			continue;

		// 방문
		closed[node.pos.x][node.pos.y] = true;

		// 목적지에 도착했을 경우
		if (node.pos == destIndex)
			break;

		// 상하좌우 대각선 

		for (int dir = 0; dir < (int)Dir::COUNT; dir++)
		{
			sf::Vector2i nextPos = node.pos + front[dir];

			if (!CanGo(nextPos))
				continue;

			if (closed[nextPos.x][nextPos.y])
				continue;

			int g = node.g + cost[dir];
			int h = { std::abs((destIndex.x - startIndex.x)) +
				std::abs((nextPos.y - nextPos.y)) };

			if (best[nextPos.x][nextPos.y] <= g + h)
				continue;
			
			best[nextPos.x][nextPos.y] = g + h;

			// open list 에 추가
			openList.push(Node(g + h, g, nextPos));
			parent[nextPos.x][nextPos.y] = node.pos;

		}
	}

	path.clear();
	pos = destIndex;

	while (true)
	{
		path.push_back(pos);

		// 시작점 일경우
		if (pos == startIndex)
			break;

		pos = parent[pos.x][pos.y];
	}

	std::reverse(path.begin() , path.end());

	isAster = true;
}

bool SCUnit::CanGo(sf::Vector2i pos)
{
	// 여기서 타일의 타입 && 인덱스 예외처리
	
	if (pos.x < 0 || pos.x > size || pos.y < 0 || pos.y > size)
	{
		return false;
	}

	return true;

}
