#ifndef TIME_H
# define TIME_H

extern volatile unsigned int jiffies;
void            tick_handler(void);
void            msleep(unsigned int ms);

unsigned int    uptime_ms(void);

#endif