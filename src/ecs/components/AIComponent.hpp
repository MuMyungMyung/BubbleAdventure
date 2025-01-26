#pragma once
#include <functional>
#include <ostream>
#include <string>

struct AIComponent {
    enum class State {
        Idle,   // Entity is doing nothing
        Patrol, // Entity is following a predefined path
        Chase,  // Entity is chasing a target
        Attack, // Entity is attacking
        Flee    // Entity is fleeing from danger
    };

    State currentState = State::Idle; // Current AI state
    float decisionTimer = 0.0f;       // Timer to delay decision-making
    float decisionInterval = 0.5f;    // Time between AI updates
    std::string targetTag;            // Target entity's tag
    float detectionRange = 5.0f;      // Distance at which the AI detects the player
    float attackRange = 1.5f;         // Distance required to attack the target

    // Behavior functions
    std::function<void()> onIdle = nullptr;   // Custom behavior for idle
    std::function<void()> onPatrol = nullptr; // Custom behavior for patrol
    std::function<void()> onChase = nullptr;  // Custom behavior for chase
    std::function<void()> onAttack = nullptr; // Custom behavior for attack
    std::function<void()> onFlee = nullptr;   // Custom behavior for flee
};

inline std::ostream &operator<<(std::ostream &os, const AIComponent::State &state)
{
    switch (state) {
        case AIComponent::State::Idle: os << "Idle"; break;
        case AIComponent::State::Patrol: os << "Patrol"; break;
        case AIComponent::State::Chase: os << "Chase"; break;
        case AIComponent::State::Attack: os << "Attack"; break;
        case AIComponent::State::Flee: os << "Flee"; break;
        default: os << "Unknown State"; break;
    }
    return os;
}
