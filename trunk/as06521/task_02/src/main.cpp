#include <iostream>
#include <iomanip>
#include "temperature_model.h"

int main() {
    TemperatureModel model;
    int time_steps = 30;
    
    std::cout << "Temperature Model Simulation" << std::endl;
    std::cout << std::setw(5) << "Step" << std::setw(15) << "Linear" 
              << std::setw(15) << "Nonlinear" << std::setw(15) << "Control" << std::endl;
    
    for (int t = 0; t < time_steps; ++t) {
        std::cout << std::setw(5) << t << std::setw(15) << std::fixed << std::setprecision(2) 
                  << model.getLinearTemperature() << std::setw(15) 
                  << model.getNonlinearTemperature() << std::setw(15) 
                  << model.getControlSignal() << std::endl;
        
        model.simulateStep();
    }
    
    return 0;
}