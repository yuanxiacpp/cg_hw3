using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <cmath>
#include "figio.h"

unsigned char* sphere_normal(int, int);
bool outsideSphere(int, int, int, int, int);
int main(int argc, char* argv[]) {
  if (argc != 3) {
	cerr << "Usage: " << argv[0] << " <n> <size>" << endl;
	return 1;
  }

  srand(time(NULL));

  int n = atoi(argv[1]);
  int size = atoi(argv[2]);
  

  if (n == 0) {
	cerr << "n cannot be zero." << endl;
	return 1;
  }
	

  stringstream ss;
  ss << "normals-" 
	 << size 
	 << "-"
	 << n
	 << ".tiff";

  string output = ss.str();


  unsigned char* result = sphere_normal(size, n);
  
 
 
  if (!save_tiff(output.c_str(), result, size, size)) {
	cerr << "Could not write output file: " << output << endl;
	return 1;
  }
 
  return 0;
}
bool outsideSphere(int center_col, int center_row, int radius, int col, int row) {
  int c = abs(col-center_col);
  int r = abs(row-center_row);

  if (c > radius || r > radius || sqrt(c*c+r*r) > radius)
	return true;
  return false;

}


unsigned char* sphere_normal(int size, int n) {
  unsigned char* result = new unsigned char[size*size*3];
  int radius = size / (2*n);
  for (int c = 0; c < n; c++) {
	int row = rand() % (size-2*radius) + radius;
	int col = c*(2*radius) + radius;
	//cout << c << "-th center pixel: (" << col << ", " << row << ")" << endl;
	
	for (int j = col-radius; j < col+radius; j++)
	  for (int i = 0; i < size; i++) {
		int index = 3*(j*size+i);

		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
		if (!outsideSphere(col, row, radius, j, i)) {
		  int x = j - col;
		  int y = i - row;
		  b = 0;
		  if (x < 0) 
			b += 128;
		  if (y > 0)
			b += 64;

		  r = (double)abs(x) / (double)radius * 255;
		  g = (double)abs(y) / (double)radius * 255;
		}
		result[index] = r;
		result[index+1] = g;
		result[index+2] = b;
	  }
	
  }


  return result;
}
