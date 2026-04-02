#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlimgui.h"

int main()
{
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(800, 450, "Ichi");

        rlImGuiSetup(true);

        while(!WindowShouldClose()){
                BeginDrawing();

                ClearBackground(RAYWHITE);

                rlImGuiBegin();

                // ! Test
                DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});
                DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});

                DrawText("Ichi text", 190, 200, 20, RED);

                // ? IMGUI Test
                ImGui::Begin("test");
                ImGui::Text("hello");
                ImGui::Button("button");
                ImGui::ShowDemoWindow();
                ImGui::End();

                rlImGuiEnd();
                EndDrawing();
        }

        rlImGuiShutdown();
        CloseWindow();

        return 0;
}
