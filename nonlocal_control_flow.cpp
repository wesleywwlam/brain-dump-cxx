#include <iostream>
#include <csignal>
#include <csetjmp>
#include <climits>

jmp_buf env;
static int UNWOUND = 1;

void unwind_signal_handler(int signum) {
    fprintf(stdout, "got exception %d, unwind the stack\n", signum);
    longjmp(env, UNWOUND);
}

double reciprocal(int num) {
    double result;
    if (setjmp(env) == UNWOUND) {
        result = INT_MIN;
    } else {
        result = 1 / num;
    }
    return result;
}

int main() {
    /*
     * Register our signal handler which will unwind the stack upon exception.
     */
    signal(SIGFPE, unwind_signal_handler);

    /*
     * Print 0.25
     */
    fprintf(stdout, "reciprocal of 5: %f\n", reciprocal(4));

    /*
     * Offending subroutine that will cause OS to send SIGFPE to the process,
     * we catch the exception and unwind the stack to handle it gracefully by
     * returning `INT_MIN` instead.
     *
     * Print `INT_MIN` which is `-2147483648.000000`
     */
    fprintf(stdout, "reciprocal of 0: %f\n", reciprocal(0));
}