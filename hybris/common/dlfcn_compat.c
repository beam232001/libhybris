#include "dlfcn_compat.h"
#include <dlfcn.h>
#include "bionic_compatibility.h"

void* android_dlopen_ext(const char* filename, int flag, const void* extinfo)
{
    // Temporary stub
    return dlopen(filename, flag);
}
