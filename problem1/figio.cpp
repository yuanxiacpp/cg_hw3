//--------------------------------------------------------------------------------
// Images I/O - TIFF/PPM
//--------------------------------------------------------------------------------


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    This file contains code for input/output of images. You are not required to 
                      understand this file for the class. 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <setjmp.h>



#include "tiffio.h"

#include "figio.h"

typedef unsigned char uchar;


//--------------------------------------------------------------------------------
// TIFF
//--------------------------------------------------------------------------------

bool load_tiff(const char *filename, uchar*& rgb, 
	       int &image_width, int &image_height) {
  
  TIFFSetErrorHandler(NULL);
  TIFFSetWarningHandler(NULL);
  bool success = false;
  TIFF* tif = TIFFOpen(filename, "ru");
  if (tif) {
    uint32 w, h;
    size_t npixels;
    uint32* raster;
  
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);  
    npixels = w * h;

		if((rgb == NULL && (rgb = new unsigned char[w*h*3]) != NULL) ||
			(int(w) <= image_width && int(h) <= image_height)) {
      image_width = w;	
      image_height = h;
  
      // alloc raster
      raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
      if (raster != NULL) {
				
				// read image into raster
				if(TIFFReadRGBAImage(tif, w, h, raster, 0)) {
					
					// copy into image
					uchar *rp = (uchar *) raster;
					uchar *ep = rp+npixels*4;
					uchar *ip = rgb;
					while(rp < ep) {
						*ip++ = *rp++;
						*ip++ = *rp++;
						*ip++ = *rp++;
						rp++;
					}
					
					success = true;
				}
        _TIFFfree(raster);
      }
    }
    TIFFClose(tif);
  }

  return success;
}


bool save_tiff(const char *filename, 
               unsigned char *rgb, 
               int image_width, 
               int image_height) {

  TIFF *file;
  unsigned char *p;
  int i;

  file = TIFFOpen(filename, "w");
  if (file == NULL) {
    return false;
  }

  TIFFSetField(file, TIFFTAG_IMAGEWIDTH, (uint32) image_width);
  TIFFSetField(file, TIFFTAG_IMAGELENGTH, (uint32) image_height);
  TIFFSetField(file, TIFFTAG_BITSPERSAMPLE, 8);
  TIFFSetField(file, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
  TIFFSetField(file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  TIFFSetField(file, TIFFTAG_SAMPLESPERPIXEL, 3);
  TIFFSetField(file, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(file, TIFFTAG_ROWSPERSTRIP, 1);
  //TIFFSetField(file, TIFFTAG_IMAGEDESCRIPTION, description);
  p = rgb;
  for (i = image_height - 1; i >= 0; i--) {
    if (TIFFWriteScanline(file, p, i, 0) < 0) {
      TIFFClose(file);
      return false;
    }
    p += image_width * sizeof(unsigned char) * 3;
  }
  TIFFClose(file);
  return true;
}

