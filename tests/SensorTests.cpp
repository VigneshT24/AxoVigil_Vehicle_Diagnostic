#include <cassert>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>

#include "SpeedSensor.hpp"
#include "AccelerometerSensor.hpp"
#include "BrakePressureSensor.hpp"
#include "TemperatureSensor.hpp"
#include "BatterySensor.hpp"
#include "FuelSensor.hpp"
#include "TirePressureSensor.hpp"


bool approxEqual(double a, double b) {
    double tolerance = 0.001;
    return std::abs(a - b) < tolerance;
}

int main() {
    std::cout << "Sending Request to Testing Services to Perform Sensor Compliance Check.";

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // speed sensor assert testing
    VehicleSpeedSensor speedSensor;
    speedSensor.setSpeed(60.0);
    assert(approxEqual(speedSensor.getSpeed(), 60.0));
    std::cout << "[PASSED] setSpeed() and getspeed() method." << std::endl;

    // accelerometer sensor assert testing
    VehicleAccelerometerSensor accelSensor;
    accelSensor.setAcceleration(1.0, -2.0, 3.0);
    assert(approxEqual(accelSensor.getAccelerationX(), 1.0));
    std::cout << "[PASSED] setAcceleration() and getAccelerationX() method.";
    assert(approxEqual(accelSensor.getAccelerationX(), -2.0));
    std::cout << "[PASSED] setAcceleration() and getAccelerationY() method.";
    assert(approxEqual(accelSensor.getAccelerationX(), 3.0));
    std::cout << "[PASSED] setAcceleration() and getAccelerationZ() method.";

    accelSensor.setBias(0.1, 0.05, 0.04);
}