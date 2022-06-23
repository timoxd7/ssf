// clang-format off

/* --------------------------------------------------------------------------------------------- */
/* Small System Framework                                                                        */
/*                                                                                               */
/* ssfport.h                                                                                     */
/* Provides port interface.                                                                      */
/*                                                                                               */
/* BSD-3-Clause License                                                                          */
/* Copyright 2020 Supurloop Software LLC                                                         */
/*                                                                                               */
/* Redistribution and use in source and binary forms, with or without modification, are          */
/* permitted provided that the following conditions are met:                                     */
/*                                                                                               */
/* 1. Redistributions of source code must retain the above copyright notice, this list of        */
/* conditions and the following disclaimer.                                                      */
/* 2. Redistributions in binary form must reproduce the above copyright notice, this list of     */
/* conditions and the following disclaimer in the documentation and/or other materials provided  */
/* with the distribution.                                                                        */
/* 3. Neither the name of the copyright holder nor the names of its contributors may be used to  */
/* endorse or promote products derived from this software without specific prior written         */
/* permission.                                                                                   */
/*                                                                                               */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS   */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF               */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE    */
/* COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL      */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE */
/* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED    */
/* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING     */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED  */
/* OF THE POSSIBILITY OF SUCH DAMAGE.                                                            */
/* --------------------------------------------------------------------------------------------- */
#ifndef SSF_PORT_H_INCLUDE
#define SSF_PORT_H_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include "Windows.h"
#else /* _WIN32 */
#include <time.h>
#endif /* _WIN32 */
#include "ssfassert.h"

/* --------------------------------------------------------------------------------------------- */
/* Platform specific tick configuration                                                          */
/* --------------------------------------------------------------------------------------------- */

/* Define SSFPortTick_t as unsigned 64-bit integer */
typedef uint64_t SSFPortTick_t;

/* Define the number of system ticks per second */
#define SSF_TICKS_PER_SEC (1000u)

/* --------------------------------------------------------------------------------------------- */
/* Platform specific byte swapping macros                                                        */
/* --------------------------------------------------------------------------------------------- */
/* If your platform has byte order macros include the header file here and set */
/* SSF_CONFIG_BYTE_ORDER_MACROS to 0. Else set SSF_CONFIG_BYTE_ORDER_MACROS to 1 and set */
/* SSF_CONFIG_LITTLE_ENDIAN to 1 for little endian systems, else 0. */
#ifdef __APPLE__
#include <arpa/inet.h>
#define SSF_CONFIG_BYTE_ORDER_MACROS (0u)
#define SSF_CONFIG_LITTLE_ENDIAN (1u)
#else
#define SSF_CONFIG_BYTE_ORDER_MACROS (1u)
#define SSF_CONFIG_LITTLE_ENDIAN (1u)
#endif

#if SSF_CONFIG_BYTE_ORDER_MACROS == 1
#if SSF_CONFIG_LITTLE_ENDIAN == 0
    #define htonl(x) (x)
    #define ntohl(x) htonl(x)

    #define htonll(x) (x)
    #define ntohll(x) htonll(x)
#else /* SSF_CONFIG_LITTLE_ENDIAN */
    #define htonl(x) ((((x) & 0xff000000u) >> 24) | \
                      (((x) & 0x00ff0000u) >> 8) | \
                      (((x) & 0x0000ff00u) << 8) | \
                      (((x) & 0x000000ffu) << 24))
    #define ntohl(x) htonl(x)

    #define htonll(x) ((((x) & 0xff00000000000000u) >> 56) | \
                       (((x) & 0x00ff000000000000u) >> 40) | \
                       (((x) & 0x0000ff0000000000u) >> 24) | \
                       (((x) & 0x000000ff00000000u) >> 8) | \
                       (((x) & 0x00000000ff000000u) << 8) | \
                       (((x) & 0x0000000000ff0000u) << 24) | \
                       (((x) & 0x000000000000ff00u) << 40) | \
                       (((x) & 0x00000000000000ffu) << 56))
    #define ntohll(x) htonll(x)
#endif /* SSF_CONFIG_LITTLE_ENDIAN */
#endif /* SSF_CONFIG_BYTE_ORDER_MACROS */

