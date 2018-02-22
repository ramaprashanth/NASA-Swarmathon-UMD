#ifndef SEARCH_CONTROLLER
#define SEARCH_CONTROLLER

#include <random_numbers/random_numbers.h>
#include "Controller.h"

/**
 * This class implements the search control algorithm for the rovers. The code
 * here should be modified and enhanced to improve search performance.
 */
class SearchController : virtual Controller {

public:

    SearchController();

    void Reset() override;

    // performs search pattern
    Result DoWork() override;
    bool ShouldInterrupt() override;
    bool HasWork() override;

    // sets the value of the current location
    //void UpdateData(geometry_msgs::Pose2D currentLocation, geometry_msgs::Pose2D centerLocation);
    void SetCurrentLocation(Point currentLocation);
    void SetCenterLocation(Point centerLocation);
    void SetSuccesfullPickup();

    Result goToStartingPoint(); // sending rover to their starting location
    bool getStartingPoint() {return startingPoint;} // returns true if rover has reached their starting location
    Result prelimSearchBehaviour(); // where rover's normal search algo goes for prelim round
    Result semiSearchBehaviour(); // rover's algo for semi-final rounds
    void setRoverName(string publishedName); // setting the rover name
    float getStartingRadius(); // radius rover is bounded by their starting location

    // starting theta each rover will have
    float getTheta(string roverName) {
        if (roverName == "achilles") { return (2*M_PI)/3; }
        else if (roverName == "ajax") {return -M_PI/4; }
        else if (roverName == "aeneas") { return M_PI/4; }
        else if (roverName == "diomedes") { return (5*M_PI)/4; }
        else if (roverName == "paris") { return (4*M_PI)/3; }
        else if (roverName == "hector") { return M_PI/3; }
        else { return 0; }
    }



protected:

    void ProcessData();

private:

    random_numbers::RandomNumberGenerator* rng;
    Point currentLocation;
    Point centerLocation;
    Point searchLocation;
    int attemptCount = 0;


    Result result; //struct for returning data to ROS adapter
    bool startingPoint = false; // true if reached starting point
    string roverName = ""; // name of the rover
    int choice = 0;
    const float C_INCREASE = .5; // constant added to the distance for rover's doing C shapes
    const float S_INCREASE = .2; // constant added to the distance for rover's doing spirls
    float distance = 0; // will hold the increased distance rovers will go
    float horizD = 2.5, verD = 5.5; // the horizontal and vertical distance
    int negation = 1; // used when we want to negate radians to make rovers turn a different direction
    float THETA_1, THETA_2, THETA_3, THETA_4;
    // Search state
    // Flag to allow special behaviour for the first waypoint
    bool first_waypoint = true;
    bool succesfullPickup = false;
    int timeDelayInt = 0;
    bool timeDelayBool = false;
    int spiralCount = 0;
    bool firstSpiral = true; // spiral going to starting location first time
    bool prelim = false;
};

#endif /* SEARCH_CONTROLLER */
