#include "raylib.h"
#include <stdbool.h>

#define SQUARE 25
#define MAX (100)

// Struct that makes SnakeSegment a x,y position for a snake segment
typedef struct SnakeSegment {
    Vector2 position;
} SnakeSegment;

int main()  {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "snakegame");
    SetTargetFPS(10);

    // Array that stores positions of each snake segment
    SnakeSegment snake[MAX];
    int snakeLength = 3;

    // sets initial position for snake
    for (int i = 0; i < snakeLength; i++) {
        snake[i].position = (Vector2){screenWidth/2 - i*SQUARE, screenHeight/2};
    }

    // vector that stores where snake will go next
    Vector2 direction = {SQUARE, 0};

    // makes food
    Vector2 food = {(float)(GetRandomValue(0, (screenWidth / SQUARE) - 1) * SQUARE), 
                    (float)(GetRandomValue(0, (screenHeight / SQUARE) - 1) * SQUARE)};
    
    bool GAMEOVER = false;

    while(!WindowShouldClose()) {
        if (!GAMEOVER){
            // inputs
            if (IsKeyPressed(KEY_RIGHT) && direction.x == 0) {
                direction = (Vector2) {SQUARE, 0};
            }
            if (IsKeyPressed(KEY_LEFT) && direction.x == 0) {
                direction = (Vector2) {-SQUARE, 0};
            }
            if (IsKeyPressed(KEY_UP) && direction.y == 0) {
                direction = (Vector2) {0, -SQUARE};
            }
            if (IsKeyPressed(KEY_DOWN) && direction.y == 0) {
                direction = (Vector2) {0, SQUARE};
            }

            // move snake
            for (int i = snakeLength -1; i > 0; i--) {
                snake[i].position = snake[i-1].position;
            }
            snake[0].position.x += direction.x;
            snake[0].position.y += direction.y;
            
            // food collision
            if ((int)snake[0].position.x == (int)food.x && (int)snake[0].position.y == (int)food.y) {
                if (snakeLength < MAX) {
                    // updates new snake block here instead of waiting
                    snake[snakeLength].position = snake[snakeLength - 1].position;
                    snakeLength++;
                }
                // new food location
                food = (Vector2){(float)(GetRandomValue(0, (screenWidth / SQUARE) - 1) * SQUARE), 
                        (float)(GetRandomValue(0, (screenHeight / SQUARE) - 1) * SQUARE)};
            }

            // wall collision
            if (snake[0].position.x < 0 || snake[0].position.x >= screenWidth || snake[0].position.y < 0 || snake[0].position.y >= screenHeight) {
                GAMEOVER = true;
            }

            //self collision
            for (int i = 1; i < snakeLength; i++) {
                if (snake[0].position.x == snake[i].position.x && snake[0].position.y == snake[i].position.y) {
                    GAMEOVER = true;
                }
            }

            // max length reached
            if (snakeLength > MAX) GAMEOVER = true;
        }
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (!GAMEOVER){
            // draws snake
            for(int i = 0; i < snakeLength; i++) {
                DrawRectangleV(snake[i].position, (Vector2){SQUARE, SQUARE}, DARKGREEN);
            }

            // draws food
            DrawRectangleV(food, (Vector2) {SQUARE, SQUARE}, RED);
        }
        else {
            DrawText("GAME OVER", screenWidth/2, screenHeight/2, 20, RED);
        }
        


        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}