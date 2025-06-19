#include "raylib.h"

// Struct that makes SnakeSegment a x,y position for a snake segment
typedef struct SnakeSegment {
    Vector2 position;
} SnakeSegment;

int main()  {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "snakegame");
    SetTargetFPS(60);

    // Array that stores positions max length of 7 for testing
    SnakeSegment snake[7];
    int snakeLength = 3;

    //sets initial position for snake
    for (int i = 0; i < snakeLength; i++) {
        snake[i].position = (Vector2){screenWidth/2 - i*20, screenHeight/2};
    }

    while(!WindowShouldClose()) {



        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // draws snake
        for(int i = 0; i < snakeLength; i++) {
            DrawRectangleV(snake[i].position, (Vector2){20, 20}, DARKGREEN);
        }


        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}