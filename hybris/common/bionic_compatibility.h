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

#if defined(__aarch64__)
#define __get_tls() ({ void** __val; __asm__("mrs %0, tpidr_el0" : "=r"(__val)); __val; })
#elif defined(__arm__)
#define __get_tls() ({ void** __val; __asm__("mrc p15, 0, %0, c13, c0, 3" : "=r"(__val)); __val; })
#elif defined(__x86_64__)
#define __get_tls() ({ void** __val; __asm__("mov %%fs:0, %0" : "=r"(__val)); __val; })
#elif defined(__i386__)
#define __get_tls() ({ void** __val; __asm__("movl %%gs:0, %0" : "=r"(__val)); __val; })
#endif

// Android 15 compatibility for struct stat
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

struct stat_hybris_compat {
    dev_t     st_dev;
    ino_t     st_ino;
    nlink_t   st_nlink;
    mode_t    st_mode;
    uid_t     st_uid;
    gid_t     st_gid;
    dev_t     st_rdev;
    off_t     st_size;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
};

static inline int stat_hybris(const char* path, struct stat_hybris_compat* out) {
    struct stat raw;
    if (stat(path, &raw) != 0) return -1;
    out->st_dev = raw.st_dev;
    out->st_ino = raw.st_ino;
    out->st_nlink = raw.st_nlink;
    out->st_mode = raw.st_mode;
    out->st_uid = raw.st_uid;
    out->st_gid = raw.st_gid;
    out->st_rdev = raw.st_rdev;
    out->st_size = raw.st_size;
    out->st_atim = raw.st_atim;
    out->st_mtim = raw.st_mtim;
    out->st_ctim = raw.st_ctim;
    return 0;
}
