/**
 * @author alvaro.zurinaga
 * @brief Declare the entity base supplied with the assignment
 */

#pragma once
#include <vector>
#include "component.hh"

/**
 * @brief Group components into a game entity
 */
class Entity
{
protected:
    // Components attached to the class
    std::vector<Component*> components;
public:
    /**
     * @brief Find a component by its name
     */
    Component* getComponent(const char* name);
    
    /**
     * @brief Add a component to the entity
     */
    void attach(Component* component);
    
    /**
     * @brief Update the entity
     */
    virtual void Update();

    /**
     * @brief Draw the entity
     */
    virtual void Draw();

    /**
     * @brief Delete the entity components
     */
    virtual ~Entity();
};

