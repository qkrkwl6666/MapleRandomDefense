#include "pch.h"
#include "Animator.h"
#include "rapidcsv.h"

Animator::Animator()
{

}

Animator::~Animator()
{
	
}

void Animator::AddEvent(const std::string& clipId, int frame , std::function<void()> action)
{
	eventList.push_back({ clipId , frame , action});
}

void Animator::ClearEvent()
{
	eventList.clear();
}

void Animator::AddClip(const AnimationClip& clip)
{
	if (clips.find(clip.id) == clips.end())
	{
		//clips.insert({ clip.id , clip });
		clips[clip.id] = clip;
	}
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::Update(float dt)
{
	if (this == nullptr)
	{
		return;
	}

	// �÷��̰� �ƴѰ�쿡�� return
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt * speed;
	
	if (accumTime < clipDuration)
	{
		return;
	}
	accumTime = 0.f;

	++currentFrame;

	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id = queue.front();
			queue.pop();
			Play(id, false);
			return;
		}

		switch (currentClip->loopType)
		{
			case AnimationLoopTypes::SINGLE:
				currentFrame = totalFrame - 1;
				isPlaying = false;
				break;
			case AnimationLoopTypes::LOOP:
				currentFrame = 0;
				break;
		}
	}

	for (auto& event : eventList)
	{
		if (currentClip->id == event.clipId && currentFrame == event.frame)
		{
			if (event.action != nullptr)
			{
				event.action();
			}
		}
	}

	if (currentFrame >= totalFrame)
		return;

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Update(float dt, Angle currentAngle)
{
	if (this == nullptr)
	{
		return;
	}

	// �÷��̰� �ƴѰ�쿡�� return
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt * speed;

	if (accumTime < clipDuration)
	{
		return;
	}
	accumTime = 0.f;

	if (currentFrame == -1 || currentAngle != beforeAngle)
	{
		currentFrame = static_cast<int>(currentAngle) * currentClip->frame;
		totalFrame = currentFrame + currentClip->frame - 1;
	}

	++currentFrame;

	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id = queue.front();
			queue.pop();
			Play(id, true , true , currentAngle);
			return;
		}

		switch (currentClip->loopType)
		{
			case AnimationLoopTypes::SINGLE:
				currentFrame = totalFrame - 1;
				isPlaying = false;
				break;
			case AnimationLoopTypes::LOOP:
				currentFrame = currentClip->frame * static_cast<int>(currentAngle);
				break;
		}
	}

	for (auto& event : eventList)
	{
		if (currentClip->id == event.clipId && currentFrame == event.frame)
		{
			if (event.action != nullptr)
			{
				event.action();
			}
		}
	}

	beforeAngle = currentAngle;
	if (currentFrame >= totalFrame)
		return;
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	target->setTexture(frame.GetTexture());

	target->setTextureRect(frame.texCoord);
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	// clipId�� find�Ҷ��� �۵�

	isPlaying = true;
	accumTime = 0.f;
	currentClip = &clips[clipId];
	currentFrame = 0;

	totalFrame = currentClip->GetTotalFrame();

	clipDuration = 1.f / currentClip->fps; // 0.333
	SetFrame(currentClip->frames[0]);
	
}

void Animator::Play(const std::string& clipId, bool clearQueue, bool isAngle, Angle currentAngle)
{
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	// clipId�� find�Ҷ��� �۵�

	isPlaying = true;
	accumTime = 0.f;
	currentClip = &clips[clipId];
	currentFrame = currentFrame = static_cast<int>(currentAngle) * currentClip->frame;
	if (!isAngle)
	{
		totalFrame = currentClip->GetTotalFrame();
	}
	else
	{
		totalFrame = currentClip->frame;
		this->isAngle = isAngle;
	}

	clipDuration = 1.f / currentClip->fps; // 0.333
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::PlayIdle(const std::string& clipId, bool clearQueue, Angle currentAngle)
{
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	// clipId�� find�Ҷ��� �۵�
	accumTime = 0.f;
	isPlaying = true;

	currentClip = &clips[clipId];
	clipDuration = 1.f / currentClip->fps; // 0.333
	SetFrame(currentClip->frames[static_cast<int>(currentClip->frame) 
		* static_cast<int>(currentAngle)]);
}

void Animator::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	//rapidcsv::Document doc(filePath , rapidcsv::LabelParams(0, -1));

	rapidcsv::Document doc(filePath);

	id = doc.GetCell<std::string>(0, 0);
	//id = filePath;
	fps = doc.GetCell<int>(1, 0);

	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	// ���� ó��
	if (doc.GetCell<std::string>(3, 0) != "")
	{
		frame = doc.GetCell<int>(3, 0);
	}

	for (int i = 3; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);

		if (row[0] == "")
		{
			continue;
		}
		frames.push_back({ row[0] , {std::stoi(row[1]),std::stoi(row[2]),
			std::stoi(row[3]),std::stoi(row[4])}, std::stoi(row[5]) });
	}

	return true;
}
