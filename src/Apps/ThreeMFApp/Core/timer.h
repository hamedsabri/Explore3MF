#ifndef TIMER_H
#define TIMER_H

namespace E3D
{
    namespace Timer
    {
        void updateTime();

        double getDeltaSec();
        double getDeltaMillSec();
        double getMillSecPerFrame();
    }
}

#endif // TIMER_H
