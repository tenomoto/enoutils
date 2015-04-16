#include <stdlib.h>
#include <stdio.h>
#ifdef SWAPENDIAN
#include "endian.h"
#endif

/// eav calculates ensemble average and variance
/** eav reads random access binary files,
 *  calculates the ensemble mean and variance and
 *  save to specified files.
 */
int main(int argc, char *argv[])
{
  if (argc < 8) {
    printf("%s missing n nrec inputs mean variance\n", argv[0]);
    return 0;
  }

  FILE *f;
  float *xf;
  double *xavg;
  double *xvar;
  int *count;

  float missing = atof(argv[1]);
  int n = atoi(argv[2]);
  int nrec = atoi(argv[3]);
#ifdef VERBOSE
  printf("missing %f\n", missing);
  printf("file size %d\n", n);
#endif

  xf  = (float *)malloc(sizeof(float)*n);
  xavg  = (double *)malloc(sizeof(double)*n);
  xvar  = (double *)malloc(sizeof(double)*n);
  count = (int *)malloc(sizeof(int)*n);

  for (int r=0; r < nrec; r++) {
#ifdef VERBOSE
    printf("rec %d/%d\n", r, nrec);
#endif
    for (int i = 0; i < n; i++) {
      xavg[i] = 0.0;
      count[i] = 0;
    }
    
    for (int j = 4; j < argc - 2; j++) {
#ifdef VERBOSE
      printf("read from %s\n", argv[j]);
#endif
      f = fopen(argv[j], "rb");
      fseek(f, r*n, SEEK_SET);
      fread(xf, sizeof(float), n, f);
#ifdef SWAPENDIAN
#ifdef VERBOSE
      printf("calling eno_endian_swap_float\n");
#endif
      for (int i = 0; i < n; i++) {
        xf[i] = eno_endian_swap_float(xf[i]);
      }
#endif
      fclose(f);
      for (int i = 0; i < n; i++) {
        if (xf[i] != missing) {
          xavg[i] = xavg[i] + xf[i];
          count[i] = count[i] + 1;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (count[i] > 1) {
        xavg[i] = xavg[i]/count[i];
        xf[i] = xavg[i];
      } else {
        xavg[i] = missing;
        xf[i] = missing;
      }
    }
#ifdef VERBOSE
    printf("save ensemble mean to  %s\n", argv[argc-2]);
#endif
    f = fopen(argv[argc-2], (r!=0)? "ab": "wb");
#ifdef SWAPENDIAN
#ifdef VERBOSE
    printf("calling eno_endian_swap_float\n");
#endif
    for (int i = 0; i < n; i++) {
      xf[i] = eno_endian_swap_float(xf[i]);
    }
#endif
    fwrite(xf, sizeof(float), n, f);
    fclose(f);

    for (int i=0; i < n; i++) {
      xvar[i] = 0.0;
    }
    
    for (int j = 4; j < argc - 2; j++) {
#ifdef VERBOSE
      printf("read from %s\n", argv[j]);
#endif
      f = fopen(argv[j], "rb");
      fseek(f, r*n, SEEK_SET);
      fread(xf, sizeof(float), n, f);
#ifdef SWAPENDIAN
#ifdef VERBOSE
      printf("calling eno_endian_swap_float\n");
#endif
      for (int i = 0; i < n; i++) {
        xf[i] = eno_endian_swap_float(xf[i]);
      }
#endif
      fclose(f);
      for (int i = 0; i < n; i++) {
        if (xf[i] != missing) {
          xvar[i] = xvar[i] + ((double)xf[i]*(double)xf[i]-xavg[i]*xavg[i]);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (count[i] > 1) {
        xf[i] = xvar[i]/(count[i]-1);
      } else {
        xf[i] = missing;
      }
    }
#ifdef VERBOSE
    printf("save variance to  %s\n", argv[argc-1]);
#endif
    f = fopen(argv[argc-1], (r!=0)? "ab": "wb");
#ifdef SWAPENDIAN
#ifdef VERBOSE
    printf("calling eno_endian_swap_float\n");
#endif
    for (int i = 0; i < n; i++) {
      xf[i] = eno_endian_swap_float(xf[i]);
    }
#endif
    fwrite(xf, sizeof(float), n, f);
    fclose(f);
  }

  return 0;
}
