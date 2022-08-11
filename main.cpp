
#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/main.hpp"
#include "include/hud.hpp"
#include "include/intro.hpp"
#include "include/gameplay.hpp"



//----------------------------------------------------------------------------------------
enum class GameStates
{
    LAUNCHING, LOADING,

    INTRO    ,
    MENU     , SAVES_MENU,
    PLAYING  , PAUSE     , DEFEAT,
    QUITTING

    // CREDITS // Credits after the end of the game.
}; GameStates _GameState = GameStates::LAUNCHING;
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
class Intro : public ActiveScreen
{
    public:
        void Draw() override
        {
             ClearBackground (Color {38, 36, 40});

            if (_TimeAccumilator < 5.0f && _GameState != GameStates::MENU) {
                _TimeAccumilator += GetFrameTime();
                DrawTitle (GetFrameTime());
            } else if (_TimeAccumilator = 5.0f) {
                _TimeAccumilator = 0.0f;
                GoToMainMenu();
            }
        };
}; Intro _Intro;
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
class MainMenu : public ActiveScreen
{
    public:
        void Draw() override
        {
            // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 1.0f));
            ClearBackground (Color {105, 105, 105, 255});

            if(CreateBasicButton(
                    vf2d  (100.0f, 200.0f),
                    vf2d  (40 + MeasureText("START GAME", 20), 50.0f),
                    Color {255, 255, 255, 20},
                    "START GAME",
                    Color {0, 0, 0, 255}
                )) {
                GoToSavesMenu();
            }
            if(CreateBasicButton(
                    vf2d  (100.0f, 270.0f),
                    vf2d  (40 + MeasureText("QUIT", 20), 50.0f),
                    Color {255, 255, 255, 20},
                    "QUIT",
                    Color {0, 0, 0, 255}
                ))
                QuitApplication();

        };
}; MainMenu _MainMenu;
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
class SavesMenu : public ActiveScreen
{
    public:
        void Draw() override
        {
            // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 1.0f));
            ClearBackground (Color {0, 0, 0, 255});

            CreateBasicButton(
                    vf2d  (100.0f, 200.0f),
                    vf2d  (40 + MeasureText("NEW LOAD", 20), 50.0f),
                    Color {255, 255, 255, 255},
                    "NEW LOAD",
                    Color {0, 0, 0, 255}
                );

            if(CreateBasicButton(
                    vf2d  (100.0f, 270.0f),
                    vf2d  (40 + MeasureText("NEW GAME",20), 50.0f),
                    Color {255, 255, 255, 255},
                    "NEW GAME",
                    Color {0, 0, 0, 255}
                ))
                StartGame();

        };
}; SavesMenu _SavesMenu;
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
class Playing : public ActiveScreen
{
    void Draw() override
    {
        ClearBackground(Color{255, 255, 255});
    };
};Playing _Playing;    
//----------------------------------------------------------------------------------------


// Binding functions
//----------------------------------------------------------------------------------------
void SetupWindow()
{
    SetExitKey (0);
    // ToggleFullscreen();
    SetTargetFPS (60);
};

void GoToMainMenu()
{
    _GameState = GameStates::MENU;
    SetActiveScreen (&_MainMenu);
};

void UpdateMenu()
{
    if(IsKeyPressed(KEY_ESCAPE))
        QuitApplication();
};

// TODO: Add load system
//---------------------
void GoToSavesMenu()
{
    _GameState = GameStates::SAVES_MENU;
    SetActiveScreen (&_SavesMenu);
};

void StartGame()
{
    _GameState = GameStates::PLAYING;
    SetActiveScreen (&_Playing);

    // InitGame();
};

void QuitApplication()
{
    _GameState = GameStates::QUITTING;
};
//----------------------------------------------------------------------------------------

