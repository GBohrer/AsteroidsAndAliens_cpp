#pragma once
#include "../master_header.h"

#include "character.h"

class Player : public Character {

public:
    Player(); 
    Player(std::string name);
    
    std::string GetName();
    void SetName(std::string name);
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);

    Rectangle GetHitBox();
    void SetHitBox();
    void DrawHitBox();

    void Move();

private:
    Rectangle hitbox;
    std::string name;
    int score;
    bool isBuffed;


};