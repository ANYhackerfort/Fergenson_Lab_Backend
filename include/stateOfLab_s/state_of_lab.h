#ifndef STATE_OF_LABS_H
#define STATE_OF_LABS_H

#include "lab_component.h"
#include "thermometer.h"
#include <map>
#include <string>
#include <memory>
#include <tuple>
#include <mutex>
#include <stdexcept>

// StateOfLabs class for managing lab components
class StateOfLabs {
public:
    // Constructor
    explicit StateOfLabs(const std::string& preset);

    // Method to update a component's value (thread-safe)
    void updateComponent(const std::string& id, double value);

    // Method to get a component's current value (thread-safe)
    double getComponent(const std::string& id) const;

    // Method to get the class name of a component
    std::string getComponentClassName(const std::string& id) const;

private:
    // Map of component ID to a tuple containing additional information
    std::map<std::string, std::tuple<std::string, std::shared_ptr<LabComponentBase>, std::string>> lab_components;

    mutable std::mutex mtx; // Mutex for thread-safe access
};

#endif // STATE_OF_LABS_H
