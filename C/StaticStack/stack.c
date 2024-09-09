// # PILHA ESTÁTICA
#include "stdio.h"
#include "stdlib.h"

typedef struct Stack {
    int *data, size, used;
} Stack;

Stack* stack_init() {
    Stack* stack = malloc(sizeof(Stack));

    if (stack == NULL) {
        fprintf(stderr, "[stack_init] Erro: Alloc de stack falhou.\n");
        return NULL;
    }

    stack->used = 0;
    stack->size = 8;
    stack->data = malloc(stack->size * sizeof(int));

    if (stack->data == NULL) {
        fprintf(stderr, "[stack_init] Erro: Alloc de dados falhou.\n");
        return NULL;
    }

    return stack;
}

// Size: tamanho específico ou 0 para dobrar
void stack_resize(Stack* stack, int size) {
    if (size == 0)
        size = stack->size * 2;

    if (size < 0) {
        fprintf(stderr, "[stack_resize] Erro: Tamanho negativo.\n");
        return;
    }

    stack->data = realloc(stack->data, sizeof(int) * size);

    if (stack->data == NULL) {
        fprintf(stderr, "[stack_resize] Erro: Realloc falhou.\n");
        return;
    }

    stack->size = size;
}

void stack_push(Stack* stack, int val) {
    if (stack->used == stack->size)
        stack_resize(stack, 0);

    stack->data[stack->used++] = val;
}

int stack_pop(Stack* stack) {
    if (stack->used == 0) {
        fprintf(stderr, "[stack_pop] Erro: Pilha vazia.\n");
        return 0;
    }

    // Pop remove o último, o último vai ser used - 1, pop também irá diminuir o
    // valor de used, por isso usamos --
    int val = stack->data[--stack->used];
    return val;
}

int stack_top(Stack* stack) {
    if (stack->used == 0) {
        fprintf(stderr, "[stack_top] Erro: Pilha vazia.\n");
        return 0;
    }

    return stack->data[stack->used - 1];
}

int stack_size(Stack* stack) {
    return stack->used;  // Não tenho certeza se queremos o tamanho máximo ou o
                         // tamanho utilizado
}

int stack_empty(Stack* stack) {
    return stack->used == 0;
}

void show_stack(Stack* stack) {
    printf("==============================\n");
    printf("Stack location: %p\nStack size: %d\n", stack, stack->size);
    printf("Stack used: %d\n", stack->used);

    for (int i = stack->size - 1; i >= 0; i--) {
        printf("[%d]\t%d", i, stack->data[i]);
        if (i < stack->used)
            printf(" !");
        printf("\n");
    }
    printf("==============================\n");
}

int main() {
    Stack* s = stack_init();
    for (int i = 0; i < 6; i++)
        stack_push(s, rand() % 100);

    show_stack(s);

    for (int i = 0; i < 6; i++)
        stack_push(s, rand() % 100);

    show_stack(s);

    stack_pop(s);
    show_stack(s);

    printf("top = %d\n", stack_top(s));

    stack_push(s, 2323);
    show_stack(s);
}