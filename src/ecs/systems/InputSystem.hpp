#pragma once

#include <SDL3/SDL.h>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/InputComponent.hpp"

class InputSystem {
  public:
    void update(ComponentManager<InputComponent> &inputManager, const SDL_Event &event)
    {
        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
            bool isPressed = (event.type == SDL_EVENT_KEY_DOWN);

            InputAction action;
            if (mapKeyToAction(event.key.key, action)) {
                for (auto &[entity, input] : inputManager.getAllComponents()) {
                    input.setAction(action, isPressed);
                }
            }
        }
    }

  private:
    bool mapKeyToAction(SDL_Keycode key, InputAction &action)
    {
        switch (key) {
            case SDLK_Z: action = InputAction::MoveUp; return true;
            case SDLK_S: action = InputAction::MoveDown; return true;
            case SDLK_Q: action = InputAction::MoveLeft; return true;
            case SDLK_D: action = InputAction::MoveRight; return true;
            case SDLK_SPACE: action = InputAction::Attack; return true;
            case SDLK_LSHIFT: action = InputAction::Dash; return true;
            default: return false;
        }
    }
};
