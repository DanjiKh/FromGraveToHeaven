
#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/main.hpp"
#include "include/intro.hpp"

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
    SetTargetFPS (144);
}

void QuitApplication()
{
    _GameState = GameStates::QUITTING;
};  

int main()
{
    const int screenWidth  = 640;
    const int screenHeight = 360;
          int screenScale  = 2;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow (screenWidth * screenScale, screenHeight * screenScale, _NameOfApplicatoin);

    SetupWindow();

    GameStates _GameState = GameStates::LOADING;
    
    // Initialisation 
    //----------------------------------------------------------------------------------------    
    // TODO: Create function UpdateLoda(), and update right there.

    _TimeAccumilator = 0.0f;
    _DeltaFade       = 0.0f;
    _TitleFontSize   = 50;

    _8_bit_Limit = LoadFontEx ("resources/fonts/8-bit-limit.brk.ttf", 32, 0, 250); 

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
            // ======================================//
            if (_TimeAccumilator < 5.0f) {           //
                DrawTitle (GetFrameTime());          //
            }                                        //
            else if (_TimeAccumilator = 5.0f) {      //
                _GameState = GameStates::MENU;       //
                ClearBackground (Color{0, 0, 0});    //
            }                                        //
            // ======================================// 



        EndDrawing();
        //----------------------------------------------------------------------------------------
   }

    CloseWindow();

    return 0;
}