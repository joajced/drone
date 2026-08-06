#include <memory>

#include "flight_controller/FlightControllerNode.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto controller = std::make_shared<FlightControllerNode>();
  rclcpp::spin(controller);
  rclcpp::shutdown();
}
