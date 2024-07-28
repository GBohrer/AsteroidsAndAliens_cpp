#include "../include/master_header.h"


Game::Game() {
    SetInitialGameStates();
    currentGameState = GetGameStates().at(State::InMenu);
}

void Game::Start() {
    SetCurrentGameState(GetGameStates().at(State::InGame));
    isGameOver = false;
    LevelMap.Set();
    this->player = Player(Vector2Scale(GetGameLevelMap().GetCurrentLevelBounds().back(), 0.5f));
    SetCamera();
    SetMousePosition((int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f);
}

void Game::Reset() {
    currentGameState = GetGameStates().at(State::InMenu);
    LevelMap.Reset();
}

void Game::CheckGameState() {
    if (isGameOver) SetCurrentGameState(GetGameStates().at(State::GameOver));
}

LevelMap Game::GetGameLevelMap() {
    return this->LevelMap;
}


// GAME STATE:
std::unordered_map<State, GameStateInfo>& Game::GetGameStates() {
    return gameStates;
}

void Game::SetInitialGameStates() {

    //TEXT BOXES
    TextBox start(TextBoxId::Start,"Start", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox restart(TextBoxId::Restart,"Restart", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox exit(TextBoxId::Exit,"Exit", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 200, 230, 70 });
    TextBox resume(TextBoxId::Resume,"Resume", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox menu(TextBoxId::Menu,"Menu", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 300, 230, 70 });
    TextBox loading(TextBoxId::Loading,"Loading...", { (int)GetScreenWidth()/2.0f - 140, (int)GetScreenHeight()/2.0f + 100, 230, 70 });

    GameStateInfo state1(State::InMenu, {start,exit});
    GameStateInfo state2(State::InGame, {});
    GameStateInfo state3(State::Paused, {resume,exit});
    GameStateInfo state4(State::GameOver, {restart,menu,exit});
    GameStateInfo state5(State::IsLoading, {loading});

    this->gameStates.insert({{State::InMenu,state1}, 
                             {State::InGame,state2}, 
                             {State::Paused, state3}, 
                             {State::GameOver,state4},
                             {State::IsLoading,state5}});
}

GameStateInfo Game::GetCurrentGameState () {
    return currentGameState;
}

void Game::SetCurrentGameState(GameStateInfo gameStateInfo) {
    this->currentGameState = gameStateInfo;
}

void Game::UpdateCurrentGameStateTextBox (TextBox tb, int position) {
    this->currentGameState.text_boxes[position] = tb;
}

Vector2 Game::GetLastMousePosition() {
    return LastMousePosition;
}

void Game::SetLastMousePosition(Vector2 mouse) {
    this->LastMousePosition = mouse;
}


// PLAYER
Player& Game::GetPlayer() {
    return player;
}

void Game::SetPlayer(Player p) {
    this->player = player;
}

void Game::UpdatePlayer() {

    EntityVelocity v = GetPlayer().GetVelocity();

    //Check Spaceship Fuel:
    if (v.current.x != 0.0f || v.current.y != 0.0f) {
        Spaceship s = GetPlayer().GetSpaceshipStats();
        float new_current_fuel = s.currentFuel - ((0.0001f * (abs(v.current.x) + abs(v.current.y))) / s.fuelInfo.burningEfficiency);
        
        PrintTextInGame(true, s.currentFuel - new_current_fuel, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 220.0f}, 20, WHITE);
        GetPlayer().UpdateSpaceshipCurrentFuel(new_current_fuel);
    }
    if (GetPlayer().GetSpaceshipStats().currentFuel <= 0.0f) isGameOver = true;

    //Player Move:
    this->player.Move(GetGameLevelMap().GetDeltaT());
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) GetPlayer().SetVelocity(0.0f, 0.0f);
    this->player.UpdateAim(GetGameLevelMap().GetDeltaT());
}


// CAMERA 2D
Camera2D& Game::GetCamera() {
    return camera;
}

void Game::SetCamera() {
    camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.target = GetPlayer().GetPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;
}

void Game::SetCameraZoom(float zoom){
    this->camera.zoom = zoom;
}

void Game::UpdateCamera(int screenWidth, int screenHeight) {

    ////////// ZOOM
    float camera_zoom = camera.zoom;
    camera_zoom += GetMouseWheelMove() * 0.1f;

    if (camera_zoom > 2.0f) camera_zoom = 2.0f;
    else if (camera_zoom < 0.25f) camera_zoom = 0.25;
    SetCameraZoom(camera_zoom);

    ////////// OFFSET and TARGET

    this->camera.target = GetPlayer().GetPosition();
}


