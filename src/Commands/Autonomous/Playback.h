#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include <vector>
#include <string>
#include "../../RobotMap.h"
#include <fstream>

/*! \brief Class to read from file and playback
	Reads from a file and executes through Talon SRX in RobotMap
	Using std::fstream to read from file line by line and executes
	according to the timemark.
	Also uses voltage compensation mode to increase accuracy.
*/
class Playback: public Command {
private:
    struct playback_frame {
        double time;
        double l;
        double r;
    };

    bool isFinished;

	/*! \brief Time counter variable
		Used to check if the current timemark at a given 
		line (in the file) is smaller than the current time.
	*/
    uint32_t t = 0;

    playback_frame playback_frame_buf;

    std::vector<playback_frame> playback_vec;

    std::string filePath;
    std::ifstream inputFile;

	/*! \brief Timer object
		Used to check the current time in relation to 
		the current timemark in the current line (in the file).
	*/
    frc::Timer timer;

	/*! \brief A multiplier variable
		Used to playback at another speed. 
		A multiplier of 0.5 will play at half the speed, 
		while a multiplier of 2.0 will play at 2x speed of when it was recorded.
		
		Note: if the file was recorded with a max speed of 25%, it must be 
		played back with a multiplier of 4 to achieve 100% 
	*/
    const double TIME_MULTIPLIER = 1;

public:
    Playback(std::string filePath);
    void Initialize() override;
	/*! \brief Execution of MotionProfile
		Executes at 60 times a second to drive the 
		RobotMap Talon SRX according the file
	*/
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
