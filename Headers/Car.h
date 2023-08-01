#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
#include <iostream>
// Vehicle interface
class Car: public Vehicle {
    protected:
        double vehicle_speed;
        bool engine_on;
        double fuel_level;
        int current_gear;
        double max_speed;

    public:
        Car() {
            vehicle_speed = 0.0;
            engine_on = true;
            fuel_level = 0.0;
            current_gear = 0;
            max_speed = 10.0;
        }


        // Properties
        double getSpeed() override { return vehicle_speed; }
        bool isEngineOn() override { return engine_on; }
        double getFuelLevel() override { return fuel_level; }
        int getCurrentGear() override { return current_gear; }
        double getMaxSpeed() override { return max_speed; }

        // Methods
        void startEngine() override { engine_on = true; }
        void stopEngine() override { engine_on = false; }
        void changeGear(int new_gear) { current_gear = new_gear; }
        void accelerate(double amount) { vehicle_speed += amount; }
        void brake() { vehicle_speed = 0; }
};

#endif // CAR_H
