#include <gtest/gtest.h>
#include "../src/temperature_model.h"
#include <cmath>

TEST(TemperatureModelTest, InitialValues) {
    TemperatureModel model;
    
    EXPECT_DOUBLE_EQ(20.0, model.getLinearTemperature());
    EXPECT_DOUBLE_EQ(20.0, model.getNonlinearTemperature());
    EXPECT_DOUBLE_EQ(1.0, model.getControlSignal());
    EXPECT_DOUBLE_EQ(0.8, model.getPreviousControl());
}

TEST(TemperatureModelTest, CalculateLinear) {
    TemperatureModel model;
    
    double result = model.calculateLinear(20.0, 1.0);
    EXPECT_DOUBLE_EQ(0.8 * 20.0 + 0.2 * 1.0, result);
    
    result = model.calculateLinear(10.0, 2.0, 0.5, 0.3);
    EXPECT_DOUBLE_EQ(0.5 * 10.0 + 0.3 * 2.0, result);
    
    result = model.calculateLinear(0.0, 0.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(TemperatureModelTest, CalculateNonlinear) {
    TemperatureModel model;
    
    double result = model.calculateNonlinear(20.0, 1.0, 0.8);
    double expected = 0.7 * 20.0 - 0.005 * 20.0 * 20.0 + 0.25 * 1.0 + 0.1 * sin(0.8 - 1);
    EXPECT_NEAR(expected, result, 1e-10);
    
    result = model.calculateNonlinear(10.0, 2.0, 1.5, 0.6, 0.01, 0.3, 0.2);
    expected = 0.6 * 10.0 - 0.01 * 10.0 * 10.0 + 0.3 * 2.0 + 0.2 * sin(1.5 - 1);
    EXPECT_NEAR(expected, result, 1e-10);
}

TEST(TemperatureModelTest, UpdateControlSignal) {
    TemperatureModel model;
    
    EXPECT_DOUBLE_EQ(1.0, model.updateControlSignal(20.0, 1.0));
    EXPECT_DOUBLE_EQ(1.0, model.updateControlSignal(18.0, 1.0));
    EXPECT_DOUBLE_EQ(1.0, model.updateControlSignal(28.0, 1.0));
    
    EXPECT_DOUBLE_EQ(0.0, model.updateControlSignal(28.1, 1.0));
    EXPECT_DOUBLE_EQ(0.0, model.updateControlSignal(30.0, 1.0));
    
    EXPECT_DOUBLE_EQ(1.5, model.updateControlSignal(17.9, 1.0));
    EXPECT_DOUBLE_EQ(1.5, model.updateControlSignal(10.0, 1.0));
}

TEST(TemperatureModelTest, SettersAndGetters) {
    TemperatureModel model;
    
    model.setLinearTemperature(25.0);
    EXPECT_DOUBLE_EQ(25.0, model.getLinearTemperature());
    
    model.setNonlinearTemperature(22.5);
    EXPECT_DOUBLE_EQ(22.5, model.getNonlinearTemperature());
    
    model.setControlSignal(0.5);
    EXPECT_DOUBLE_EQ(0.5, model.getControlSignal());
    
    model.setPreviousControl(0.7);
    EXPECT_DOUBLE_EQ(0.7, model.getPreviousControl());
}

TEST(TemperatureModelTest, SimulateStep) {
    TemperatureModel model;
    
    double initial_linear = model.getLinearTemperature();
    double initial_nonlinear = model.getNonlinearTemperature();
    double initial_u = model.getControlSignal();
    
    model.simulateStep();
    
    EXPECT_NE(initial_linear, model.getLinearTemperature());
    EXPECT_NE(initial_nonlinear, model.getNonlinearTemperature());
    EXPECT_NE(initial_u, model.getControlSignal());
    
    EXPECT_DOUBLE_EQ(initial_u, model.getPreviousControl());
}

TEST(TemperatureModelTest, MultipleSimulationSteps) {
    TemperatureModel model;
    
    for (int i = 0; i < 10; ++i) {
        // ??????????: ??????? ?????????????? ??????????
        model.simulateStep();
        double linear_after = model.getLinearTemperature();
        
        EXPECT_GE(linear_after, -100.0);
        EXPECT_LE(linear_after, 100.0);
    }
}

TEST(TemperatureModelTest, BoundaryConditions) {
    TemperatureModel model;
    
    model.setLinearTemperature(29.0);
    model.setControlSignal(1.0);
    model.simulateStep();
    EXPECT_DOUBLE_EQ(0.0, model.getControlSignal());
    
    model.setLinearTemperature(15.0);
    model.setControlSignal(1.0);
    model.simulateStep();
    EXPECT_DOUBLE_EQ(1.5, model.getControlSignal());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}