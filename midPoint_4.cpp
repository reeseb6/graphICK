/*Reese: Case of vertical line with slope less than 1 start at 
leftmost endpoint (x0, y0) --> iterate over all y values to get
to (x1, y1) x = x0 for y = y0:y1 (stepping over all x values) fill
in/color pixel at location (x,y) if f(x+0.5,y-1) > 0: x = x+1*/

//g++ -o midpoint_4.exe midpoint_4.cpp -O2 -lgdi32



#include <iostream>
#include "CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;

// Midpoint function
float f(float x, float y, int x0, int y0, int x1, int y1) {
    return (y1 - y0) * x + (x0 - x1) * y + (x1 * y0 - x0 * y1);
}

int main() {
    CImg<unsigned char> image(500, 500, 1, 3, 5);
    vector<int> coords_x;
    vector<int> coords_y;

    CImgDisplay disp1(image, "Click control points");
    unsigned char color[] = {128, 120, 250};

    while (!disp1.is_closed()) {
        disp1.wait();
        if (disp1.button()) {
            int x = disp1.mouse_x();
            int y = disp1.mouse_y();
            coords_x.push_back(x);
            coords_y.push_back(y);
            image.draw_circle(x, y, 5, color);
            disp1.display(image);
        }
    }

    if (coords_x.size() < 2) return 1;

    int x0 = coords_x[0];
    int y0 = coords_y[0];
    int x1 = coords_x[1];
    int y1 = coords_y[1];

    // Ensure y0 is less than y1 (iterate upward)
    if (y0 > y1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int x = x0;

    for (int y = y0; y <= y1; y++) {
        image.draw_point(x, y, color);
        float midpoint = f(x + 0.5, y - 1, x0, y0, x1, y1);
        if (midpoint > 0) {
            x++;
        }
    }

    CImgDisplay disp(image);
    while (!disp.is_closed()) disp.wait();

    return 0;
}