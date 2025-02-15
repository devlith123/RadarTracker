#include "trackAnalyzer.hpp"

int main() {
    TrackAnalyzer trackAnalyzer;

    trackAnalyzer.loadTrackData("data/track.txt");
    trackAnalyzer.loadAreaData("data/rect.txt");

    trackAnalyzer.analyzeTracker();
}