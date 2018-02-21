#ifndef OROCOS_STATIC_DEPLOYMENT_DEMO_COMPONENT_HPP
#define OROCOS_STATIC_DEPLOYMENT_DEMO_COMPONENT_HPP

#include <rtt/RTT.hpp>

class Static_deployment_demo : public RTT::TaskContext{
  public:
    Static_deployment_demo(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
};
#endif
