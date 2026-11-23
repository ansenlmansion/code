#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Linked stack storing int values. The stack internals are private. */
typedef struct LinkStack LinkStack;

/* Create an empty stack; returns NULL if allocation fails. */
LinkStack *linkstack_create(void);

/* Release the stack. Passing NULL is safe. */
void linkstack_destroy(LinkStack *stack);

/* Push value onto stack; returns 0 on success, nonzero on failure. */
int linkstack_push(LinkStack *stack, int value);

/* Remove the top value and write it to out_value; returns 0 on success. */
int linkstack_pop(LinkStack *stack, int *out_value);

/* Read the top value without removing it; returns 0 on success. */
int linkstack_peek(const LinkStack *stack, int *out_value);

/* Return nonzero if stack is NULL or empty. */
int linkstack_is_empty(const LinkStack *stack);

/* Return the number of values in the stack (0 for NULL). */
size_t linkstack_size(const LinkStack *stack);

#ifdef __cplusplus
}
#endif

#endif /* LINKSTACK_H */
