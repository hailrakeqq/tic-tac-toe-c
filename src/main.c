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
__u_int XWin = 0;
__u_int OWin = 0;
__u_int draw = 0;

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

void drawStats(){
    char stats[30];
    snprintf(stats, 30, "X wins: %d\tO wins: %d\tDraw: %d", XWin, OWin, draw);
    DrawText(stats, SCREEN_WIDTH / 2 - 200, MARGIN - 50, 36, BLACK);
}

gameResult checkGameResult(){
    cellState winSide = NONE; 
    for(int i = 0; i < 3; i++){
        if(map[i][0] == map[i][1] && map[i][1] == map[i][2] && map[i][0] != NONE){
            winSide = map[i][0];
            break;
        }
        if(map[0][i] == map[1][i] && map[1][i] == map[2][i] && map[0][i] != NONE){
            winSide = map[0][i];
            break;
        }
    }
    if(map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[0][0] != NONE)
        winSide = map[0][0];
    if(map[2][0] == map[1][1] && map[1][1] == map[0][2] && map[2][0] != NONE)
        winSide = map[2][0];    


    if(winSide == X) return WIN;
    if(winSide == O) return LOSE;
    return NO_RESULT;
}

bool checkIsMapHaveFreeCell(){
    int posibleFreeCell = 3*3;        
    int i = 0;
    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 3; x++)
            if(map[y][x] != NONE)
                i++;

    return i == posibleFreeCell ? false : true;
}

void clearMap(){
      for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            map[y][x] = NONE;
        }
      }
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
                    if(mousePosition.x >= cellX && mousePosition.x <= cellX + CELL_WIDTH && mousePosition.y >= cellY && mousePosition.y <= cellY + CELL_HEIGHT && map[y][x] == NONE)
                        map[y][x] = X;
                }
            }
        }
         if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            mousePosition = GetMousePosition();

            for(int y = 0; y < 3; y++){
                for(int x = 0; x < 3; x++){
                    int cellX = MARGIN + x * CELL_WIDTH;
                    int cellY = MARGIN + y * CELL_HEIGHT;
                    if(mousePosition.x >= cellX && mousePosition.x <= cellX + CELL_WIDTH && mousePosition.y >= cellY && mousePosition.y <= cellY + CELL_HEIGHT && map[y][x] == NONE)
                        map[y][x] = O;
                }
            }
        }

        game_result = checkGameResult(); 
        
        BeginDrawing();
            ClearBackground(WHITE);
            
            drawStats();
            drawField();
            drawItems();
            
            if(game_result == WIN){
                XWin++;
                TraceLog(LOG_INFO, "WIN!!!");
                clearMap();
            }
            if(game_result == LOSE){
                OWin++;
                TraceLog(LOG_INFO, "LOSE(");
                clearMap();
            }

            if(!checkIsMapHaveFreeCell()){
                draw++;
                clearMap();
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}