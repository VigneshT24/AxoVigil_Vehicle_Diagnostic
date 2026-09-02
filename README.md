# AxoVigil Vehicle Diagnostic

AxoVigil is a C++ vehicle diagnostic and sensor simulation project. The goal is to simulate a vehicle through acceleration, cruising, and deceleration while displaying live sensor data through a clean terminal dashboard.

The project is currently focused on building and testing the individual vehicle sensors before integrating them into the full simulation.

## Sensors

AxoVigil currently includes:

- Vehicle speed
- Acceleration
- Brake pressure
- Coolant temperature
- Battery voltage, current, and temperature
- Fuel level
- Tire pressure and temperature

Sensors also simulate characteristics such as bias, noise, and measurement ranges.

## Planned Features

- Live-updating terminal dashboard
- Acceleration, cruise, and deceleration simulation
- Vehicle diagnostic warnings
- Sensor fault detection
- PID-based speed control
- Telemetry logging
- Vehicle fault scenarios

## Running the Sensor Tests

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

### 6. Build the Sensor Test Suite

```bash
cmake --build build-linux --target SensorTests
```

### 7. Run the Tests

```bash
./build-linux/SensorTests
```

If all tests succeed, the program will display:

```text
ALL SENSOR COMPLIANCE TESTS PASSED.
```

If an assertion fails, the test suite will stop at the sensor check that produced an unexpected result.

## Rebuilding After Changes

After modifying sensor code:

```bash
cmake --build build-linux --target SensorTests
./build-linux/SensorTests
```

## Build Files

The generated build directories should not be committed to GitHub.

Add these to `.gitignore`:

```gitignore
build/
build-linux/
```
