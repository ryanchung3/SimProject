#ifndef VEHICLE_H
#define VEHICLE_H

// Vehicle interface
class Vehicle {

    public:

        // Properties
        virtual double getSpeed() = 0;
        virtual bool isEngineOn() = 0;
        virtual double getFuelLevel() = 0;
        virtual int getCurrentGear() = 0;
        virtual double getMaxSpeed()  = 0;

        // Methods
        virtual void startEngine() = 0;
        virtual void stopEngine() = 0;
        virtual void changeGear(int newGear) = 0;
        virtual void accelerate(double amount) = 0;
        virtual void brake() = 0;
};

#endif // VEHICLE_H