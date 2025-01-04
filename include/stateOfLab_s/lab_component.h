#ifndef LAB_COMPONENT_H
#define LAB_COMPONENT_H

#include <string>
#include <memory>

// Base class for lab components
class LabComponentBase {
public:
    explicit LabComponentBase(const std::string& id) : unique_id(id) {}
    virtual ~LabComponentBase() = default;

    // Virtual method to update the component
    virtual void updateComponent(double value) = 0;

    // Virtual method to get the current component state
    virtual double getComponentCurrently() const = 0;

    // Getter for the unique ID
    std::string getID() const { return unique_id; }

private:
    std::string unique_id; // Unique identifier for the component
};

// Templated derived class for specific types
template <typename T>
class LabComponent : public LabComponentBase {
public:
    explicit LabComponent(const std::string& id) : LabComponentBase(id) {}
    virtual void updateComponent(const T& value) override = 0;
    virtual T getComponentCurrently() const override = 0;
};

#endif // LAB_COMPONENT_H
