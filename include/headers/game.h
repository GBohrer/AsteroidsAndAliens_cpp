#pragma once
#include "../master_header.h"

#include "bullet.h"
#include "asteroid.h"

enum State {
    InMenu,
    InGame,
    GameOver,
    Paused,
    IsLoading
};

typedef struct GameStateInfo {
    State state;
    std::vector<TextBox> text_boxes;

    GameStateInfo() {}
    GameStateInfo(State s, std::vector<TextBox> v) : state(s), text_boxes(v) {}

} GameStateInfo;

class Game {

    public:
        Game();

        void Start();
        void Reset();
        void SetGameLevel();
        bool CheckDifficultyIncrease();
        void IncreaseDifficulty();
        void UpdateAnimationTime();
        float GetDeltaT();

        int GetScore();
        void SetScore(int value);

        //GAME STATE
        std::unordered_map<State, GameStateInfo>& GetGameStates();
        void SetInitialGameStates();
        GameStateInfo GetCurrentGameState();
        void SetCurrentGameState (GameStateInfo gameStateInfo);
        void UpdateCurrentGameStateTextBox (TextBox tb, int position);

        std::vector<Vector2>& GetCurrentLevelBounds();
        void SetCurrenLevelBounds(std::vector<Vector2> level_bounds);

        //ASTEROIDS
        std::vector<Asteroid>& GetCurrentAsteroids();
        int GetAsteroidsInGame();
        void SpawnAsteroids();
        void UpdateAsteroidInGame(Asteroid ast, int position);
        void DeleteAsteroidInGame(int position);

        bool CollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2);
        bool CollisionAsteroidAlien(Asteroid ast, Alien a);
        bool CollisionAsteroidBullet(Asteroid ast, Bullet b);
        bool CollisionAsteroidPlayer(Asteroid ast, Player p);
        void CheckAsteroidCollisions();

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
        void UpdatePlayer();
        bool IsPlayerOutOfBounds();

        //CAMERA
        Camera2D& GetCamera();
        void SetCamera();
        void SetCameraZoom(float zoom);
        void UpdateCamera(int screenWidth, int screenHeight);

        void CheckEntityCollisions();
        std::tuple<Vector2, Vector2> CollisionResponse(Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2);

    protected:
        GameStateInfo currentGameState;
        int totalAliens;
        int totalAsteroids;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        float AsteroidDirectionAngle;
        int scoreThreshold;
        bool isPlayerOutOfBounds;
        float PlayerOutOfBoundsTimer;

        float VoidVelocityDecay;
        float VoidVelocityMin;
        float VoidDecayTimer;


    private:
        std::unordered_map<State, GameStateInfo> gameStates;
        std::vector<Vector2> currentLevelBounds;
        std::vector<Asteroid> asteroidsInGame;
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        Player player;
        Camera2D camera;

        int score;
        
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;
};

