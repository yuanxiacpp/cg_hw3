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


void grayscale(unsigned char* im_in, unsigned char* im_gray);
void hist(unsigned char* im_gray, int* im_hist);
void cdf(int *im_hist, double* im_cdf);
void equalized(unsigned char* im_gray, double* im_cdf, unsigned char* equalized_im);
void equalized(unsigned char* im_in, unsigned char* equalized_im, unsigned char* final_out);


int main(int argc, char* argv[]) {
  if (argc != 3) {
	cerr << "Usage: " << argv[0] << "<input_file> <output_file>" << endl;
	return 1;
  }


  unsigned char* im_in = new unsigned char[max_w*max_h*3];
  
  if (!load_tiff(argv[1], im_in, w, h)) {
	cout << "Could not read input file: " << argv[1] << endl;
	return 1;
  }

  unsigned char* im_gray = new unsigned char[w*h];
  grayscale(im_in, im_gray);

  int* im_hist = new int[256];
  hist(im_gray, im_hist);

  double* im_cdf = new double[256];
  cdf(im_hist, im_cdf);
  
  unsigned char* equalized_im = new unsigned char[w*h];
  equalized(im_gray, im_cdf, equalized_im);

  unsigned char* final_out = new unsigned char[w*h*3];
  equalized(im_in, equalized_im, final_out);

  if (!save_tiff(argv[2], final_out, w, h)) {
	cerr << "Could not write output file: " << argv[2] << endl;
	return 1;
  }
  return 0;

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
void hist(unsigned char* im_gray, int* im_hist) {
  for (int i = 0; i < 256; i++)
	im_hist[i] = 0;

  for (int j = 0; j < h; j++)
	for (int i = 0; i < w; i++) {
	  im_hist[im_gray[j*w+i]]++;
	}
  return;
}
void cdf(int* im_hist, double* im_cdf) {
  double total = 0.0;
  for (int i = 0; i < 256; i++)
	total += im_hist[i];
  for (int i = 0; i < 256; i++)
	im_cdf[i] = (double)(im_hist[i]) / total;
  return;
}
void equalized(unsigned char* im_gray, double* im_cdf, unsigned char* equalized_im) {
  double min_cdf = 0.0;
  for (int i = 0; i < 256; i++)
	if (im_cdf[i] < min_cdf)
	  min_cdf = im_cdf[i];


  for (int j = 0; j < h; j++)
	for (int i = 0; i < w; i++) {
	  equalized_im[j*w+i] = round((im_cdf[im_gray[j*w+i]]-min_cdf) / (1.0-min_cdf) * 255);
	}

  return;
}
void equalized(unsigned char* im_in, unsigned char* equalized_im, unsigned char* final_out) {
  unsigned char* im_gray = new unsigned char[w*h];
  for (int j = 0; j < h; j++) 
	for (int i = 0; i < w; i++) {
	  int index = 3*(j*w+i);
	  double gray_value = im_in[index]*0.3 + im_in[index+1]*0.5 + im_in[index+2]*0.2;
	  double ratio = gray_value / equalized_im[j*w+i];
	  final_out[index] = im_in[index] * ratio;
	  final_out[index+1] = im_in[index+1] * ratio;
	  final_out[index+2] = im_in[index+2] * ratio;
	}
  return;

}
