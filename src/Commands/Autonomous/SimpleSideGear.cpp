#include "SimpleSideGear.h"
#include "../../Robot.h"

SimpleSideGear::SimpleSideGear(double speed, double timeout, bool inverted)
        : Command("SimpleSideGear") {
    Requires(Robot::drivetrain.get());
    base_speed = speed;
    is_inverted = inverted;
    SetTimeout(timeout);
}

void SimpleSideGear::Initialize() {
    time.Reset();
    time.Start();
    //start driving with the robot angled towards the side of the airship
    Robot::drivetrain->TankDrive(base_speed * .95, base_speed);
}

void SimpleSideGear::Execute() {
    //if the (right) robot is less than 15 inches away from the wall
    //TODO test 15 inches as threshold
    if(Robot::drivetrain->GetURSide()->GetDistanceInches() < 15) {
        //slowly curve in the correct direction
        if(is_inverted)
            Robot::drivetrain->TankDrive(base_speed * 0.95 / 2.0, base_speed / 4.0);
        else
            Robot::drivetrain->TankDrive(base_speed * 0.95 / 4.0, base_speed / 2.0);
    } else
        Robot::drivetrain->TankDrive(base_speed, base_speed); //TODO, watch if jumpyness in Ultrasonic values causes robot to come off course
}

bool SimpleSideGear::IsFinished() {
    return IsTimedOut();
}

void SimpleSideGear::End() {
    Robot::drivetrain->TankDrive(0, 0);
}

void SimpleSideGear::Interrupted() {
    Robot::drivetrain->TankDrive(0, 0);
}
