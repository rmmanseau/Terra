#include "cmovement.h"

SRC_FACTORY_REGISTER(CMovement);

bool CMovement::init(YAML::Node node)
{
    try
    {
        int dirInt = node["direction"].as<int>();
        if (dirInt < 0 || dirInt > 7)
            throw std::range_error("direction must be between 0 and 7");
        direction = (Dir)dirInt;

        velocity  = node["velocity"].as<double>();
        if (velocity <= 0)
            throw std::range_error("velocity must be greater than 0");

        turnAngle = node["turn_angle"].as<int>();
        if (turnAngle < 0 || turnAngle > 4)
            throw std::range_error("turn_angle must be between 0 and 4");

        active = false;
    }
    catch (std::range_error& re)
    {
        std::cout << re.what() << std::endl;
        return false;
    }
    catch (...)
    {
        return false;
    }
    return true;
}

Dir CMovement::getUpdatedDirection()
{
    if (turnAngle > 0)
    {
        int turn = (rand() % (turnAngle*2 + 1)) - turnAngle;
        direction = (Dir)(((int)direction + turn + 8) % 8);
    }
    return direction;
}

double CMovement::getUpdatedVelocity()
{
    return velocity;
}
