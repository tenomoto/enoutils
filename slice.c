#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// slice records from direct access binary file in float
/*
 * @author Takeshi Enomoto
 *
 * Synopsis :: slice infile size rec_start (>=1)
 *
 * output is written in slice.tmp
 */
int main(int argc, char **argv)
{
  const char outfile[] = "slice.tmp";

  char infile[256];
  size_t s, r, n;
  FILE *f;
  float *x;

  if (argc < 4) {
    printf("%s infile size rec [nrec]\n", argv[0]);
    return 0;
  }
  strcpy(infile,argv[1]);
  s = atoi(argv[2]);
  r = atoi(argv[3]);
  if (argc>4) {
    n = atoi(argv[4]);
  } else {
    n = 1;
  }

#ifdef VERBOSE
  printf("infile = %s s = %zd r = %zd n = %zd\n", infile, s, r, n);
#endif

  x = (float *)malloc(sizeof(float)*s*n);

  f = fopen(infile, "rb");
  fseek(f, s*(r-1)*4, SEEK_SET);
  fread(x, sizeof(float), s*n, f);
  fclose(f);

  f = fopen(outfile, "wb");
  fwrite(x, sizeof(float), s*n, f);
  fclose(f);

  return 0;
}
