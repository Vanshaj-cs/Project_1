#include <iostream>
#include "raylib.h"

using namespace std;

int main(){
    InitWindow(900, 900, "test");
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Hello World", 10, 10, 20, BLACK);
        EndDrawing();
    }
}