#include <signal.h>

void signal_handler(int signum);
void set_signal_handler(int signum);
void ignore_signal(int signum);
void reset_signal(int signum);
void check_state(void);
void set_up_signal(void);