int main()
{       
    const int screenWidth  = 640;
    const int screenHeight = 360;
          int screenScale  = 2;

    InitWindow (screenWidth * screenScale, screenHeight * screenScale, _NameOfApplicatoin);

    SetupWindow();

//---------------------------------------------------------------------------------------
//Creating Class Objects
//---------------------------------------------------------------------------------------
    Player _player;

    _player.pos = {(float)screenWidth * screenScale * 0.1f, (float)screenHeight * screenScale * 0.6f};
    _player.size = {64, 64};
    _player.vel = {0.0, 0.0};
    _player.gravity = 9.8;
    _player.speed = {100, 35};
    _player.jump = true;
    _player.HP = 100;
    _player.damage = 20;
    _player.damage_counted = false;

    Boss _alcohol;

    _alcohol.pos = {(float)screenWidth * screenScale * 0.8f, (float)screenHeight * screenScale * 0.6f};
    _alcohol.size = {64, 64};
    _alcohol.vel = {0.0, 0.0};
    _alcohol.gravity = 9.8;
    _alcohol.speed = {100, 35};
    _alcohol.HP = 500;
    _alcohol.damage = 10;
    _alcohol.damage_counted = false;

//----------------------------------------------------------------------------------------
//Downloading Textures
//----------------------------------------------------------------------------------------
Texture2D player_idle = LoadTexture("Graphics/Player/Mehses/Idle/Player_idle_spriteshit.png");
Texture2D alcohol_idle = LoadTexture("Graphics/Boss/Meshes/1st_boss_standing_spriteshit.png");
Texture2D player_walking = LoadTexture("Graphics/Player/Mehses/Walking/Player_walking_spriteshit.png");
Texture2D alcohol_walking = LoadTexture("Graphics/Boss/Meshes/1st_boss_walking_spriteshit.png");
    
//---------------------------------------------------------------------------------------
//Creating Animated Objects
//---------------------------------------------------------------------------------------

    AnimatedObject alcohol_anim;
    AnimatedObject player_anim;
    
    alcohol_anim.title = "IDLE";
    alcohol_anim.img = alcohol_idle;
    alcohol_anim.pos = _alcohol.pos; 
    alcohol_anim.frame_amount = 7;
    alcohol_anim.FrameRec = {0.0f, 0.0f, (float)alcohol_anim.img.width/(float)alcohol_anim.frame_amount, (float)alcohol_anim.img.height};
    alcohol_anim.color = WHITE;
    alcohol_anim.frameSpeed = 6;

    player_anim.title = "IDLE";
    player_anim.img = player_idle;
    player_anim.pos = _player.pos;                
    player_anim.frame_amount = 6;
    player_anim.FrameRec = {0.0f, 0.0f, (float)player_anim.img.width/(float)player_anim.frame_amount, (float)player_anim.img.height};
    player_anim.color = WHITE;
    player_anim.frameSpeed = 9;

    _GameState = GameStates::LOADING;
    
    // Initialisation 
    //----------------------------------------------------------------------------------------    
    // TODO: Create function UpdateLodad(), and update in game state.

    _TimeAccumilator = 0.0f;
    _DeltaFade       = 0.0f;
    _TitleFontSize   = 70;

    _8_bit_Limit = LoadFont ("resources/fonts/8-bit-limit.brk.ttf");
    
    //----------------------------------------------------------------------------------------
    // Start of updating game states
    //----------------------------------------------------------------------------------------
    while (!WindowShouldClose() && _GameState != GameStates::QUITTING)
    { 
        switch (_GameState)
        {
            case GameStates::LOADING:
                // UpdateLoad();
                _GameState = GameStates::INTRO;
                SetActiveScreen (&_Intro);
                break;

            case GameStates::INTRO:
                UpdateIntro (GetFrameTime());
                break;

            case GameStates::MENU:
                UpdateMenu();
                break;

            case GameStates::SAVES_MENU:
                
                break;

            case GameStates::PLAYING:
                updateInputs();

                alcohol_anim.DrawAnimatedObject();
                player_anim.DrawAnimatedObject();
                
                break;

            case GameStates::PAUSE:
                
                break;
        };

        //----------------------------------------------------------------------------------------
        BeginDrawing();

            //if(_GameState == GameStates::PLAYING)

            DrawFPS (5 * screenScale, 5 * screenScale);

            DrawScreen();

        EndDrawing();
        //----------------------------------------------------------------------------------------
    };

    UnloadFont(_8_bit_Limit);
    UnloadTexture(alcohol_anim.img);
    UnloadTexture(player_anim.img);
    CloseWindow();

    return 0;
}