#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

class FlightControllerNode : public rclcpp::Node {
public:
  FlightControllerNode();

private:
  void imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
};