// COLLISIONS
bool Game::CollisionAlienAlien(Alien a1, Alien a2) {
    return CheckCollisionCircles(a1.GetPosition(), static_cast<float>(a1.GetRadius()), a2.GetPosition(), static_cast<float>(a2.GetRadius()));
}

bool Game::CollisionAlienPlayer(Alien a) {
    return CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), GetPlayer().GetHitBox());
}

bool Game::CollisionAlienAsteroid(Alien a,Asteroid ast) {
    return CheckCollisionCircles(a.GetPosition(), a.GetRadius(), ast.GetPosition(), ast.GetRadius());
}

void Game::CheckAlienCollisions() {
    if (GetAliensInGame() == 0) return;

    // ALIEN-PLAYER
    int a_index = 0;
    for (Alien& a : GetCurrentAliens()) {
        if (CollisionAlienPlayer(a)) {
            isGameOver = true;
            return;
        }

        bool alien_collision = false;

        // ALIEN-ASTEROID
        int ast_index = 0;
        for (Asteroid& ast : GetCurrentAsteroids()) {
            if (CollisionAlienAsteroid(a, ast)) {
                alien_collision = true;
                const auto velocities = CollisionResponse(a.GetVelocity().current, ast.GetVelocity().current,
                                                          a.GetPosition(), ast.GetPosition(),
                                                          a.GetRadius(), ast.GetRadius() + 30.0f);
                Vector2 new_velocity = std::get<0>(velocities); 
                a.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAlienInGame(a, a_index);

                new_velocity = std::get<1>(velocities); 
                ast.SetVelocity(new_velocity.x, new_velocity.y);
                ast.Move(GetGameLevelMap().GetDeltaT());
                UpdateAsteroidInGame(ast, ast_index);
            }
            ast_index++;
        }

        // ALIEN-ALIEN
        int aa_index = 0;
        for (Alien& aa : GetCurrentAliens()) {
            if (&a != &aa && CollisionAlienAlien(a, aa)) {
                alien_collision = true;

                const auto velocities = CollisionResponse(a.GetVelocity().current, aa.GetVelocity().current,
                                                          a.GetPosition(), aa.GetPosition(),
                                                          a.GetRadius(), aa.GetRadius());
                Vector2 new_velocity = std::get<0>(velocities); 
                a.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAlienInGame(a, a_index);

                new_velocity = std::get<1>(velocities); 
                aa.SetVelocity(new_velocity.x, new_velocity.y);
                aa.Move(GetGameLevelMap().GetDeltaT());
                UpdateAlienInGame(aa, aa_index);
                break;
            }
            aa_index++;
        }

        if (!alien_collision) {
            a.Move(GetGameLevelMap().GetDeltaT());
            a.UpdateDirection(GetPlayer());
            UpdateAlienInGame(a, a_index);
        }
        a_index++;
    }
}

bool Game::CollisionBulletAlien(Bullet b, Alien a) {
    return CheckCollisionCircleRec(a.GetPosition(), static_cast<float>(a.GetRadius()), b.GetHitBox());
}

bool Game::CollisionBulletPlayer(Bullet b) {
    return CheckCollisionRecs(b.GetHitBox(), GetPlayer().GetHitBox());
}

// BULLETS
void Game::CheckBulletCollisions() {
    if (GetBulletsInGame() == 0) return;

    int b_index = 0;
    for (Bullet& b : GetCurrentBullets()) {
        if (b.IsOutOfBounds(GetPlayer().GetPosition())) {
            DeleteBulletInGame(b_index);
            continue;
        }

        if (CollisionBulletPlayer(b)) {
            GetPlayer().UpdateCurrentLife(GetPlayer().GetLife().current - (b.GetDamage() / 2.0f));
            DeleteBulletInGame(b_index);

            if (GetPlayer().GetLife().current <= 0) {
                isGameOver = true;
            }
        } else {
            b.Move(GetGameLevelMap().GetDeltaT());
            UpdateBulletInGame(b, b_index);
        }

        int a_index = 0;
        for (Alien& a : GetCurrentAliens()) {
            if (CollisionBulletAlien(b, a)) {
                a.UpdateCurrentLife(a.GetLife().current - b.GetDamage());
                if (a.GetLife().current <= 0) {
                    DeleteAlienInGame(a_index);
                }
                DeleteBulletInGame(b_index);
                break;
            }
            a_index++;
        }
        b_index++;
    }
}

