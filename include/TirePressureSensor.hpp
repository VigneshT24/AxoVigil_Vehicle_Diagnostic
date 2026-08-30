#pragma once

class VehicleTirePressureSensor {
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
        double pressureNoise;
    
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

        void setPressureBias(double bias);
        void setPressureNoise(double noise);
}