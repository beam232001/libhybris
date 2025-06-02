#ifndef HYBRIS_BIONIC_COMPATIBILITY_H
#define HYBRIS_BIONIC_COMPATIBILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/cdefs.h>
#include <sys/sysmacros.h>
#include <sys/uio.h>
#include <sys/types.h>

// Compatibility macros (customize as needed for AOSP15)
#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(exp) \
    ({ \
        typeof (exp) _rc; \
        do { _rc = (exp); } while (_rc == -1 && errno == EINTR); \
        _rc; \
    })
#endif

#ifdef __cplusplus
