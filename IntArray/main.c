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
    }

    array->data[array->used] = num;
    array->used++;
}

// Remove e retorna o índice especificado
int int_array_remove(IntArray* array, unsigned int index) {
    if (index > array->used - 1)
        perror("Erro em remove fora de índice"), exit(1);

    int num = array->data[index];

    for (int i = index; i < array->used - 1; i++)
        array->data[i] = array->data[i + 1];

    array->used--;

    return num;
};

// Remove e retorna o último item do array
int int_array_pop(IntArray* array) {
    if (array->used == 0)
        perror("Erro em pop lista vazia"), exit(1);
    return array->data[--array->used];
};

int int_array_get(const IntArray* array, unsigned int index) {
    if (index < array->used - 1)
        perror("Erro em get fora de índice"), exit(1);

    return array->data[index];
}

void int_array_set(IntArray* array, unsigned int index, int val) {
    if (index > array->used - 1)
        return;
    array->data[index] = val;
}

// Insere o valor no índice específicado, sem substituição
void int_array_insert(IntArray* array, unsigned int index, int val) {
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
    printf("\nAddress: %p\nData address: %p\n", array, array->data);
    printf("\n");
}

int main() {

    return 0;
}