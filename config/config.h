#ifndef CONFIG_H
# define CONFIG_H

# define HZ 1000
# define TICK_US (1000000 / (HZ))

# define PAGE_SHIFT 10
# define RAM_SIZE (1u << 19)
# define MAX_ORDER 7
# define PAGE_SIZE (1u << (PAGE_SHIFT))
# define NUM_PAGES ((RAM_SIZE) >> (PAGE_SHIFT))
# define RAM_START (0x20000000u)
# define RAM_END (0x20080000u)
#endif

