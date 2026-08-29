cmake_minimum_required(VERSION 3.16)

project(AxoVigil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AxoVigil
    src/main.cpp
    src/SpeedSensor.cpp
    src/AccelerometerSensor.cpp
    src/BrakePressureSensor.cpp
    src/TemperatureSensor.cpp
    src/BatterySensor.cpp
    src/FuelSensor.cpp
    src/TirePressureSensor.cpp
)

target_include_directories(AxoVigil PRIVATE include)