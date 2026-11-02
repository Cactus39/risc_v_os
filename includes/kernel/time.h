#ifndef TIME_H
# define TIME_H

# define TIME_BEFORE(a,b) (((int)((a) - (b))) < 0 ? 1 : 0)
# define TIME_AFTER(a,b) (((int)((b) - (a))) < 0 ? 1 : 0)

extern volatile unsigned int jiffies;
void            tick_handler(void);
void            msleep(unsigned int ms);
void            udelay(unsigned int us);
unsigned int    uptime_ms(void);

#endif