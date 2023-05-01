#include <cstdio>
#include <algorithm>
#include <stack>
#include <limits>
#include <chrono>
#include <bits/stdc++.h>
#define MAX_POINTS 3000
#define INFINITY_VALUE numeric_limits<double>::infinity()
typedef std::chrono::high_resolution_clock HighResClock;
using namespace std;


/**
 * @brief Struct representing a Coordinates with x and y values.
 */
struct Coordinate {
    double x_coord, y_coord;

    /**
     * @brief Overloaded less-than operator for sorting coord by x value.
     *
     * @param other The other Coordinates to compare to.
     * @return True if this Coordinates's x value is less than the other Coordinates's x value, false otherwise.
     */
    bool operator < (const Coordinate& other) const {
        return x_coord < other.x_coord;
    }
} coordinates[MAX_POINTS + 1];


/**
 * @brief Array storing the cumulative sum of x values up to each point.
 */
double cumul_x[MAX_POINTS + 1], cumul_y[MAX_POINTS + 1], cumul_xy[MAX_POINTS + 1], cumul_xSqr[MAX_POINTS + 1];  // cumulative sum for x,y,x*x,x*y

/**
 * @brief 2D array storing the slope of the line between two points.
 */
double line_slope[MAX_POINTS + 1][MAX_POINTS + 1], line_intercept[MAX_POINTS + 1][MAX_POINTS + 1], Error[MAX_POINTS + 1][MAX_POINTS + 1]; //2D  matrices containing slope, intercept term for two points, and error term

/**
 * @brief Array storing the optimal solution error for each point.
 */
double optimal_solution[MAX_POINTS + 1];  //vector for storing optimal solution error for each point

/**
 * @brief Array storing the optimal solution segment starting point for each point.
 */
double optimal_segment[MAX_POINTS + 1];   //vector for storing optimal solution segment starting point for each point

/**
 * @brief Calculates the slope and intercept for the best fit line given a set of points.
 *
 * @param obj.num_p The number of points in the dataset.
 * @param obj.xs The sum of the x values in the dataset.
 * @param obj.ys The sum of the y values in the dataset.
 * @param obj.xys The sum of the product of x and y values in the dataset.
 * @param x2_sum The sum of the square of the x values in the dataset.
 * @param slope The slope of the best fit line, passed by reference.
 * @param intercept The intercept of the best fit line, passed by reference.
 */

/*this function takes in parameters : num_points,x_sum,y_sum,xy_sum. The values x_sum,y_sum,xy_sum,x2_sum is used to calculate the value of slope intercept for the best fit line for a given set of points, and the values given are the values extracted from those mentioned points.*/
void findBestFitLine(int num_points, double x_sum, double y_sum, double xy_sum, double x2_sum, double& slope, double& intercept) {
    double denominator = (num_points * x2_sum - x_sum * x_sum);
    if (denominator == 0) {                //if straight vertical line
        slope = INFINITY_VALUE;
        intercept = x_sum / num_points;
        return;
    }
    slope = (num_points * xy_sum - x_sum * y_sum) / denominator;  //from the formula
    intercept = (y_sum - slope * x_sum) / num_points;            //from the formula
} 

