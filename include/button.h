#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

#define MAX_BTN_LABEL_SIZE 255

typedef struct Button Button;

typedef void (*ButtonEvent)(struct Button *button);

struct Button {
	char label[MAX_BTN_LABEL_SIZE];
	Rectangle bounds;
	Color color;
	ButtonEvent onClick;
	bool highlighted;
	bool pressed;
};


void CreateButton(char *label, int x, int y, int width, int height, ButtonEvent onClick);
Button *GetButton(int index);

void SetButtonLabel(Button *button, const char *text);
void DrawButton(struct Button *button);
void UpdateButton(struct Button *button);
void CheckButton(struct Button *button, Vector2 mouseClickPosition);

#endif /* BUTTON_H */