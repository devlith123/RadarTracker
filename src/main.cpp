#include "trackAnalyzer.hpp"
#include <thread>

int main() {
    auto trackAnalyzer = std::make_unique<TrackAnalyzer>();

    std::thread trackThread(&TrackAnalyzer::loadTrackData, trackAnalyzer.get(), "data/track.txt");
    std::thread areaThread(&TrackAnalyzer::loadAreaData, trackAnalyzer.get(), "data/rect.txt");

    trackThread.join();
    areaThread.join();

    trackAnalyzer->analyzeTracker();
}