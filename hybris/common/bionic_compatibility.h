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

