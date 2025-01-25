#pragma once

struct AttackComponent {
    float damage = 10.0f;      // Damage dealt by the attack
    float range = 1.5f;        // Hitbox tile range
    float attackSpeed = 1.0f;  // Attacks per seconds (see if needed)
    float cooldown = 0.0f;     // cooldown timer in seconds
    float cooldownTime = 1.0f; // Time required before the next attack (based on attackSpeed ( = 1.0f / attackSpeed))
    bool isAttacking = false;  // Whether the entity is attacking or not

    void resetCooldown()
    {
        cooldown = cooldownTime;
    }

    void updateCooldown(float deltaTime)
    {
        if (cooldown > 0.0f) {
            cooldown -= deltaTime;
            if (cooldown < 0.0f)
                cooldown = 0.0f;
        }
    }

    bool canAttack()
    {
        return cooldown <= 0.0f;
    }
};
