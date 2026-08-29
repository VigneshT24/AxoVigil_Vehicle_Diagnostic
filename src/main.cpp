#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

#include <AccelerometerSensor.hpp>
#include <BatterySensor.hpp>
#include <BrakePressureSensor.hpp>
#include <FuelSensor.hpp>
#include <SpeedSensor.hpp>
#include <TemperatureSensor.hpp>
#include <TirePressureSensor.hpp>

// our vehicle diagnostic system will utilize a trapezoidal velocity profile testing methodology

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

    int max = test_duration;
    while (test_duration != 0) {
        std::cout << "\r\033[2K";

        if (test_duration <= max && test_duration > (max * (2.0/3.0))) {
            std::cout << "[ACCELERATING] | Time Remaining: " << test_duration << " seconds.";
        }
        else if (test_duration <= (max * (2.0/3.0)) && test_duration > (max * (1.0/3.0))) {
            std::cout << "[CRUSING] | Time Remaining: " << test_duration << " seconds.";
        }
        else {
            std::cout << "[DECELERATING] | Time Remaining: " << test_duration << " seconds.";
        }
        std::cout << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        test_duration--;
    }
    std::cout << std::endl;
    return 0;
}