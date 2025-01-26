#pragma once

#include <SDL3/SDL.h>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/InputComponent.hpp"

class InputSystem {
  public:
    void update(ComponentManager<InputComponent> &inputManager, const SDL_Event &event);

  private:
    bool mapKeyToAction(SDL_Keycode key, InputAction &action);
};
