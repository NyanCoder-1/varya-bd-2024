#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <stdint.h>

char* loadAsset(const char* path, uint32_t* size /* optional, out */);

#endif // _ASSETS_H_