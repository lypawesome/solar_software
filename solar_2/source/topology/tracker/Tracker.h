#ifndef TRACKER_H
#define TRACKER_H

#include "topology/tracker/Armature.h"
#include "topology/tracker/Target.h"

namespace solar{

    class Tracker
    {
        private: 
            std::shared_ptr<Armature> armature_;
            std::shared_ptr<Target> target_;
    };
}



#endif

