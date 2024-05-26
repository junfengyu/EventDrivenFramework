#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

// Event types
enum class EventType {
    EVENT_TYPE_A,
    EVENT_TYPE_B,
    EVENT_TYPE_C
};

// Base class for event data
struct BaseEventData {
    virtual ~BaseEventData() = default;
    virtual void extractData() const = 0; // Pure virtual method to extract data
};

// Derived classes for different types of event data
struct EventDataA : BaseEventData {
    int data;
    EventDataA(int d);
    void extractData() const override;
};

struct EventDataB : BaseEventData {
    std::string data;
    EventDataB(const std::string& d);
    void extractData() const override;
};

struct EventDataC : BaseEventData {
    double data;
    EventDataC(double d);
    void extractData() const override;
};

// Event structure using std::shared_ptr<BaseEventData> to hold any type of event data
struct Event {
    EventType type;
    std::shared_ptr<BaseEventData> data;
};

// EventDispatcher class
class EventDispatcher {
public:
    using EventHandler = std::function<void(const Event&)>;

    EventDispatcher();
    ~EventDispatcher();

    void registerEventHandler(EventType type, EventHandler handler);
    void enqueueEvent(const Event& event);

    template<typename T>
    void addEvent(EventType type, T&& data) {
        auto event = Event{type, std::make_shared<std::decay_t<T>>(std::forward<T>(data))};
        enqueueEvent(event);
    }

private:
    void eventWorker();
    void dispatchEvent(const Event& event);

    std::queue<Event> eventQueue;
    std::unordered_map<EventType, std::vector<EventHandler>> eventHandlers;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    std::mutex handlersMutex;
    std::thread workerThread;
    bool stopFlag;
};

#endif // EVENT_DISPATCHER_H
