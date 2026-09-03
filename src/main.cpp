#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>
#include <unordered_map>

#include <AccelerometerSensor.hpp>
#include <BatterySensor.hpp>
#include <BrakePressureSensor.hpp>
#include <FuelSensor.hpp>
#include <SpeedSensor.hpp>
#include <TemperatureSensor.hpp>
#include <TirePressureSensor.hpp>

// our vehicle diagnostic system will utilize a trapezoidal velocity profile testing methodology

double randomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

int main() {
    std::cout << "================================================= AxoVigil Vehical Diagnostic =================================================" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    double speed = 0;
    // in celsius (standard metric)
    double temperature = 0;

    // currently either "NORMAL" or "ABNORMAL"
    std::string status = "";

    int test_duration = 0;

    std::cout << "Enter the duration of the vehicle diagnostic test (in seconds): ";
    std::cin >> test_duration;

    std::string min_or_mins = (int(test_duration / 60) <= 1) ? " minute " : " minutes ";
    std::string sec_or_secs = (int(test_duration % 60) <= 1) ? " second " : " seconds ";

    std::cout << "The test duration: " << (test_duration / 60) << min_or_mins << "and " << (test_duration % 60) << sec_or_secs << std::endl;

    std::cout << "I need some information about your vehicle." << std::endl << std::endl;

    std::unordered_map<std::string, int> vehicleType;
    double fuelRemain;

    std::cout << "Please enter the number corresponding to your vehicle's type: " << std::endl
              << "0: Sedan" << std::endl 
              << "1: SUV" << std::endl
              << "2: Hatchback" << std::endl
              << "3: Coupe" << std::endl
              << "4: Convertible" << std::endl
              << "5: Pickup Truck" << std::endl;
    
    std::cout << "Enter: ";

    int temp_num;
    std::cin >> temp_num;

    while (temp_num < 0 || temp_num > 5) {
        std::cout << "\nPlease enter an integer between 0 and 5, corresponding to your vehicle type." << std::endl;
        std::cout << "Enter: ";
        std::cin >> temp_num;
    }

    std::cout << "\nGot it. Now please enter your vehicle's current fuel remaining (a number between 0.0 and 100.0, as percentage, no percent sign)." << std::endl;
    std::cout << "Enter: ";
    std::cin >> fuelRemain;

    while (fuelRemain < 0.0 || fuelRemain > 100.0) {
        std::cout << "\nPlease enter an integer between 0.0 and 100.0, corresponding to the fuel percentage of your vehicle currently." << std::endl;
        std::cout << "Enter: ";
        std::cin >> fuelRemain;
    }
    
    switch(temp_num) {
        case 0:
            vehicleType["Sedan"] = 55;
            break;
        case 1:
            vehicleType["SUV"] = 65;
            break;
        case 2:
            vehicleType["Hatchback"] = 45;
            break;
        case 3:
            vehicleType["Coupe"] = 60;
            break;
        case 4:
            vehicleType["Convertible"] = 55;
            break;
        case 5:
            vehicleType["Pickup Truck"] = 98;
            break;
    }

    std::cout << "\n\nJust to confirm, your vehicle type is a " << vehicleType.begin()->first << "." << std::endl
              << "You have currently " << (fuelRemain / 100.0) * vehicleType.begin()->second << " liters of fuel out of " << vehicleType.begin()->second << " total liters." << std::endl; 
    
    double tankCapacity = vehicleType.begin()->second;
    double fuelLiters = (fuelRemain / 100.0) * tankCapacity;

    VehicleSpeedSensor speedSensor;
    VehicleAccelerometerSensor accelSensor;
    VehicleBatterySensor battSensor;
    VehicleFuelSensor fuelSensor;
    VehicleBrakePressureSensor brakeSensor;
    VehicleTemperatureSensor tempSensor;
    VehicleTirePressureSensor tireSensor;
    
    // setting initial values before phase 1
    // values are chosen based on research on average estimated sensor reading of an idle vehicle
    double ambientTemperature = randomDouble(18.0, 30.0);
    speedSensor.setSpeed(0.0);

    tempSensor.setAmbientTemperature(ambientTemperature);
    tempSensor.setCoolantTemperature(randomDouble(91.0, 98.0));
    tempSensor.setBias(randomDouble(-0.4, 0.4));
    tempSensor.setNoiseLevel(randomDouble(0.02, 0.15));

    accelSensor.setBias(randomDouble(-0.15, 0.15), randomDouble(-0.15, 0.15), randomDouble(-0.15, 0.15));
    accelSensor.setNoiseLevel(randomDouble(0.005, 0.030));
    accelSensor.setAcceleration(0.0, 0.0, 9.80665);

    battSensor.setVoltage(randomDouble(13.7, 14.5));
    battSensor.setCurrent(randomDouble(1.0, 15.0));
    battSensor.setTemperature(ambientTemperature + randomDouble(0.0, 5.0));
    battSensor.setVoltageBias(randomDouble(-0.03, 0.03));
    battSensor.setCurrentBias(randomDouble(-0.10, 0.10));
    battSensor.setTemperatureBias(randomDouble(-3.0, 3.0));
    battSensor.setVoltageNoise(randomDouble(0.005, 0.025));
    battSensor.setCurrentNoise(randomDouble(0.005, 0.025));
    battSensor.setTemperatureNoise(randomDouble(0.005, 0.025));

    fuelSensor.setTankCapacity(tankCapacity); // this one depends on the type of vehicle (prompted prior)
    fuelSensor.setFuelLiters(fuelLiters); // this one depends on the fuel set by user (prompted prior)
    fuelSensor.setBias(randomDouble(-0.50, 0.50));
    fuelSensor.setSloshNoise(randomDouble(0.0, 0.05));

    brakeSensor.setPressureBias(randomDouble(-5.0, 5.0));
    brakeSensor.setNoiseLevel(randomDouble(0.25, 2.0));
    brakeSensor.setFrontBrakePressure(randomDouble(0.0, 2.0));
    brakeSensor.setRearBrakePressure(randomDouble(0.0, 2.0));

    tireSensor.setFrontLeftPressure(randomDouble(34.0, 36.0));
    tireSensor.setFrontRightPressure(randomDouble(34.0, 36.0));
    tireSensor.setRearLeftPressure(randomDouble(34.0, 36.0));
    tireSensor.setRearRightPressure(randomDouble(34.0, 36.0));
    tireSensor.setFrontLeftTemperature(ambientTemperature + randomDouble(-1.0, 1.0));
    tireSensor.setFrontRightTemperature(ambientTemperature + randomDouble(-1.0, 1.0));
    tireSensor.setRearLeftTemperature(ambientTemperature + randomDouble(-1.0, 1.0));
    tireSensor.setRearRightTemperature(ambientTemperature + randomDouble(-1.0, 1.0));
    tireSensor.setPressureBias(randomDouble(-0.5, 0.5));
    tireSensor.setPressureNoise(randomDouble(0.02, 0.10));

    
    double phaseDuration = (test_duration / 3.0);
    double maxSpeed = 160;
    double speedIncreasePerSecond = (maxSpeed / phaseDuration);
    double longitudinalAcceleration = speedIncreasePerSecond * 0.44704; // calculating the acceleration
    int elapsed = 0;


    // phase 1 of trapezoidal profile testing (idle to top speed)
    for (int i = 0; i < phaseDuration; i++) {

        // speed
        double newSpeed = speedSensor.getSpeed() + speedIncreasePerSecond;

        if (newSpeed > maxSpeed) {
            newSpeed = maxSpeed;
        }

        speedSensor.setSpeed(newSpeed);

        // acceleration
        accelSensor.setAcceleration(longitudinalAcceleration, 0.0, 9.80665);

        // coolant temperature
        tempSensor.setCoolantTemperature(tempSensor.getCoolantTemperature() + randomDouble(0.10, 0.30));

        // battery voltage
        battSensor.setVoltage(battSensor.getVoltage() + randomDouble(-0.03, 0.03));

        // battery current
        battSensor.setCurrent(battSensor.getCurrent() + randomDouble(-0.5, 0.5));

        // battery temperature
        battSensor.setTemperature(battSensor.getTemperature() + randomDouble(0.01, 0.05));

        // fuel
        fuelSensor.setFuelLiters(fuelSensor.getFuelLiters() - randomDouble(0.002, 0.006));

        // brake pressure stays near zero
        brakeSensor.setFrontBrakePressure(randomDouble(0.0, 2.0));

        brakeSensor.setRearBrakePressure(randomDouble(0.0, 2.0));

        // tire pressure
        tireSensor.setFrontLeftPressure(tireSensor.getFrontLeftPressure() + randomDouble(0.005, 0.020));

        tireSensor.setFrontRightPressure(tireSensor.getFrontRightPressure() + randomDouble(0.005, 0.020));

        tireSensor.setRearLeftPressure(tireSensor.getRearLeftPressure() + randomDouble(0.005, 0.020));

        tireSensor.setRearRightPressure(tireSensor.getRearRightPressure() + randomDouble(0.005, 0.020));

        // tire temperature
        tireSensor.setFrontLeftTemperature(tireSensor.getFrontLeftTemperature() + randomDouble(0.03, 0.08));

        tireSensor.setFrontRightTemperature(tireSensor.getFrontRightTemperature() + randomDouble(0.03, 0.08));

        tireSensor.setRearLeftTemperature(tireSensor.getRearLeftTemperature() + randomDouble(0.03, 0.08));

        tireSensor.setRearRightTemperature(tireSensor.getRearRightTemperature() + randomDouble(0.03, 0.08));

        // temperory debug output
        std::cout
            << "Phase 1 | "
            << "Time: " << elapsed + 1 << "s | "
            << "Speed: " << speedSensor.getSpeed()
            << " mph | "
            << "Accel: " << accelSensor.getAccelerationX()
            << " m/s^2 | "
            << "Coolant: " << tempSensor.getCoolantTemperature()
            << " C"
            << std::endl;
        
        elapsed++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}