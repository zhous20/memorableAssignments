#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"
void writePPM(const char *file, int width, int height, int max, const RGB *image)
{
  int i;
  FILE *fd;
  fd = fopen(file, "w");

  fprintf(fd, "P3\n");
  fprintf(fd, "%d %d\n%d\n", width, height, max);

  for(i=0; i<height*width; i++)
  {
    const RGB *p = image+i;
    fprintf(fd, "%d %d %d ", p->r, p->g, p->b);
  }
}
