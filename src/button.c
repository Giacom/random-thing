#include "raylib.h"
#include "button.h"
#include "helpers.h"

#include <stdio.h>
#include <string.h>

int buttonCount = 0;
Button buttons[MAX_BUTTONS];

void CreateButton(char *label, int x, int y, int width, int height, ButtonEvent onClick)
{
	// Possible improvement: Allocate this all on the heap.
	Button button = (Button) {
		.bounds = (Rectangle) {
			.x = x, .y = y, .width = width, .height = height
		},
		.color = RED, .onClick = onClick
	};
	SetButtonLabel(&button, label);
	buttons[buttonCount++] = button; // Important, do this last or the changes will not save
}

Button *GetButton(int index)
{
	if (index < buttonCount) {
		return &buttons[index];
	}
	return NULL;
}

void SetButtonLabel(Button *button, const char *label)
{
	strncpy(button->label, label, MAX_BTN_LABEL_SIZE - 1);
}

void DrawButton(struct Button *button)
{

	int highlightAmount = button->highlighted ? 30 : 0;
	Color color = (Color){
		CLAMP(button->color.r + highlightAmount, 0, 255),
		CLAMP(button->color.g + highlightAmount, 0, 255),
		CLAMP(button->color.b + highlightAmount, 0, 255),
		button->color.a
	};

	int buttonYOffset = button->bounds.height / 10;
	if (!button->pressed) {
		int shadowAmount = 20;
		Color shadowColor = (Color){
			CLAMP(button->color.r - shadowAmount, 0, 255),
			CLAMP(button->color.g - shadowAmount, 0, 255),
			CLAMP(button->color.b - shadowAmount, 0, 255),
			button->color.a
		};
		buttonYOffset = 0;
		DrawRectangleRec(button->bounds, shadowColor);
	}
	DrawRectangle(button->bounds.x, button->bounds.y + buttonYOffset, button->bounds.width, button->bounds.height - button->bounds.height / 10, color);

	// Label
	int centerTextPos = MeasureText(button->label, BTN_FONT_SIZE) / 2;
	DrawText(button->label, button->bounds.x + (button->bounds.width / 2) - centerTextPos, button->bounds.y + (BTN_FONT_SIZE / 2) + buttonYOffset, BTN_FONT_SIZE, WHITE);
}

void UpdateButton(struct Button *button)
{
	button->highlighted = CheckCollisionPointRec(GetMousePosition(), button->bounds);
	button->pressed = button->highlighted && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	if (button->highlighted && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		button->onClick(button);
	}
}
