#pragma once

#include <SDL3/SDL.h>
#include "../ComponentManager.hpp"
#include "../components/InputComponent.hpp"

class InputSystem {
  public:
    void update(ComponentManager<InputComponent> &inputManager, float deltaTime)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
                bool isPressed = (event.type == SDL_EVENT_KEY_DOWN);

                InputAction action;
                if (mapKeyToAction(event.key.key, action)) {
                    for (auto &[entity, input] : inputManager.getAllComponents()) {
                        auto *mutableInput = inputManager.getComponent(entity);
                        mutableInput->setAction(action, isPressed);
                    }
                }
            }
        }
    }

  private:
    bool mapKeyToAction(SDL_Keycode key, InputAction &action)
    {
        switch (key) {
            case SDLK_W: action = InputAction::MoveUp; return true;
            case SDLK_S: action = InputAction::MoveDown; return true;
            case SDLK_A: action = InputAction::MoveLeft; return true;
            case SDLK_D: action = InputAction::MoveRight; return true;
            case SDLK_SPACE: action = InputAction::Attack; return true;
            case SDLK_LSHIFT: action = InputAction::Dash; return true;
            default: return false;
        }
    }
};
