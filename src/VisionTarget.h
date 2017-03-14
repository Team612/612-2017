#pragma once

#include "WPILib.h"
#include <cmath>

/// A struct to represent a fixed point.
struct Point {
        int x;
        int y;
};

/*!
* @brief A class to represent a tracked vision target.
* Used to store information about each vision target being sent over. Basically a bounding box with some extra perks.
*/
class VisionTarget {
public:

    static const int PARAM_COUNT = 4; /// The amount of parameters being sen

    static const double HEIGHT; /// The physical height of the target
    static const double WIDTH; /// The physical width of the target

    /*!
     * @brief Uses a set of points and an ID to create a box
     * @param initPoints The set of points
     * @param id The target's ID
     */
    VisionTarget(std::vector<int> initPoints, int id); //See "Set()"
    virtual ~VisionTarget();

    /*!
     * @brief Get the upper left point
     * @return The upper left point
     */
    Point GetUL(); //
    /*!
     * @brief Get the lower left point
     * @return The lower left point
     */
    Point GetLL(); //Lower-Left
    /*!
     * @brief Get the upper right point
     * @return The upper right point
     */
    Point GetUR(); //Upper-Right
    /*!
     * @brief Get the lower right point
     * @return The lower right point
     */
    Point GetLR(); //Lower-Right

    /*!
     * @brief Get the center point
     * @return The center point
     */
    Point GetCenter();

    /*!
     * @brief Get width of the bounding box
     * @return The width of the bounding box
     */
    int GetWidth();

    /*!
     * @brief Get height of the bounding box
     * @return The height of the bounding box
     */
    int GetHeight();

    int GetHeightConvex();

    /*!
     * @brief Get the physical distance of the target from the wall
     * @return The height of the bounding box
     */
    double GetDistance();

    /*!
     * @brief Get the aspect ratio of the box
     * @return Aspect ratio
     */
    double GetAspectRatio(); //width/height

    int GetID(); //The tracking ID set by RoboRealm to distinguish one object as it moves frame to frame

    /*!
     * @brief Set the points of the box based on a vector.
     * Sets the points in a size 8 vector in the following format {x, y, width, height}
     * This is the way they are sent over from the microprocessor.
     * @param setPoints The vector of points
     */
    void Set(std::vector<int> setPoints); 

    /*!
     * @brief Print the location and ID of the box for debugging
     */
    void Print();

    /*!
     * @brief Find the box in a provided list that most closely matches the provided aspect ratio.
     * @param aspect The target aspect ratio
     * @param targets The list of targets
     */
    static std::shared_ptr<VisionTarget> FindClosestAspect(double aspect, std::vector<std::shared_ptr<VisionTarget>> targets);

private:
    int x; /// X Coordinate
    int y; /// Y Coordinate
    int width = 0; /// Width
    int height = 0; /// Height
    int hHeight;

    int id; ///The tracking ID as given by the microprocessor

    /*!
     * @brief A simple function to ease the creation of points.
     * @param x The x position
     * @param y The y position
     */
    Point MakePoint(int x, int y);

};
