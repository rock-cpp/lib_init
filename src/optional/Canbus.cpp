#include "Canbus.hpp"


init::Canbus::Canbus(const std::string& canbusName) : Base("CanBus"), 
    canbus(DependentTask<canbus::proxies::Task>::getInstance(this, canbusName))
{
   
}

void init::Canbus::initProxies()
{
    init::Base::initProxies();
}

bool init::Canbus::configure()
{
    
    bool ret = init::Base::configure();
    if(!ret)
        return ret;
    
    for(const CanbusWatch& watch : watches)
    {
        bool isWatched = canbus.getConcreteProxy()->watch(watch.name, watch.id, watch.mask);
        if(!isWatched)
        {
            std::cout << "init::Canbus::error: watching caused error" << std::endl;
            throw new std::runtime_error("init::Canbus::error: watching caused error");
        }
        
        canbus.getConcreteProxy()->synchronize();
        
        OutputProxyPort<canbus::Message> *msgOut = new OutputProxyPort<canbus::Message> 
                                                    (canbus.getConcreteProxy()->getPort(watch.name));
        
        outputs.insert(std::make_pair(watch.name, msgOut));
    }
    
    return true;
}

bool init::Canbus::watch(const std::string& name, int id, int mask)
{
    CanbusWatch watch = {name, id, mask};
    watches.push_back(watch);
    return true;
}

InputProxyPort< canbus::Message >& init::Canbus::getMsgInPort()
{
    return canbus.getConcreteProxy()->in;
}

OutputProxyPort< canbus::Message >& init::Canbus::getMsgOutPort(const std::string& watchedName)
{
    if(outputs.find(watchedName) == outputs.end())
        throw new std::runtime_error("error: tried to access unwatched output port from canbus");
    
    return *outputs.at(watchedName);
}


