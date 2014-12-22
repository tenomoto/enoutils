#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/// print yyyymmddhh n times with  a specified increment
/*
 * @author Takeshi Enomoto
 *
 * Synopsis :: yyyymmddhh y0 m0 d0 h0 dy dm dd dh n
 *
 */
int main(int argc, char *argv[])
{
  struct tm s;
  int dh, dd, dm, dy, n;
  char yyyymmddhh[16];

  if (argc < 10) {
    printf("%s y0 m0 d0 h0 dy dm dd dh n\n", argv[0]);
    return 0;
  }
#ifdef VERBOSE
  printf("%s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
  printf("%s %s %s %s\n", argv[5], argv[6], argv[7], argv[8]);
#endif
  s.tm_year = atoi(argv[1])-1900;
  s.tm_mon = atoi(argv[2])-1;
  s.tm_mday = atoi(argv[3]);
  s.tm_hour = atoi(argv[4]);
  s.tm_min = 0;
  s.tm_sec = 0;
  s.tm_isdst = 0;
  dy = atoi(argv[5]);
  dm = atoi(argv[6]);
  dd = atoi(argv[7]);
  dh = atoi(argv[8]);
  n = atoi(argv[9]);
#ifdef VERBOSE
  printf("%d %d %d %d\n", s.tm_year, s.tm_mon, s.tm_mday, s.tm_hour);
#endif
  for (int i=0; i<n; i++) {
#ifdef VERBOSE
    printf("%d %d %d %d\n", s.tm_year, s.tm_mon, s.tm_mday, s.tm_hour);
#endif
    mktime(&s);
    strftime(yyyymmddhh, 11, "%Y%m%d%H", &s);
    printf("%s\n", yyyymmddhh);
    s.tm_hour = s.tm_hour + dh;
    s.tm_mday = s.tm_mday + dd;
    s.tm_mon  = s.tm_mon  + dm;
    s.tm_year = s.tm_year + dy;
  }
  return 0;
}
