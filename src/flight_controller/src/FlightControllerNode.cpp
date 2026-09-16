#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include "flight_controller/FlightControllerNode.hpp"

constexpr double HOVER_THROTTLE { 769.192 };
constexpr double PRESSURE_0 { 101322.27 }; // 1 atm = 101325 Pa
constexpr double KP { 1.0 }; // Proportional gain

FlightControllerNode::FlightControllerNode()
  : Node("flight_controller_node")
  , flightMode_{FlightMode::THROTTLE}
  , throttleCommand_{0.0}
  , targetHoverAltitude_{0.0} {
  imuSubscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
    "/x500/imu",
    10,
    [this](sensor_msgs::msg::Imu::ConstSharedPtr msg) { imuCallback(msg); }
  );

  airPressureSubscription_ = this->create_subscription<sensor_msgs::msg::FluidPressure>(
    "/x500/air_pressure",
    10,
    [this](sensor_msgs::msg::FluidPressure::ConstSharedPtr msg) { airPressureCallback(msg); }
  );

  throttleCommandSubscription_ = this->create_subscription<std_msgs::msg::Float64>(
    "/command/throttle",
    10,
    [this](std_msgs::msg::Float64::ConstSharedPtr msg) { throttleCommandCallback(msg); }
  );

  hoverCommandSubscription_ = this->create_subscription<std_msgs::msg::Float64>(
    "/command/hover",
    10,
    [this](std_msgs::msg::Float64::ConstSharedPtr msg) { hoverCommandCallback(msg); }
  );

  motorSpeedPublisher_ = this->create_publisher<actuator_msgs::msg::Actuators>(
    "/x500/command/motor_speed",
    10
  );

  /* Initialize control timer (250 Hz) */
  controlTimer_ = this->create_wall_timer(
    std::chrono::milliseconds(4),
    [this]() { controlLoop(); }
  );
}

void FlightControllerNode::controlLoop() {
  actuator_msgs::msg::Actuators motorSpeeds;

  switch (flightMode_) {
    case FlightMode::THROTTLE:
      doThrottle(motorSpeeds); // Drive straight up or down at a specific rotor speed
      break;

    case FlightMode::HOVER:
      doHover(motorSpeeds); // Maintain a specific target altitude
      break;
  }

  motorSpeedPublisher_->publish(motorSpeeds);
}

void FlightControllerNode::imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg) {
  latestImuData_ = *msg;
}

void FlightControllerNode::airPressureCallback(sensor_msgs::msg::FluidPressure::ConstSharedPtr msg) {
  latestAirPressureData_ = *msg;
}

void FlightControllerNode::throttleCommandCallback(std_msgs::msg::Float64::ConstSharedPtr msg) {
  throttleCommand_ = msg->data;
  flightMode_ = FlightMode::THROTTLE;
}

void FlightControllerNode::hoverCommandCallback(std_msgs::msg::Float64::ConstSharedPtr msg) {
  targetHoverAltitude_ = msg->data;
  flightMode_ = FlightMode::HOVER;
}

void FlightControllerNode::doThrottle(actuator_msgs::msg::Actuators& motorSpeeds) {
  motorSpeeds.velocity = {
    throttleCommand_,
    throttleCommand_,
    throttleCommand_,
    throttleCommand_
  };
}

void FlightControllerNode::doHover(actuator_msgs::msg::Actuators& motorSpeeds) {
  double currentPressure { latestAirPressureData_.fluid_pressure };
  double currentAltitude { 44330.8 * (1.0 - std::pow(currentPressure / PRESSURE_0, 0.1903)) };
  double error { targetHoverAltitude_ - currentAltitude };
  double throttle { HOVER_THROTTLE + KP * error };

  throttle = std::clamp(throttle, 0.0, 1000.0); // Keep throttle within expected range

  motorSpeeds.velocity = {
    throttle,
    throttle,
    throttle,
    throttle
  };
}
