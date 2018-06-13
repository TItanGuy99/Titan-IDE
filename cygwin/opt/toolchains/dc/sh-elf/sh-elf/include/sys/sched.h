/** \file   sys/sched.h
    \brief  Basic sys/sched.h file for newlib.

    This file specifies a few things to make sure pthreads stuff compiles.
*/

#ifndef __SYS_SCHED_H
#define __SYS_SCHED_H

#include <kos/cdefs.h>
__BEGIN_DECLS

// These are copied from Newlib to make stuff compile as expected.

#define SCHED_OTHER    0    /**< \brief Other scheduling */
#define SCHED_FIFO     1    /**< \brief FIFO scheduling */
#define SCHED_RR       2    /**< \brief Round-robin scheduling */

/** \brief  Scheduling Parameters, P1003.1b-1993, p. 249.
    \note   Fields whose name begins with "ss_" added by P1003.4b/D8, p. 33.
    \headerfile sys/sched.h
*/
struct sched_param {
    int sched_priority;           /**< \brief Process execution scheduling priority */
};

// And all this maps pthread types to KOS types for pthread.h.
#include <kos/thread.h>
#include <kos/sem.h>
#include <kos/cond.h>
#include <kos/mutex.h>
#include <kos/tls.h>
#include <kos/once.h>

// Missing structs we don't care about in this impl.
/** \brief  POSIX mutex attributes.

    Not implemented in KOS.

    \headerfile sys/sched.h
*/
typedef struct {
    // Empty
} pthread_mutexattr_t;

/** \brief  POSIX condition variable attributes.

    Not implemented in KOS.

    \headerfile sys/sched.h
*/
typedef struct {
    // Empty
} pthread_condattr_t;

/** \brief  POSIX thread attributes.

    Not implemented in KOS.

    \headerfile sys/sched.h
*/
typedef struct {
    // Empty
} pthread_attr_t;

// Map over KOS types. The mutex/condvar maps have to be pointers
// because we allow _INIT #defines to work.
typedef kthread_t * pthread_t;      /**< \brief POSIX thread type */
typedef mutex_t pthread_mutex_t;    /**< \brief POSIX mutex type */
typedef condvar_t pthread_cond_t;   /**< \brief POSIX condition type */

// These, on the other hand, map right over.
typedef kthread_once_t pthread_once_t;  /**< \brief POSIX once control */
typedef kthread_key_t pthread_key_t;    /**< \brief POSIX thread data key */

__END_DECLS

#endif  /* __SYS_SCHED_H */
