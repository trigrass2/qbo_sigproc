/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"
#include <string>

/*int segment(float sigma, float k, int min_size, const char* inputStr, const char* outputStr){
	
  printf("loading input image.\n");
  image<rgb> *input = loadPPM(inputStr);
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  savePPM(seg, outputStr);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;
}*/

