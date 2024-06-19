#pragma once
#include "../master_header.h"

#include "bullet.h"

enum GameState {
    Menu,
    InGame,
    GameOver,
    Paused
};

class Game {

    public:
        Game();

        void Start(std::string nickname);
        void Reset();
        void UpdateAnimationTime();
        float GetDeltaT();
        bool CheckDifficultyIncrease(int score);
        void IncreaseDifficulty();
        GameState GetGameState();
        void SetGameState(GameState state);

        std::vector<Vector2>& GetCurrentLevelBounds();
        void SetCurrenLevelBounds(std::vector<Vector2> level_bounds);

        std::vector<Entity>& GetCurrentAsteroidsInGame();
        void SetCurrentAsteroidsInGame();

        //ALIENS
        std::vector<Alien>& GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens();
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

        bool CollisionAlienAlien(Alien a1, Alien a2);
        bool CollisionAlienPlayer(Alien a);
        void CheckAlienCollisions();

        //BULLETS
        std::vector<Bullet>& GetCurrentBullets();
        int GetBulletsInGame();
        void SpawnBullets();
        void UpdateBulletInGame(Bullet bullet, int position);
        void DeleteBulletInGame(int position);

        bool CollisionBulletAlien(Bullet b, Alien a);
        bool CollisionBulletPlayer(Bullet b);
        void CheckBulletCollisions();

        //PLAYER
        Player& GetPlayer();
        void SetPlayer(Player p);
        void PlayerMove();
        void UpdatePlayerScore();

        //CAMERA
        Camera2D& GetCamera();
        void SetCamera();
        void SetCameraZoom(float zoom);
        void UpdateCamera(int screenWidth, int screenHeight);

        void CheckEntityCollisions();

    protected:
        int totalAliens;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        int scoreThreshold;


    private:
        GameState state;
        std::vector<Vector2> currentLevelBounds;
        std::vector<Entity> asteroidsInGame;
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        Player player;
        Camera2D camera;
        
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;
};

