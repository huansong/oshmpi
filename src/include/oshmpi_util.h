/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * (C) 2018 by Argonne National Laboratory.
 *     See COPYRIGHT in top-level directory.
 */
#ifndef OSHMPI_UTIL_H
#define OSHMPI_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <oshmpiconf.h>

/* ======================================================================
 * Generic MACROs and inline functions.
 * ====================================================================== */

#ifndef OSHMPI_UNLIKELY
#ifdef HAVE_BUILTIN_EXPECT
#  define OSHMPI_UNLIKELY(x_) __builtin_expect(!!(x_),0)
#else
#  define OSHMPI_UNLIKELY(x_) (x_)
#endif
#endif /* OSHMPI_UNLIKELY */

#ifndef OSHMPI_LIKELY
#ifdef HAVE_BUILTIN_EXPECT
#  define OSHMPI_LIKELY(x_)   __builtin_expect(!!(x_),1)
#else
#  define OSHMPI_LIKELY(x_)   (x_)
#endif
#endif /* OSHMPI_LIKELY */

#ifndef OSHMPI_ATTRIBUTE
#ifdef HAVE_GCC_ATTRIBUTE
#define OSHMPI_ATTRIBUTE(a_) __attribute__(a_)
#else
#define OSHMPI_ATTRIBUTE(a_)
#endif
#endif /* OSHMPI_ATTRIBUTE */

#ifndef OSHMPI_MAX
#define OSHMPI_MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef OSHMPI_MAX
#define OSHMPI_MAX(a,b) ((a) < (b) ? (a) : (b))
#endif

#define OSHMPI_ASSERT(EXPR) do { if (OSHMPI_UNLIKELY(!(EXPR))){           \
            fprintf(stderr, "OSHMPI assert fail in [%s:%d]: \"%s\"\n",    \
                          __FILE__, __LINE__, #EXPR);               \
            fflush(stderr);                                         \
            MPI_Abort(MPI_COMM_WORLD, -1);                          \
        }} while (0)

/* TODO: define consistent error handling & report */
#define OSHMPI_ERR_ABORT(MSG,...) do {                                  \
            fprintf(stderr, "OSHMPI abort in [%s:%d]:"MSG,              \
                          __FILE__, __LINE__, ## __VA_ARGS__);     \
            fflush(stderr);                                        \
            MPI_Abort(MPI_COMM_WORLD, -1);                         \
        } while (0)

/*  MPI call wrapper.
 *  No consistent error handling is defined in OpenSHMEM. For now,
 *  we simply assume processes abort inside MPI when an MPI error occurs
 *  (MPI default error handler: MPI_ERRORS_ARE_FATAL). */
#define OSHMPI_CALLMPI(fnc_stmt) do {      \
            fnc_stmt;                      \
        } while (0)

/* ======================================================================
 * Convenient helper functions
 * ====================================================================== */

static inline const char *OSHMPI_thread_level_str(int level)
{
    const char *str = "";
    switch (level) {
        case MPI_THREAD_SINGLE:
            str = "THREAD_SINGLE";
            break;
        case MPI_THREAD_FUNNELED:
            str = "THREAD_FUNNELED";
            break;
        case MPI_THREAD_SERIALIZED:
            str = "THREAD_SERIALIZED";
            break;
        case MPI_THREAD_MULTIPLE:
            str = "THREAD_MULTIPLE";
            break;
    }
    return str;
}


#endif /* OSHMPI_UTIL_H */