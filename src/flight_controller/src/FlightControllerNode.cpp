#include <iostream>
#include <memory>

#include "flight_controller/FlightControllerNode.hpp"

FlightControllerNode::FlightControllerNode()
  : Node("flight_controller_node") {
  /* Subscribe to the IMU topic */
  imu_subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
    "/x500/imu",
    10,
    [this](sensor_msgs::msg::Imu::ConstSharedPtr msg) { imuCallback(msg); }
  );
}

void FlightControllerNode::imuCallback(sensor_msgs::msg::Imu::ConstSharedPtr msg) {
  std::cout << "Linear Acc Z: " << msg->linear_acceleration.z << " m/s^2" << std::endl;
}
