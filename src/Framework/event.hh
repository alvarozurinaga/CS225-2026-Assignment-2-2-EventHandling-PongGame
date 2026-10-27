/**
 * @author alvaro.zurinaga
 * @brief Declare the event base supplied with the assignment
 */

#pragma once

/**
 * @brief Provide a base for game events
 */
class Event
{
    public:
        /**
         * @brief Destroy the event
         */
        virtual ~Event() = default;
};
