#ifndef TEMPERATURE_MODEL_H
#define TEMPERATURE_MODEL_H

class TemperatureModel {
public:
    explicit TemperatureModel(double y_linear = 20.0, double y_nonlinear = 20.0);
    
    double calculateLinear(double y_current, double u_t, double a = 0.8, double b = 0.2) const;
    double calculateNonlinear(double y_current, double u_t, double u_prev, 
                             double a = 0.7, double b = 0.005, double c = 0.25, double d = 0.1) const;
    double updateControlSignal(double y_linear, double u_current = 1.0) const;
    
    double getLinearTemperature() const;
    double getNonlinearTemperature() const;
    double getControlSignal() const;
    double getPreviousControl() const;
    
    void setLinearTemperature(double temp);
    void setNonlinearTemperature(double temp);
    void setControlSignal(double u);
    void setPreviousControl(double u_prev);
    
    void simulateStep();
    
private:
    double y_linear_ = 20.0;
    double y_nonlinear_ = 20.0;
    double u_t_ = 1.0;
    double u_prev_ = 0.8;
};

#endif