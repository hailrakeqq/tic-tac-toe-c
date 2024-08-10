#include <raylib.h>
#include <raymath.h>
#include <stdio.h>


int main(void) {
    const int screenWidth = 800; 
    const int screenHeight = 600;  
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");

    const int lineThickness = 5;
    const int margin = 100;
    
    // Вычисление размера клетки
    int cellWidth = (screenWidth - 2 * margin) / 3;
    int cellHeight = (screenHeight - 2 * margin) / 3;

    Vector2 mousePosition;

    char test_map[3][3] = {
        'x', 'o', 'x',
        'x', 'x', 'o',
        'o', 'o', 'x'
    };
    char map[3][3];

    SetTargetFPS(30);

    while (!WindowShouldClose()){
        mousePosition = GetMousePosition();
        BeginDrawing();
            ClearBackground(WHITE);

            //draw field section
            for(int i = 1; i < 3; i++){
                DrawRectangle(margin + i * cellWidth - lineThickness / 2, margin, lineThickness, screenHeight - 2 * margin, BLACK);
                DrawRectangle(margin, margin + i * cellHeight - lineThickness / 2, screenWidth - 2 * margin, lineThickness, BLACK);        
            }

            //draw item section
            for(int y = 0; y < 3; y++){
                for(int x = 0; x < 3; x++){
                    //get centre of each cell
                    int cellCentreX = margin + y * cellWidth + cellWidth / 2;
                    int cellCentreY = margin + x * cellHeight + cellHeight / 2;

                    if(test_map[x][y] == 'x'){
                        int offsetX = cellWidth / 4;
                        int offsetY = cellHeight / 4;
                        
                        DrawLineEx((Vector2){cellCentreX - offsetX, cellCentreY - offsetY}, (Vector2){cellCentreX + offsetX, cellCentreY + offsetY}, lineThickness, BLACK);
                        DrawLineEx((Vector2){cellCentreX - offsetX, cellCentreY + offsetY},(Vector2){cellCentreX + offsetX, cellCentreY - offsetY}, lineThickness, BLACK);
                    }                    
                    if(test_map[x][y] == 'o'){
                        float circleRadius = cellWidth / 4;
                        DrawRing((Vector2){cellCentreX, cellCentreY}, circleRadius - lineThickness / 2, circleRadius + lineThickness / 2, 0, 360, 100, BLACK);
                    }
                }
            }

            // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // int x = mousePosition.x / GRID_SIZE;
            // int y = mousePosition.y / GRID_SIZE;
            // }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}