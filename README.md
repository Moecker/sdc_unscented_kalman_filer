# Unscented Kalman Filter Project
Self-Driving Car Engineer Nanodegree Program

---

## Results

# Result for sample-laser-radar-measurement-data-1.txt
Required accuracy: [0.09, 0.09, 0.65, 0.65].
![Visualization Data Set 2](results/ukf-visualization2.png)
![RMSE Data Set 2](results/output2.png)

# Result for sample-laser-radar-measurement-data-2.txt
Required accuracy: [0.20, 0.20, 0.55, 0.55].
![Visualization Data Set 1](results/ukf-visualization1.png)
![RMSE Data Set 1](results/output1.png)

Note that the first to values of the input data file have been manually set to a small floating point number as suggested by the lecture.
"One way to catch for this is to observe when both px, py are zero and instead set them to some small floating value."

## How To
Use the configure.bat to configure two project:
- One for Visual Studio 2015 with MSVC compiler
- One generating Make file with GNU g++ compiler

Call run_vs or run_make for either compiler.
Or simply use the command suggested in "Basic Build Instructions"

The run_vs is by default using the first set of example measurments.
The run_make is by default using the second set of example measurements.

## Dependencies

* cmake >= v3.5
* make >= v4.1
* gcc/g++ >= v5.4

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./UnscentedKF path/to/input.txt path/to/output.txt`. You can find
   some sample inputs in 'data/'.
    - eg. `./UnscentedKF ../data/sample-laser-radar-measurement-data-1.txt output.txt`

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html) as much as possible.

## Generating Additional Data

This is optional!

If you'd like to generate your own radar and lidar data, see the
[utilities repo](https://github.com/udacity/CarND-Mercedes-SF-Utilities) for
Matlab scripts that can generate additional data.

## Project Instructions and Rubric

This information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/c3eb3583-17b2-4d83-abf7-d852ae1b9fff/concepts/4d0420af-0527-4c9f-a5cd-56ee0fe4f09e)
for instructions and the project rubric.
