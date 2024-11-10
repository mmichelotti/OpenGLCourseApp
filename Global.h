#ifndef COMMONVALS
#define COMMONVALS

#include "stb_image.h"

const unsigned int MAX_POINT_LIGHTS = 3;
const unsigned int MAX_SPOT_LIGHTS = 3;
#define SAFE_DELETE(ptr) do { delete (ptr); (ptr) = nullptr; } while(0)

#endif 