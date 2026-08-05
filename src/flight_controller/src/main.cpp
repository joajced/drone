#include <memory>

#include "flight_controller/ImuDriver.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto imu = std::make_shared<ImuDriver>();
  rclcpp::spin(imu);
  rclcpp::shutdown();
}
