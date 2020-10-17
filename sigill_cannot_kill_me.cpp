#include <sys/types.h>
#include <csignal>
#include <cstdio>

/*
 * This program demonstrates that if the default SIGILL handler is overridden to our own
 * which is an noop.
 *
 * The process is rescheduled to execute the offending statement which is causing OS sending SIGILL
 * to this process.
 *
 * With our noop signal handler, the process will keep running the `noop_signal_handler` until eternity...
 */
void noop_signal_handler(int signum) {
    fprintf(stdout, "ignore signal %d so the process doesn't get killed\n", signum);
}

int main() {
    /*
     * Override the default signal handler which is killing the process
     */
    signal(SIGILL, noop_signal_handler);

    /*
     * Create some mess which will cause OS tries to kill the process by sending SIGILL to the process
     * `volatile` is used so compiler doesn't optimize away the statement
     */
    volatile int discarded = 1 / 0;

    /*
     * Can't reach below line since we keep hitting exception on above statement
     */
    fprintf(stderr, "never run\n");
    return 0;
}