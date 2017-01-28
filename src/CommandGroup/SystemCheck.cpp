#include "Robot.h"
#include "SystemCheck.h"
#include "Commands/WaitCommand.h"
#include "Commands/EncoderTest.h"
#include "Commands/TalonTest.h"

SystemCheck::SystemCheck()
{
  AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::SHOOTER));
  AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::SHOOTER));
  AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::FL));
  AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::FL));
  AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::RL));
  AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::RL));
  AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::FR));
  AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::FR));
  AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::RR));
  AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::RR));
  AddParallel(new EncoderTest( 2.0f, Encode::L));
  AddParallel(new TalonTest( 2.0f,  0.5f, TalonENUM::FL));
  AddParallel(new TalonTest( 2.0f,  0.5f, TalonENUM::RL));
  AddSequential(new TalonTest(0.0f, 0.0f, TalonENUM::FR)); //buffer
  AddParallel(new EncoderTest( 2.0f, Encode::R));
  AddParallel(new TalonTest( 2.0f,  0.5f, TalonENUM::FR));
  AddParallel(new TalonTest( 2.0f,  0.5f, TalonENUM::RR));

}
