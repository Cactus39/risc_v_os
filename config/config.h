#ifndef CONFIG_H
# define CONFIG_H

# define HZ 1000
# define TICK_US (1000000 / (HZ))

# define PAGE_SHIFT 10
# define RAM_SIZE (1u << 19)
# define MAX_ORDER 8
# define PAGE_SIZE (1u << (PAGE_SHIFT))

#endif

