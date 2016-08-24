
#include "raylib.h"
#include "button.h"
#include "helpers.h"
#include "export.h"

#include <stdio.h>
#include <string.h>

const int mainScreenWidth = 800;
const int mainScreenHeight = 450;

int currentWindowWidth = 0;
int currentWindowHeight = 0;

const int sidePanelWidth = 100;
const int sidePanelHeight = 100;

const char windowTitle[30] = "Shader Canvas";

int droppedFilesCount;
char **droppedFiles;

Shader loadedShader;
Texture2D loadedTexture;

RenderTexture2D canvas;

Rectangle dropZone;

void Update()
{
	droppedFiles = GetDroppedFiles(&droppedFilesCount);

	if (!loadedTexture.id) {
		if (droppedFilesCount > 0) {
			char *filePath = droppedFiles[0];
			Image loadedImage = LoadImage(filePath);

			char title[255] = "Shader Canvas: ";
			strncat(title, filePath, 254);

			CloseWindow();

			currentWindowWidth = loadedImage.width + sidePanelWidth;
			currentWindowHeight = MAX(loadedImage.height, sidePanelHeight);

			InitWindow(currentWindowWidth, currentWindowHeight, title);

			canvas = LoadRenderTexture(loadedImage.width, loadedImage.height);

			loadedTexture = LoadTextureFromImage(loadedImage);
			UnloadImage(loadedImage);

			ClearDroppedFiles();
		}
	} else {
		if (droppedFilesCount > 1) {
			char *filePathVert = droppedFiles[0];
			char *filePathFrag = droppedFiles[1];

			UnloadShader(loadedShader);

			loadedShader = LoadShader(filePathVert, filePathFrag);

			ClearDroppedFiles();
		}
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

	// Canvas

	if (canvas.id) {
		BeginTextureMode(canvas);
		ClearBackground(RAYWHITE);
		if (loadedShader.id) {
			BeginShaderMode(loadedShader);
		}
		DrawTexture(loadedTexture, 0, 0, WHITE);
		if (loadedShader.id) {
			EndShaderMode();
		}
		EndTextureMode();

		// Flipped due to OpenGL
		DrawTextureRec(canvas.texture, (Rectangle){ 0, 0, canvas.texture.width, -canvas.texture.height }, (Vector2){ sidePanelWidth, 0 }, WHITE);
	}

	// Side panel
	DrawRectangleGradient(0, 0, sidePanelWidth, currentWindowHeight, DARKGRAY, GRAY);

	int i = 0;
	while(GetButton(i) != NULL) {
		DrawButton(GetButton(i++));
	}
}


void TestButton(Button *button)
{
	if (canvas.id) {
		SetButtonLabel(button, "Exported");
		//loadedTexture = TestImage(canvas.texture);
		ExportTexture(loadedTexture, true);
	}
}

int main()
{
	currentWindowWidth = mainScreenWidth;
	currentWindowHeight = mainScreenHeight;

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