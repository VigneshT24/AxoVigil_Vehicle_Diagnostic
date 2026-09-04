#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>
#include <unordered_map>
#include <iomanip>

#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <AccelerometerSensor.hpp>
#include <BatterySensor.hpp>
#include <BrakePressureSensor.hpp>
#include <FuelSensor.hpp>
#include <SpeedSensor.hpp>
#include <TemperatureSensor.hpp>
#include <TirePressureSensor.hpp>

using namespace ftxui;

// our vehicle diagnostic system will utilize a trapezoidal velocity profile testing methodology

std::string formatDouble(double value, int precision = 2) {

    std::ostringstream stream;

    stream
        << std::fixed
        << std::setprecision(precision)
        << value;

    return stream.str();
}

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
    std::string currentPhase = "INITIALIZING";

    int test_duration = 0;

    std::cout << "Enter the duration of the vehicle diagnostic test (in seconds): ";
    std::cin >> test_duration;

    while (test_duration < 80) {
        std::cout << "\nThe duration must not be shorter than 80 seconds: ";
        std::cin >> test_duration;
    }

    std::cout << std::endl;

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

    while (fuelRemain <= 0.0 || fuelRemain > 100.0) {
        std::cout << "\nPlease enter an integer between 0.0 and 100.0 (not 0.0), corresponding to the fuel percentage of your vehicle currently." << std::endl;
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

    std::this_thread::sleep_for(std::chrono::seconds(5));
    
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

    // simulated vehicle state; sensor getters are reserved for readings/output
    double vehicleSpeed = 0.0;
    double coolantTemperature = randomDouble(91.0, 98.0);
    double batteryVoltage = randomDouble(13.7, 14.5);
    double batteryCurrent = randomDouble(1.0, 15.0);
    double batteryTemperature = ambientTemperature + randomDouble(0.0, 5.0);
    double remainingFuel = fuelLiters;

    double frontLeftPressure = randomDouble(34.0, 36.0);
    double frontRightPressure = randomDouble(34.0, 36.0);
    double rearLeftPressure = randomDouble(34.0, 36.0);
    double rearRightPressure = randomDouble(34.0, 36.0);

    double frontLeftTireTemperature = ambientTemperature + randomDouble(-1.0, 1.0);
    double frontRightTireTemperature = ambientTemperature + randomDouble(-1.0, 1.0);
    double rearLeftTireTemperature = ambientTemperature + randomDouble(-1.0, 1.0);
    double rearRightTireTemperature = ambientTemperature + randomDouble(-1.0, 1.0);

    speedSensor.setSpeed(vehicleSpeed);

    tempSensor.setAmbientTemperature(ambientTemperature);
    tempSensor.setCoolantTemperature(coolantTemperature);
    tempSensor.setBias(randomDouble(-0.4, 0.4));
    tempSensor.setNoiseLevel(randomDouble(0.02, 0.15));

    accelSensor.setBias(randomDouble(-0.15, 0.15), randomDouble(-0.15, 0.15), randomDouble(-0.15, 0.15));
    accelSensor.setNoiseLevel(randomDouble(0.005, 0.030));
    accelSensor.setAcceleration(0.0, 0.0, 9.80665);

    battSensor.setVoltage(batteryVoltage);
    battSensor.setCurrent(batteryCurrent);
    battSensor.setTemperature(batteryTemperature);
    battSensor.setVoltageBias(randomDouble(-0.03, 0.03));
    battSensor.setCurrentBias(randomDouble(-0.10, 0.10));
    battSensor.setTemperatureBias(randomDouble(-3.0, 3.0));
    battSensor.setVoltageNoise(randomDouble(0.005, 0.025));
    battSensor.setCurrentNoise(randomDouble(0.005, 0.025));
    battSensor.setTemperatureNoise(randomDouble(0.005, 0.025));

    fuelSensor.setTankCapacity(tankCapacity); // this one depends on the type of vehicle (prompted prior)
    fuelSensor.setFuelLiters(remainingFuel); // this one depends on the fuel set by user (prompted prior)
    fuelSensor.setBias(randomDouble(-0.50, 0.50));
    fuelSensor.setSloshNoise(randomDouble(0.0, 0.05));

    brakeSensor.setPressureBias(randomDouble(-5.0, 5.0));
    brakeSensor.setNoiseLevel(randomDouble(0.25, 2.0));
    brakeSensor.setFrontBrakePressure(randomDouble(0.0, 2.0));
    brakeSensor.setRearBrakePressure(randomDouble(0.0, 2.0));

    tireSensor.setFrontLeftPressure(frontLeftPressure);
    tireSensor.setFrontRightPressure(frontRightPressure);
    tireSensor.setRearLeftPressure(rearLeftPressure);
    tireSensor.setRearRightPressure(rearRightPressure);
    tireSensor.setFrontLeftTemperature(frontLeftTireTemperature);
    tireSensor.setFrontRightTemperature(frontRightTireTemperature);
    tireSensor.setRearLeftTemperature(rearLeftTireTemperature);
    tireSensor.setRearRightTemperature(rearRightTireTemperature);
    tireSensor.setPressureBias(randomDouble(-0.5, 0.5));
    tireSensor.setPressureNoise(randomDouble(0.02, 0.10));

    
    double phaseDuration = (test_duration / 3.0);
    double maxSpeed = 80;
    double speedIncreasePerSecond = (maxSpeed / phaseDuration);
    double longitudinalAcceleration = speedIncreasePerSecond * 0.44704; // calculating the acceleration
    double speedDecreasePerSecond = maxSpeed / phaseDuration;
    double longitudinalDeceleration = -(speedDecreasePerSecond * 0.44704);
    int elapsed = 0;

    double currentLowFuelThreshold = 0.0;
    bool low_fuel = false;

    auto screen = App::Fullscreen();

    auto renderer = Renderer([&] {

        // gauge panel

        double speedPercent = speedSensor.getSpeed() / maxSpeed;

        if (speedPercent < 0.0) {
            speedPercent = 0.0;
        }

        if (speedPercent > 1.0) {
            speedPercent = 1.0;
        }


        double fuelPercent = fuelSensor.getFuelPercentage() / 100.0;

        if (fuelPercent < 0.0) {
            fuelPercent = 0.0;
        }

        if (fuelPercent > 1.0) {
            fuelPercent = 1.0;
        }

        // motion panel

        auto motionPanel = vbox({
            text("MOTION") | bold | hcenter,
            separator(),

            text("Speed: " + formatDouble(speedSensor.getSpeed(), 1) + " mph"),

            gauge(speedPercent),

            separator(),

            text("Acceleration X: " + formatDouble(accelSensor.getAccelerationX(), 2) + " m/s^2"),

            text("Acceleration Y: " + formatDouble(accelSensor.getAccelerationY(), 2) + " m/s^2"),

            text("Acceleration Z: " + formatDouble(accelSensor.getAccelerationZ(), 2) + " m/s^2")

        }) | border | flex;

        // temperature panel

        auto temperaturePanel = vbox({
            text("TEMPERATURE") | bold | hcenter,
            separator(),

            text("Ambient: " + formatDouble(tempSensor.getAmbientTemperature(), 1) + " C"),

            text("Coolant: " + formatDouble(tempSensor.getCoolantTemperature(), 1) + " C"),

            text("Battery: " + formatDouble(battSensor.getTemperature(), 1) + " C")

        }) | border | flex;

        // battery panel

        auto electricalPanel = vbox({
            text("BATTERY / ELECTRICAL") | bold | hcenter,
            separator(),

            text("Voltage: " + formatDouble(battSensor.getVoltage(), 2) + " V"),

            text("Current: " + formatDouble(battSensor.getCurrent(), 2) + " A"),

            text("Temperature: " + formatDouble(battSensor.getTemperature(), 1) + " C")

        }) | border | flex;

        // fuel panel

        auto fuelPanel = vbox({
            text("FUEL") | bold | hcenter,
            separator(),

            text("Remaining: " + formatDouble(fuelSensor.getFuelLiters(), 2) + " L"),

            text("Fuel Level: " + formatDouble(fuelSensor.getFuelPercentage(), 1) + " %"),

            text("Emergency Threshold: " + formatDouble(currentLowFuelThreshold, 2) + " L"),

            gauge(fuelPercent),

            text(low_fuel ? "Status: LOW FUEL" : "Status: NORMAL")

        }) | border | flex;

        // brake panel

        auto brakePanel = vbox({
            text("BRAKE SYSTEM") | bold | hcenter,
            separator(),

            text("Front Pressure: " + formatDouble(brakeSensor.getFrontBrakePressure(), 1) + " PSI"),

            text("Rear Pressure: " + formatDouble(brakeSensor.getRearBrakePressure(), 1) + " PSI"),

            text("Average Pressure: " + formatDouble(brakeSensor.getAverageBrakePressure(), 1) + " PSI"),

            text(brakeSensor.isWithinSensorRange() ? "Sensor Range: NORMAL" : "Sensor Range: INVALID")

        }) | border | flex;

        // tire pressure panel

        auto tirePressurePanel = vbox({
            text("TIRE PRESSURE") | bold | hcenter,
            separator(),

            hbox({
                text("FL: " + formatDouble( tireSensor.getFrontLeftPressure(), 2) + " PSI"),

                filler(),

                text("FR: " + formatDouble( tireSensor.getFrontRightPressure(), 2) + " PSI")
            }),

            hbox({
                text("RL: " + formatDouble( tireSensor.getRearLeftPressure(), 2) + " PSI"),

                filler(),

                text("RR: " + formatDouble( tireSensor.getRearRightPressure(), 2) + " PSI")
            })

        }) | border | flex;

        // tire temperature panel 

        auto tireTemperaturePanel = vbox({
            text("TIRE TEMPERATURE") | bold | hcenter,
            separator(),

            hbox({
                text("FL: " + formatDouble( tireSensor.getFrontLeftTemperature(), 1) + " C"),

                filler(),

                text("FR: " + formatDouble( tireSensor.getFrontRightTemperature(), 1) + " C")
            }),

            hbox({
                text("RL: " + formatDouble( tireSensor.getRearLeftTemperature(), 1) + " C"),

                filler(),

                text("RR: " + formatDouble( tireSensor.getRearRightTemperature(), 1) + " C")
            })

        }) | border | flex;

        // main dashboard

        return vbox({

            text("AXOVIGIL VEHICLE DIAGNOSTIC")
                | bold
                | hcenter,

            separator(),

            hbox({
                text("Phase: " + currentPhase), filler(),
                text("Time: " + std::to_string(elapsed) + " / " + std::to_string(test_duration) + " s")
            }),

            separator(),

            // Row 1
            hbox({
                motionPanel,
                temperaturePanel
            }),

            // Row 2
            hbox({
                electricalPanel,
                fuelPanel
            }),

            // Row 3
            hbox({
                brakePanel,
                tirePressurePanel
            }),

            // Row 4
            hbox({
                tireTemperaturePanel
            })

        }) | border;
    });

    // fuel consumed per second during worst case deceleration
    double maximumDecelerationFuelRate = 0.003;

    // always keep at least 1% of the tank as an emergency reserve
    double baseEmergencyReserve = tankCapacity * 0.01;

    std::thread simulationThread([&] {

        if (!low_fuel) {
            currentPhase = "ACCELERATING";
            for (int i = 0; i < phaseDuration; i++) {

                // speed
                vehicleSpeed += speedIncreasePerSecond;

                if (vehicleSpeed > maxSpeed) {
                    vehicleSpeed = maxSpeed;
                }

                speedSensor.setSpeed(vehicleSpeed);

                // acceleration
                accelSensor.setAcceleration(longitudinalAcceleration, 0.0, 9.80665);

                // coolant temperature
                coolantTemperature += randomDouble(0.10, 0.30);
                tempSensor.setCoolantTemperature(coolantTemperature);

                // battery voltage
                batteryVoltage += randomDouble(-0.03, 0.03);
                battSensor.setVoltage(batteryVoltage);

                // battery current
                batteryCurrent += randomDouble(-0.5, 0.5);
                battSensor.setCurrent(batteryCurrent);

                // battery temperature
                batteryTemperature += randomDouble(0.01, 0.05);
                battSensor.setTemperature(batteryTemperature);

                // fuel
                remainingFuel -= randomDouble(0.01, 0.03);
                fuelSensor.setFuelLiters(remainingFuel);

                double estimatedStopTime = vehicleSpeed / speedDecreasePerSecond;

                double fuelRequiredToStop = estimatedStopTime * maximumDecelerationFuelRate;

                currentLowFuelThreshold = baseEmergencyReserve + fuelRequiredToStop;

                if (remainingFuel <= currentLowFuelThreshold) {
                    low_fuel = true;
                    break;
                }

                // brake pressure stays near zero
                brakeSensor.setFrontBrakePressure(0.0);

                brakeSensor.setRearBrakePressure(0.0);

                // tire pressure
                frontLeftPressure += randomDouble(0.005, 0.020);
                tireSensor.setFrontLeftPressure(frontLeftPressure);

                frontRightPressure += randomDouble(0.005, 0.020);
                tireSensor.setFrontRightPressure(frontRightPressure);

                rearLeftPressure += randomDouble(0.005, 0.020);
                tireSensor.setRearLeftPressure(rearLeftPressure);

                rearRightPressure += randomDouble(0.005, 0.020);
                tireSensor.setRearRightPressure(rearRightPressure);

                // tire temperature
                frontLeftTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setFrontLeftTemperature(frontLeftTireTemperature);

                frontRightTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setFrontRightTemperature(frontRightTireTemperature);

                rearLeftTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setRearLeftTemperature(rearLeftTireTemperature);

                rearRightTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setRearRightTemperature(rearRightTireTemperature);

                elapsed++;

                screen.Post(Event::Custom);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    
        if (!low_fuel) {
            currentPhase = "CRUISING";
            for (int i = 0; i < phaseDuration; i++) {

                // speed
                vehicleSpeed = maxSpeed;
                speedSensor.setSpeed(vehicleSpeed);

                // acceleration
                accelSensor.setAcceleration(0.0, 0.0, 9.80665);

                // coolant temperature
                if (coolantTemperature < 96.0) {
                    coolantTemperature += randomDouble(0.01, 0.05);
                }
                else {
                    coolantTemperature += randomDouble(-0.02, 0.02);
                }
                tempSensor.setCoolantTemperature(coolantTemperature);

                // battery voltage
                batteryVoltage += randomDouble(-0.01, 0.01);
                battSensor.setVoltage(batteryVoltage);

                // battery current
                batteryCurrent += randomDouble(-0.5, 0.5);
                battSensor.setCurrent(batteryCurrent);

                // battery temperature
                batteryTemperature += randomDouble(0.005, 0.01);
                battSensor.setTemperature(batteryTemperature);

                // fuel
                remainingFuel -= randomDouble(0.002, 0.006);
                fuelSensor.setFuelLiters(remainingFuel);

                double estimatedStopTime = vehicleSpeed / speedDecreasePerSecond;

                double fuelRequiredToStop = estimatedStopTime * maximumDecelerationFuelRate;

                currentLowFuelThreshold = baseEmergencyReserve + fuelRequiredToStop;

                if (remainingFuel <= currentLowFuelThreshold) {
                    low_fuel = true;
                    break;
                }

                // super slight brake pressure
                brakeSensor.setFrontBrakePressure(0.0);
                brakeSensor.setRearBrakePressure(0.0);

                // tire pressure slowly rises
                frontLeftPressure += randomDouble(0.005, 0.010);
                tireSensor.setFrontLeftPressure(frontLeftPressure);

                frontRightPressure += randomDouble(0.005, 0.010);
                tireSensor.setFrontRightPressure(frontRightPressure);

                rearLeftPressure += randomDouble(0.005, 0.010);
                tireSensor.setRearLeftPressure(rearLeftPressure);

                rearRightPressure += randomDouble(0.005, 0.010);
                tireSensor.setRearRightPressure(rearRightPressure);

                // tires continue warming
                frontLeftTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setFrontLeftTemperature(frontLeftTireTemperature);

                frontRightTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setFrontRightTemperature(frontRightTireTemperature);

                rearLeftTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setRearLeftTemperature(rearLeftTireTemperature);

                rearRightTireTemperature += randomDouble(0.03, 0.08);
                tireSensor.setRearRightTemperature(rearRightTireTemperature);

                elapsed++;

                screen.Post(Event::Custom);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        (low_fuel) ? currentPhase = "LOW FUEL, DECELERATING" : currentPhase = "DECELERATING";

        for (int i = 0; i < phaseDuration && vehicleSpeed > 0.0; i++) {

            // speed
            vehicleSpeed -= speedDecreasePerSecond;

            if (vehicleSpeed <= 0.0) {
                vehicleSpeed = 0.0;
                break;
            }

            speedSensor.setSpeed(vehicleSpeed);

            // acceleration
            accelSensor.setAcceleration(longitudinalDeceleration, 0.0, 9.80665);

            // coolant temperature
            coolantTemperature += randomDouble(-0.04, 0.01);

            tempSensor.setCoolantTemperature(coolantTemperature);

            // battery voltage
            batteryVoltage += randomDouble(-0.01, 0.01);

            // keep charging voltage in a healthy range
            if (batteryVoltage > 14.5) {
                batteryVoltage = 14.5;
            }

            if (batteryVoltage < 13.7) {
                batteryVoltage = 13.7;
            }

            battSensor.setVoltage(batteryVoltage);

            // battery current
            batteryCurrent += randomDouble(-0.3, 0.3);

            battSensor.setCurrent(batteryCurrent);

            // battery temperature
            batteryTemperature += randomDouble(0.0, 0.005);

            battSensor.setTemperature(batteryTemperature);

            // fuel
            remainingFuel -= randomDouble(0.001, 0.003);

            if (remainingFuel < 0.0) {
                remainingFuel = 0.0;
            }

            fuelSensor.setFuelLiters(remainingFuel);

            // super slight brake pressure
            double frontBrakePressure = randomDouble(350.0, 500.0);

            double rearBrakePressure = randomDouble(300.0, 450.0);

            brakeSensor.setFrontBrakePressure(frontBrakePressure);
 
            brakeSensor.setRearBrakePressure(rearBrakePressure);

            // tire pressure slowly rises
            frontLeftPressure += randomDouble(-0.005, 0.005);

            frontRightPressure += randomDouble(-0.005, 0.005);

            rearLeftPressure += randomDouble(-0.005, 0.005);

            rearRightPressure += randomDouble(-0.005, 0.005);

            tireSensor.setFrontLeftPressure(frontLeftPressure);

            tireSensor.setFrontRightPressure(frontRightPressure);

            tireSensor.setRearLeftPressure(rearLeftPressure);

            tireSensor.setRearRightPressure(rearRightPressure);

            // tires continue warming
            frontLeftTireTemperature += randomDouble(0.00, 0.03);

            frontRightTireTemperature += randomDouble(0.00, 0.03);

            rearLeftTireTemperature += randomDouble(0.00, 0.02);

            rearRightTireTemperature += randomDouble(0.00, 0.02);

            tireSensor.setFrontLeftTemperature(frontLeftTireTemperature);

            tireSensor.setFrontRightTemperature(frontRightTireTemperature);

            tireSensor.setRearLeftTemperature(rearLeftTireTemperature);

            tireSensor.setRearRightTemperature(rearRightTireTemperature);

            elapsed++;

            screen.Post(Event::Custom);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        currentPhase = "TESTING COMPLETE";

        vehicleSpeed = 0.0;

        speedSensor.setSpeed(0.0);

        accelSensor.setAcceleration(0.0, 0.0, 9.80665);

        brakeSensor.setFrontBrakePressure(0.0);
        brakeSensor.setRearBrakePressure(0.0);

        screen.Post(Event::Custom);
    });

    screen.Loop(renderer);

    simulationThread.join();

    return 0;
};