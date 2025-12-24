#include "temperature_model.h"
#include <cmath>

TemperatureModel::TemperatureModel(double y_linear, double y_nonlinear) 
    : y_linear_(y_linear), y_nonlinear_(y_nonlinear) {}

double TemperatureModel::calculateLinear(double y_current, double u_t, double a, double b) const {
    return a * y_current + b * u_t;
}

double TemperatureModel::calculateNonlinear(double y_current, double u_t, double u_prev, 
                                           double a, double b, double c, double d) const {
    return a * y_current - b * y_current * y_current + c * u_t + d * sin(u_prev - 1);
}

double TemperatureModel::updateControlSignal(double y_linear, double u_current) const {
    if (y_linear > 28.0) {
        return 0.0;
    } else if (y_linear < 18.0) {
        return 1.5;
    } else {
        return u_current;
    }
}

double TemperatureModel::getLinearTemperature() const { return y_linear_; }
double TemperatureModel::getNonlinearTemperature() const { return y_nonlinear_; }
double TemperatureModel::getControlSignal() const { return u_t_; }
double TemperatureModel::getPreviousControl() const { return u_prev_; }

void TemperatureModel::setLinearTemperature(double temp) { y_linear_ = temp; }
void TemperatureModel::setNonlinearTemperature(double temp) { y_nonlinear_ = temp; }
void TemperatureModel::setControlSignal(double u) { u_t_ = u; }
void TemperatureModel::setPreviousControl(double u_prev) { u_prev_ = u_prev; }

void TemperatureModel::simulateStep() {
    double current_linear = y_linear_;
    double current_nonlinear = y_nonlinear_;
    double current_u = u_t_;
    double current_u_prev = u_prev_;
    
    y_linear_ = calculateLinear(current_linear, current_u);
    y_nonlinear_ = calculateNonlinear(current_nonlinear, current_u, current_u_prev);
    
    u_prev_ = current_u;
    u_t_ = updateControlSignal(y_linear_, current_u);
}