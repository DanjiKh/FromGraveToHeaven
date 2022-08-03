
#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/main.hpp"
#include "include/intro.hpp"
#include "include/hud.hpp"

enum class GameStates
{
    LAUNCHING, LOADING,

    INTRO    ,
    MENU     , SAVES_MENU,
    PLAYING  , PAUSE     , DEFEAT,
    QUITTING

    // CREDITS // Credits after the end of the game.
}; GameStates _GameState = GameStates::LAUNCHING;


void SetupWindow() {
    // SetExitKey(0);
    // ToggleFullscreen();
    // SetTargetFPS (144);
};

class MainMenu : public ActiveScreen
{
    public:
        void Draw() override
        {
            ClearBackground (Color {24, 41, 82});

            CreateBasicButton(
                    vf2d  (100.0f, 200.0f),
                    vf2d  (40 + MeasureText("START GAME", 20), 50.0f),
                    Color {43, 53, 149, 255},
                    "START GAME",
                    Color {112, 69, 175, 255}
                );

        };
};
MainMenu _MainMenu;


void QuitApplication()
{
    _GameState = GameStates::QUITTING;
};

int main()
{       
    const int screenWidth  = 640;
    const int screenHeight = 360;
          int screenScale  = 2;

    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow (screenWidth * screenScale, screenHeight * screenScale, _NameOfApplicatoin);

    SetupWindow();

    GameStates _GameState = GameStates::LOADING;
    
    // Initialisation 
    //----------------------------------------------------------------------------------------    
    // TODO: Create function UpdateLodad(), and update in game state.

    _TimeAccumilator = 0.0f;
    _DeltaFade       = 0.0f;
    _TitleFontSize   = 50;

    _8_bit_Limit = LoadFont ("resources/fonts/8-bit-limit.brk.ttf");

    //----------------------------------------------------------------------------------------
    // Start of updating game states
    //----------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {   
        _TimeAccumilator += GetFrameTime();

        switch (_GameState)
        {
            case GameStates::LOADING:
                // UpdateLoad();
                _GameState = GameStates::INTRO;

                break;

            case GameStates::INTRO:
                UpdateIntro(GetFrameTime());
                break;

            case GameStates::MENU:
                
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
            ClearBackground (Color{38, 36, 40});

            DrawFPS (5 * screenScale, 5 * screenScale);

            // Intro
            // ===================================== //
            if (_TimeAccumilator < 5.0f) {           //
                DrawTitle (GetFrameTime());          //
            } else if (_TimeAccumilator = 5.0f) {    //
                _GameState = GameStates::MENU;       //
                SetActiveScreen (&_MainMenu);        //
            }                                        //
            // ===================================== //

            DrawScreen();

        EndDrawing();
        //----------------------------------------------------------------------------------------
    };

    UnloadFont(_8_bit_Limit);
    CloseWindow();

    return 0;
}