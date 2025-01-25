#pragma once
#include "../ComponentManager.hpp"
#include "HealthComponent.hpp"

struct StatsComponent {
    int sanity = 0;            // Current sanity
    const int maxSanity = 100; // Max sanity
    int attackPower = 3;       // Base attack power
    int experience = 0;        // Current experience points
    int level = 1;             // Current level
    int statPoints = 0;        // Unallocated points for progression

    int healthBonusPerLevel = 10;
    int sanityBonusPerLevel = 5;

    void gainExperience(int xp, ComponentManager<HealthComponent> &healthManager, EntityManager::EntityID entity)
    {
        experience += xp;
        checkLevelUp(healthManager, entity);
    }

  private:
    void checkLevelUp(ComponentManager<HealthComponent> &healthManager, EntityManager::EntityID entity)
    {
        int xpToNextLevel = 100 + 20 * (level - 1);
        while (experience >= xpToNextLevel) {
            experience -= xpToNextLevel;
            level++;
            statPoints += 5;

            auto *health = healthManager.getComponent(entity);
            if (health) {
                health->maxHealth += healthBonusPerLevel;
                health->currentHealth = health->maxHealth;
            }

            sanity += sanityBonusPerLevel;

            xpToNextLevel = 100 + 20 * (level - 1);
        }
    }
};
