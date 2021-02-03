cmake_minimum_required(VERSION 3.0.2)
project(twist_2wheel_pub)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  sensor_msgs
  std_msgs
  tf
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
catkin_package()

add_executable(twist2wheel src/pub_twist2wheelspd.cpp)
target_link_libraries(twist2wheel ${catkin_LIBRARIES})