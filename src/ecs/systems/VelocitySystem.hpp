#pragma once
#include <cmath>
#include "../ComponentManager.hpp"
#include "../components/InputComponent.hpp"
#include "../components/VelocityComponent.hpp"

class VelocitySystem {
  public:
    void update(ComponentManager<InputComponent> &inputManager, ComponentManager<VelocityComponent> &velocityManager)
    {
        for (auto &[entity, input] : inputManager.getAllComponents()) {
            auto *velocity = velocityManager.getComponent(entity);

            if (velocity) {
                velocity->dx = 0;
                velocity->dy = 0;

                if (input.isActionActive(InputAction::MoveUp))
                    velocity->dy -= 1;
                if (input.isActionActive(InputAction::MoveDown))
                    velocity->dy += 1;
                if (input.isActionActive(InputAction::MoveLeft))
                    velocity->dx -= 1;
                if (input.isActionActive(InputAction::MoveRight))
                    velocity->dx += 1;

                float magnitude = std::sqrt(velocity->dx * velocity->dx + velocity->dy * velocity->dy);
                if (magnitude > 0) {
                    velocity->dx /= magnitude;
                    velocity->dy /= magnitude;
                }
            }
        }
    }
};
