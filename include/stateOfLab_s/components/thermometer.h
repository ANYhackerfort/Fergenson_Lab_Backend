#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "stateOfLab_s/lab_component.h"
#include <iostream>

class Thermometer : public LabComponent<double> {
public:
  // Constructor
  explicit Thermometer(const std::string &id, double initial_angle = 0.0)
      : LabComponent(id), angle(initial_angle) {}

  // Override the updateComponent method
  void updateComponent(const double &new_angle) override {
    angle = new_angle;
    std::cout << "Thermometer " << getID() << " updated to angle: " << angle
              << std::endl;
  }

  // Override the getComponentCurrently method
  double getComponentCurrently() const override { return angle; }

private:
  double angle; // Angle representing the state of the thermometer
};

#endif // THERMOMETER_H
