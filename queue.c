#include "queue.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        goto done;

    q->head = NULL;
    q->parent_of_tail = NULL;
    q->len = 0;
done:
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *cur_ele;

    if (!q)
        return;

    cur_ele = q->head;
    while (cur_ele) {
        list_ele_t *nxt_ele = cur_ele->next;
        if (cur_ele->value)
            free(cur_ele->value);
        free(cur_ele);
        cur_ele = nxt_ele;
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int len;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    len = strlen(s) + 1;
    newh->value = malloc(len);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, len);

    if (q->len == 1)
        q->parent_of_tail = newh;

    newh->next = q->head;
    q->head = newh;
    q->len += 1;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    int len;

    if (!q)
        return false;

    if (q->len == 0)
        return q_insert_head(q, s);

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    len = strlen(s) + 1;
    newh->value = malloc(len);
    if (!newh->value) {
        free(newh);
        return false;
    }
    newh->next = NULL;
    memcpy(newh->value, s, len);

    if (q->len == 1) {
        q->parent_of_tail = q->head;
        q->head->next = newh;
    } else {
        q->parent_of_tail = q->parent_of_tail->next;
        q->parent_of_tail->next = newh;
    }
    q->len += 1;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *del;

    if (!q)
        return false;

    if (!q->head)
        return false;

    if (sp)
        strncpy(sp, q->head->value, bufsize);

    del = q->head;
    q->head = q->head->next;
    q->len -= 1;
    free(del->value);
    free(del);

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    int ret = 0;

    if (!q)
        goto done;

    ret = q->len;
done:
    return ret;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *nxt, *cur, *prev;

    if (!q || !q->head || q->len == 1)
        return;

    q->parent_of_tail = q->head->next;

    cur = q->head;
    prev = NULL;

    while (cur) {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    q->head = prev;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
