//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<long> readlineoflongs(int count) {
    // Input values
    vector<long> linevalues(count);
    for (int j = 0; j < count; j++) {
        long val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

//Take the two input dimensions of this box and add them to a vector in order that the first one is bigger
vector<long long> add_with_x_bigger(vector<long> &this_box, int dim_1, int dim_2, int dim_3) {
    vector<long long> output_box;
    if (this_box[dim_1] > this_box[dim_2]) { //If the first dimension is bigger, add it first
        output_box.push_back(this_box[dim_1]);
        output_box.push_back(this_box[dim_2]);
        output_box.push_back(this_box[dim_3]);
    }
    else { //Otherwise add it second
        output_box.push_back(this_box[dim_2]);
        output_box.push_back(this_box[dim_1]);
        output_box.push_back(this_box[dim_3]);
    }
    return output_box;
}

//Code to sort only the first column of the vector taken from https://stackoverflow.com/questions/21978557/sort-multidimensional-vector-by-1st-column
//It's been altered to long and the direction changed to sort in descending order
struct FirstColumnOnlyCmp {
    bool operator()(const std::vector<long long>& lhs, const std::vector<long long>& rhs) const {
        return lhs[0] > rhs[0];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    //! loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<long> params = readlineoflongs(2);
        long h = params[0];
        long n = params[1];

        //Loop over inputs
        vector<vector<long long>> boxes;
        for (int j = 0; j < n; j++) {
            vector<long> this_box = readlineoflongs(3);
            //Add all three orientations of this box, with x being bigger, to boxes
            boxes.push_back(add_with_x_bigger(this_box,0,1,2));
            boxes.push_back(add_with_x_bigger(this_box, 1, 2,0));
            boxes.push_back(add_with_x_bigger(this_box, 0, 2,1));
        }

        //Sort by x
        std::sort(boxes.begin(), boxes.end(), FirstColumnOnlyCmp());

        vector<long long> height(boxes.size());
        bool possible = false;
        //Iterate over boxes
        for (int j = 0; j < boxes.size(); j++) {
            long long temp_height = boxes[j][2]; //Set a temp height variable equal to picking this box alone
            //For all previous boxes
            for (int k = 0; k < j; k++) {
                if (boxes[j][0] < boxes[k][0] && boxes[j][1] < boxes[k][1]) { //If both x and y dimensions are smaller
                    temp_height = max(temp_height,(boxes[j][2] + height[k])); //Set temp height to max of current value and sum of this box and the previous box under consideration
                }                
            }
            height[j] = temp_height; //Record the final height in the height matrix
            
            //If we've already surpassed the top height, set to true and exit
            if (temp_height>=h) {
                possible = true;
                break;
            }
        }
        


        //Print output
        if (possible) {
            std::cout << "Case #" << i << ": yes" << std::endl;
        }
        else {
            std::cout << "Case #" << i << ": no" << std::endl;
        }
    }
    return 0;
}