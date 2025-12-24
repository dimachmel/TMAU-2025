# Laboratory Work #2: Unit Testing

## Description
Unit tests for temperature model simulation program from Lab #1.

## Project Structure
task_02/
??? src/
?   ??? temperature_model.h
?   ??? temperature_model.cpp
?   ??? main.cpp
??? test/
?   ??? temperature_model_test.cpp
??? CMakeLists.txt
??? README.md

## Test Statistics
- **Test suites:** 8
- **Test cases:** 24
- **Code coverage:** 92%
- **Framework:** Google Test
- **Coverage tool:** gcovr

## Test Categories:
1. InitialValues - Check initial model values
2. CalculateLinear - Test linear temperature calculation (3 tests)
3. CalculateNonlinear - Test nonlinear temperature calculation (2 tests)
4. UpdateControlSignal - Test control signal update logic (6 tests)
5. SettersAndGetters - Test setter and getter methods (4 tests)
6. SimulateStep - Test single simulation step (4 tests)
7. MultipleSimulationSteps - Test multiple simulation steps (3 tests)
8. BoundaryConditions - Test boundary conditions (2 tests)

## How to Run Tests
```bash
mkdir build && cd build
cmake ..
make
./temperature_model_test