#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;


 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

 void printList(ListNode* head) {
     while (head) {
         printf("%d ", head->val);
         head = head->next;
     }
     printf("\n");
 }

 class MyLinkedList {
 public:
     MyLinkedList() : head(nullptr) {}
     ListNode* getHead() {
         return head;
     }
     ListNode* getNode(int index);
     ListNode* getTail();
     int get(int index);
     void addAtHead(int val);
     void addAtTail(int val);
     void addAtIndex(int index, int val);
     void deleteAtIndex(int index);

     ListNode* head;
 };


 ListNode* MyLinkedList::getNode(int index) {
     ListNode* curr = head;
     for (int i = 0; i < index && curr; ++i) {
         curr = curr->next;
     }
     return curr;
 }

 ListNode* MyLinkedList::getTail() {
     ListNode* curr = head;
     while (curr && curr->next) {
         curr = curr->next;
     }
     return curr;
 }

int MyLinkedList::get(int index) {
    ListNode* n = getNode(index);
    return n ? n->val : -1;
 }

void MyLinkedList::addAtHead(int val) {
    ListNode* n = new ListNode(val);
    n->next = head;
    head = n;
}

void MyLinkedList::addAtIndex(int index, int val) {
    if (index == 0) {
        addAtHead(val);
        return;
    }

    ListNode* prev = getNode(index - 1);
    if (prev == nullptr) {
        return;
    }
    ListNode* n = new ListNode(val);
    n->next = prev->next;
    prev->next = n;
}

void MyLinkedList::addAtTail(int val) {
    if (head == nullptr) {
        addAtHead(val);
        return;
    }

    ListNode* n = new ListNode(val);
    ListNode* tail = getTail();
    tail->next = n;
}

void MyLinkedList::deleteAtIndex(int index) {
    ListNode* curr = getNode(index);
    if (curr == nullptr) {
        return;
    }
    
    ListNode* next = curr->next;
    if (index == 0) {
        head = next;
    } else {
        ListNode* prev = getNode(index - 1);
        prev->next = next;
    }

    delete curr;
}

ListNode* reverseList(ListNode* head) {
    if (head == nullptr) {
        return head;
    }

    ListNode* currHead = head;
    while (head->next) {
        ListNode* p = head->next;
        head->next = p->next;
        p->next = currHead;
        currHead = p;
    }

    return currHead;
}

ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* tail = head, *newTail = head, *newHead = nullptr;
    int len = 1;
    while (tail->next) {
        len++;
        tail = tail->next;
    }
    tail->next = head; // connect tail to head

    int n = len - k % len - 1;
    while (n) {
        n--;
        newTail = newTail->next;
    }
    newHead = newTail->next;
    newTail->next = nullptr;
    return newHead;
}

bool palindromeListCheck(ListNode* head) {
    static ListNode* frontNode = head;
    if (head) {
        if (!palindromeListCheck(head->next)) {
            return false;
        }
        if (frontNode->val != head->val) {
            return false;
        }
        frontNode = frontNode->next;
    }
    return true;
}

// floyd's hare and tortoise
ListNode* findCycleStart(ListNode* head) {
    ListNode* r1 = head, *r2 = head;
    ListNode* p1 = head, *p2 = nullptr;

    // 1st go to  meet in the circle
    while (r1 && r2 && r2->next) {
        r1 = r1->next;
        r2 = r2->next->next;
        if (r1 == r2) {
            p2 = r1;
            break;
        }
    }

    if (p2 == nullptr) {
        return p2; // no cycle found
    }

    // 2nd go to meet int the entry node
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
}

void testList() {
    MyLinkedList lst;
    lst.addAtHead(5);
    lst.addAtHead(4);
    lst.addAtHead(3);
    lst.addAtHead(2);
    lst.addAtHead(1);

    ListNode* tail = lst.getTail();
    ListNode* n = lst.getNode(2);
    tail->next = n;

    ListNode* head = lst.getHead();
    //printList(head);
    //ListNode* rhead = reverseList(head);
    ListNode* entry = findCycleStart(head);
    printf("Cycle start is %d\n", entry->val);
}


