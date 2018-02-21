#include <rtt/os/main.h>

#include "static_deployment_demo-component.hpp"
#include <ocl/TaskBrowser.hpp>

#include <rtt/deployment/ComponentLoader.hpp>
#include <rtt/scripting/Scripting.hpp>
#include <rtt/internal/GlobalService.hpp>

// #include <ocl/DeploymentComponent.hpp>

#include <stdlib.h>
#include <unistd.h>

static void catch_signals(void);

// Reimplementation of OCL::DeploymentComponent::import()
void import(const std::string &package) {
  std::cout << "Importing packge " <<  package << "..." << std::endl;
  RTT::ComponentLoader::Instance()->import(package, "");
}

//
// Main function ORO_main.
// Like main(), but calls Orocos-specific initialization and cleanup functions
//
// argc and argc are not touched, but made available to be used inside RTT code
// through __os_main_argc() and __os_main_argv() (see rtt/os/startstop.h).

int ORO_main(int argc, char **argv) {

  // Optional: set default logger level
  if (!getenv("ORO_LOGLEVEL")) {
    RTT::Logger::Instance()->setLogLevel(RTT::Logger::Info);
  }

  // A deployer-like root component
  RTT::TaskContext deployer("Deployer");
  deployer.addOperation("import", &import);

  // Optional: Run a full-fledged DeploymentComponent instead
//  OCL::DeploymentComponent deployer("Deployer");

  // Statically link to component library (requires target_link_libraries(...))
  // and instantiate the component on the stack
//  Static_deployment_demo component("Foo");

  // ... or load the component library and instantiate dynamically
  boost::shared_ptr<RTT::ComponentLoader> loader = RTT::ComponentLoader::Instance();
  loader->import("static_deployment_demo", "");
      // imports all component libraries and typekit/service plugins from
      // package `static_deployment_demo`
  RTT::TaskContext *component
      = loader->loadComponent("Foo", "Static_deployment_demo");
  if (!component) {
    // log error...
    return 1;
  }
  deployer.addPeer(component);

  // Example: use scripting service to run a script from the command line
  //     in the context of component "Deployer"
  if (argc > 1) {
    boost::shared_ptr<RTT::Scripting> scripting = deployer.getProvider<RTT::Scripting>("scripting");
    if (!scripting->runScript(argv[1])) {
      // log error...
      return 1;
    }
  }

  // Example: Orocos package import (without dependencies)
  loader->import("rtt_ros", "");
  loader->import("rtt_geometry_msgs", "");

  // Get pointer to global service "ros"
  RTT::ServicePtr ros = RTT::internal::GlobalService::Instance()->provides("ros");
  RTT::OperationCaller<int(std::string)> ros_import = ros->getOperation("import");

  // Import ROS package rtt_geometry_msgs (including its <plugin_depend> dependencies)
  if (ros_import.ready()) {
    ros_import("rtt_geometry_msgs");
  }

  // You can also list all dependencies you want to import in the
  // <export>/<rtt_ros>/<plugin_depend> section of this package's package.xml
  // file and only import that one:
  ros_import(ROS_PACKAGE_NAME);  // note: ROS_PACKAGE_NAME defined in CMakeLists.txt

  // Optional: run a taskbrowser (requires use_orocos_package(ocl-taskbrowser) in CMakeLists.txt)
  if (true) {
    OCL::TaskBrowser browser(&deployer);
    browser.loop();
  // or
  } else {
    catch_signals();
    pause();
  }

  return 0;
}

// Signal handling (only required if you do not run the TaskBrowser or use the DeploymentComponent)
#include <signal.h>
static int s_interrupted = 0;
static void signal_handler (int signal_value)
{
  s_interrupted = 1;
}
static void catch_signals (void)
{
  struct sigaction action;
  action.sa_handler = signal_handler;
  action.sa_flags = 0;
  sigemptyset(&action.sa_mask);
  sigaction(SIGINT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);
}
