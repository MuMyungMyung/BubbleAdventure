#pragma once

#include <bitset>

enum class InputAction {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Attack,
    Dash,
    NUM_ACTIONS,
};

struct InputComponent {
    std::bitset<static_cast<size_t>(InputAction::NUM_ACTIONS)> actions;

    void setAction(InputAction action, bool isActive)
    {
        actions.set(static_cast<size_t>(action), isActive);
    }

    bool isActionActive(InputAction action) const
    {
        return actions.test(static_cast<size_t>(action));
    }
};
