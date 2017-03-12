#include "PIDAutoTuner.h"

template<class FEEDBACK_DEVICE>
lib612::PIDAutoTuner<FEEDBACK_DEVICE>::PIDAutoTuner(SpeedController& plant, FEEDBACK_DEVICE& source)
{
    this->plant = plant;
    this->source = source;
}

template<class FEEDBACK_DEVICE>
lib612::PIDAutoTuner<FEEDBACK_DEVICE>::
