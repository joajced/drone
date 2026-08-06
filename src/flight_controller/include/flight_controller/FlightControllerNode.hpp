#pragma once

#include "actuator_msgs/msg/actuators.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

class FlightControllerNode : public rclcpp::Node {
public:
  FlightControllerNode();

private:
  void imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg);
  void controlLoop();

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imuSubscription_;
  rclcpp::Publisher<actuator_msgs::msg::Actuators>::SharedPtr motorSpeedPublisher_;
  rclcpp::TimerBase::SharedPtr controlTimer_;

  sensor_msgs::msg::Imu latestImuData_;
};
