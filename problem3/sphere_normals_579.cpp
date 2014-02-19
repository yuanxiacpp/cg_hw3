using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "figio.h"

unsigned char* sphere_normal(int, int);

int main(int argc, char* argv[]) {
  if (argc != 3) {
	cerr << "Usage: " << argv[0] << " <n> <size>" << endl;
	return 1;
  }

  

  int n = atoi(argv[1]);
  int size = atoi(argv[2]);
  
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

unsigned char* sphere_normal(int size, int n) {
  unsigned char* result = new unsigned char[size*size*3];
  



  return result;
}
