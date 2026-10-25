#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// 1. Syscall Storm: Millions of tiny read/write calls to/from a pipe.
// This forces constant user/kernel transitions.
void syscall_storm_pipe() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return;
    }
    
    char write_buf = 'x';
    char read_buf = 0;
    
    // We execute 500k loops = 1 million system calls (500k writes + 500k reads)
    for (int i = 0; i < 500000; i++) {
        if (write(pipefd[1], &write_buf, 1) != 1) break;
        if (read(pipefd[0], &read_buf, 1) != 1) break;
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
}

// 2. Lock Contention Storm (Futex/Context Switch saturation)
pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;
volatile long long shared_counter = 0;

void *lock_contender(void *arg) {
    (void)arg;
    // Tight loop with high lock contention
    // This triggers kernel futex sleeps and wakes, resulting in high cswch/s
    for (int i = 0; i < 300000; i++) {
        pthread_mutex_lock(&global_lock);
        shared_counter++;
        pthread_mutex_unlock(&global_lock);
    }
    return NULL;
}

void mutex_contention_storm() {
    const int num_threads = 6;
    pthread_t threads[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, lock_contender, NULL) != 0) {
            perror("pthread_create failed");
            return;
        }
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

// 3. Thread Creation/Destruction Storm
// Saturates kernel process management and scheduler overhead.
void *dummy_thread_worker(void *arg) {
    (void)arg;
    return NULL;
}

void thread_creation_storm() {
    const int count = 2000;
    pthread_t t;
    for (int i = 0; i < count; i++) {
        if (pthread_create(&t, NULL, dummy_thread_worker, NULL) == 0) {
            pthread_join(t, NULL);
        }
    }
}

int main() {
    printf("Kernel-mode saturation target started. PID: %d\n", getpid());
    printf("Press Ctrl+C to stop.\n");
    printf("Executing kernel-mode workloads...\n");

    int iteration = 0;
    while (1) {
        iteration++;
        
        syscall_storm_pipe();
        mutex_contention_storm();
        thread_creation_storm();
        
        printf("Sys iteration %d completed\n", iteration);
        fflush(stdout);
    }
    return 0;
}
