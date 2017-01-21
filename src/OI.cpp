#include "OI.h"
#include "Ports.h"

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AlignToTarget.h"
#include "Commands/Climb.h"
#include "Commands/Drive.h"
#include "Commands/DriveDistance.h"
#include "Commands/Gear.h"
#include "Commands/MoveBalls.h"
#include "Commands/Shoot.h"

OI::OI() {
    gunner.reset(new frc::XboxController(PORTS::OI::gunner_joyport));

    driver.reset(new frc::XboxController(PORTS::OI::driver_joyport));


    // SmartDashboard Buttons
    SmartDashboard::PutData("MoveBalls", new MoveBalls());
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
