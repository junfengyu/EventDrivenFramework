#include "event_dispatcher.h"

// EventDataA implementation
EventDataA::EventDataA(int d) : data(d) {}

void EventDataA::extractData() const {
    std::cout << "EventDataA: " << data << std::endl;
}

// EventDataB implementation
EventDataB::EventDataB(const std::string& d) : data(d) {}

void EventDataB::extractData() const {
    std::cout << "EventDataB: " << data << std::endl;
}

// EventDataC implementation
EventDataC::EventDataC(double d) : data(d) {}

void EventDataC::extractData() const {
    std::cout << "EventDataC: " << data << std::endl;
}

// EventDispatcher implementation
EventDispatcher::EventDispatcher() : stopFlag(false) {
    workerThread = std::thread(&EventDispatcher::eventWorker, this);
}

EventDispatcher::~EventDispatcher() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopFlag = true;
    }
    queueCV.notify_all();
    workerThread.join();
}

void EventDispatcher::registerEventHandler(EventType type, EventHandler handler) {
    std::lock_guard<std::mutex> lock(handlersMutex);
    eventHandlers[type].emplace_back(handler);
}

void EventDispatcher::enqueueEvent(const Event& event) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push(event);
    }
    queueCV.notify_one();
}

void EventDispatcher::eventWorker() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, [this] { return !eventQueue.empty() || stopFlag; });

        if (stopFlag && eventQueue.empty()) {
            return;
        }

        Event event = eventQueue.front();
        eventQueue.pop();
        lock.unlock();

        dispatchEvent(event);
    }
}

void EventDispatcher::dispatchEvent(const Event& event) {
    std::lock_guard<std::mutex> lock(handlersMutex);
    if (eventHandlers.find(event.type) != eventHandlers.end()) {
        for (auto& handler : eventHandlers[event.type]) {
            handler(event);
        }
    }
}
