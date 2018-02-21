
#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#

# Expose package name to C/C++
add_definitions(-DROS_PACKAGE_NAME=\"${PROJECT_NAME}\")

# Creates a component library libstatic_deployment_demo-<target>.so
# and installs in the directory lib/orocos/static_deployment_demo/
#
orocos_component(static_deployment_demo static_deployment_demo-component.hpp static_deployment_demo-component.cpp) # ...you may add multiple source files

## Find and use other Orocos packages
orocos_use_package(ocl-taskbrowser)
#orocos_use_package(ocl-deployment)

## Create an Orocos executable
orocos_executable(my_static_deployment main.cpp)
#target_link_libraries(my_static_deployment static_deployment_demo)
target_link_libraries(my_static_deployment ${OROCOS-RTT_RTT-SCRIPTING_LIBRARY})

#
# You may add multiple orocos_component statements.

#
# Additional headers:
#
# Installs in the include/orocos/static_deployment_demo/ directory
#
orocos_install_headers(static_deployment_demo-component.hpp) # ...you may add multiple header files
#
# You may add multiple orocos_install_headers statements.

