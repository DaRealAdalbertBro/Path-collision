#pragma once

// VISUALIZATION
#define VISUALIZATION true	// turn on/off visualization
#define V_DRIVER1_COLOR "blue"	// color of driver1's line
#define V_DRIVER2_COLOR "green"	// color of driver2's line
#define V_SOLUTION_POINTS_COLOR "red"	// color of solution points
#define V_SOLUTION_POINTS_PEN_WIDTH 15	// width of solution points
#define V_SPEED ct::TS_FASTEST	// visualization speed
#define V_SCALE 0.05	// view - scale						// try using 0.2,
#define V_OFFSET_X -200	// view - offset X					// -1000,
#define V_OFFSET_Y -200	// view - offset Y					// -1200
#define V_ANIMATION_SKIP_FRAMES 20	// skip animation frames - set 0 to disable.
#define V_ANIMATION_SKIP_FRAMES_DELAY 1	// delay between the next move [ms]

// OTHER
#define PROCESS_TIME true	// Show & process execution time
#define DEFAULT_DATA_DIRECTORY "Data.txt"	// default Data.txt file directory
#define RESULT_LIMIT 5	// Limiting the number of solutions

// LANG
#define L_VISUALIZATION "Do you want to visualize the solution? [Y/N]"
#define L_PROCESS_TIME "Processing time"
#define L_INVALID_TRACK_FORMAT "Invalid track format entered!"
#define L_INVALID_INTERVAL_FORMAT "Incorrect interval format, try using the XXX-XXX format in the Data.txt file!"
#define L_FILE_NOT_FOUND "Couldn't find the Data.txt file!"
#define L_NO_SOLUTIONS "No solution has been found!"
#define L_RESULT_COORDS "The resulting coordinates of a possible break"
#define L_RESULT_COORDS_OTHER "Other possible breaks"
