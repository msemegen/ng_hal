#pragma once

#define xmcu_assert(expression)   \
    do                            \
    {                             \
        (void)sizeof(expression); \
    } while (0)
