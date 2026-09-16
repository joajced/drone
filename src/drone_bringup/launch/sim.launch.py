from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

  # ROS2 <-> Gazebo topic bridges

  imu_bridge = Node(
    package='ros_gz_bridge',
    executable='parameter_bridge',
    arguments=['/x500/imu@sensor_msgs/msg/Imu[gz.msgs.IMU'],
    output='screen'
  )

  air_pressure_bridge = Node(
    package='ros_gz_bridge',
    executable='parameter_bridge',
    arguments=['/x500/air_pressure@sensor_msgs/msg/FluidPressure[gz.msgs.FluidPressure'],
    output='screen'
  )

  motor_bridge = Node(
    package='ros_gz_bridge',
    executable='parameter_bridge',
    arguments=['/x500/command/motor_speed@actuator_msgs/msg/Actuators]gz.msgs.Actuators'],
    output='screen'
  )

  # Flight controller node

  flight_controller = Node(
    package='flight_controller',
    executable='flight_controller_node',
    output='screen'
  )

  return LaunchDescription([
      imu_bridge,
      air_pressure_bridge,
      motor_bridge,
      flight_controller
  ])
