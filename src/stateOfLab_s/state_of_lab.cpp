#include "state_of_lab.h"
#include <iostream>

StateOfLabs::StateOfLabs(const std::string& preset) {
    if (preset.empty()) {
        throw std::invalid_argument("Error: You need a preset to construct StateOfLabs.");
    }

    if (preset == "frankhertz1") {
        std::cout << "Initializing StateOfLabs with preset: frankhertz1" << std::endl;

        // Add a thermometer as an example component
        lab_components["thermometer_1"] = std::make_tuple(
            "Thermometer 1",
            std::make_shared<Thermometer>("thermometer_1", 0.0),
            "Thermometer"
        );
    } else {
        throw std::invalid_argument("Error: Unknown preset provided.");
    }
}

void StateOfLabs::updateComponent(const std::string& id, double value) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = lab_components.find(id);
    if (it != lab_components.end()) {
        auto& [name, component, className] = it->second;
        if (className == "Thermometer") {
            auto thermometer = std::dynamic_pointer_cast<Thermometer>(component);
            if (thermometer) {
                thermometer->updateComponent(value);
                return;
            }
        }
        // Add other types as needed
        throw std::runtime_error("Unsupported or mismatched component type: " + className);
    } else {
        throw std::runtime_error("Component not found.");
    }
}

double StateOfLabs::getComponent(const std::string& id) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = lab_components.find(id);
    if (it != lab_components.end()) {
        auto& [name, component, className] = it->second;
        if (className == "Thermometer") {
            auto thermometer = std::dynamic_pointer_cast<Thermometer>(component);
            if (thermometer) {
                return thermometer->getComponentCurrently();
            }
        }
        // Add handling for other types if needed
        throw std::runtime_error("Unsupported or mismatched component type: " + className);
    } else {
        throw std::runtime_error("Component not found.");
    }
}


std::string StateOfLabs::getComponentClassName(const std::string& id) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = lab_components.find(id);
    if (it != lab_components.end()) {
        return std::get<2>(it->second);
    } else {
        throw std::runtime_error("Component not found.");
    }
}
