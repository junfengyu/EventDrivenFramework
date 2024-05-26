#include "event_dispatcher.h"

// Example event handler functions
void handleEventTypeA(const Event& event) {
    auto data = std::dynamic_pointer_cast<EventDataA>(event.data);
    if (data) {
        data->extractData();
    }
}

void handleEventTypeB(const Event& event) {
    auto data = std::dynamic_pointer_cast<EventDataB>(event.data);
    if (data) {
        data->extractData();
    }
}

void handleEventTypeC(const Event& event) {
    auto data = std::dynamic_pointer_cast<EventDataC>(event.data);
    if (data) {
        data->extractData();
    }
}

int main() {
    // Create an EventDispatcher instance
    EventDispatcher dispatcher;

    // Register event handlers
    dispatcher.registerEventHandler(EventType::EVENT_TYPE_A, handleEventTypeA);
    dispatcher.registerEventHandler(EventType::EVENT_TYPE_B, handleEventTypeB);
    dispatcher.registerEventHandler(EventType::EVENT_TYPE_C, handleEventTypeC);

    // Main thread: generate and add events using addEvent
    for (int i = 0; i < 10; ++i) {
        switch (i % 3) {
            case 0:
                dispatcher.addEvent(EventType::EVENT_TYPE_A, EventDataA{i}); // int data
                break;
            case 1:
                dispatcher.addEvent(EventType::EVENT_TYPE_B, EventDataB{std::to_string(i)}); // string data
                break;
            case 2:
                dispatcher.addEvent(EventType::EVENT_TYPE_C, EventDataC{i * 0.1}); // double data
                break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // The destructor of EventDispatcher will join the worker thread

    return 0;
}
