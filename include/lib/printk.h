#ifndef __TAOS_PRINTK_H__
#define __TAOS_PRINTK_H__

#include "stddef.h"

#define bool _Bool
#define true 1
#define false 0

int printk(const char *, ...);

#endif
