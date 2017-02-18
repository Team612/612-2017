#include "AlignToTarget.h"

AlignToTarget::AlignToTarget(): Command() {
    Requires(Robot::drivetrain.get());
}

void AlignToTarget::Initialize() {

}

void AlignToTarget::Execute() {

}

bool AlignToTarget::IsFinished() {
    return false;
}

void AlignToTarget::End() {

}

void AlignToTarget::Interrupted() {

}
