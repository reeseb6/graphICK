#include <iostream>
#include "CImg.h"
#include <cmath>
#include <vector>

using namespace std;
using namespace cimg_library;

// case 1. slope: 0 <= m <= 1

// made a function to return the midpoint formula
float f(float x, float y, int x_0, int y_0, int x_1, int y_1){
	
	// f(x,y) = (y1-y0)*x + (x0-x1)*y + x1*y0 - x0*y1
	return (y_1-y_0) * x + (x_0-x_1) * y + (x_1*y_0 - x_0*y_1);
}

int main(){
	
	CImg<unsigned char> image(500, 500, 1, 3, 0); 

	// using vectors to save the x and y coords
	vector<int> coords_x;
	vector<int> coords_y;

	CImgDisplay window(image, "Click 2 control points");
	
	// color for the dots
	unsigned char color[] = { 255,128,64 };
	
	while (!window.is_closed()){
		window.wait();
		if (window.button()){
			
			int x = window.mouse_x();
			int y = window.mouse_y();
			
			// adding the x and y coords to the vectors
			coords_x.push_back(x);
			coords_y.push_back(y);	
			
			// draw circle's inputs: (coordinate, size of circle, color of circle)
			image.draw_circle(x, y, 5, color);

			window.display(image);
		}
	}
	// get the height of the image 
	int img_height = image.height();
	
	// get x 0 and x 1
	int x_0 = coords_x[0];
	int x_1 = coords_x[1];
	// get y 0 and y 1. subtracting the y from the height since cimg y starts at top 
	int y_0 = (img_height-1) - coords_y[0];
	int y_1 = (img_height-1) - coords_y[1];
	
	// first y val 
	int y = y_0;

	for (int x=x_0; x <= x_1; x++){	// go through all x vals
		// when drawing the points, invert the y back to accurately draw line 
		int y_draw = (img_height - 1) - y;
		image.draw_point(x, y_draw, color);
		
		float midpoint = f(x+1, y+0.5, x_0, y_0, x_1, y_1);
		
		// call the midpoint function, f, passing x+1 and y+0.5
		if ( midpoint > 0){
			y++;
		}
		
	}
	
	// display an image
	CImgDisplay disp(image);
	
	while (!disp.is_closed())
		disp.wait();
	
	return 0;
	
}