#include <chrono>
#include <iostream>
#include <memory>
#include "flight_controller/FlightControllerNode.hpp"

FlightControllerNode::FlightControllerNode()
  : Node("flight_controller_node") {
  /* Subscribe to the IMU topic */
  imuSubscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
    "/x500/imu",
    10,
    [this](sensor_msgs::msg::Imu::ConstSharedPtr msg) { imuCallback(msg); }
  );

  /* Subscribe to the air pressure topic */
  airPressureSubscription_ = this->create_subscription<sensor_msgs::msg::FluidPressure>(
    "/x500/air_pressure",
    10,
    [this](sensor_msgs::msg::FluidPressure::ConstSharedPtr msg) { airPressureCallback(msg); }
  );

  /* Publish to the motor speed topic */
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

  motorSpeeds.velocity = {
    780.0,
    780.0,
    780.0,
    780.0
  };

  motorSpeedPublisher_->publish(motorSpeeds);
}

void FlightControllerNode::imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg) {
  latestImuData_ = *msg;
}

void FlightControllerNode::airPressureCallback(sensor_msgs::msg::FluidPressure::ConstSharedPtr msg) {
  latestAirPressureData_ = *msg;
}
