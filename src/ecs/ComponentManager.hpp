#pragma once

#include "EntityManager.hpp"
#include <unordered_map>
template <typename ComponentType> class ComponentManager {
  public:
    void addComponent(EntityManager::EntityID entity, const ComponentType &component)
    {
        m_components[entity] = component;
    }

    void removeComponent(EntityManager::EntityID entity)
    {
        m_components.erase(entity);
    }

    ComponentType *getComponent(EntityManager::EntityID entity)
    {
        if (m_components.find(entity) != m_components.end()) {
            return &m_components[entity];
        }
        return nullptr;
    }

    std::unordered_map<EntityManager::EntityID, ComponentType> &getAllComponents()
    {
        return m_components;
    }

    std::vector<EntityManager::EntityID> getAllEntities() const
    {
        std::vector<EntityManager::EntityID> entities;
        for (auto &[entity, _] : m_components) {
            entities.push_back(entity);
        }
        return entities;
    }

  private:
    std::unordered_map<EntityManager::EntityID, ComponentType> m_components;
};
