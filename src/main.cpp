
#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/main.hpp"
#include "include/hud.hpp"
#include "include/intro.hpp"
#include "include/game.hpp"

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
                    Color {255, 255, 255, 255},
                    "START GAME",
                    Color {0, 0, 0, 255}
                )) {
                GoToSavesMenu();
            }
            if(CreateBasicButton(
                    vf2d  (100.0f, 270.0f),
                    vf2d  (40 + MeasureText("QUIT", 20), 50.0f),
                    Color {255, 255, 255, 255},
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

            if(CreateBasicButton(
                    vf2d  (100.0f, 200.0f),
                    vf2d  (40 + MeasureText("NEW LOAD", 20), 50.0f),
                    Color {255, 255, 255, 255},
                    "NEW LOAD",
                    Color {0, 0, 0, 255}
                ))
                StartGame();

        };
}; SavesMenu _SavesMenu;
//----------------------------------------------------------------------------------------


// Binding functions
//----------------------------------------------------------------------------------------
void SetupWindow()
{
    SetExitKey (0);
    // ToggleFullscreen();
    SetTargetFPS (300);
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
    SetActiveScreen (nullptr);

    InitGame();
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
                
                break;

            case GameStates::PAUSE:
                
                break;
        };

        //----------------------------------------------------------------------------------------
        BeginDrawing();

            DrawFPS (5 * screenScale, 5 * screenScale);

            DrawScreen();

        EndDrawing();
        //----------------------------------------------------------------------------------------
    };

    UnloadFont(_8_bit_Limit);
    CloseWindow();

    return 0;
}