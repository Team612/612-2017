#include "EncoderTest.h"

EncoderTest::EncoderTest(float timer, Encode e) {
  difEncoder = e;
  SetTimeout((double)timer);
}

void EncoderTest::Initialize() {
  switch (difEncoder) {
    case Encode::L:
      std::cout<<  RobotMap::drivetrainleft_encoder->Get();
      break;
    case Encode::R:
      std::cout<<  RobotMap::drivetrainright_encoder->Get();
      break;
    default:
      std::cout << "ERROR IN EncoderTest.cpp";
      break;
  }
}

void EncoderTest::Execute() {

}

bool EncoderTest::IsFinished() {
  return IsTimedOut();
}

void EncoderTest::End() {

}

void EncoderTest::Interrupted() {

}
