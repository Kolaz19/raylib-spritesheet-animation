#ifndef ANIMATION_H
#define ANIMATION_H
#include "include/raylib.h"

typedef enum animation_rc {
    E_SUCCESS = 1,
    E_SPRITESHEET_WRONG_ID = 2,
    E_FILE_NOT_FOUND = 3,
    E_WRONG_PLAYMODE_TYPE = 4
} animation_rc;

#define ID_SUCCESS 7

typedef struct SpriteSheet {
    Texture2D* texture;
    int pxHeight;
    int pxWidth;
    int xTileAmount;
    int yTileAmount;
    int id;
} SpriteSheet;

typedef enum playMode {
    PLAY_ONCE = 1,
    PLAY_LOOP = 2
} playMode;

typedef struct Animation {
    SpriteSheet* spriteSheet;
    int startTile;
    int endTile;
    float frameDuration;
    float timeCounter;
    int currentTile;
    playMode playMode;
} Animation;

SpriteSheet* initSpriteSheet(char* fileName, int pxHeight, int pxWidth, int xTileAmount, int yTileAmount, int* rc);
Animation initAnimation(SpriteSheet* spriteSheet, int startTile, int endTile, float frameDuration,playMode playMode, int* rc);
void unloadSpriteSheet(SpriteSheet* spriteSheet);
void drawCurrentTile(Animation* animation, int x, int y, int width, int height, int* rc);
void playAnimation(Animation* animation);
void resetAnimation(Animation* animation, int* rc);
void startAnimation(Animation* animation, int* rc);
int isAnimationRunning(Animation* animation, int* rc);

#endif