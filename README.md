# twist_2wheel_pub
Subscribe Twist msgs and write text file for EPOSx_2wheels.

## Installation

- This program depends on ROS1 Melodic.
- Subscribe geometry_msgs/Twist (Default : cmd_vel)
- Please run `$ catkin_build` on ROS1 workspace to build.

## Usage

#### Example

 `$ rosrun twist_2wheel_pub twist2wheel _path:="/home/ubuntu/EPOSx_2wheels/yaml/"`

#### options

- path : Directory path for EPOS0.txt and EPOS1.txt. (Communicate by text file.)



It is assumed to use [this repository](https://github.com/Ar-Ray-code/EPOSx_2wheels).

## License

Apache-2.0