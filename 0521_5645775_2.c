#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

typedef struct listNode {
    char data[MAX_NAME_LENGTH];
    struct listNode* link;
} ListNode;

ListNode* insert_last(ListNode* head, char* value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return head;
    }
    strcpy(p->data, value);
    p->link = NULL;

    if (head == NULL) {
        return p;
    }

    ListNode* temp = head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = p;
    return head;
}

ListNode* delete_node(ListNode* head, char* value, ListNode** deleted) {
    ListNode* current = head;
    ListNode* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            if (previous == NULL) {
                head = current->link;
            }
            else {
                previous->link = current->link;
            }

            ListNode* deleted_node = (ListNode*)malloc(sizeof(ListNode));
            if (deleted_node == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return head;
            }
            strcpy(deleted_node->data, current->data);
            deleted_node->link = *deleted;
            *deleted = deleted_node;

            free(current); 
            printf("%s가 리스트에서 삭제되었습니다.\n", value);
            return head;
        }
        previous = current;
        current = current->link;
    }
    printf("해당 과일이 리스트에 없습니다.\n");
    return head;
}

void print_list(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int search_list(ListNode* head, char* value) {
    ListNode* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data, value) == 0) {
            return 1;
        }
        temp = temp->link;
    }
    return 0;
}

void remove_deleted(ListNode** head, char* value) {
    ListNode* current = *head;
    ListNode* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            if (previous == NULL) {
                *head = current->link;
            }
            else {
                previous->link = current->link;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->link;
    }
}

void print_menu() {
    printf("\n메뉴:\n");
    printf("1. 리스트의 매 마지막에 새로운 과일 추가\n");
    printf("2. 리스트에 있는 과일을 삭제\n");
    printf("3. 삭제된 과일 목록 출력\n");
    printf("4. 종료\n");
}

int main() {
    ListNode* head = NULL;
    ListNode* deleted = NULL;
    char initial_fruits[10][MAX_NAME_LENGTH] = {
        "Mango", "Orange", "Apple", "Grape", "Cherry",
        "Plum", "Guava", "Raspberry", "Banana", "Peach"
    };

    for (int i = 0; i < 10; i++) {
        head = insert_last(head, initial_fruits[i]);
    }

    int choice;
    char fruit[MAX_NAME_LENGTH];

    while (1) {
        print_menu();
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
        case 1:
            printf("추가할 과일을 입력하세요: ");
            fgets(fruit, MAX_NAME_LENGTH, stdin);
            fruit[strcspn(fruit, "\n")] = '\0';

            if (search_list(head, fruit)) {
                printf("해당 과일이 이미 존재합니다.\n");
            }
            else {
                head = insert_last(head, fruit);
                printf("%s가 리스트에 추가되었습니다.\n", fruit);
                remove_deleted(&deleted, fruit);
            }
            break;
        case 2:
            printf("삭제할 과일을 입력하세요: ");
            fgets(fruit, MAX_NAME_LENGTH, stdin);
            fruit[strcspn(fruit, "\n")] = '\0';

            head = delete_node(head, fruit, &deleted);
            break;
        case 3:
            printf("삭제된 과일 목록: ");
            print_list(deleted);
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }

    return 0;
}