int main() {
    int num_points, index_i, index_j, index_k, point_interval;
    double x_sum, y_sum, xy_sum, xsqr_sum, temp_val, min_val, cost;
    auto start_time = HighResClock::now();  //starting clock for calculating execution time 
    cin >> num_points;     //take number of points as input
    cin >> cost;         // take cost/penalty term input

    for (index_i = 1; index_i <= num_points; index_i++)
        cin >> coordinates[index_i].x_coord >> coordinates[index_i].y_coord;   //taking points input 

    sort(coordinates + 1, coordinates + num_points + 1);      //sorting the points by x coordinate 

    cumul_x[0] = cumul_y[0] = cumul_xy[0] = cumul_xSqr[0] = 0;    //initially all 4 cumulative values start with 0 
    for (index_j = 1; index_j <= num_points; index_j++) {                                                                  //for each point j 
        /*for each cumulative vector, we will increment the values of the vector by adding the current x_coordinate with the previous cumulative value, implementing a basic prefix array here*/
        cumul_x[index_j] = cumul_x[index_j - 1] + coordinates[index_j].x_coord;                                            
        cumul_y[index_j] = cumul_y[index_j - 1] + coordinates[index_j].y_coord;
        cumul_xy[index_j] = cumul_xy[index_j - 1] + coordinates[index_j].x_coord * coordinates[index_j].y_coord;
        cumul_xSqr[index_j] = cumul_xSqr[index_j - 1] + coordinates[index_j].x_coord * coordinates[index_j].x_coord;

        for (index_i = 1; index_i <= index_j; index_i++) {  //for each i 
            point_interval = index_j - index_i + 1;
            x_sum = cumul_x[index_j] - cumul_x[index_i - 1];  //calculating cumulative x_sum value for window i->j
            y_sum = cumul_y[index_j] - cumul_y[index_i - 1];    //calculating cumulative y_sum value for window i->j
            xy_sum = cumul_xy[index_j] - cumul_xy[index_i - 1];    //calculating cumulative xy_sum value for window i->j
            xsqr_sum = cumul_xSqr[index_j] - cumul_xSqr[index_i - 1];    //calculating cumulative x2_sum value for window i->j
            findBestFitLine(point_interval, x_sum, y_sum, xy_sum, xsqr_sum, line_slope[index_i][index_j], line_intercept[index_i][index_j]);

            for (index_k = index_i, Error[index_i][index_j] = 0.0; index_k <= index_j; index_k++) {
                if (line_slope[index_i][index_j] != INFINITY_VALUE && line_intercept[index_i][index_j] != INFINITY_VALUE) {  //if not vertical line
                    temp_val = coordinates[index_k].y_coord - line_slope[index_i][index_j] * coordinates[index_k].x_coord - line_intercept[index_i][index_j];
                    Error[index_i][index_j] += temp_val * temp_val;   //finding out error value for each point on best fit line 
                } else {
                    temp_val = coordinates[index_k].x_coord - line_intercept[index_i][index_j];
                    Error[index_i][index_j] += temp_val * temp_val;
                }
            }
        }
    }

    optimal_solution[0] = optimal_segment[0] = 0;
    for (index_j = 1; index_j <= num_points; index_j++) {
        for (index_i = 1, min_val = INFINITY_VALUE, index_k = 0; index_i <= index_j; index_i++) {
            temp_val = Error[index_i][index_j] + optimal_solution[index_i - 1];
            if (temp_val < min_val) {
                min_val = temp_val;              //finding minimum error pair
                index_k = index_i;
            }
        }
        optimal_solution[index_j] = min_val + cost;
        optimal_segment[index_j] = index_k;
    }


    vector<double> segments;
    for (index_i = num_points, index_j = optimal_segment[num_points]; index_i > 0; index_i = index_j - 1, index_j = optimal_segment[index_i]) {
        segments.push_back(index_i);      //adding to segment, points of the best segments 
        segments.push_back(index_j);
    }
    ofstream outputFile("task2printer.txt");   //this is for giving input to plotter 

    if (!outputFile.is_open()) {
        cerr << "Failed to open file!" << endl;   
        return 1;
    }

    outputFile << num_points << endl;    //this is for giving input to plotter 
    for (index_i = 1; index_i <= num_points; index_i++) {
        outputFile << coordinates[index_i].x_coord << " " << coordinates[index_i].y_coord << endl;
    }

    outputFile << segments.size() / 2 << endl;  //this is for giving input to plotter 

    while (!segments.empty()) {
        //index_i and idnex_j are the two points of a segment(best fit)
        index_i = segments.back(); segments.pop_back();
        index_j = segments.back(); segments.pop_back();
        outputFile << line_slope[index_i][index_j] << " " << line_intercept[index_i][index_j] << " " << coordinates[index_i].x_coord << " " << coordinates[index_j].x_coord << endl; //this is for giving input to plotter 
    }


    auto end_time = HighResClock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Execution time: " << elapsed_time / 1000 << " microseconds" << endl;  //printing execution time

    outputFile.close();


    string filename = "plotterTask2.py";   //running plotter file through system command
    string command = "python ";
    command += filename;
    system(command.c_str());

    return 0;
}
