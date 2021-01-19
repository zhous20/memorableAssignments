#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"
RGB *readPPM(const char *file, int *width, int *height, int *max)
{
  FILE *fd;
  char c;
  int red, green, blue, i;

  fd = fopen(file, "r");
  fscanf(fd, "%c%c",&c,&c);
  fscanf(fd, "%d%d%d", width, height, max);

  int size = (*width)*(*height);
  RGB *image = (RGB*)malloc(size*sizeof(RGB));

  for(i=0; i < size; i++)
  {
    fscanf(fd, "%d%d%d", &red, &green, &blue);
    image[i].r = red;
    image[i].g = green;
    image[i].b = blue;
  }
  return image;
}
