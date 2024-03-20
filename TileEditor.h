#pragma once
#include "GameObject.h"
#include "TileSet.h"

class TileSet;
class SceneTilemapEditor;

class TileEditor :
    public GameObject
{

protected:
    sf::RectangleShape selectBox;
    sf::RectangleShape typeselectBox;
    TileSet::TileType selectedType;
    
public:


};

