#include "pch.h"

int main()
{
   // sf::Style::Fullscreen
    FRAMEWORK.Init(1365, 768, "MapleRandomDefense" , sf::Style::Fullscreen);
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}