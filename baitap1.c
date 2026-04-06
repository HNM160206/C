#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct File {
    char name[50];
    float size;   
    long time;    
} File;

typedef struct Node {
    File data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

void init(List* L) {
    L->head = NULL;
}

Node* createNode(File f) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = f;
    p->next = NULL;
    return p;
}

void insertSorted(List* L, File f) {
    Node* p = createNode(f);

    if (L->head == NULL || f.time < L->head->data.time) {
        p->next = L->head;
        L->head = p;
        return;
    }

    Node* cur = L->head;
    while (cur->next != NULL && cur->next->data.time < f.time) {
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;
}

File inputFile() {
    File f;
    printf("Nhap ten file: ");
    scanf("%s", f.name);

    printf("Nhap kich thuoc (GB): ");
    scanf("%f", &f.size);

    printf("Nhap thoi gian: ");
    scanf("%ld", &f.time);

    return f;
}

void display(List L) {
    Node* p = L.head;

    if (p == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\nDanh sach file:\n");
    while (p != NULL) {
        printf("%s | %.2f GB | time: %ld\n",
               p->data.name, p->data.size, p->data.time);
        p = p->next;
    }
}

float totalSize(List L) {
    float sum = 0;
    Node* p = L.head;

    while (p != NULL) {
        sum += p->data.size;
        p = p->next;
    }

    return sum;
}

Node* findMinNode(List L) {
    Node* p = L.head;
    Node* min = p;

    while (p != NULL) {
        if (p->data.size < min->data.size) {
            min = p;
        }
        p = p->next;
    }
    return min;
}

void deleteNode(List* L, Node* target) {
    if (L->head == NULL || target == NULL) return;
    if (L->head == target) {
        Node* tmp = L->head;
        L->head = L->head->next;
        free(tmp);
        return;
    }

    Node* prev = L->head;
    while (prev->next != NULL && prev->next != target) {
        prev = prev->next;
    }

    if (prev->next == target) {
        prev->next = target->next;
        free(target);
    }
}

void fitToUSB(List* L) {
    float sum = totalSize(*L);

    printf("\nTong ban dau: %.2f GB\n", sum);

    while (sum > 32) {
        Node* minNode = findMinNode(*L);

        printf("Loai bo: %s (%.2f GB)\n",
               minNode->data.name, minNode->data.size);

        sum -= minNode->data.size;
        deleteNode(L, minNode);
    }

    printf("\nDanh sach sau khi xu ly:\n");
    display(*L);
    printf("Tong cuoi: %.2f GB\n", sum);
}

void menu() {
    printf("\n===== MENU =====\n");
    printf("1. Them file\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tong dung luong\n");
    printf("4. Xu ly USB 32GB (xoa file nho nhat)\n");
    printf("0. Thoat\n");
    printf("Chon: ");
}

int main() {
    List L;
    init(&L);

    int choice;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                File f = inputFile();
                insertSorted(&L, f);
                break;
            }
            case 2:
                display(L);
                break;
            case 3:
                printf("Tong dung luong: %.2f GB\n", totalSize(L));
                break;
            case 4:
                fitToUSB(&L);
                break;
            case 0:
                printf("Thoat!\n");
                break;
            default:
                printf("Sai lua chon!\n");
        }

    } while (choice != 0);

    return 0;
}