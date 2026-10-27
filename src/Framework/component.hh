/**
 * @author alvaro.zurinaga
 * @brief Declare the component base supplied with the assignment
 */

#pragma once

#include <string.h>
#include <iostream>

/**
 * @brief Group components into a game entity
 */
class Entity;


/**
 * @brief Provide a base for entity components
 */
class Component
{
protected:
    // Name of the component. All componenet must have an unique Id
    const char* name;
    // Pointer to the Entity that owns thew component. 
	Entity* mOwner;
public:
    
    /**
     * @brief Set the component name
     */
    Component(const char* name);
    
    /**
     * @brief Return the component name
     */
    const char* getName();
    
	/**
	 * @brief Return the entity that owns the component
	 */
	Entity* getOwner();

    /**
     * @brief Set the entity that owns the component
     */
    void setOwner(Entity* owner);

    /**
     * @brief Destroy the component
     */
    virtual ~Component() = default;
};
