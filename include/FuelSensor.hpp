#pragma once

class VehicleFuelSensor {
    private:
        double fuelLiters;
        double tankCapacityLiters;
        double bias;
        double sloshNoise;

    public:
        VehicleFuelSensor();

        void setActualFuelLiters(double new_liters);
        void setTankCapacity(double new_liters);

        double getFuelLiters() const;
        double getFuelPercentage() const;

        void setBias(double new_bias);
        void setSloshNoise(double new_noise);

        bool isLowFuel() const;
}