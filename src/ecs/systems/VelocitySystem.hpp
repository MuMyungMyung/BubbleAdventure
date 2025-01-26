#pragma once
#include <cmath>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/InputComponent.hpp"
#include "ecs/components/VelocityComponent.hpp"

class VelocitySystem {
  public:
    void update(ComponentManager<InputComponent> &inputManager, ComponentManager<VelocityComponent> &velocityManager);
};
