

#include "DriveDistance.h"



DriveDistance::DriveDistance(double distance): Command() {
    m_distance = distance;

}


void DriveDistance::Initialize() {

}


void DriveDistance::Execute() {

}


bool DriveDistance::IsFinished() {
    return false;
}


void DriveDistance::End() {

}


void DriveDistance::Interrupted() {

}
