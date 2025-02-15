# Track Analyzer - Movement Analysis Tool

A C++ program to analyze object movement tracks, detect entry into defined areas of interest, and calculate speed/direction. Supports rectangles initially.

## Installation

### Prerequisites
- C++20 compatible compiler (GCC 9+/Clang 10+/MSVC 2019+)
- CMake 3.14+

### Build Instructions
```bash
# Clone repository
git clone https://github.com/devlith123/RadarTracker.git
cd track-analyzer

# Create build directory
mkdir build && cd build

# Generate build system
cmake ..

# Build project
cmake --build .
