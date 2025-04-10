#include "include/vesa.h"

int sleep(unsigned long ms);
void *shm_open(const char *name);
unsigned long fbmap(void);
void get_mode_info(struct mode_info*);