#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <ranges>
#include <cmath>
#include <vector>

class TrackData {
    public:
    double time, x, y;

    TrackData(double t, double xPos, double yPos) : time(t), x(xPos), y(yPos) {}
};

class AreaOfInterest {
    public:
    double x, y;

    AreaOfInterest(double xPos, double yPos) : x(xPos), y(yPos) {} 
};

class TrackAnalyzer {
    std::vector<TrackData> track;
    std::vector<AreaOfInterest> area;

    public:
    void loadTrackData(const std::string& fileName) {
        std::ifstream file(fileName);

        if (!file) {
            std::cerr << "Error in opening File" << std::endl;
            return;
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

    void loadAreaData(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file) {
            std::cerr << "Error in opening Area file" << std::endl;
            return;
        }

        std::string line;
        while(std::getline(file, line)) {
            std::istringstream ss(line);
            double x, y;
            char comma;
            if (ss >> x >> comma >> y) {
                area.emplace_back(x, y);
            }
        }
    }

    std::optional<std::pair<double, AreaOfInterest>> willEnterArea() {
        if (track.size() < 2 || area.size() != 4) {
            std::cerr << "Not Enough Data" << std::endl;
            return std::nullopt;
        }

        auto isInside = [this](double x, double y) {
            return (x >= area[0].x && x <= area[1].x) &&
                   (y >= area[2].y && y <= area[0].y); 
        };

        for (std::size_t i = 1; i < track.size(); i++) {
            auto [t1, x1, y1] = track[i - 1];
            auto [t2, x2, y2] = track[i];

            if (isInside(x1, y1)) {
                return std::make_pair(t1, AreaOfInterest(x1, y1));
            }

            if ((x1 < area[0].x && x2 >= area[0].x) ||
                (x1 > area[1].x && x2 >= area[1].x)) {
                    double t_entry = t1 + (t2 - t1) * (area[0].x - x1) / (x2 - x1);
                    double y_entry = y1 + (y2 - y1) * (area[0].x - x1) / (x2 - x1);

                    return std::make_pair(t_entry, AreaOfInterest(area[0].x, y_entry));
                } 
        }
         return std::nullopt;
    }
};