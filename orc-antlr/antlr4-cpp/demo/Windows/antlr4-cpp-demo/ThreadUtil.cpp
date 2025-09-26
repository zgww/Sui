#include "ThreadUtil.h"
#include <thread>
#include <sstream>

std::string ThreadUtil::getThisThreadIdString()
{
    auto id = std::this_thread::get_id();
    std::stringstream sin;
    sin << id;
    return sin.str();
}