/* --------------------------------------------------------------------------------------------- */
/* Enable/disable unit tests                                                                     */
/* --------------------------------------------------------------------------------------------- */
#define SSF_CONFIG_BFIFO_UNIT_TEST (1u)
#define SSF_CONFIG_LL_UNIT_TEST (1u)
#define SSF_CONFIG_MPOOL_UNIT_TEST (1u)
#define SSF_CONFIG_JSON_UNIT_TEST (1u)
#define SSF_CONFIG_BASE64_UNIT_TEST (1u)
#define SSF_CONFIG_HEX_UNIT_TEST (1u)
#define SSF_CONFIG_FCSUM_UNIT_TEST (1u)
#define SSF_CONFIG_SM_UNIT_TEST (1u)
#define SSF_CONFIG_RS_UNIT_TEST (1u)
#define SSF_CONFIG_CRC16_UNIT_TEST (1u)
#define SSF_CONFIG_CRC32_UNIT_TEST (1u)
#define SSF_CONFIG_SHA2_UNIT_TEST (1u)
#define SSF_CONFIG_TLV_UNIT_TEST (1u)
#define SSF_CONFIG_AES_UNIT_TEST (1u)
#define SSF_CONFIG_AESGCM_UNIT_TEST (1u)
#define SSF_CONFIG_CFG_UNIT_TEST (1u)
#define SSF_CONFIG_PRNG_UNIT_TEST (1u)

/* If any unit test is enabled then enable unit test mode */
#if SSF_CONFIG_BFIFO_UNIT_TEST == 1 || \
    SSF_CONFIG_LL_UNIT_TEST == 1 || \
    SSF_CONFIG_MPOOL_UNIT_TEST == 1 || \
    SSF_CONFIG_JSON_UNIT_TEST == 1 || \
    SSF_CONFIG_BASE64_UNIT_TEST == 1 || \
    SSF_CONFIG_HEX_UNIT_TEST == 1 || \
    SSF_CONFIG_FCSUM_UNIT_TEST == 1 || \
    SSF_CONFIG_SM_UNIT_TEST == 1 || \
    SSF_CONFIG_RS_UNIT_TEST == 1 || \
    SSF_CONFIG_CRC16_UNIT_TEST == 1 || \
    SSF_CONFIG_CRC32_UNIT_TEST == 1 || \
    SSF_CONFIG_SHA2_UNIT_TEST == 1 || \
    SSF_CONFIG_TLV_UNIT_TEST == 1 || \
    SSF_CONFIG_AES_UNIT_TEST == 1 || \
    SSF_CONFIG_AESGCM_UNIT_TEST == 1 || \
    SSF_CONFIG_CFG_UNIT_TEST == 1 || \
    SSF_CONFIG_PRNG_UNIT_TEST == 1
#define SSF_CONFIG_UNIT_TEST (1u)
#else
#define SSF_CONFIG_UNIT_TEST (0u)
#endif

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfbfifo's byte fifo interface                                                      */
/* --------------------------------------------------------------------------------------------- */

/* Define the maximum fifo size. */
#define SSF_BFIFO_CONFIG_MAX_BFIFO_SIZE (255UL)

#define SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_ANY         (0u)
#define SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_255         (1u)
#define SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_POW2_MINUS1 (2u)

/* Define the allowed runtime fifo size. */
/* SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_ANY allows any fifo size up to
   SSF_BFIFO_CONFIG_MAX_BFIFO_SIZE. */
/* SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_255 allows only fifo sizes of 255. */
/* SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_POW2_MINUS1 allows fifo sizes that are power of 2 minus 1
   up to SSF_BFIFO_CONFIG_MAX_BFIFO_SIZE. */
#define SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE (SSF_BFIFO_CONFIG_RUNTIME_BFIFO_SIZE_255)

/* Enable or disable the multi-byte fifo interface. */
#define SSF_BFIFO_MULTI_BYTE_ENABLE                     (1u)

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfmpool's memory pool interface                                                    */
/* --------------------------------------------------------------------------------------------- */
#define SSF_MPOOL_DEBUG (0u)

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfjson's parser limits                                                             */
/* --------------------------------------------------------------------------------------------- */
/* Define the maximum parse depth, each opening { or [ starts a new depth level. */
#define SSF_JSON_CONFIG_MAX_IN_DEPTH (4u)

/* Define the maximum JSON string length to be parsed. */
#define SSF_JSON_CONFIG_MAX_IN_LEN  (2047u)

/* Allow parser to use floating point to convert numbers. */
#define SSF_JSON_CONFIG_ENABLE_FLOAT_PARSE (0u)

/* Allow generator to print floats. */
#define SSF_JSON_CONFIG_ENABLE_FLOAT_GEN (1u)

/* Enable interface that can update specific fields in a JSON string. */
#define SSF_JSON_CONFIG_ENABLE_UPDATE (1u)

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfsm's state machine interface                                                     */
/* --------------------------------------------------------------------------------------------- */
/* 0, API calls must be made in same context; 1, events may be signalled from other contexts. */
#define SSF_SM_CONFIG_ENABLE_THREAD_SUPPORT (0u)

