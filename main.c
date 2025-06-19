#include "raylib.h"

#define SQUARE 20

// Struct that makes SnakeSegment a x,y position for a snake segment
typedef struct SnakeSegment {
    Vector2 position;
} SnakeSegment;

int main()  {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "snakegame");
    SetTargetFPS(10);

    // Array that stores positions max length of 3 for testing
    SnakeSegment snake[3];
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

    while(!WindowShouldClose()) {

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
        


        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // draws snake
        for(int i = 0; i < snakeLength; i++) {
            DrawRectangleV(snake[i].position, (Vector2){SQUARE, SQUARE}, DARKGREEN);
        }

        // draws food
        DrawRectangleV(food, (Vector2) {SQUARE, SQUARE}, RED);


        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}