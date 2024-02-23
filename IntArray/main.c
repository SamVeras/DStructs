#include <stdio.h>
#include <stdlib.h>

// int* data, size_t max_size e size_t used
typedef struct IntArray {
    int* data;
    size_t max_size;
    size_t used;
} IntArray;

// Retorna pointer para array vazio com tamanho especificado
IntArray* int_array_init(size_t initial_size) {
    IntArray* array = malloc(sizeof(IntArray));

    if (array == NULL)
        perror("Erro em inicialização de array struct."), exit(1);

    array->max_size = initial_size;
    array->used = 0;
    array->data = malloc(initial_size * sizeof(int));

    if (array->data == NULL)
        perror("Erro em inicialização de array."), exit(1);

    return array;
}
