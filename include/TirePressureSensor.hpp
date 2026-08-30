#pragma once
#include "GeneralSensor.hpp"

class VehicleTirePressureSensor : protected VehicleGeneralSensor {
    private:
        // in PSI
        double frontLeftPressure;
        double frontRightPressure;
        double rearLeftPressure;
        double rearRightPressure;

        // in Celsius
        double frontLeftTemperature;
        double frontRightTemperature;
        double rearLeftTemperature;
        double rearRightTemperature;

        double pressureBias;
        double temperatureBias;
        double pressureNoise;
        double temperatureNoise;
    
    public:
        VehicleTirePressureSensor();

        void setFrontLeftPressure(double new_fl_pressure);
        void setFrontRightPressure(double new_fr_pressure);
        void setRearLeftPressure(double new_rl_pressure);
        void setRearRightPressure(double new_rr_pressure);

        void setFrontLeftTemperature(double temperature);
        void setFrontRightTemperature(double temperature);
        void setRearLeftTemperature(double temperature);
        void setRearRightTemperature(double temperature);

        double getFrontLeftPressure() const;
        double getFrontRightPressure() const;
        double getRearLeftPressure() const;
        double getRearRightPressure() const;

        double getFrontLeftTemperature() const;
        double getFrontRightTemperature() const;
        double getRearLeftTemperature() const;
        double getRearRightTemperature() const;

        void setPressureBias(double p_bias);
        void setPressureNoise(double p_noise);
        void setTemperatureBias(double t_bias);
        void setTemperatureNoise(double t_noise);
};