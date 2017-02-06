#include "EncoderTest.h"

EncoderTest::EncoderTest(float timer, Encode e) {
  difEncoder = e;
  //this->timer = timer;
  SetTimeout((double)timer);
}

void EncoderTest::Initialize() {
  switch (difEncoder) {
    case Encode::L:
      encodes = RobotMap::drivetrainleft_encoder;
      std::cout<<  encodes;
      break;
    case Encode::R:
      encodes = RobotMap::drivetrainright_encoder;
      std::cout<<  encodes;
      break;
    default:
      encodes = nullptr;
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
