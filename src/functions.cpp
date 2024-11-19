#include "../include/master.hpp"


// GAME

std::unordered_map<State, GameState> GameStateInit () {
    std::unordered_map<State, GameState> gameStates;
    std::vector<std::shared_ptr<UIObject>> screenObjs;

    // START_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Press Enter", 40, SCREEN_POS_CENTER, true, true)
    };
    gameStates.emplace(State::START_MENU, GameState(State::START_MENU, screenObjs));
    screenObjs.clear();

    // MAIN_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::PLAY, std::vector<std::string>{"Play"}, SCREEN_POS_CENTER_1, false, true),
        std::make_shared<TextBox>(BoxID::LEADERBOARD, std::vector<std::string>{"Leaderboard"}, SCREEN_POS_CENTER_2, false, true),
        std::make_shared<TextBox>(BoxID::OPTIONS, std::vector<std::string>{"Options"}, SCREEN_POS_CENTER_3, false, true),
        std::make_shared<TextBox>(BoxID::ABOUT, std::vector<std::string>{"About"}, SCREEN_POS_CENTER_4, false, true),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_5, false, true),
    };
    gameStates.emplace(State::MAIN_MENU, GameState(State::MAIN_MENU, screenObjs));
    screenObjs.clear();

    // SCORES_MENU
    screenObjs = {
        std::make_shared<SimpleText>("LEADERBOARD", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("ABC   12000", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<TextBox>(BoxID::SEE, std::vector<std::string>{"See"}, SCREEN_POS_CENTER_LEFT_1, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::SCORES_MENU, GameState(State::SCORES_MENU, screenObjs));
    screenObjs.clear();

    // OPTIONS_MENU
    screenObjs = {
        std::make_shared<SimpleText>("OPTIONS", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Screen Mode:", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_LEFT_1, false, false),
        std::make_shared<TextBox>(BoxID::SCREEN_MODE, std::vector<std::string>{"Windowed", "FullScreen"}, SCREEN_POS_CENTER_1, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM, false, true),
    };
    gameStates.emplace(State::OPTIONS_MENU, GameState(State::OPTIONS_MENU, screenObjs));
    screenObjs.clear();

    // ABOUT_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("You are lost in deep space. You have only one spacechip.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<SimpleText>("Aliens lives in deep space and are not friendly.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_2, false, false),
        std::make_shared<SimpleText>("Endure. Survive. Explore.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_3, false, false),
        std::make_shared<SimpleText>("Created by GAB", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_5, false, false),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM, false, true),
    };
    gameStates.emplace(State::ABOUT_MENU, GameState(State::ABOUT_MENU, screenObjs));
    screenObjs.clear();

    // GAME
    screenObjs = {
        std::make_shared<SimpleText>("Score: 0", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::ABORT, std::vector<std::string>{"Abort Mission"}, SCREEN_POS_LEFT_BOTTOM, false, true),
    };
    gameStates.emplace(State::GAME, GameState(State::GAME, screenObjs));
    screenObjs.clear();

    // PAUSE
    screenObjs = {
        std::make_shared<SimpleText>("PAUSED", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER, false, false),
        std::make_shared<TextBox>(BoxID::RESUME, std::vector<std::string>{"Continue"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::ABORT, std::vector<std::string>{"Abort"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::PAUSE, GameState(State::PAUSE, screenObjs));
    screenObjs.clear();

    // GAMEOVER
    screenObjs = {
        std::make_shared<SimpleText>("GAME OVER", TITLE_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<TextBox>(BoxID::RESUME, std::vector<std::string>{"Next"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::GAMEOVER, GameState(State::GAMEOVER, screenObjs));
    screenObjs.clear();

    // SAVE_MENU
    screenObjs = {
        std::make_shared<SimpleText>("MISSION SCORE", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Save score in Leaderboard?", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_4, false, false),
        std::make_shared<TextBox>(BoxID::YES, std::vector<std::string>{"Yes"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::NO, std::vector<std::string>{"No"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::SAVE_MENU, GameState(State::SAVE_MENU, screenObjs));
    screenObjs.clear();

    // LEAVING
    screenObjs = {
        std::make_shared<SimpleText>("ARE YOU SURE?", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true)
    };
    gameStates.emplace(State::LEAVING, GameState(State::LEAVING, screenObjs));
    screenObjs.clear(); 
    
    return gameStates;
}

GameInfo GameInfoInit() {
    GameInfo info;
    info.isGameRunning = true;
    info.debugMode = false;

    info.gameStates = GameStateInit();
    info.currentGameState = info.gameStates.at(State::START_MENU);

    //info.gameImages = LoadGameImages();
    return info;
}

std::unique_ptr<ECSManager> GameECSManagerInit() {

    auto ecs = std::make_unique<ECSManager>();
    ecs->Init();

    // Component:
    ecs->RegisterComponent<Transform>();
    ecs->RegisterComponent<Velocity>();
    ecs->RegisterComponent<Acceleration>();
    ecs->RegisterComponent<Vitality>();
    ecs->RegisterComponent<Input>();
    ecs->RegisterComponent<EState>();

    // System:
    auto movementSys = ecs->RegisterSystem<MovementSystem>();
    {
        Signature sig;
        sig.set(ecs->GetComponentType<EState>());
        sig.set(ecs->GetComponentType<Transform>());
        sig.set(ecs->GetComponentType<Velocity>());
        sig.set(ecs->GetComponentType<Acceleration>());
        ecs->SetSystemSignature<MovementSystem>(sig);
    }
    movementSys->Init();

    auto inputSys = ecs->RegisterSystem<PlayerInputSystem>();
    {
        Signature sig;
        sig.set(ecs->GetComponentType<Input>());
        sig.set(ecs->GetComponentType<EState>());
        ecs->SetSystemSignature<PlayerInputSystem>(sig);
    }
    inputSys->Init();

    return ecs;

}


// MISSION

void CreatePlayer(std::shared_ptr<ECSManager> ecs) {

    Entity player;
    player = ecs->CreateEntity();

    ecs->AddComponent(
        player,
        Transform {
            .translation = Vector3({SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 1.0f}),
            .rotation = Quaternion({1.0f, 1.0f, 1.0f, 1.0f}),
            .scale = Vector3({15.0f, 15.0f, 15.0f})
        });
    ecs->AddComponent(
        player,
        Velocity {
            .current = Vector2({0.0f, 0.0f}),
            .max = 200.0f,
            .min = -200.0f
        });
    ecs->AddComponent(
        player,
        Acceleration {
            .current = Vector2({0.0f, 0.0f}),
            .max = 20.0f,
            .min = 0.0f
        });
    ecs->AddComponent(
        player,
        EState {
            EttState::IDLE
        });
}

void CreateAsteroids(std::shared_ptr<ECSManager> ecs) {
 std::vector<Entity> asteroids (MAX_ENTITIES);
    int teste = 20;

    for (auto& asteroid : asteroids) {
        asteroid = ecs->CreateEntity();


        ecs->AddComponent(
            asteroid,
            Transform {
                .translation = Vector3({100.0f + teste , 100.0f, 1.0f}),
                .rotation = Quaternion({1.0f, 1.0f, 1.0f, 1.0f}),
                .scale = Vector3({5.0f, 5.0f, 5.0f})
            });

        ecs->AddComponent(
            asteroid,
            Velocity {
                .current = Vector2({0.0f, 0.0f}),
                .max = 200.0f,
                .min = -200.0f
            });

        ecs->AddComponent(
            asteroid,
            Acceleration {
                .current = Vector2({2.5f, 2.5f}),
                .max = 10.0f,
                .min = 0.0f
            });

        ecs->AddComponent(
            asteroid,
            EState {
                EttState::IDLE
            });

        teste += 10;
    }

}

void CreateAliens(std::shared_ptr<ECSManager> ecs) {

}