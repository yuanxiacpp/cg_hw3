//--------------------------------------------------------------------------------
// Images I/O - TIFF/JPEG/PPM
//--------------------------------------------------------------------------------

#ifndef FIGIO_H
#define FIGIO_H

/* 
	if rgb is NULL on entry, then memory is allocated by the function

	if rgb is non-NULL,
  image_width and image_height are assumed to be max values.
  on exit, they are the actual image sizes
*/



bool load_tiff(const char* filename, 
               unsigned char*& rgb, 
               int &image_width, 
               int &image_height);

bool save_tiff(const char* filename, 
               unsigned char* rgb, 
               int image_width, 
               int image_height);




#endif
