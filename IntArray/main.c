#include <stdio.h>
#include <stdlib.h>

#define ERROR_ALLOC_FAILURE -1
#define ERROR_INDEX_ERROR -2
#define ERROR_NONLETHAL -3

// int* data, size_t max_size e size_t used
typedef struct IntArray {
    int* data;
    size_t max_size;
    size_t used;
} IntArray;

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

        default:
            fprintf(stderr, "UnknownError: %s (%d)\n", message, error_code);
            exit(1);
    }
}

// Retorna pointer para array vazio com tamanho especificado
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

// Destroy array e todos os dados
void int_array_destroy(IntArray* array) {
    free(array->data);
    free(array);
}

// Empurra valor para o final do array, mudando o tamanho do array se necessário
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

// Remove e retorna o índice especificado, realocando os índices restantes
int int_array_remove(IntArray* array, unsigned int index) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "remove index out of range");

    int num = array->data[index];

    for (int i = index; i < array->used - 1; i++)
        array->data[i] = array->data[i + 1];

    array->used--;

    return num;
};

// Remove e retorna o último item do array
int int_array_pop(IntArray* array) {
    if (array->used == 0)
        error_manager(ERROR_INDEX_ERROR, "pop empty array");

    return array->data[--array->used];
};

// Retorna o valor do índice especificado, sem modificar o array
int int_array_get(const IntArray* array, unsigned int index) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "get index out of range");

    return array->data[index];
}

// Modifica o valor do índice especificado
void int_array_set(IntArray* array, unsigned int index, int val) {
    if (index > array->used - 1) {
        error_manager(ERROR_NONLETHAL, "set unused index");
        return;
    }

    array->data[index] = val;
}

// Insere o valor no índice específicado, sem substituição
void int_array_insert(IntArray* array, unsigned int index, int val) {
    if (index > array->used - 1)
        error_manager(ERROR_INDEX_ERROR, "insert outside of array");
    // Coisas acontecerão aqui.
}

// Visualização do array
void int_array_show(const IntArray* array) {
    for (unsigned int i = 0; i < array->used; i++)
        printf("[%d]", array->data[i]);
    printf("\n");
}

// Visualização do array com detalhes
void int_array_status(const IntArray* array) {
    printf("Size: %d  Used: %d\n", array->max_size, array->used);
    for (unsigned int i = 0; i < array->used; i++)
        printf("[%d]", array->data[i]);
    printf("\nAddress: %p\nData:    %p\n", array, array->data);
    printf("\n");
}

int main() {

    return 0;
}