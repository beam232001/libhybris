#include "dlfcn_compat.h"
#include <dlfcn.h>
#include <android/dlext.h>
#include <string.h>
#include <stdio.h>

void* android_dlopen_ext(const char* filename, int flag, const android_dlextinfo* extinfo)
{
    // extinfo is optional; we ignore its fields for now
    if (extinfo != NULL) {
        fprintf(stderr, "android_dlopen_ext: ignoring extinfo fields (not implemented)\n");
    }
    return dlopen(filename, flag);
}

