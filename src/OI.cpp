#include "OI.h"
#include "Ports.h"

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/Vision/AlignToTarget.h"
#include "Commands/Climber/Climb.h"
#include "Commands/Drive/Drive.h"
#include "Commands/Drive/DriveDistance.h"
#include "Commands/Gear/Gear.h"
#include "Commands/Internal/IntakeFuel.h"
#include "Commands/Shooter/Shoot.h"

OI::OI() {
    gunner.reset(new frc::XboxController(PORTS::OI::gunner_joyport));

    driver.reset(new frc::XboxController(PORTS::OI::driver_joyport));


    // SmartDashboard Buttons
    SmartDashboard::PutData("MoveBalls", new IntakeFuel());
    SmartDashboard::PutData("Climb", new Climb());
    //SmartDashboard::PutData("DriveDistance", new DriveDistance());
    SmartDashboard::PutData("Gear", new Gear());
    SmartDashboard::PutData("AlignToTarget", new AlignToTarget());
    SmartDashboard::PutData("Shoot", new Shoot());
    SmartDashboard::PutData("Drive", new Drive());
}

std::shared_ptr<XboxController> OI::getdriver() {
   return driver;
}

std::shared_ptr<XboxController> OI::getgunner() {
   return gunner;
}
