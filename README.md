# Project Basic Lane Finding 

This project is just a self-learning experience by implementing in C++14 an 
algorithm similar to this
 [Udacity project](https://github.com/ndrplz/self-driving-car/blob/master/project_1_lane_finding_basic/).

Demo on straight road [videoclip](https://www.youtube.com/watch?v=mbqWboRy95Q):

<a href="https://www.youtube.com/watch?v=mbqWboRy95Q" target="_blank"><img src="https://img.youtube.com/vi/mbqWboRy95Q/0.jpg" 
alt="circuit" width="240" height="180" border="10" /></a>

Demo on cornering road [videoclip](https://www.youtube.com/watch?v=qCyg2w0ElU4):

<a href="https://www.youtube.com/watch?v=qCyg2w0ElU4" target="_blank"><img src="https://img.youtube.com/vi/qCyg2w0ElU4/0.jpg" 
alt="circuit" width="240" height="180" border="10" /></a>

## Basic Build Instructions
We should first install OpenCV for C++ and Boost. After that,

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./basic_lane_finding_cpp`

## Explanation

The implementation can be seen in `src/main.cpp` with the following steps:

1. Read in image as RGB
2. Apply Gaussian blur
3. Apply a region of interest (ROI)
4. Apply Hough line detection
5. Transform Hough line to Cartesian line (with slope and bias)
6. Filter lines based on slopes
7. Separate into left and right lines based on slopes
8. On left lines, get the median line
9. On right lines, get the median line.
10. Apply moving average on each left and right line
11. Visualize