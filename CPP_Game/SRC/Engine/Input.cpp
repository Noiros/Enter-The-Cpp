#include "Input.h"
#include "Logger.h"

Input::Input() {
	Logger::Log("Input constructor called");

	if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0)) {
		gameController = SDL_GameControllerOpen(0);
		Logger::Log("Game controller found");
	}
}

Input::~Input() {
	if (gameController) SDL_GameControllerClose(gameController);
	Logger::Log("Input destructor called");
}

void Input::BindKey(Action action, SDL_Scancode key) {
	keyBinding[action] = key;
}

void Input::BindButton(Action action, SDL_GameControllerButton button) {
	buttonBinding[action] = button;
}

void Input::ProcessInput() {
	heldKeys.clear();
	pressedKeys.clear();
	heldButtons.clear();
	pressedButtons.clear();

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for (const auto& [action, key] : keyBinding) {
		if (state[key]) heldKeys.insert(key);
		if (state[key] && !heldKeys.count(key)) pressedKeys.insert(key);
	}

	if (gameController) {
		for (const auto& [action, button] : buttonBinding) {
			if (SDL_GameControllerGetButton(gameController, button)) {
				heldButtons.insert(button);
				if (!heldButtons.count(button)) pressedButtons.insert(button);
			}
		}

		leftStickX = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
		leftStickY = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
		rightStickX = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f;
		rightStickY = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_RIGHTY) / 32767.0f;

		if (fabs(leftStickX) < DEAD_ZONE) leftStickX = 0.0f;
		if (fabs(leftStickY) < DEAD_ZONE) leftStickY = 0.0f;
		if (fabs(rightStickX) < DEAD_ZONE) rightStickX = 0.0f;
		if (fabs(rightStickY) < DEAD_ZONE) rightStickY = 0.0f;
	}
}

bool Input::IsActionHeld(Action action) {
	return heldKeys.count(keyBinding[action]) || heldButtons.count(buttonBinding[action]);
}

bool Input::IsActionPressed(Action action) {
	return pressedKeys.count(keyBinding[action]) || pressedButtons.count(buttonBinding[action]);
}

glm::vec2 Input::GetStick(uint8_t id) {
	if (id == 0) return glm::vec2(leftStickX, leftStickY);
	if (id == 1) return glm::vec2(rightStickX, rightStickY);
}