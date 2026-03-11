#include <stdbool.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};
 

typedef struct ListNode* node;
bool isPalindrome(struct ListNode* head) {
    node cur = head;
    node last = head;

    while (last->next != NULL) {
        last = last->next;
    }

    while (cur != NULL) {
        node tmp = cur->next;
        cur->next = last;
        last->next = tmp;
        cur = tmp;
        last = tmp->next;

        while (last != NULL && last->next != NULL) {
            last = last->next;
        }
    }

    cur = head;

    while (cur != NULL && cur->next != NULL) {
        if (cur->val != cur->next->val) {
            return false;
        }

        cur = cur->next->next;
    }

    return true;
}