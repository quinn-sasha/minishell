#ifndef SIGNAL_H
#define SIGNAL_H

void signal_handler(int signum);
void set_signal_handler(int signum);
void ignore_signal(int signum);
void reset_signal(int signum);
int check_state(void);
void set_up_signal(void);

#endif