/* To synchronize event signals from other contexts the following macros must be implemented. */
#if SSF_SM_CONFIG_ENABLE_THREAD_SUPPORT == 1
#ifdef _WIN32
#define SSF_SM_THREAD_SYNC_DECLARATION static HANDLE _ssfsmSyncMutex
#define SSF_SM_THREAD_SYNC_INIT() { \
    _ssfsmSyncMutex = CreateMutex(NULL, FALSE, NULL); \
    SSF_ASSERT(_ssfsmSyncMutex != NULL); \
}
#define SSF_SM_THREAD_SYNC_ACQUIRE() { \
    SSF_ASSERT(WaitForSingleObject(_ssfsmSyncMutex, INFINITE) == WAIT_OBJECT_0); \
}
#define SSF_SM_THREAD_SYNC_RELEASE() { SSF_ASSERT(ReleaseMutex(_ssfsmSyncMutex)); }

#define SSF_SM_THREAD_WAKE_DECLARATION HANDLE gssfsmWakeSem
#define SSF_SM_THREAD_WAKE_INIT() { \
    gssfsmWakeSem = CreateSemaphore(NULL, 0, 1, NULL); \
    SSF_ASSERT(gssfsmWakeSem != NULL); \
}
#define SSF_SM_THREAD_WAKE_POST() { ReleaseSemaphore(gssfsmWakeSem, 1, NULL); }
#define SSF_SM_THREAD_WAKE_WAIT(timeout) { \
    DWORD waitResult; \
    waitResult = WaitForSingleObject(gssfsmWakeSem, timeout); \
    SSF_ASSERT((waitResult == WAIT_OBJECT_0) || (waitResult == WAIT_TIMEOUT)); \
}
extern HANDLE gssfsmWakeSem;
#else /* WIN32 */
/* 0, no CLOCK_MONOTONIC support for pthread_cond_timedwait(), potential timeouts bugs */
/* 1, CLOCK_MONOTONIC support for pthread_cond_timedwait(), recommended */
#define SSF_SM_THREAD_PTHREAD_CLOCK_MONOTONIC (1u)
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>

#define SSF_SM_THREAD_SYNC_DECLARATION pthread_mutex_t _ssfsmSyncMutex
#define SSF_SM_THREAD_SYNC_INIT() { \
    pthread_mutexattr_t attr; \
    SSF_ASSERT(pthread_mutexattr_init(&attr) == 0); \
    SSF_ASSERT(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) == 0); \
    SSF_ASSERT(pthread_mutex_init(&_ssfsmSyncMutex, &attr) == 0); \
}
#define SSF_SM_THREAD_SYNC_ACQUIRE() { SSF_ASSERT(pthread_mutex_lock(&_ssfsmSyncMutex) == 0); }
#define SSF_SM_THREAD_SYNC_RELEASE() { SSF_ASSERT(pthread_mutex_unlock(&_ssfsmSyncMutex) == 0); }

#define SSF_SM_THREAD_WAKE_DECLARATION \
    bool gssfsmIsWakeSignalled; pthread_cond_t gssfsmWakeCond; pthread_mutex_t gssfsmWakeMutex
extern bool gssfsmIsWakeSignalled;
extern pthread_cond_t gssfsmWakeCond;
extern pthread_mutex_t gssfsmWakeMutex;

#if SSF_SM_THREAD_PTHREAD_CLOCK_MONOTONIC == 1
#define SSF_SM_THREAD_PTHREAD_CLOCK CLOCK_MONOTONIC
#define SSF_SM_THREAD_WAKE_INIT() { \
    pthread_condattr_t attr; \
    SSF_ASSERT(pthread_condattr_init(&attr) == 0); \
    SSF_ASSERT(pthread_condattr_setclock(&attr, CLOCK_MONOTONIC) == 0); \
    SSF_ASSERT(pthread_cond_init(&gssfsmWakeCond, &attr) == 0); \
    SSF_ASSERT(pthread_mutex_init(&gssfsmWakeMutex, NULL) == 0); \
}
#else
#define SSF_SM_THREAD_PTHREAD_CLOCK CLOCK_REALTIME
#define SSF_SM_THREAD_WAKE_INIT() { \
    SSF_ASSERT(pthread_cond_init(&gssfsmWakeCond, NULL) == 0); \
    SSF_ASSERT(pthread_mutex_init(&gssfsmWakeMutex, NULL) == 0); \
}
#endif
#define SSF_SM_THREAD_WAKE_POST() { \
    SSF_ASSERT(pthread_mutex_lock(&gssfsmWakeMutex) == 0); \
    gssfsmIsWakeSignalled = true; \
    SSF_ASSERT(pthread_cond_signal(&gssfsmWakeCond) == 0); \
    SSF_ASSERT(pthread_mutex_unlock(&gssfsmWakeMutex) == 0); \
}

