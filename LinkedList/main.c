#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    LinkedList* n = linked_list_init();

    linked_list_append(n, 75);
    linked_list_append(n, 97);
    linked_list_append(n, 145);
    linked_list_append(n, -94);
    linked_list_append(n, 97);

    linked_list_prepend(n, 166);
    linked_list_prepend(n, -25);

    linked_list_show(n);

    printf("Number of items in list:\t%d\n", linked_list_size(n));
    printf("Smallest item in list:\t\t%d\n", linked_list_min(n)->data);
    printf("Largest item in list:\t\t%d\n", linked_list_max(n)->data);
    printf("Number of times 97 appears:\t%d\n", linked_list_count(n, 97));
    printf("Value 97 first appears at:\t%p\n", linked_list_find(n, 97));
    printf("Item at position 4:\t\t%d\n", linked_list_item_at(n, 4));
    printf("Removed first item in list:\t%d\n", linked_list_remove_first(n));
    printf("Removed last item in list:\t%d\n\n", linked_list_remove_last(n));

    linked_list_show(n);

    LinkedList* m = linked_list_copy(n);
    printf("Created a copy of the list.\n");

    linked_list_empty(n);
    printf("Original list is now empty.\n");

    linked_list_show(n);

    linked_list_destroy(n);
    printf("Original list destroyed.\n");

    printf("New list has %d items.\n", linked_list_size(m));

    linked_list_destroy(m);
    printf("New list destroyed.\n");

    return 0;
};
