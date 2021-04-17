#include "Bus.h"
#include "global.h"

bool Bus::check(int f,int t)
{
    if((from==f && to==t) || (from==t && to==f))
        return true;
    return false;
}

FixedBus::FixedBus(int f, int t, const std::string &n, std::vector<int> &v) : Bus(f, t, n), time(v)
{
}

int FixedBus::getNearestTime()
{
    int cur = CurTime;
    unsigned int i = 0;
    for (i = 0; i < time.size(); i++)
    {
        if (time[i] > cur)
            break;
    }
    return time[i] - cur;
}

RepeatBus::RepeatBus(int f, int t, const std::string &n, int interv) : Bus(f, t, n), interval(interv)
{
}

int RepeatBus::getNearestTime()
{
    return CurTime % interval;
}
