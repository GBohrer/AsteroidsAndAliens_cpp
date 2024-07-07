#include "../include/master_header.h"


Player::Player() {}

Player::Player(Vector2 pos) {
    SetPosition(pos.x, pos.y);
    SetVelocity({0.0f, 0.0f}, 100.0f, -100.0f);
    SetAcceleration({0.0f, 0.0f}, 2.0f, -2.0f);
    SetLife(100.0f, 100.0f, 0.0f);
    SetAimTarget(pos);
    SetHitBox();

    SetMaxSpeed(5.0f);
    SetCurrentSpeed(GetMaxSpeed());
    SetDirection({0,0});
    SetMaxLife(100.0f);
    SetCurrentLife(GetMaxLife());
}

// GETTERS & SETTERS
Rectangle Player::GetHitBox() {
    return hitbox;
}

void Player::SetHitBox() {
    this->hitbox.width = 20.0f;
    this->hitbox.height = 20.0f;
    this->hitbox.x = GetPosition().x - hitbox.width/2.0f;
    this->hitbox.y = GetPosition().y - hitbox.height/2.0f;
}

Vector2 Player::GetAimTarget() {
    return aimTarget;
}

void Player::SetAimTarget(Vector2 target) {
    this->aimTarget = target;
}


//METHODS
void Player::Move(float delta) {

    Vector2 force = GetVelocity().current;
    float min = GetVelocity().min;
    float max = GetVelocity().max;

    if (IsKeyDown(KEY_W)) { force.y -= 5.0f; }
    if (IsKeyDown(KEY_A)) { force.x -= 5.0f; }
    if (IsKeyDown(KEY_S)) { force.y += 5.0f; }
    if (IsKeyDown(KEY_D)) { force.x += 5.0f; }

    if (force.x > max) { force.x = max; }
    else if (force.x < min) { force.x = min; }

    if (force.y > max) { force.y = max; }
    else if (force.y < min) { force.y = min; }

    SetVelocity(force.x + GetAcceleration().current.x * delta,
                force.y + GetAcceleration().current.y * delta);

    SetPosition(GetPosition().x + GetVelocity().current.x * delta,
                GetPosition().y + GetVelocity().current.y * delta);

    SetHitBox();
}

void Player::UpdateAim(float delta) {

    Vector2 mouseDelta = GetMouseDelta();
    Vector2 dir = GetVelocity().current;
    Vector2 newAimTarget = {GetAimTarget().x + mouseDelta.x + dir.x * delta,
                            GetAimTarget().y + mouseDelta.y + dir.y * delta};
    
    SetAimTarget(newAimTarget);
}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

void Player::DrawAim() {
    Vector2 dir = {GetPosition().x - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).x * 100.0f,
                   GetPosition().y - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).y * 100.0f};

    DrawLineEx(dir, GetPosition(), 3, GREEN);
}

void Player::DrawHealthBar () {
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetLife().max, 10, RED);                 
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetLife().current, 10, GREEN);                 

}

