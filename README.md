# AxoVigil Vehicle Diagnostic

AxoVigil is a C++ vehicle diagnostic and sensor simulation project. The system simulates a vehicle through a trapezoidal velocity profile consisting of acceleration, constant-speed cruising, and deceleration while displaying live telemetry through an FTXUI terminal dashboard.

The project currently includes a complete three-phase drive simulation, simulated vehicle sensors, dynamic low-fuel safety behavior, and sensor compliance testing.

## Sensors

AxoVigil currently includes:

- Vehicle speed
- 3-axis acceleration
- Front and rear brake pressure
- Ambient and coolant temperature
- Battery voltage, current, and temperature
- Fuel level
- Four-wheel tire pressure and temperature

Sensors simulate characteristics such as bias, noise, and measurement ranges while maintaining stable readings between simulation updates.

## Current Features

- Live-updating FTXUI terminal dashboard
- Trapezoidal acceleration, cruise, and deceleration profile
- Real-time vehicle telemetry
- Fuel, battery, brake, temperature, motion, and tire monitoring
- Dynamic low-fuel emergency detection
- Automatic emergency deceleration when fuel becomes critically low
- Sensor bias and noise simulation
- Sensor compliance test suite

## Planned Features

- Expanded vehicle diagnostic warnings
- Sensor fault detection
- Simulated vehicle fault scenarios
- PID-based speed control
- Telemetry logging and replay
- Additional FTXUI diagnostic and sensor-detail views

## Running AxoVigil

### 1. Clone the Repository

```bash
git clone https://github.com/VigneshT24/AxoVigil_Vehicle_Diagnostic.git

cd AxoVigil_Vehicle_Diagnostic
```

### 2. Install WSL

Check if WSL is already installed:

```powershell
wsl --status
```

If WSL is not installed, open PowerShell as Administrator and run:

```powershell
wsl --install
```

Restart the computer if prompted, then start WSL:

```powershell
wsl
```

### 3. Install Build Tools

Inside WSL:

```bash
sudo apt update

sudo apt install build-essential cmake ninja-build
```

### 4. Navigate to the Repository

Windows drives are available through `/mnt/`.

For example:

```bash
cd "/mnt/c/Users/YourName/Downloads/AxoVigil_Vehicle_Diagnostic"
```

### 5. Configure the Project

```bash
cmake -S . -B build-linux
```

### 6.1 Build AxoVigil

```bash
cmake --build build-linux --target AxoVigil
```

### 6.2 Build the Sensor Test Suite

```bash
cmake --build build-linux --target SensorTests
```

### 7.1 Run AxoVigil

```bash
./build-linux/AxoVigil
```

The program will prompt for the diagnostic test duration, vehicle type, and current fuel level before launching the live FTXUI dashboard.

### 7.2 Run the Sensor Tests

```bash
./build-linux/SensorTests
```

If all tests succeed, the program will display:

```text
ALL SENSOR COMPLIANCE TESTS PASSED.
```

If an assertion fails, the test suite will stop at the sensor check that produced an unexpected result.

## Rebuilding After Changes

After modifying AxoVigil:

```bash
cmake --build build-linux --target AxoVigil

./build-linux/AxoVigil
```

After modifying the sensor test suite:

```bash
cmake --build build-linux --target SensorTests

./build-linux/SensorTests
```

## Build Files

Generated build directories should not be committed to GitHub.

Add these to `.gitignore`:

```gitignore
build/
build-linux/
```