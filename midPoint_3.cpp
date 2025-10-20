
#include <iostream>
#include "CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;


int main() {
	CImg<unsigned char> image(500, 500, 1, 3, 5);
	
	vector<int> coords_x;
	vector<int> coords_y;
	
	
	CImgDisplay disp1(image, "Click control points");
	unsigned char color[] = { 128,120,250 };
	while (!disp1.is_closed()){
			disp1.wait();
			
			if (disp1.button()){
			
				int x = disp1.mouse_x();
				double y = disp1.mouse_y();
				//vector package
				coords_x.push_back(x);
				coords_y.push_back(y);
				
				cout << x << ", " << y << endl;
				image.draw_circle(x, y, 5, color); 
				
				disp1.display(image);
			}
	}
	//get coords from selected points -I had to use the idexes of 1 and 2 because the first point gets taken twice for some reason :)
	int x0 = coords_x[1]; //coords_x[0]
	int y0 = coords_y[1]; //coords_x[0]
	int x1 = coords_x[2]; //coords_x[1]
	int y1 = coords_y[2]; //coords_x[1]
	
	
	//the larger y value will be the further left point (CImg the y's increase as you go down the image)
	if (y0 < y1) {
        int swap_x = x0;
		x0 = x1;
		x1 = swap_x;
		
		int swap_y = y0;
		y0 = y1;
		y1 = swap_y;
    }
	
	
	//slope and other equations used in MidPt formula
	int run = x1 - x0;
	int rise = y0 - y1;
	double slope = rise / run;
	
	//set to first x vlalue
    int x = x0;
	
	
	//loop through the y values
	for(int y = y0; y >= y1; y--){
		
		//algorithm f(x+.5,y+1)
		double MidPt = (rise) * (x + .5) + (run) * y + (x0 * y1 - x1 * y0);
		if(MidPt < 0){
			x = x + 1;
		}
		
		image.draw_point(x, y, color);
	}
	
	CImgDisplay disp(image); 
    while (!disp.is_closed())
        disp.wait(); 
	
	return 0;
}
		