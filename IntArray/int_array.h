#pragma once
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

void error_manager(int error_code, char* message);

// Retorna pointer para array vazio com tamanho especificado
IntArray* int_array_init(size_t initial_size);
// Destroy array e todos os dados
void int_array_destroy(IntArray* array);
// Empurra valor para o final do array, mudando o tamanho do array se necessário
void int_array_push(IntArray* array, int num);
// Remove e retorna o índice especificado, realocando os índices restantes
int int_array_remove(IntArray* array, size_t index);
// Remove e retorna o último item do array
int int_array_pop(IntArray* array);
// Retorna o valor do índice especificado, sem modificar o array
int int_array_get(const IntArray* array, size_t index);
// Modifica o valor do índice especificado
void int_array_set(IntArray* array, size_t index, int val);
// Insere o valor no índice específicado, sem substituição
void int_array_insert(IntArray* array, size_t index, int val);
// Visualização do array
void int_array_show(const IntArray* array);
// Visualização do array com detalhes
void int_array_status(const IntArray* array);