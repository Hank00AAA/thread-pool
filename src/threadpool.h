/* Copyright same as original repo
 */


#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @file threadpool.h
 * @bried Threadpool Header File
 */

#define MAX_THREADS 64
#define MAX_QUEUE 65535

typedef struct threadpool_t threadpool_t;

typedef enum {
	threadpool_invalid        = -1,
	threadpool_lock_failure   = -2,
	threadpool_queue_full     = -3,
	threadpool_shutdown       = -4,
	threadpool_thread_failure = -5
} threadpool_error_t;

typedef enum {
	threadpool_graceful = 1
} threadpool_destroy_flags_t;

/**
 * @function threadpool_create
 * @brief Create a thread_pool_t object.
 * @param thread_count Number of worker threads.
 * @param flags unused.
 * @return a newly created thread pool or NULL
 */
threadpool_t *threadpool_create(int thread_count, int queue_size, int flags);

/**
 * @function threadpool_add
 * @bried add a new task in the queue of a thread pool
 * @param pool Thread pool to which add the task.
 * @param argument Argument to be passed to the function
 * @param flags unused parameter
 * @return 0 if all goes well, negative values in case of error
 */
int threadpool_add(threadpool_t *pool, void (*routine)(void *), 
                   void *arg, int flags);

/**
 * @function threadpool_destroy
 * @brief Stops and destroys a thread pool
 * @param pool Thread pool to destroy
 * @param flags Flags for shutdown
 *
 * Know values for flags are 0 (default) and threadpool_graceful in 
 * which case the thread pool doesn't accept any new tasks but 
 * process all pending tasks before shutdown
 */
int threadpool_destroy(threadpool_t *pool, int flags);

#ifdef __cplusplus
}
#endif

#endif /* _THREADPOOL_H_ */


