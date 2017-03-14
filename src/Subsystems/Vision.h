#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../VisionTarget.h"
#include <vector>
#include "DigitalOutput.h"

/*!
 * @brief The class for the vision subsystem.
 * This class stores and keeps track of all targets being detected on the vision microprocessor.
 */
class Vision: public Subsystem
{
private:
	const std::string BOUNDING_KEY = "BOUNDING_COORDINATES"; /// The key in the network table for the list of target coordinates
	const std::string IDS_KEY = "IDS"; /// The key in the network table for the list of target IDs

	std::shared_ptr<NetworkTable> table = NULL; /// The network table used to transfer the target information
	std::vector<std::shared_ptr<VisionTarget>> targets; /// A list of all targets being sent to the robot

	std::shared_ptr<VisionTarget> goal; /// The current target that the robot is following

	const float TARGET_ASPECT = 1.66f/1.00f; /// The target aspect ratio for the goal's bounding box.

public:
	Vision();
	void InitDefaultCommand();

	/*!
	 * @brief Pulls values from the vision network table
	 * This function must be called periodically from Robot
	 */
	void PullValues();
	//void SetCamera(const char* camera);

	/*!
	 * Lists all of the current targets detected by the camera.
	 * @return A list of detected vision targets as VisionTarget objects
	 */
	std::vector<std::shared_ptr<VisionTarget>> GetAllTargets(); //List all detected vision targets

	/*!
	 * @brief Get the number of detected vision targets.
	 * Basically equivalent to GetAllTargets().size()
	 * @return The amount of detected targets
	 */
	int GetTargetAmount(); //Amount of detected vision targets (targets.size())

	/*!
	 * @brief Get a target by it's tracking ID.
	 * @return The amount of detected targets
	 */
	std::shared_ptr<VisionTarget> GetTargetById(int id); //Get target by it's ID in our jank Python program

	/*!
	 * @brief Check to see if a target exists in the list of tracked targets
	 * @param id The id of the target to check
	 */
	bool TargetExists(int id); //Check if an ID exists


	/*!
	 * @brief Check to see if a target exists in the list of tracked targets
	 * @param target The target to check
	 */
	bool TargetExists(std::shared_ptr<VisionTarget> target);

	/*
	 * I am so sorry
	 */

	/*!
	 * @brief Get the raw network table object.
	 * @return The vision network table object.
	 */
	std::shared_ptr<NetworkTable> GetRawTable();

	/*!
	 * @brief Update which target the robot is aligning to.
	 * @return Whether or not a target was found
	 */
	bool UpdateCurrentTarget();

	/*!
	 * @brief Get the current goal that the robot is trying to align to.
	 * @return The tracked goal as a VisionTarget
	 */
	std::shared_ptr<VisionTarget> GetTrackedGoal();

	/*!
	 * @brief Set which goal is being followed by the robot
	 * Basically equivalent to SetTrackingID(target.getTrackingID())
	 * @param target The target to track
	 */
	void SetTrackedGoal(std::shared_ptr<VisionTarget> target);

	/*!
	 * @brief Set the ID of the target the robot is following.
	 * @param id The ID of the target to track
	 */
	void SetTrackingID(int id);

	/*!
	 * @brief Retrieve the ID of the target the robot is following.
	 * @returb id The ID of the tracked target
	 */
	int GetTrackingID();
};
