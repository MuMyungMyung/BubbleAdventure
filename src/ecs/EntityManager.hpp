#pragma once

#include <algorithm>
#include <vector>

class EntityManager {
  public:
    using EntityID = int;

    EntityID createEntity()
    {
        EntityID id = nextID++;
        activeEntities.push_back(id);
        return id;
    }

    void destroyEntities(EntityID id)
    {
        activeEntities.erase(std::remove(activeEntities.begin(), activeEntities.end(), id), activeEntities.end());
    }

  private:
    EntityID nextID = 0;
    std::vector<EntityID> activeEntities;
};
