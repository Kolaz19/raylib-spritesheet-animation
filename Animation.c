#include "Animation.h"
#include <stdlib.h>


#define PLAY_ONCE_RUNNING 3


SpriteSheet* initSpriteSheet(char* fileName, int pxHeight, int pxWidth, int xTileAmount, int yTileAmount, int* rc) {
    SpriteSheet* spriteSheet = malloc(sizeof(SpriteSheet));
    spriteSheet->texture = malloc(sizeof(Texture2D));
    *spriteSheet->texture = LoadTexture(fileName);
    //Check Texture not loaded
    if(spriteSheet->texture->id <= 0) {
        free(spriteSheet->texture);
        free(spriteSheet);
        *rc = E_FILE_NOT_FOUND;
        return NULL;
    }
    spriteSheet->id = ID_SUCCESS;
    spriteSheet->pxHeight = pxHeight;
    spriteSheet->pxWidth = pxWidth;
    spriteSheet->xTileAmount = xTileAmount;
    spriteSheet->yTileAmount = yTileAmount;
    *rc = E_SUCCESS;
    return spriteSheet;
}

Animation initAnimation(SpriteSheet* spriteSheet, int startTile, int endTile, float frameDuration,playMode playMode, int* rc) {
    if (spriteSheet->id != ID_SUCCESS) {
        *rc = E_SPRITESHEET_WRONG_ID;
    }

    Animation animation = {
        spriteSheet,
        startTile,
        endTile,
        frameDuration,
        0.0f,
        startTile,
        playMode
    };
    *rc = E_SUCCESS;
    return animation;
}

void unloadSpriteSheet(SpriteSheet* spriteSheet) {
    UnloadTexture(*spriteSheet->texture);
    free(spriteSheet->texture);
    free(spriteSheet);
}

void drawCurrentTile(Animation* animation, int x, int y, int width, int height, int* rc) {
    SpriteSheet* spriteSheet = animation->spriteSheet;

    int tileXPos = 0;
    //Check if tile is last element in row -> MODULO would return 0
    if (animation->currentTile % spriteSheet->xTileAmount == 0) {
        tileXPos = (spriteSheet->pxWidth / spriteSheet->xTileAmount) * (spriteSheet->xTileAmount - 1);
    } else {
        tileXPos = (animation->currentTile % spriteSheet->xTileAmount - 1) * (spriteSheet->pxWidth / spriteSheet->xTileAmount);
    } 

    int tileYPos = ((int)((animation->currentTile - 1) / spriteSheet->xTileAmount)) * (spriteSheet->pxHeight / spriteSheet->yTileAmount);

    Rectangle source = {tileXPos,tileYPos,spriteSheet->pxWidth / spriteSheet->xTileAmount,spriteSheet->pxHeight / spriteSheet->yTileAmount};
    Rectangle dest = source;
    dest.x = x;
    dest.y = y;
    dest.width = width,
    dest.height = height;
    DrawTexturePro(*animation->spriteSheet->texture,source, dest, (Vector2){0.0f,0.0f},0.0f, RAYWHITE);
    *rc = E_SUCCESS;
}

/// @brief Advance the animation one frame after frameDuration.
/// Loops back to starting tile if last tile was reached.
/// Animation with PlayMode PLAY_ONCE is ignored
void playAnimation(Animation* animation) {
    if(animation->playMode != PLAY_ONCE_RUNNING && animation->playMode != PLAY_LOOP) {
        return;
    }

    animation->timeCounter += GetFrameTime();
    if (animation->timeCounter >= animation->frameDuration) {
        animation->timeCounter = 0;
        if(animation->currentTile == animation->endTile) {
            animation->currentTile = animation->startTile;
            if(animation->playMode == PLAY_ONCE_RUNNING) {
                animation->playMode = PLAY_ONCE;
            }
        } else {
            animation->currentTile++;
        }
    }
}

/// @brief Set current tile to the starting tile
void resetAnimation(Animation* animation, int* rc) {
    if (animation->spriteSheet->id != ID_SUCCESS) {
        *rc = E_SPRITESHEET_WRONG_ID;
    }
    animation->currentTile = animation->startTile;
}

/// @brief Start animation for PlayMode PLAY_ONCE.
/// This does reset the animation
/// @param animation Animation with PlayMode PLAY_ONCE
void startAnimation(Animation* animation, int* rc) {
    if (animation->playMode == PLAY_LOOP) {
        *rc = E_WRONG_PLAYMODE_TYPE;
        return;
    }
    resetAnimation(animation, rc);
    if (*rc != E_SUCCESS) {
        return;
    }
    animation->playMode = PLAY_ONCE_RUNNING;
    *rc = E_SUCCESS;
}

/// @brief Check if animation with PlayMode PLAY_ONCE
/// was already started
/// @return 1 if true, 0 if false
int isAnimationRunning(Animation* animation, int* rc) {
    if (animation->playMode == PLAY_LOOP) {
        *rc = E_WRONG_PLAYMODE_TYPE;
        return -1;
    }
    if(animation->playMode == PLAY_ONCE_RUNNING) {
        return 1;
    } else { 
        return 0;
    }
}


