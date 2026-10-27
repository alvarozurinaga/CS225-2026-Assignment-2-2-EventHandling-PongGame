/**
 * @author alvaro.zurinaga
 * @brief Declare the generic event framework supplied with the assignment
 */

#pragma once

#include "event.hh"
#include <vector>

/**
 * @brief Define the interface for receiving events
 */
class IEventHandler
{
    public:
        /**
         * @brief Process the received event
         */
        virtual void call(Event* event) = 0;
};

/**
 * @brief Connect typed events to a subscriber callback
 */
template<typename T, typename EVT>
class EventHandler : public IEventHandler
{
    protected:
        // typedef of the function pointer that process the event
        typedef void (T::*ActionMethod)(EVT*); 
        // Object itereste din the event
        T* object;
        // Function pointer to the action processing the event
        ActionMethod method;
    public:
        /**
         * @brief Connect a subscriber to its event callback
         */
        EventHandler(T* object, ActionMethod method) : object(object), method(method) {}
        
        /**
         * @brief Process the received event
         */
        void call(Event *event) override {
            EVT* specific_event = dynamic_cast<EVT*>(event);
            if(specific_event != nullptr)
                (object->*method)(specific_event);
        }
};


/**
 * @brief Manage event subscriptions and notifications
 */
class EventManager
{
    std::vector<IEventHandler*> listeners;
    public:
        /**
         * @brief Subscribe a handler to events
         */
        void registerEventHandler(IEventHandler* handler) {
            listeners.push_back(handler);
        }

        /**
         * @brief Return the handler at an index
         */
        IEventHandler* getEventHandlerAt(int index){
            return listeners[index];   
        }

        /**
         * @brief Send an event to the subscribed handlers
         */
        void notifyEvent(Event* event) {
            for(auto *listener : listeners) 
                listener->call(event);
        }

	/**
	 * @brief Detect events for the current update
	 */
	virtual void update() = 0;
};
