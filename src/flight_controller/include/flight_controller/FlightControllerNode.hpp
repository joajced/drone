#pragma once

#include "actuator_msgs/msg/actuators.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/imu.hpp"

class FlightControllerNode : public rclcpp::Node {
public:
  FlightControllerNode();

private:
  void controlLoop();
  void imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg);
  void airPressureCallback(sensor_msgs::msg::FluidPressure::ConstSharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imuSubscription_;
  rclcpp::Subscription<sensor_msgs::msg::FluidPressure>::SharedPtr airPressureSubscription_;
  rclcpp::Publisher<actuator_msgs::msg::Actuators>::SharedPtr motorSpeedPublisher_;
  rclcpp::TimerBase::SharedPtr controlTimer_;

  sensor_msgs::msg::Imu latestImuData_;
  sensor_msgs::msg::FluidPressure latestAirPressureData_;
};
