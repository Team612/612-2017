#include "Commands/Auto.h"

Auto::Auto(String NameOfCommand) {
  switch(NameOfCommand){
    case ("Simple"):
      AddSequential();
      break;
    case("1 Gear Auto"):
      AddSequential();
      break;
    case("10 Ball Auto"):
      AddSequential();
      break;
    case("Full Gear Auto"):
      AddSequential();
      break;
    case("The Polymath"):
      AddSequential();
      break;
    case("Operation: Hopper Hack"):
      AddSequential();
      break;
    case("60 Ball Madlad Autonomous"):
      AddSequential();
      break;


  }
}
