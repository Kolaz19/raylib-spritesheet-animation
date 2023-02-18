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
    SetTargetFPS(60);             
    float scale = 1.0f;

    initRect(100, 100, 100, 100,&rect);        

    //Initialize sprite sheet to use for all our animations
    SpriteSheet* spriteSheet_box = initSpriteSheet("spriteSheetBox.png",256,288,9,8,&rc);
    //PLAY_LOOP Loop animation back to the start if last frame is reached
    Animation boxAnimationLoop = initAnimation(spriteSheet_box,1,65,0.02f,PLAY_LOOP,&rc);
    //PLAY_ONCE Start animation after startAnimation() and end when last frame was reached
    Animation boxAnimationOnce = initAnimation(spriteSheet_box,1,65,0.01f,PLAY_ONCE,&rc);
    Animation boxAnimationOnceNoInterrupt = initAnimation(spriteSheet_box,1,65,0.01f,PLAY_ONCE,&rc);
    

    while (!WindowShouldClose()) 
    {

        updatePosition(&rect, 10.0f);

        scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

        // Check if animation should be started -> Restarts animation if it is already running
        if(IsKeyPressed(KEY_ENTER)) {
            startAnimation(&boxAnimationOnce,&rc);
        }

        //Check if animation should be started and animation is not already running -> Can not interrupt animation
        if(IsKeyPressed(KEY_ENTER) && !isAnimationRunning(&boxAnimationOnceNoInterrupt,&rc)) {
            startAnimation(&boxAnimationOnceNoInterrupt, &rc);
        }

        //Advance frames after specific time
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