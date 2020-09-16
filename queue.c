#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (!q)
        return;

    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
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
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    size_t length = strlen(s) + 1;
    newh->value = (char *) malloc(length * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    newh->next = NULL;

    // memset(newh->value, '\0', strlen(s) + 1);
    // strncpy(newh->value, s, strlen(s));
    // memcpy(newh->value, s, strlen(s) + 1);
    snprintf(newh->value, length, "%s", s);

    // insert head
    newh->next = q->head;
    q->head = newh;
    /* What if either call to malloc returns NULL? */
    if (!q->tail)
        q->tail = newh;
    (q->size)++;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    size_t length = strlen(s) + 1;
    newt->value = (char *) malloc(length * sizeof(char));
    if (!newt->value) {
        free(newt);
        return false;
    }

    // memset(newt->value, '\0', strlen(s) + 1);
    // strncpy(newt->value, s, strlen(s));
    // memcpy(newt->value, s, strlen(s) + 1);
    snprintf(newt->value, length, "%s", s);

    // insert tail
    newt->next = NULL;
    if (!q->tail) {
        q->head = newt;
        q->tail = newt;
        return true;
    }
    q->tail->next = newt;
    q->tail = newt;
    (q->size)++;

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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    /*Return false if queue is NULL or empty.*/
    if (!q || !q->head)
        return false;
    /*
     *If sp is non-NULL and an element is removed, copy the removed string to
     **sp (up to a maximum of bufsize-1 characters, plus a null terminator.)
     */
    list_ele_t *tmp;
    tmp = q->head;
    if (sp) {
        // strncpy(sp, tmp->value, bufsize - 1);
        // sp[bufsize - 1] = '\0';
        snprintf(sp, bufsize, "%s", tmp->value);
    }

    // remove head
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    (q->size)--;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q) {
        return 0;
    }
    return q->size;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || q->size == 1)
        return;

    q->tail = q->head;

    list_ele_t *cursor = NULL;
    list_ele_t *next = NULL;
    while (q->head) {
        next = q->head->next;
        q->head->next = cursor;
        cursor = q->head;
        q->head = next;
    }
    q->head = cursor;
    q->tail->next = NULL;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void split_list(list_ele_t **head, list_ele_t **list1, list_ele_t **list2)
{
    list_ele_t **slow = list1;
    list_ele_t **fast = list2;

    while ((*fast) && (*fast)->next) {
        *slow = (*slow)->next;
        *fast = (*fast)->next->next;
    }
    // slow is at the midnode

    *list2 = (*slow)->next;
    // Split actually
    (*slow)->next = NULL;

    *list1 = *head;
}

void merge_list(list_ele_t **head, list_ele_t **list1, list_ele_t **list2)
{
    list_ele_t **cursor = head;

    while ((*list1) && (*list2)) {
        if (strcmp((*list1)->value, (*list2)->value) < 0) {
            *cursor = *list1;
            *list1 = (*list1)->next;
        } else {
            *cursor = *list2;
            *list2 = (*list2)->next;
        }
        cursor = &((*cursor)->next);
    }
    // avoid dropped off
    if (*list1)
        *cursor = *list1;
    if (*list2)
        *cursor = *list2;
}

void merge_sort(list_ele_t **head)
{
    // Base case
    if (!(*head) || !(*head)->next)
        return;

    // Splitting list
    list_ele_t *list1 = *head;
    list_ele_t *list2 = (*head)->next;

    split_list(head, &list1, &list2);

    // Recursive sorting two list
    merge_sort(&(list1));
    merge_sort(&(list2));

    // Merge sorted lists
    merge_list(head, &list1, &list2);
}

// void merge_sort1(list_ele_t **head)
// {
//     if (!(*head) || !((*head)->next))
//         return;

//     list_ele_t *l1 = (*head)->next;
//     list_ele_t *l2 = *head;

//     while (l1 && l1->next) {
//         l2 = l2->next;
//         l1 = l1->next->next;
//     }
//     l1 = l2->next;
//     l2->next = NULL;
//     l2 = *head;

//     merge_sort1(&l2);
//     merge_sort1(&l1);

//     *head = NULL;
//     list_ele_t **tmp = head;

//     while (l1 && l2) {
//         if (strcmp(l1->value, l2->value) < 0) {
//             *tmp = l1;
//             l1 = l1->next;
//         } else {
//             *tmp = l2;
//             l2 = l2->next;
//         }
//         tmp = &((*tmp)->next);
//     }

//     *tmp = l1 ? l1 : l2;
// }

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    /* No effect if q is NULL or empty.*/
    if (!q || !q->head)
        return;

    merge_sort(&q->head);
    // merge_sort1(&q->head);

    while (q->tail->next)
        q->tail = q->tail->next;
}

// void q_print(queue_t *q)
// {
//     for (list_ele_t *current = q->head; current; current = current->next)
//         printf("%s ", current->value);
//     printf("\n");
// }


// int main(int argc, char const *argv[])
// {
//     queue_t *q = NULL;

//     q_print(q);

//     q_insert_head(q, 72);
//     q_insert_head(q, 101);
//     q_insert_head(q, 108);
//     q_insert_head(q, 109);
//     q_insert_head(q, 110);
//     q_insert_head(q, 111);

//     print_list(head);

//     node_t *entry = find_entry(head, 101);
//     remove_entry(&head, entry);

//     entry = find_entry(head, 111);
//     remove_entry(&head, entry);

//     print_list(head);

//     /* swap pair.
//      * See https://leetcode.com/problems/swap-nodes-in-pairs/
//      */
//     //head = swap_pair(head);
//     swap_pair3(&head);
//     print_list(head);

//     //head = reverse(head);
//     reverse2(&head);
//     print_list(head);

//     return 0;
// }
