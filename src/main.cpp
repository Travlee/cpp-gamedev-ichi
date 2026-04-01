#include <iostream>
#include <raylib.h>

int main()
{
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(800, 450, "Ichi");

        while(!WindowShouldClose()){
                BeginDrawing();

                ClearBackground(RAYWHITE);

                DrawText("Ichi text", 190, 200, 20, RED);

                EndDrawing();
        }

        CloseWindow();

        return 0;
}
