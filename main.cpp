#include <iostream>
#include <vector>
#include <raylib.h>
#include <stdlib.h>

struct Vector2a {
    int x, y;
};

enum Direction {
    Up,
    Right,
    Down,
    Left
};

std::vector<Vector2a> snake;
int main() {
    int snakeSize = 25;
    InitWindow(600, 600, "Snake!");
    snake.push_back({ 10, 10 });
    Direction direction = Right;

    srand(time(NULL));
    Vector2a fruit = { rand() % 21, rand() % 21 };
    bool close = false;
    bool lost = false;
    float timeSinceMove = 0;
    Direction prevDirection = Right;
    while (!close) {
        if (!lost) {
            timeSinceMove += GetFrameTime();
            close = WindowShouldClose();

            if (IsKeyDown(KEY_UP) && prevDirection != Down) direction = Up;
            if (IsKeyDown(KEY_RIGHT) && prevDirection != Left) direction = Right;
            if (IsKeyDown(KEY_DOWN) && prevDirection != Up) direction = Down;
            if (IsKeyDown(KEY_LEFT) && prevDirection != Right) direction = Left;

            BeginDrawing(); {
                ClearBackground({ 255, 255, 255 });
                DrawRectangle(0, 0, 600, 50, BLACK);
                DrawRectangle(550, 0, 50, 600, BLACK);
                DrawRectangle(0, 550, 600, 50, BLACK);
                DrawRectangle(0, 0, 50, 600, BLACK);

                for (int i = 0; i < snake.size(); i++)
                    DrawRectangle(snake[i].x*snakeSize + 50, snake[i].y*snakeSize + 50, snakeSize, snakeSize, {0, 255, 0, 255});
                
                DrawRectangle(fruit.x*snakeSize+50, fruit.y*snakeSize+50, snakeSize, snakeSize, {255, 0 ,0, 255});
            } EndDrawing();

            if (timeSinceMove >= 0.2) {
                timeSinceMove = 0;
                int count = 0;
                for (int i = snake.size()-1; i > 0; i--) {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }

                switch (direction) {
                    case Up: {
                        snake[0].y--;
                        prevDirection = Up;
                        break;
                    }
                    case Right: {
                        snake[0].x++;
                        prevDirection = Right;
                        break;
                    }
                    case Down: {
                        snake[0].y++;
                        prevDirection = Down;
                        break;
                    }
                    case Left: {
                        snake[0].x--;
                        prevDirection = Left;
                        break;
                    }
                }

                bool dead = false;
                for (int i = 1; i < snake.size(); i++) {
                    dead = (snake[0].x == snake[i].x && snake[0].y == snake[i].y);
                }

                lost = (dead || snake[0].x < 0 || snake[0].y < 0 || snake[0].x >= 20 || snake[0].y >= 20);
                if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
                    int fruitx = rand() % 21, fruity = rand() % 21;
                    while (snake[0].x == fruitx) fruitx = rand() % 21;
                    while (snake[0].y == fruity) fruity = rand() % 21;

                    fruit = { fruitx, fruity };
                    snake.push_back({snake[snake.size()-1].x, snake[snake.size()-1].y});
                }
            }
        } else { 
            while (!close) {
                close = WindowShouldClose();
                BeginDrawing(); 
                    DrawText("You Lost! (press escape to exit)", 300-MeasureText("You Lost! (press escape to exit)", 20)/2, 290, 20, RED); 
                EndDrawing();
            }
        }
    }
}