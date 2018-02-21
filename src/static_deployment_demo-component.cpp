#include "static_deployment_demo-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

#include <rtt/os/startstop.h>

Static_deployment_demo::Static_deployment_demo(std::string const& name) : TaskContext(name){
  std::cout << "Static_deployment_demo constructed !" <<std::endl;
  std::cout << "Orocos was called with " << __os_main_argc() << " arguments!" << std::endl;
}

bool Static_deployment_demo::configureHook(){
  std::cout << "Static_deployment_demo configured !" <<std::endl;
  return true;
}

bool Static_deployment_demo::startHook(){
  std::cout << "Static_deployment_demo started !" <<std::endl;
  return true;
}

void Static_deployment_demo::updateHook(){
  std::cout << "Static_deployment_demo executes updateHook !" <<std::endl;
}

void Static_deployment_demo::stopHook() {
  std::cout << "Static_deployment_demo executes stopping !" <<std::endl;
}

void Static_deployment_demo::cleanupHook() {
  std::cout << "Static_deployment_demo cleaning up !" <<std::endl;
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Static_deployment_demo)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Static_deployment_demo)
