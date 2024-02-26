// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}

int int_stack_over(int_stack_t *stk) {
    if (stk->size < 2)
        return 0; // Not enough elements

    int_entry_t *second_entry = SLIST_NEXT(SLIST_FIRST(&stk->head), entries);
    if (second_entry) {
        return int_stack_push(stk, second_entry->value);
    }
    return 0; // Fail
}

int int_stack_rot(int_stack_t *stk) {
    if (stk->size < 3)
        return 0; // not enough elements

    int_entry_t *first = SLIST_FIRST(&stk->head);
    int_entry_t *second = SLIST_NEXT(first, entries);
    int_entry_t *third = SLIST_NEXT(second, entries);

    // remove third from its place
    SLIST_REMOVE_AFTER(first, entries);
    // insert it at the head
    SLIST_INSERT_HEAD(&stk->head, third, entries);

    return 1; // Success
}

int int_stack_drop(int_stack_t *stk) {
    if (stk->size < 1)
        return 0; // Stack is empty

    return int_stack_pop(stk, &(int){0}); // get ride of top value
}

int int_stack_2swap(int_stack_t *stk) {
    if (stk->size < 4)
        return 0; // Not enough elements

    int a, b, c, d;
    int_stack_pop(stk, &d);
    int_stack_pop(stk, &c);
    int_stack_pop(stk, &b);
    int_stack_pop(stk, &a);
    int_stack_push(stk, c);
    int_stack_push(stk, d);
    int_stack_push(stk, a);
    int_stack_push(stk, b);

    return 1; // Success
}

int int_stack_2dup(int_stack_t *stk) {
    if (stk->size < 2)
        return 0; // Not enough elements

    int a, b;
    int_stack_top(stk, &b);
    int_entry_t *second_entry = SLIST_NEXT(SLIST_FIRST(&stk->head), entries);
    a = second_entry->value;

    int_stack_push(stk, a);
    int_stack_push(stk, b);

    return 1; // Success
}

int int_stack_2over(int_stack_t *stk) {
    if (stk->size < 4)
        return 0; // Not enough elements

    int_entry_t *first = SLIST_FIRST(&stk->head);
    int_entry_t *second = SLIST_NEXT(first, entries);
    int_entry_t *third = SLIST_NEXT(second, entries);
    int_entry_t *fourth = SLIST_NEXT(third, entries);

    int_stack_push(stk, third->value);
    int_stack_push(stk, fourth->value);

    return 1; // Success
}

int int_stack_2drop(int_stack_t *stk) {
    if (stk->size < 2)
        return 0; // Not enough elements

    int_stack_pop(stk, &(int){0}); // Discard the top value
    int_stack_pop(stk, &(int){0}); // Discard the next top value

    return 1; // Success
}

int int_stack_subtract(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value - top_value);
}

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value + top_value);
}

int int_stack_multiply(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value * top_value);
}

int int_stack_divide(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value / top_value);
}
