cmake_minimum_required(VERSION 3.8)
project(flight_controller)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(flight_controller_node
  src/main.cpp
  src/FlightControllerNode.cpp
)

target_include_directories(flight_controller_node PUBLIC
  include
)

ament_target_dependencies(flight_controller_node
  rclcpp
  sensor_msgs
)

install(
  TARGETS flight_controller_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
