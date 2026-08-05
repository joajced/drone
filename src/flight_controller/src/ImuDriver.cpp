#include <functional>
#include <iostream>
#include <memory>

#include "flight_controller/ImuDriver.hpp"

ImuDriver::ImuDriver()
  : Node("imu_driver") {
  subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
    "/x500/imu",
    10,
    std::bind(
      &ImuDriver::imuCallback,
      this,
      std::placeholders::_1
    )
  );
}

void ImuDriver::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
  std::cout << msg->linear_acceleration.z << std::endl;
}
