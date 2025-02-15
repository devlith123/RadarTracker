#include "trackAnalyzer.hpp"

/*
** -------------------------- **
** Function to calculate the deltas between first and last Coordinates **
** return(std::tuple) -> tuple of deltas of x, y and Time **
** ----------------------------- **
*/
std::tuple<double, double, double> TrackAnalyzer::calculateDeltas() const {
    if (track.size() < 2) {
        throw std::runtime_error("Insufficient track data to calculate deltas");
    }
    double dx = track.back().x - track.front().x;
    double dy = track.back().y - track.front().y;
    double dt = track.back().time - track.front().time;
    return std::make_tuple(dx, dy, dt);
}

/*
** ----------------------------- **
** Function to load and read the Track File **
** Input - fileName-> Track File
** ----------------------------- **
*/
void TrackAnalyzer::loadTrackData(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file) {
        std::cerr << "Error in opening Track File" << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        double t, x, y;
        char comma;

        if (ss >> t >> comma >> x >> comma >> y) {
            track.emplace_back(t, x, y);
        }
    }
}

/*
** ----------------------------- **
** Function to load and read the Area File **
** Input- fileName-> Rect File
** ----------------------------- **
*/
void TrackAnalyzer::loadAreaData(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file) {
        std::cerr << "Error in opening Area File" << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        double x, y;
        char comma;

        if (ss >> x >> comma >> y) {
            area.emplace_back(x, y);
        }
    }
}

/*
** ----------------------------- **
** Function to check whether track will enter the Area, if yes returns time and point else nullopt **
** Return(std::optional) - If Track will Enter Area then return (Time, Point), else return (nullopt)
** ----------------------------- **
*/
std::optional<std::pair<double, AreaOfInterest>> TrackAnalyzer::willEnterArea() {
    if (track.size() < 2 || area.size() != 4) {
        std::cerr << "Not Enough Data" << std::endl;
        return std::nullopt;
    }

    auto isInside = [&](double x, double y) {
        return(x >= area[0].x && x <= area[1].x &&
                y >= area[2].y && y <= area[0].y);
    };

    for (std::size_t pos = 1; pos < track.size(); pos++) {
        auto [t1, x1, y1] = track[pos - 1];
        auto [t2, x2, y2] = track[pos];

        if (isInside(x1, y1)) {
            return std::make_pair(t1, AreaOfInterest{x1, y1});
        }

        if ((x1 < area[0].x && x2 >= area[0].x) || (x1 > area[1].x && x2 >= area[1].x) ||
            (y1 < area[2].y && y2 >= area[2].y) || (y1 > area[0].y && y2 >= area[2].y)) {
                double t_entry = t1 + ((t2 - t1) * (area[0].x - x1)) / (x2 - x1);
                double y_entry = y1 + ((y2 - y1) * (area[0].x - x1)) / (x2 - x1);

                return std::make_pair(t_entry, AreaOfInterest{area[0].x, y_entry});  
            }
    }

    return std::nullopt;
}

/*
** ----------------------------- **
** Function to return speed of track **
** Return(std::optional) - If there is enough data and able to calculate speed return speed, else nullopt **
** Formula used to calculate speed (speed = Distance Travelled / Time Elapsed)
** ----------------------------- **
*/
std::optional<double> TrackAnalyzer::calculateSpeed() {    
    try {
        auto [dx, dy, dt] = calculateDeltas();
        return dt > 0 ? std::make_optional(std::hypot(dx, dy) / dt) : std::nullopt;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

/*
** ----------------------------- **
** Function to return speed of track **
** Return(std::optional) - If there is enough data and able to calculate speed return speed, else nullopt **
** Formula Used to Calculate Direction (Direction = atan2(yend - ystart, xend - xstart))->radians * (180/pi) -> degrees.
** ----------------------------- **
*/
std::optional<double> TrackAnalyzer::calculateDirection() {
    try {
        auto [dx, dy, dt] = calculateDeltas();
        return std::atan2(dx, dy) * (180.0 / M_PI);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

/*
** ----------------------------- **
** Function to analyze tracker and print the output in console **
** ----------------------------- **
*/
void TrackAnalyzer::analyzeTracker() {
    const auto entryInfo = willEnterArea();

    if (entryInfo) {
        std::cout << "Track will Enter Area at time: " << " " << entryInfo->first << " "
                  << "at Position (" << entryInfo->second.y << ")" << std::endl;
    } else {
        std::cout << " Track will not enter Restricted Area" << std::endl;
    }

    const auto speed = calculateSpeed();
    const auto direction = calculateDirection();

    if (speed) {
        std::cout << "Speed of track: " << *speed << " m/s" << std::endl;
    } else {
        std::cout << " Speed cannot be calculated" << std::endl;
    }

    if (direction) {
        std::cout << "Direction of track: " << *direction << " degrees" << std::endl;
    } else {
        std::cout << " Direction cannot be calculated" << std::endl;
    }

}