// #include <tasks.h>
typedef struct task_s {
    unsigned int *sp;
} task_t;

static unsigned char stack[3][2048] __attribute__((aligned(16)));

// unsigned int *schedule(unsigned int *frame) {
//     current->sp = frame;
//     current = next_task(current);
//     return (current->sp);
// }