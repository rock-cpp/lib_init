#include "Init.hpp"
#include "../InitHelper.hpp"

Init::Init(orocos_cpp::TransformerHelper &trHelper, orocos_cpp::ConfigurationHelper &confHelper, init::Base &toStart, state_machine::State *success) : 
    State("Init", success), 
    toStart(&toStart), 
    helper(trHelper, confHelper)
{
}

Init::~Init()
{

}


void Init::enter(const state_machine::State* lastState)
{

}

void Init::activateLogging(const std::vector<std::string> &excludeList)
{
    helper.activateLogging(excludeList);
}


void Init::executeFunction()
{
    std::cout << "Init" << std::endl;
    std::cout << "Inits with dependencies to start :" << std::endl;
    
    helper.printDependencies(*toStart, 0);
    
    if(!helper.start(*toStart))
    {
        fail();
        std::cout << "Init Failed" << std::endl;
        return;
    }
    
    std::cout << "Init Done" << std::endl;
    
    finish();
}

void Init::exit()
{

}
