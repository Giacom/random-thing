
#include "raylib.h"
#include "button.h"
#include "helpers.h"

#include <stdio.h>
#include <string.h>

const int mainScreenWidth = 800;
const int mainScreenHeight = 450;

int currentWindowWidth = mainScreenWidth;
int currentWindowHeight = mainScreenHeight;

const int sidePanelWidth = 100;
const int sidePanelHeight = 100;

const char windowTitle[30] = "Shader Canvas";

int droppedFilesCount;
char **droppedFiles;

Shader shader;
Texture2D loadedTexture;

void Update()
{
    droppedFiles = GetDroppedFiles(&droppedFilesCount);

    if (droppedFilesCount > 0) {
        char *filePath = droppedFiles[0];
        Image loadedImage = LoadImage(filePath);

        char title[255] = "Shader Canvas: ";
        strncat(title, filePath, 255);

        CloseWindow();

        currentWindowWidth = loadedImage.width + sidePanelWidth;
        currentWindowHeight = MAX(loadedImage.height, sidePanelHeight);

        InitWindow(currentWindowWidth, currentWindowHeight, title);

        loadedTexture = LoadTextureFromImage(loadedImage);
        UnloadImage(loadedImage);

        ClearDroppedFiles();
    }

    int i = 0;
    while(GetButton(i) != NULL) {
        UpdateButton(GetButton(i++));
    }
}

void Draw()
{
    char* message = "DRAG AND DROP YOUR IMAGE HERE";

    if (!loadedTexture.id) {
        DrawText(message, sidePanelWidth + mainScreenWidth / 2 - (20 * 16), mainScreenHeight / 2, 28, BLACK);
    }

    DrawRectangleGradient(0, 0, sidePanelWidth, currentWindowHeight, DARKGRAY, GRAY);

    int i = 0;
    while(GetButton(i) != NULL) {
        DrawButton(GetButton(i++));
    }

    if (shader.id) {
        BeginShaderMode(shader);
    }
    DrawTexture(loadedTexture, sidePanelWidth, 0, WHITE);
    if (shader.id) {
        EndShaderMode();
    }
}

int counter = 0;

void TestButton(Button *button)
{
    SetButtonLabel(button, FormatText("%i", ++counter));
}

int main()
{
    InitWindow(mainScreenWidth, mainScreenHeight, windowTitle);
	SetTargetFPS(60);

    // Buttons
    CreateButton("Export", 8, 8, sidePanelWidth - 16, 20, TestButton);

    while (!WindowShouldClose()) {
        Update();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}