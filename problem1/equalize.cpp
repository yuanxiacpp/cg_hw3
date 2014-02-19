#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

#include "figio.h"

using namespace std;
const unsigned int max_h = 10000;
const unsigned int max_w = 10000;
int w = 0;
int h = 0;


unsigned char* readInTiff(char* filename);
void grayscale(unsigned char* im_in, unsigned char* im_gray);
void hist(unsigned char* im_gray, int* hist);
void cdf(int *hist, double* cdf);
void equalized(unsigned char* im_gray, double* cdf, unsigned char* equalized_im);
void equalized(unsigned char* im_in, unsigned char* equalized_im, unsigned char* final_out);


int main(int argc, char* argv[]) {
  if (argc != 3) {
	cerr << "Usage: " << argv[0] << "<input_file> <output_file>" << endl;
	return 1;
  }

  unsigned char* im_in = readInTiff(argv[1]);
  unsigned char* im_gray = new unsigned char[w*h];
  grayscale(im_in, im_gray);

  int* hist = new int[256];
  hist(im_gray, hist);

  double* cdf = new double[256];
  cdf(hist, cdf);
  
  unsigned char* equalized_im = new unsigned char[w*h];
  equalized(im_gray, cdf, equalized_im);

  unsigned char* final_out = new unsigned char[w*h*3];
  equalized(im_in, equalized_im, final_out);

  if (!save_tiff(argv[2], final_out, w, h)) {
	cerr << "Could not write output file: " << argv[2] << endl;
	return 1;
  }
  return 0;

}

unsigned char* readInTiff(char* filename) {
  unsigned char* im_in = new unsigned char[max_w*max_h*3];

  if (!load_tiff(filename, im_in, w, h)) {
	cout << "Could not read input file" << filename << endl;
	return 1;
  }
  return image;
}

void grayscale(unsigned char* im_in, unsigned char* im_gray) {
  for (int j = 0; j < h; j++) {
	for (int i = 0; i < w; i++) {
	  int index = 3*(j*w+i);
	  im_gray[j*w+i] = im_in[index]*0.3 + im_in[index+1]*0.5 + im_in[index+2]*0.2;
	  
	}
  }
  return;
}
void hist(unsigned char* im_gray, int* hist) {
  for (int i = 0; i < 256; i++)
	hist[i] = 0;

  for (int j = 0; j < h; j++)
	for (int i = 0; i < w; i++) {
	  hist[im_gray[j*w+i]]++;
	}
  return;
}
void cdf(int* hist, double* cdf) {
  double total = 0.0;
  for (int i = 0; i < 256; i++)
	total += hist[i];
  for (int i = 0; i < 256; i++)
	cdf[i] = (double)(hist[i]) / total;
  return;
}
void equalized(unsigned char* im_gray, double* cdf, unsigned char* equalized_im) {
  double min_cdf = 0.0;
  for (int i = 0; i < 256; i++)
	if (cdf[i] < min_cdf)
	  min_cdf = cdf[i];


  for (int j = 0; j < h; j++)
	for (int i = 0; i < w; i++) {
	  equalized_im[j*w+i] = round((cdf[im_gray[j*w+i]]-min_cdf) / (1.0-min_cdf) * 255);
	}

  return;
}
void equalized(unsigned char* im_in, unsigned char* equalized_im, unsigned char* final_out) {
  unsigned char* im_gray = new unsigned char[w*h];
  for (int j = 0; j < h; j++) 
	for (int i = 0; i < w; i++) {
	  int index = 3*(j*w+i);
	  double gray_value = im_in[index]*0.3 + im_in[index+1]*0.5 + im_in[index+2]*0.2;
	  double ratio = gray_value / equalized_im[y*w+i];
	  final_out[index] = im_in[index] * ratio;
	  final_out[index+1] = im_in[index+1] * ratio;
	  final_out[index+2] = im_in[index+2] * ratio;
	}
  return;

}
