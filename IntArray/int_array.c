#include "int_array.h"

void error_manager(int error_code, char* message) {
    switch (error_code) {
        case ERROR_ALLOC_FAILURE:
            fprintf(stderr, "AllocFailure: %s\n", message);
            exit(1);

        case ERROR_INDEX_ERROR:
            fprintf(stderr, "IndexError: %s\n", message);
            exit(1);

        case ERROR_NONLETHAL:
            fprintf(stderr, "NonLethal: %s\n", message);
            break;

        default:
            fprintf(stderr, "UnknownError: %s (%d)\n", message, error_code);
            exit(1);
    }
}

IntArray* int_array_init(size_t initial_size) {
    IntArray* array = malloc(sizeof(IntArray));

    if (array == NULL)
        error_manager(ERROR_ALLOC_FAILURE, "array init");

    array->max_size = initial_size;
    array->used = 0;
    array->data = malloc(initial_size * sizeof(int));

    if (array->data == NULL)
        error_manager(ERROR_ALLOC_FAILURE, "array data init");

    return array;
}

void int_array_destroy(IntArray* array) {
    free(array->data);
    free(array);
}

void int_array_push(IntArray* array, int num) {
    if (array->used == array->max_size) {
        array->max_size *= 2;
        array->data = realloc(array->data, sizeof(int) * array->max_size);
        if (array->data == NULL)
            error_manager(ERROR_ALLOC_FAILURE, "array push realloc");
    }

    array->data[array->used] = num;
    array->used++;
}

int int_array_remove(IntArray* array, size_t index) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "remove index out of range");

    int num = array->data[index];

    for (size_t i = index; i < array->used - 1; i++)
        array->data[i] = array->data[i + 1];

    array->used--;

    return num;
};

int int_array_pop(IntArray* array) {
    if (array->used == 0)
        error_manager(ERROR_INDEX_ERROR, "pop empty array");

    return array->data[--array->used];
};

int int_array_get(const IntArray* array, size_t index) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "get index out of range");

    return array->data[index];
}

void int_array_set(IntArray* array, size_t index, int val) {
    if (index > array->used - 1) {
        error_manager(ERROR_NONLETHAL, "set unused index");
        return;
    }

    array->data[index] = val;
}

void int_array_insert(IntArray* array, size_t index, int val) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "insert outside of array");
    // Coisas acontecerão aqui.
    printf("%d", val);
}

void int_array_show(const IntArray* array) {
    for (unsigned int i = 0; i < array->used; i++)
        printf("[%d]", array->data[i]);
    printf("\n");
}

void int_array_status(const IntArray* array) {
    printf("Size: %zu  Used: %zu\n", array->max_size, array->used);
    for (unsigned int i = 0; i < array->used; i++)
        printf("[%d]", array->data[i]);
    printf("\nAddress: %p\nData:    %p\n", array, array->data);
    printf("\n");
}