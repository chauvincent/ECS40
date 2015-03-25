#include <time.h>
// used as the seed for the random number generator.
static int currentTime = 424242;
time_t __wrap_time(time_t* timer) {
 return currentTime++;
}
