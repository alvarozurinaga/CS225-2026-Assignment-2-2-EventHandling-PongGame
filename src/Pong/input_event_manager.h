/**
 * @author alvaro.zurinaga
 * @brief Convert keyboard state into device-independent movement events
 */

#ifndef INPUT_EVENT_MANAGER_H
#define INPUT_EVENT_MANAGER_H

#include "../Framework/event_handlers.hh"

/**
 * @brief Convert keyboard input into movement events
 */
class InputEventManager : public EventManager
{
private:
    bool enabled;

public:
    /**
     * @brief Enable gameplay input
     */
    InputEventManager();

    /**
     * @brief Enable or disable gameplay input
     */
    void setEnabled(bool newEnabled);

    /**
     * @brief Send movement events from the keyboard state
     */
    virtual void update() override;
};

#endif