bool Game::CollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2) {
    return CheckCollisionCircles(ast1.GetPosition(), ast1.GetRadius(), ast2.GetPosition(), ast2.GetRadius());
}

bool Game::CollisionAsteroidBullet(Asteroid ast, Bullet b) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), b.GetHitBox());
}

bool Game::CollisionAsteroidPlayer(Asteroid ast) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), GetPlayer().GetHitBox());
}

// ASTEROIDS
void Game::CheckAsteroidCollisions() {
    if (GetAsteroidsInGame() == 0) return;

    int ast_index = 0;
    for (Asteroid& ast : GetCurrentAsteroids()) {
        bool delete_asteroid = false;

        //if (ast.IsOutOfBounds(GetGameLevelMap().GetCurrentLevelBounds())) {
        //    ast.UpdateCurrentLife(ast.GetLife().current - 1.0f);
        //    if (ast.GetLife().current <= 0) delete_asteroid = true;
        //}

        // ASTEROID-BULLET
        int b_index = 0;
        for (Bullet& b : GetCurrentBullets()) {
            if (CollisionAsteroidBullet(ast, b)) {
                ast.UpdateCurrentLife(ast.GetLife().current - b.GetDamage());
                DeleteBulletInGame(b_index);
                if (ast.GetLife().current <= 0) delete_asteroid = true;
            }
            b_index++;
        }

        // ASTEROID-PLAYER
        if (CollisionAsteroidPlayer(ast)) {
            const auto velocities = CollisionResponse(ast.GetVelocity().current, GetPlayer().GetVelocity().current,
                                                      ast.GetPosition(), GetPlayer().GetPosition(),
                                                      ast.GetRadius(), GetPlayer().GetHitBox().width);
            Vector2 new_velocity = std::get<0>(velocities);                                          
            ast.SetVelocity(new_velocity.x, new_velocity.y);
            UpdateAsteroidInGame(ast, ast_index);

            new_velocity = std::get<1>(velocities);
            GetPlayer().SetVelocity(new_velocity.x, new_velocity.y);
        }

        // ASTEROID-ASTEROID
        int ast2_index = 0;
        for (Asteroid& ast2 : GetCurrentAsteroids()) {
            if (&ast != &ast2 && CollisionAsteroidAsteroid(ast, ast2)) {
                const auto velocities = CollisionResponse(ast.GetVelocity().current, ast2.GetVelocity().current,
                                                          ast.GetPosition(), ast2.GetPosition(),
                                                          ast.GetRadius(), ast2.GetRadius());
                Vector2 new_velocity= std::get<0>(velocities);
                ast.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAsteroidInGame(ast, ast_index);

                new_velocity = std::get<1>(velocities);
                ast2.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAsteroidInGame(ast2, ast2_index);
            }
            ast2_index++;
        }

        ast.Move(GetGameLevelMap().GetDeltaT());
        UpdateAsteroidInGame(ast, ast_index);

        if (delete_asteroid) DeleteAsteroidInGame(ast_index);
        ast_index++;
    }
}

void Game::CheckEntityCollisions() {
    CheckAlienCollisions();
    CheckBulletCollisions();
    CheckAsteroidCollisions();
}


std::tuple<Vector2, Vector2> Game::CollisionResponse (Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2) {

    Vector2 C1 = Vector2Subtract(pos1,pos2);
    Vector2 C2 = Vector2Subtract(pos2,pos1);

    float value1 = (2 * m2) / (m1 + m2);
    float value2 = Vector2DotProduct(v1,C1) - Vector2DotProduct(v2,C1);
    float value3 = Vector2LengthSqr(C1);

    Vector2 new_velocity1 = Vector2Subtract(v1, (Vector2Scale(C1,(value1 * value2 / value3))));

    value1 = (2 * m1) / (m1 + m2);
    value2 = Vector2DotProduct(v2,C2) - Vector2DotProduct(v1,C2);
    value3 = Vector2LengthSqr(C2);

    Vector2 new_velocity2 = Vector2Subtract(v2, (Vector2Scale(C2,(value1 * value2 / value3))));

    return {new_velocity1, new_velocity2};

}