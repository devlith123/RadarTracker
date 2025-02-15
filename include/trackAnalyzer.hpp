#ifndef TRACKANALYZER_HPP
#define TRACKANALYZER_HPP

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <optional>
#include <tuple>

/*
** -------------------------- **
** Structure To Store Area Data **
** time -> Timestamp of the Track **
** x -> x coordinate of the Track **
** y -> y coordinate of the Track **
** ----------------------------- **
*/
struct TrackData {
    double time, x, y;

    // Constructor to initialize members
    TrackData(double t, double xPos, double yPos) : time(t), x(xPos), y(yPos) {}
};

/*
** -------------------------- **
** Structure To Store Area Data **
** x -> x coordinate of the Area **
** y -> y coordinate of the Area **
** ----------------------------- **
*/
struct AreaOfInterest {
    double x, y;

    // Constructor to initialize members
    AreaOfInterest(double xPos, double yPos) : x(xPos), y(yPos) {}
};


class TrackAnalyzer {
private:
    std::vector<TrackData> track;
    std::vector<AreaOfInterest> area;

public:
    void loadTrackData(const std::string& fileName); // Load Track Data from the File track.txt.
    void loadAreaData(const std::string& fileName); // Load Track Data from the File track.txt.
    std::optional<std::pair<double, AreaOfInterest>> willEnterArea(); // Get the time and point where the track will enter Area.
    std::optional<double> calculateSpeed(); // Calculate the speed of track.
    std::optional<double> calculateDirection(); // Calculate direction of the track.
    void analyzeTracker(); // Analyze the Track.

    std::tuple<double, double, double> calculateDeltas() const; // Generic Function to calculate Deltas.

};

#endif // TRACKANALYZER_HPP