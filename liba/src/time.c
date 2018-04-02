#include <time.h>

time_t time(time_t * t) {
  // Straight back to the good'ol days
  if (t) {
    *t = 0;
  }
  return 0;
}
