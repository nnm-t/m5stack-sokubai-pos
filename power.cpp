#include "power.h"

namespace SokubaiPos
{
    int8_t Power::GetBatteryLevel()
    {
        return M5.Power.getBatteryLevel();
    }
}