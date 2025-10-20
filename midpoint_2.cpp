#include <iostream>
#include "CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;

int main() 
{
	CImg<unsigned char> orig(500, 500, 1, 3, 5);
	
	vector<int> coords_x;
	vector<double> coords_y;
	
	
	CImgDisplay disp1(orig, "Click control points");
	unsigned char color[] = { 255,128,64 };
	while (!disp1.is_closed()){
			disp1.wait();
			
			if (disp1.button()){
			
				int x = disp1.mouse_x();
				double y = disp1.mouse_y();
				//vector package
				coords_x.push_back(x);
				coords_y.push_back(y);
				
				cout << x << ", " << y << endl;
				orig.draw_circle(x, y, 5, color); 
				
				disp1.display(orig);
			}
	}
	
	//check to start at leftmost point
	if (coords_x[0] > coords_x[1]){
		int swap_x = coords_x[0];
		coords_x[0] = coords_x[1];
		coords_x[1] = swap_x;
		
		double swap_y = coords_y[0];
		coords_y[0] = coords_y[1];
		coords_y[1] = swap_y;
	}
	
	int domain = coords_x[1] - coords_x[0]; //used for slope and algorithm
	int range = coords_y[1] - coords_y[0]; //used for slope and algorithm
	double slope = range / domain; //slope, should be between (-1, 0)
	
	double pos_y = coords_y[0]; //tracks current Y position
	int pos_x = coords_x[0]; //tracks current x position
	
	
	for (int i=0; i < domain-1;i++){
		
		pos_x += 1; //iterate through X values
		orig(pos_x, pos_y, 0, 0) = 255; //red 
		orig(pos_x, pos_y, 0, 1) = 128; //green
		orig(pos_x, pos_y, 0, 2) = 64; //blue

		//algorithm f(x+1,y+0.5)
		double f_xy = ((pos_x + 1) * (range)) - ((pos_y + 0.5) * (domain)) + (coords_y[0] * coords_x[1]) - (coords_y[1] * coords_x[0]);
		if (f_xy > 0){ //if f(x+1,y+0.5) > 0, iterate y
			pos_y = pos_y + 1;
		}
	}
	
	//dusplay
	CImgDisplay disp2(orig, "draw lines");	
	while (!disp2.is_closed()){
		disp2.wait();
	}

}