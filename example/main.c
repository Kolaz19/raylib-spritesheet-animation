/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0

*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "../include/raylib.h"
#include "../Animation.h"





const int screenWidth = 1920*0.8f;
const int screenHeight = 1080*0.8f;
static Rectangle rect;

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int rc = 0;

void initRect (int startPosX, int startPosY, int height, int width, Rectangle *rect);
void updatePosition(Rectangle *rect, float speed);

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Move Rectangle");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    float scale = 1.0f;
    //float scaleHeight = 1.0f;
    //float scaleWidth = 1.0f;

    initRect(100, 100, 100, 100,&rect);        
    RenderTexture2D target = LoadRenderTexture(screenWidth,screenHeight);

    SpriteSheet* spriteSheet_box = initSpriteSheet("spriteSheetBox.png",256,288,9,8,&rc);
    Animation boxAnimationLoop = initAnimation(spriteSheet_box,1,65,0.02f,PLAY_LOOP,&rc);
    Animation boxAnimationOnce = initAnimation(spriteSheet_box,1,65,0.01f,PLAY_ONCE,&rc);
    Animation boxAnimationOnceNoInterrupt = initAnimation(spriteSheet_box,1,65,0.01f,PLAY_ONCE,&rc);
    

    while (!WindowShouldClose()) 
    {

        updatePosition(&rect, 10.0f);

        scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        if(IsKeyPressed(KEY_ENTER)) {
            startAnimation(&boxAnimationOnce,&rc);
        }

        if(IsKeyPressed(KEY_ENTER) && !isAnimationRunning(&boxAnimationOnceNoInterrupt,&rc)) {
            startAnimation(&boxAnimationOnceNoInterrupt, &rc);
        }

        playAnimation(&boxAnimationLoop);
        playAnimation(&boxAnimationOnce);
        playAnimation(&boxAnimationOnceNoInterrupt);


        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawCurrentTile(&boxAnimationLoop,rect.x, rect.y,4*32,4*32,&rc);
            drawCurrentTile(&boxAnimationOnce,rect.x + 200, rect.y, 4*32, 4*32, &rc);
            drawCurrentTile(&boxAnimationOnceNoInterrupt,rect.x + 400, rect.y, 4*32, 4*32, &rc);

        EndDrawing();
    

    }

    unloadSpriteSheet(spriteSheet_box);
    CloseWindow();       
    return 0;
}


void initRect (int startPosX, int startPosY, int height, int width, Rectangle *rect) {
    rect->x = startPosX;
    rect->y = startPosY;
    rect->height = height;
    rect->width = width;
}

void updatePosition(Rectangle *rect, float speed) {
    if(IsKeyDown(KEY_W)) rect->y -= speed;
    if(IsKeyDown(KEY_S)) rect->y += speed;
    if(IsKeyDown(KEY_A)) rect->x -= speed;
    if(IsKeyDown(KEY_D)) rect->x += speed;
}