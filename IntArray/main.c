#include <stdio.h>
#include <stdlib.h>
#include "int_array.h"

int main() {
    IntArray* a = int_array_init(4);

    int_array_push(a, 31);
    int_array_push(a, 3);
    int_array_push(a, 48);
    int_array_push(a, 80);

    int_array_status(a);

    int_array_push(a, 8);
    int_array_push(a, 39);
    int_array_push(a, 33);

    int_array_status(a);

    int_array_set(a, 2, 555);
    int_array_status(a);

    int_array_insert(a, 1, 999);
    int_array_insert(a, 8, 12341234);

    int_array_status(a);

    int_array_destroy(a);

    return 0;
}