#pragma once

#include "actuator_msgs/msg/actuators.hpp"
#include "flight_controller/FlightMode.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float64.hpp"

class FlightControllerNode : public rclcpp::Node {
public:
  FlightControllerNode();

private:
  void controlLoop();

  /* Callbacks */

  void imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg);
  void airPressureCallback(sensor_msgs::msg::FluidPressure::ConstSharedPtr msg);
  void throttleCommandCallback(std_msgs::msg::Float64::ConstSharedPtr msg);
  void hoverCommandCallback(std_msgs::msg::Float64::ConstSharedPtr msg);

  /* Flight mode logic */

  void doThrottle(actuator_msgs::msg::Actuators& motorSpeeds);
  void doHover(actuator_msgs::msg::Actuators& motorSpeeds);

  /* Subscriptions */

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imuSubscription_;
  rclcpp::Subscription<sensor_msgs::msg::FluidPressure>::SharedPtr airPressureSubscription_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr throttleCommandSubscription_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr hoverCommandSubscription_;

  /* Publishers */

  rclcpp::Publisher<actuator_msgs::msg::Actuators>::SharedPtr motorSpeedPublisher_;

  /* Sensor data */

  sensor_msgs::msg::Imu latestImuData_;
  sensor_msgs::msg::FluidPressure latestAirPressureData_;

  /* Command data */

  FlightMode flightMode_;
  double throttleCommand_;
  double targetHoverAltitude_;

  /* Timers */

  rclcpp::TimerBase::SharedPtr controlTimer_;
};
