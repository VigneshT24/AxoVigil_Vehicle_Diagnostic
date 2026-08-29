#pragma once

class VehicleSpeedSensor {
    private:
        // speed in MPH for now
        int speed;
    
    public:
        // constructor
        VehicleSpeedSensor();

        // setter method to set speed
        void setSpeed(double new_speed);

        // getter method to get speed
        double getSpeed() const;
};