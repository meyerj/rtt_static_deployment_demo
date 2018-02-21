#
# The find_package macro for Orocos-RTT requires
# cmake >= 2.8
#
cmake_minimum_required(VERSION 2.8)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(static_deployment_demo)

# Find catkin and ROS package rtt_ros
#
# rtt_ros already finds OROCOS-RTT including the rtt-marshalling and rtt-scripting
# plugins and includes the UseOROCOS-RTT.cmake helper.
#
find_package(catkin REQUIRED COMPONENTS rtt_ros)

# Rest of the configuration is in src/
add_subdirectory( src )

#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#
orocos_generate_package()
