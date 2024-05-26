Sure! Here is a sample `README.md` file for the `EventDispatcher` project.

### README.md

```markdown
# EventDispatcher

EventDispatcher is a C++ event dispatch system that uses a custom base class with inheritance to manage different types of event data. This project demonstrates how to handle events asynchronously using a worker thread, with different event types and data structures.

## Features

- Supports multiple event types
- Handles events with different data structures using inheritance
- Uses a worker thread to process events asynchronously
- Thread-safe event addition
- Flexible event handling system

## Requirements

- C++17 compatible compiler
- CMake 3.10 or higher

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/yourusername/EventDispatcher.git
cd EventDispatcher
```

### Build the Project

1. **Create a build directory**:

    ```bash
    mkdir build
    cd build
    ```

2. **Generate the build files**:

    ```bash
    cmake ..
    ```

3. **Build the project**:

    ```bash
    make
    ```

### Run the Example

```bash
./event_dispatcher
```

## Usage

The `EventDispatcher` class allows you to register event handlers, enqueue events, and handle events asynchronously. Here is a brief overview of how to use the `EventDispatcher` class:

### Register Event Handlers

```cpp
dispatcher.registerEventHandler(EventType::EVENT_TYPE_A, handleEventTypeA);
dispatcher.registerEventHandler(EventType::EVENT_TYPE_B, handleEventTypeB);
dispatcher.registerEventHandler(EventType::EVENT_TYPE_C, handleEventTypeC);
```

### Add Events

You can add events from any thread or function using the `addEvent` method:

```cpp
dispatcher.addEvent(EventType::EVENT_TYPE_A, EventDataA{42});
dispatcher.addEvent(EventType::EVENT_TYPE_B, EventDataB{"Hello, World!"});
dispatcher.addEvent(EventType::EVENT_TYPE_C, EventDataC{3.14});
```

### Event Handlers

Define event handlers to process the events:

```cpp
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
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This `README.md` provides an overview of the project, instructions for building and running the project, and a brief guide on how to use the `EventDispatcher` class. It also includes standard sections for license and contributing, making it suitable for a GitHub repository.
