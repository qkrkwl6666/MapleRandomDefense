#include "pch.h"
#include "Interface.h"

Interface::Interface(const std::string& name)
{
}

Interface::~Interface()
{
}

void Interface::Init()
{

	UiInit();
	ObjectsSort();
}

void Interface::Release()
{
}

void Interface::Reset()
{
}

void Interface::Update(float dt)
{
}

void Interface::LateUpdate(float dt)
{
}
