#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//���ȶ���һ������ڵ�ṹ����ʾÿ����
//���嵥�
struct ShoppingItem {
    char name[50]; // ��Ʒ����
    int quantity; // ��Ʒ����
    struct ShoppingItem* next;//ָ����һ���ڵ�ָ��
};
//����һ������ͷָ�룬��ʾ�����嵥����ʼ�㣺
struct ShoppingItem* shoppingList = NULL; // ��ʼ�������嵥Ϊ��
//
//1. �����Ʒ�������嵥��
void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    struct ShoppingItem* p=shoppingList;
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;
    if (shoppingList == NULL)
    {
        shoppingList = newItem;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newItem;
    }
}

//2. �ӹ����嵥���Ƴ���Ʒ��
void removeItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (previous != NULL) {
                previous->next = current->next;
            }
            else {
                shoppingList = current->next;
            }
            free(current);
            break;
        }
        /*�˴���д���У�*/
        previous = current;
        current = current->next;
    }
}

//3. �鿴�����嵥��
void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("�����嵥:\n");
    while (current != NULL) {
        printf("%s - ������%d\n", current->name, current->quantity);
        current = current->next;
    }
}

//4. �޸Ĺ����嵥����Ʒ��������
void updateQuantity(char itemName[], int newItemQuantity) {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            current->quantity=newItemQuantity;
                break;
        }
        current = current->next;
    }
}

//5. ��չ����嵥��
void clearList() {
    while (shoppingList != NULL) {
        /*�˴���д���䡣*/
        struct ShoppingItem* temp = shoppingList;
        shoppingList = shoppingList->next;
            free(temp);
    }
}

//6. ���㹺���嵥����Ʒ����������
int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL) {
        /*�˴���д���䣻*/
        current = current->next;
        total++;
    }
    return total;
}

//7. ���ҹ����嵥�е���Ʒ��
void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" ��\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - ������%d\n", current->name, current->quantity);
            return;
        }
        /*�˴���дһ�䡣*/
        current = current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

//8. �������嵥��
void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL) {
        nextItem = current->next;
        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                // ������Ʒ��Ϣ
               /* �˴���д 3 �䣻*/
                strcpy(tempName, current->name);
                strcpy(current->name, nextItem->name);
                strcpy(nextItem->name, tempName);
                    tempQuantity = current->quantity;
                current->quantity = nextItem->quantity;
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

//9. �ϲ������嵥��
//��������������ͬ�Ĺ����嵥����ϣ�������Ǻϲ���һ����
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
    struct ShoppingItem* current = *list1;
    /*���Ա����ʽ�洢�ṹ������ϰ��*/
        // ��������һ�������嵥��ĩβ
        /*����ѭ����䣻*/
    while (current != NULL)
    {
        current = current->next;
    }
        // ���ڶ��������嵥���ӵ���һ���嵥��ĩβ
        current->next = *list2;
    *list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

//10. ɾ�������嵥�е���Ʒ��
//ʵ��һ�����������Ը�����Ʒ����ɾ�������嵥�е���Ʒ�����ж����ͬ���Ƶ���Ʒ��
//����ѡ��ɾ������һ����ȫ����
void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // ���Ҫɾ�����ǵ�һ���ڵ�
                struct ShoppingItem* temp = shoppingList;
                /*��дһ�䣻*/
                shoppingList = shoppingList->next;
                    free(temp);
                if (!deleteAll) break;
            }
            else {
                // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
                /*��дһ�䣻*/
                prev->next = current->next;
                    free(current);
                current = prev->next;
                if (!deleteAll) break;
            }
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}
int main()
{
    char name[50];
    int num;
    printf("�������������Ʒ\n");
    for (int i = 0; i < 2; i++)
    {
        scanf("%s %d", &name, &num);
        addItem(name, num);
    }
    printf("����ѡ��:");
    int swch;
    scanf("%d", &swch);
    if (swch == 1)
    {
        //1.�����Ʒ+3.չʾ�����嵥
        for (int i = 0; i < 2; i++)
        {
            scanf("%s %d", &name, &num);
            addItem(name, num);
        }
        displayList();
    }
    if (swch == 2)
    {
        //2.ɾ����Ʒ+չʾ�����嵥
        char dename[50];
        scanf("%s", &dename);
        removeItem(dename);
        displayList();
    }
    if (swch == 4)
    {
        //4.�޸���Ʒ������
        char changename[50];
        int cnum;
        scanf("%s %d", &changename, &cnum);
        updateQuantity(changename, cnum);
        displayList();
    }
    if (swch == 5)
    {
        //5.��չ����嵥
        clearList();
        displayList();
    }
    if (swch == 6)
    {
        //6.������Ʒ������
        totalQuantity();
    }
    if (swch == 7)
    {
        char fname[50];
        scanf("%s", &fname);
        findItem(fname);
    }
    if (swch == 8)
    {
        sortList();
        displayList();
    }
}