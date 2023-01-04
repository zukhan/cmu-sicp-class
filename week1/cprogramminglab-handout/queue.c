/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t* q =  malloc(sizeof(queue_t));
    if (q == NULL) {
      return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }
    int v = -1;
    while (q_remove_head(q, &v)) {
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t* q, int v)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t* new_head = malloc(sizeof(list_ele_t));
    if (new_head == NULL) {
        return false;
    }

    new_head->value = v;
    new_head->next = q->head;

    if (q->tail == NULL) {
        q->tail = new_head;
    }
    q->head = new_head;
    q->size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t* q, int v)
{
    if (q == NULL) {
        return false;
    }

    // handle case of an empty queue
    if (q->tail == NULL) {
        // q_insert_head will update the tail as well
        return q_insert_head(q, v);
    }

    list_ele_t* new_tail = malloc(sizeof(list_ele_t));
    if (new_tail == NULL) {
        return false;
    }
    new_tail->value = v;
    new_tail->next = NULL;

    q->tail->next = new_tail;
    q->tail = new_tail;

    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t* q, int* vp)
{
    if (q_size(q) == 0) {
        return false;
    }

    list_ele_t* head = q->head;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    if (vp != NULL) {
        *vp = head->value;
    }
    free(head);
    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t* q)
{
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t* q)
{
    if (q_size(q) <= 1) {
        return;
    }
    list_ele_t* new_head = q->tail;
    list_ele_t* new_tail = q->head;

    list_ele_t* prev_node = NULL;
    list_ele_t* cur_node = q->head;
    list_ele_t* next_node = cur_node->next;

    while (cur_node != NULL) {
        next_node = cur_node->next;
        cur_node->next = prev_node;
        prev_node = cur_node;
        cur_node = next_node;
    }

    q->head = new_head;
    q->tail = new_tail;
}

