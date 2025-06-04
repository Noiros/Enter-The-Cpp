#pragma once

#include <SDL.h>
#include <unordered_map>
#include <set>
#include <__msvc_string_view.hpp>

enum class Action;

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void BindKey(Action action, SDL_Scancode key);
    void BindButton(Action action, SDL_GameControllerButton button);
    void ProcessInput();
    bool IsActionHeld(Action action);
    bool IsActionPressed(Action action);
    float GetLeftStickX();
    float GetLeftStickY();
    float GetRightStickX();
    float GetRightStickY();
    float GetMouseX();
    float GetMouseY();

    static void SetInstance(InputManager* instance) { s_instance = instance; };
    static InputManager& Get() { return *s_instance; };
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

private:
    static InputManager* s_instance;

    std::unordered_map<Action, SDL_Scancode> keyBindings;
    std::unordered_map<Action, SDL_GameControllerButton> buttonBindings;
    SDL_GameController* gameController = nullptr;

    std::set<SDL_Scancode> heldKeys;
    std::set<SDL_Scancode> pressedKeys;
    std::set<uint8_t> heldButtons;
    std::set<uint8_t> pressedButtons;

    float leftStickX = 0.0f;
    float leftStickY = 0.0f;
    float rightStickX = 0.0f;
    float rightStickY = 0.0f;
    const float DEAD_ZONE = 0.2f;
};
