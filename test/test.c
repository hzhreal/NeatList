#include <stdint.h>

#include "list.h"

int main(void) {
    uint8_t x = 123, y = 12, z = 1;

    List *l = list_init((void *)&x);
    list_print(l, stdout);

    list_insert_head(l, (void *)&y);
    list_print(l, stdout);

    list_insert_tail(l, (void *)&z);
    list_print(l, stdout);

    list_delete_head(l);
    list_print(l, stdout);

    list_delete_tail(l);
    list_print(l, stdout);

    list_clean(l);

    return 0;
}