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

    std::cout
        << "Sending Request to Testing Services to Perform Sensor Compliance Check."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // SPEED SENSOR ASSERT TESTING
    VehicleSpeedSensor speedSensor;

    speedSensor.setSpeed(60.0);

    assert(
        approxEqual(
            speedSensor.getSpeed(),
            60.0
        )
    );

    std::cout
        << "[PASSED] setSpeed() and getSpeed() methods."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // ACCELEROMETER SENSOR ASSERT TESTING
    VehicleAccelerometerSensor accelSensor;

    // Disable bias/noise while testing basic acceleration values.
    accelSensor.setBias(0.0, 0.0, 0.0);
    accelSensor.setNoiseLevel(0.0);

    accelSensor.setAcceleration(
        1.0,
        -2.0,
        3.0
    );

    assert(
        approxEqual(
            accelSensor.getAccelerationX(),
            1.0
        )
    );

    std::cout
        << "[PASSED] setAcceleration() and getAccelerationX() methods."
        << std::endl;


    assert(
        approxEqual(
            accelSensor.getAccelerationY(),
            -2.0
        )
    );

    std::cout
        << "[PASSED] setAcceleration() and getAccelerationY() methods."
        << std::endl;


    assert(
        approxEqual(
            accelSensor.getAccelerationZ(),
            3.0
        )
    );

    std::cout
        << "[PASSED] setAcceleration() and getAccelerationZ() methods."
        << std::endl;


    // Test accelerometer bias separately.
    accelSensor.setBias(
        0.1,
        0.05,
        -0.2
    );

    assert(
        approxEqual(
            accelSensor.getAccelerationX(),
            1.1
        )
    );

    assert(
        approxEqual(
            accelSensor.getAccelerationY(),
            -1.95
        )
    );

    assert(
        approxEqual(
            accelSensor.getAccelerationZ(),
            2.8
        )
    );

    std::cout
        << "[PASSED] Accelerometer bias application."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // BRAKE PRESSURE SENSOR ASSERT TESTING
    VehicleBrakePressureSensor brakeSensor;

    brakeSensor.setPressureBias(0.0);
    brakeSensor.setNoiseLevel(0.0);

    brakeSensor.setFrontBrakePressure(600.0);
    brakeSensor.setRearBrakePressure(400.0);

    assert(
        approxEqual(
            brakeSensor.getFrontBrakePressure(),
            600.0
        )
    );

    std::cout
        << "[PASSED] Front brake pressure setter/getter."
        << std::endl;


    assert(
        approxEqual(
            brakeSensor.getRearBrakePressure(),
            400.0
        )
    );

    std::cout
        << "[PASSED] Rear brake pressure setter/getter."
        << std::endl;


    assert(
        approxEqual(
            brakeSensor.getAverageBrakePressure(),
            500.0
        )
    );

    std::cout
        << "[PASSED] getAverageBrakePressure() calculation."
        << std::endl;


    assert(brakeSensor.isWithinSensorRange());

    std::cout
        << "[PASSED] Brake pressure sensor valid-range check."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // TEMPERATURE SENSOR ASSERT TESTING
    VehicleTemperatureSensor tempSensor;

    tempSensor.setBias(0.0);
    tempSensor.setNoiseLevel(0.0);

    tempSensor.setCoolantTemperature(90.0);
    tempSensor.setAmbientTemperature(25.0);

    assert(
        approxEqual(
            tempSensor.getCoolantTemperature(),
            90.0
        )
    );

    std::cout
        << "[PASSED] Coolant temperature setter/getter."
        << std::endl;


    assert(
        approxEqual(
            tempSensor.getAmbientTemperature(),
            25.0
        )
    );

    std::cout
        << "[PASSED] Ambient temperature setter/getter."
        << std::endl;


    assert(
        tempSensor.isWithinSensorRange()
    );

    std::cout
        << "[PASSED] Temperature sensor valid-range check."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // BATTERY SENSOR ASSERT TESTING
    VehicleBatterySensor battSensor;

    battSensor.setVoltageBias(0.0);
    battSensor.setCurrentBias(0.0);
    battSensor.setTemperatureBias(0.0);
    battSensor.setNoiseLevel(0.0);

    battSensor.setVoltage(13.8);
    battSensor.setCurrent(20.0);
    battSensor.setTemperature(30.0);

    assert(
        approxEqual(
            battSensor.getVoltage(),
            13.8
        )
    );

    std::cout
        << "[PASSED] Battery voltage setter/getter."
        << std::endl;


    assert(
        approxEqual(
            battSensor.getCurrent(),
            20.0
        )
    );

    std::cout
        << "[PASSED] Battery current setter/getter."
        << std::endl;


    assert(
        approxEqual(
            battSensor.getTemperature(),
            30.0
        )
    );

    std::cout
        << "[PASSED] Battery temperature setter/getter."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // FUEL SENSOR ASSERT TESTING
    VehicleFuelSensor fuelSensor;

    fuelSensor.setBias(0.0);
    fuelSensor.setSloshNoise(0.0);

    fuelSensor.setTankCapacity(60.0);
    fuelSensor.setFuelLiters(30.0);

    assert(
        approxEqual(
            fuelSensor.getFuelLiters(),
            30.0
        )
    );

    std::cout
        << "[PASSED] Fuel quantity setter/getter."
        << std::endl;


    assert(
        approxEqual(
            fuelSensor.getFuelPercentage(),
            50.0
        )
    );

    std::cout
        << "[PASSED] Fuel percentage calculation."
        << std::endl;


    assert(
        !fuelSensor.isLowFuel()
    );

    std::cout
        << "[PASSED] Normal fuel-level detection."
        << std::endl;


    fuelSensor.setFuelLiters(3.0);

    assert(fuelSensor.isLowFuel());

    std::cout
        << "[PASSED] Low-fuel detection."
        << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // TIRE PRESSURE SENSOR ASSERT TESTING
    VehicleTirePressureSensor tireSensor;

    tireSensor.setPressureBias(0.0);
    tireSensor.setPressureNoise(0.0);

    tireSensor.setFrontLeftPressure(33.0);
    tireSensor.setFrontRightPressure(32.5);
    tireSensor.setRearLeftPressure(34.0);
    tireSensor.setRearRightPressure(33.5);

    assert(
        approxEqual(
            tireSensor.getFrontLeftPressure(),
            33.0
        )
    );

    std::cout
        << "[PASSED] Front-left tire pressure."
        << std::endl;


    assert(
        approxEqual(
            tireSensor.getFrontRightPressure(),
            32.5
        )
    );

    std::cout
        << "[PASSED] Front-right tire pressure."
        << std::endl;


    assert(
        approxEqual(
            tireSensor.getRearLeftPressure(),
            34.0
        )
    );

    std::cout
        << "[PASSED] Rear-left tire pressure."
        << std::endl;


    assert(
        approxEqual(
            tireSensor.getRearRightPressure(),
            33.5
        )
    );

    std::cout
        << "[PASSED] Rear-right tire pressure."
        << std::endl;


    tireSensor.setFrontLeftTemperature(31.0);
    tireSensor.setFrontRightTemperature(32.0);
    tireSensor.setRearLeftTemperature(30.0);
    tireSensor.setRearRightTemperature(31.5);

    assert(
        approxEqual(
            tireSensor.getFrontLeftTemperature(),
            31.0
        )
    );

    assert(
        approxEqual(
            tireSensor.getFrontRightTemperature(),
            32.0
        )
    );

    assert(
        approxEqual(
            tireSensor.getRearLeftTemperature(),
            30.0
        )
    );

    assert(
        approxEqual(
            tireSensor.getRearRightTemperature(),
            31.5
        )
    );

    std::cout
        << "[PASSED] All tire temperature setters/getters."
        << std::endl;

    // TESTING COMPLETE
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << std::endl;
    std::cout
        << "=================================================="
        << std::endl;

    std::cout
        << "ALL SENSOR COMPLIANCE TESTS PASSED."
        << std::endl;

    std::cout
        << "=================================================="
        << std::endl;


    return 0;
}