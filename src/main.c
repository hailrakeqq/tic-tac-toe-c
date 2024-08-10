#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define LINE_THICKNESS 5
#define MARGIN 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CELL_WIDTH (SCREEN_WIDTH - 2 * MARGIN) / 3
#define CELL_HEIGHT (SCREEN_HEIGHT - 2 * MARGIN) / 3

typedef enum{NONE, X, O} cellState;
typedef enum{NO_RESULT, WIN, LOSE} gameResult;

cellState map[3][3] = { NONE }; 
gameResult game_result = {NO_RESULT};

void drawField(){
    for(int i = 1; i < 3; i++){
        DrawRectangle(MARGIN + i * CELL_WIDTH - LINE_THICKNESS / 2, MARGIN, LINE_THICKNESS, SCREEN_HEIGHT - 2 * MARGIN, BLACK);
        DrawRectangle(MARGIN, MARGIN + i * CELL_HEIGHT - LINE_THICKNESS / 2, SCREEN_WIDTH - 2 * MARGIN, LINE_THICKNESS, BLACK);        
    }
}

void drawItems(){
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            //get centre of each cell
            int cellCentreX = MARGIN + y * CELL_WIDTH + CELL_WIDTH / 2;
            int cellCentreY = MARGIN + x * CELL_HEIGHT + CELL_HEIGHT /  2;

            if(map[x][y] == X){
                int offsetX = CELL_WIDTH / 4;
                int offsetY = CELL_HEIGHT / 4;

                DrawLineEx((Vector2){cellCentreX - offsetX, cellCentreY - offsetY}, (Vector2){cellCentreX + offsetX, cellCentreY + offsetY}, LINE_THICKNESS, BLACK);
                DrawLineEx((Vector2){cellCentreX - offsetX, cellCentreY + offsetY},(Vector2){cellCentreX + offsetX, cellCentreY - offsetY}, LINE_THICKNESS, BLACK);
            }                    
            if(map[x][y] == O){
                float circleRadius = CELL_WIDTH / 4;
                DrawRing((Vector2){cellCentreX, cellCentreY}, circleRadius - LINE_THICKNESS / 2, circleRadius + LINE_THICKNESS / 2, 0, 360, 100, BLACK);
            }
        }
    }
}

gameResult checkGameResult(){
    return NO_RESULT;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
    SetTargetFPS(30);

    Vector2 mousePosition;

    while (!WindowShouldClose()){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            mousePosition = GetMousePosition();

            for(int y = 0; y < 3; y++){
                for(int x = 0; x < 3; x++){
                    int cellX = MARGIN + x * CELL_WIDTH;
                    int cellY = MARGIN + y * CELL_HEIGHT;
                    TraceLog(LOG_INFO, "x: %d y: %d",cellX, cellY);
                    if(mousePosition.x >= cellX && mousePosition.x <= cellX + CELL_WIDTH && mousePosition.y >= cellY && mousePosition.y <= cellY + CELL_HEIGHT && map[y][x] == NONE)
                        map[y][x] = X;
                }
            }
        }

        game_result = checkGameResult(); 
        
        BeginDrawing();
            ClearBackground(WHITE);
            
            //draw field section
            drawField();
            drawItems();
            
            if(game_result == WIN){
                TraceLog(LOG_INFO, "WIN!!!");
            }
            if(game_result == LOSE){
                TraceLog(LOG_INFO, "LOSE(");
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}