/* On a cond_timedwait() timeout OS X has errno set to ETIMEDOUT + 256! */
/* On a cond_timedwait() timeout a recent version of Debian Linux has errno set to 0! */
/* Based on documentation a cond_timedwait() timeout should set errno to ETIMEDOUT. */
#define SSF_SM_THREAD_WAKE_WAIT(timeout) { \
    SSF_ASSERT(pthread_mutex_lock(&gssfsmWakeMutex) == 0); \
    if (gssfsmIsWakeSignalled == false) { \
        struct timespec ts; \
        SSF_ASSERT(clock_gettime(SSF_SM_THREAD_PTHREAD_CLOCK, &ts) == 0); \
        ts.tv_nsec += (((timeout * 1000ul) / SSF_TICKS_PER_SEC) * 1000000ul); \
        while (ts.tv_nsec >= 1000000000l) { \
            ts.tv_nsec -= 1000000000l; \
            ts.tv_sec++; } \
        if (pthread_cond_timedwait(&gssfsmWakeCond, &gssfsmWakeMutex, &ts) != 0) { \
            SSF_ASSERT(((errno & 0xff) == ETIMEDOUT) || (errno == 0)); } } \
    gssfsmIsWakeSignalled = false; \
    SSF_ASSERT(pthread_mutex_unlock(&gssfsmWakeMutex) == 0); \
}
#endif /* WIN32 */
#endif /* SSF_SM_CONFIG_ENABLE_THREAD_SUPPORT */

/* Maximum number of simultaneously queued events for all state machines. */
#define SSF_SM_MAX_ACTIVE_EVENTS (3u)

/* Maximum number of simultaneously running timers for all state machines. */
#define SSF_SM_MAX_ACTIVE_TIMERS (3u)

/* Defines the state machine identifers. */
enum SSFSMList
{
    SSF_SM_UNIT_TEST_1,
    SSF_SM_UNIT_TEST_2,
    SSF_SM_END
};

/* Defines the event identifiers for all state machines. */
enum SSFSMEventList
{
    SSF_SM_EVENT_ENTRY,
    SSF_SM_EVENT_EXIT,
#if SSF_CONFIG_SM_UNIT_TEST == 1
    SSF_SM_EVENT_UT1_1,
    SSF_SM_EVENT_UT1_2,
    SSF_SM_EVENT_UT2_1,
    SSF_SM_EVENT_UT2_2,
    SSF_SM_EVENT_UTX_1,
    SSF_SM_EVENT_UTX_2,
#endif /* SSF_CONFIG_SM_UNIT_TEST */
    SSF_SM_EVENT_END
};

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfrs's Reed-Solomon interface                                                      */
/* --------------------------------------------------------------------------------------------- */
/* 1 to enable Reed-Solomon encoding interface, else 0. */
#define SSF_RS_ENABLE_ENCODING (1u)

/* 1 to enable Reed-Solomon decoding interface, else 0. */
#define SSF_RS_ENABLE_DECODING (1u)

/* Determine if we can run unit test */
#if SSF_CONFIG_RS_UNIT_TEST == 1
#if SSF_RS_ENABLE_ENCODING != 1 || SSF_RS_ENABLE_DECODING != 1
#undef SSF_CONFIG_RS_UNIT_TEST
#define SSF_CONFIG_RS_UNIT_TEST (0u)
#endif
#endif

/* The maximum total size in bytes of a message to be encoded or decoded */
#define SSF_RS_MAX_MESSAGE_SIZE (5)
#if SSF_RS_MAX_MESSAGE_SIZE > 2048
#error SSFRS invalid SSF_RS_MAX_MESSAGE_SIZE.
#endif

/* The maximum number of bytes that will be encoded with up to SSF_RS_MAX_SYMBOLS bytes */
#define SSF_RS_MAX_CHUNK_SIZE (5)
#if SSF_RS_MAX_CHUNK_SIZE > 253
#error SSFRS invalid SSF_RS_MAX_CHUNK_SIZE.
#endif

/* The maximum number of chunks that a message will be broken up into for encoding and decoding */
#if SSF_RS_MAX_MESSAGE_SIZE % SSF_RS_MAX_CHUNK_SIZE == 0
#define SSF_RS_MAX_CHUNKS (SSF_RS_MAX_MESSAGE_SIZE / SSF_RS_MAX_CHUNK_SIZE)
#else
#define SSF_RS_MAX_CHUNKS ((SSF_RS_MAX_MESSAGE_SIZE / SSF_RS_MAX_CHUNK_SIZE) + 1)
#endif

/* The maximum number of symbols in bytes that will encode up to SSF_RS_MAX_CHUNK_SIZE bytes */
/* Reed-Solomon can correct SSF_RS_MAX_SYMBOLS/2 bytes with errors in a message */
#define SSF_RS_MAX_SYMBOLS (3ul)
#if (SSF_RS_MAX_SYMBOLS < 2) || (SSF_RS_MAX_SYMBOLS > 254)
#error SSFRS Invalid SSF_RS_MAX_SYMBOLS.
#endif

/* For now we are limiting the total of chunk bytes and symbols to 254 max */
#if SSF_RS_MAX_CHUNK_SIZE + SSF_RS_MAX_SYMBOLS > 254
#error SSFRS total of SSF_RS_MAX_CHUNK_SIZE + SSF_RS_MAX_SYMBOLS not supported.
#endif

/* For now we are limiting the total encoded msg + ecc to 61440 (60KiB) */
#if (SSF_RS_MAX_SYMBOLS * SSF_RS_MAX_CHUNKS) + SSF_RS_MAX_MESSAGE_SIZE > 61440ul
#error SSFRS total of SSF_RS_MAX_CHUNK_SIZE + SSF_RS_MAX_SYMBOLS not supported.
#endif

/* --------------------------------------------------------------------------------------------- */
/* Configure ssftlv interface                                                                    */
/* --------------------------------------------------------------------------------------------- */
/* 1 to use 1 byte TAG and LEN fields, else 0 for variable 1-4 byte TAG and LEN fields */
/* 1 allows 2^8 unique TAGs and VALUE fields < 2^8 bytes in length */
/* 0 allows 2^30 unique TAGs and VALUE fields < 2^30 bytes in length */
#define SSF_TLV_ENABLE_FIXED_MODE (0u)

/* --------------------------------------------------------------------------------------------- */
/* Configure ssfcfg interface                                                                    */
/* --------------------------------------------------------------------------------------------- */
#define SSF_CFG_TYPEDEF_STRUCT typedef struct /* Optionally add packed struct attribute here */
#define SSF_CFG_MAX_STORAGE_SIZE (4096u) /* Max size of erasable NV storage sector */
#define SSF_MAX_CFG_DATA_SIZE_LIMIT (32u) /* Max size of data */
#define SSF_CFG_WRITE_CHECK_CHUNK_SIZE (32u) /* Max size of tmp stack buffer for write checking */

/* 1 to use RAM as storage, 0 to specify another storage interface */
#define SSF_CFG_ENABLE_STORAGE_RAM (1u)
#if SSF_CFG_ENABLE_STORAGE_RAM == 0
#define SSF_CFG_ERASE_STORAGE(dataId)
#define SSF_CFG_WRITE_STORAGE(data, dataSize, dataId, dataOffset)
#define SSF_CFG_READ_STORAGE(data, dataSize, dataId, dataOffset)
#else
#define SSF_MAX_CFG_RAM_SECTORS (3u)
#define SSF_MAX_CFG_RAM_SECTOR_SIZE (SSF_MAX_CFG_DATA_SIZE_LIMIT + 32u)
#define SSF_CFG_ERASE_STORAGE(dataId) { \
    memset(&_ssfCfgStorageRAM[dataId], 0xff, SSF_MAX_CFG_RAM_SECTOR_SIZE); \
}
#define SSF_CFG_WRITE_STORAGE(data, dataLen, dataId, dataOffset) { \
    memcpy(&_ssfCfgStorageRAM[dataId][dataOffset], data, dataLen); \
}
#define SSF_CFG_READ_STORAGE(data, dataSize, dataId, dataOffset) { \
    memcpy(data, &_ssfCfgStorageRAM[dataId][dataOffset], dataSize); \
}
#endif

/* --------------------------------------------------------------------------------------------- */
/* External interface                                                                            */
/* --------------------------------------------------------------------------------------------- */
#ifdef _WIN32
__declspec(noreturn)
#endif
void SSFPortAssert(const char* file, unsigned int line);

#ifdef _WIN32
#define SSFPortGetTick64() GetTickCount64()
#else /* _WIN32 */
SSFPortTick_t SSFPortGetTick64(void);
#endif /* _WIN32 */

#include "ssf.h"

#ifdef __cplusplus
}
#endif

#endif /* SSF_PORT_H_INCLUDE */
