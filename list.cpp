#include <iostream>
struct node
{
    node* next;//8
    int data; //4
};

void Print(node *head){
    if (head != NULL){
        std::cout << "链表拥有数据:"<<" ";
        node * temp = head;
        while (temp != NULL)
        {
            std::cout <<temp->data<<" ";
            temp = temp->next;
        }

        std::cout << std::endl;
    }
};

// 头节点插入
void head_Insert(node**head, int num){
    node * temp = new node;
    temp->data = num;
    temp->next = NULL;
    if (*head != NULL){
        temp->next = *head;
    }
    *head = temp;
};

// 任意插入节点（pos没有做边际检查）
void Insert(node**head, int num, int pos){
    node * temp = new node;
    temp->data = num;
    temp->next = NULL;
    if(pos == 1){
        temp->next = *head;
        *head = temp;
        return;
    }

    node * temp2 = *head;
    for (int i = 0; i < pos-2; i++)
    {
        temp2 = temp2->next;//将temp2指针指向需要插入的位置处
    }

    temp->next = temp2->next;
    temp2->next = temp;
};

// 迭代反转
void Reverse(node** head){
    node *current, *pre, *next;
    current = *head;
    pre = NULL;
    next = NULL;
    while (current != NULL)
    {
        next = current->next;//记录下一个节点
        current->next = pre;//将当前节点的 下一个节点指针指向前一个节点
        pre = current;//记录当前节点
        current = next;// 将当前节点指针 移动到 下一个节点
    }

    *head = pre;
};

// 递归反转
void re_Reverse(node** head, node *p){
    if (p->next == NULL){
        *head = p;  // 改变头指针的指向地址
        return; 
    }

    re_Reverse(&(*head), p->next);

    //反转操作
    node * ptr = p->next;   //取当前节点的下一个节点
    ptr->next = p;// 当前节点的下一个节点 的 next指针指向当前节点
    p->next = NULL;  //当前节点的next指针指向NULL
};

// 1   2    3

//链表删除节点
void delete_node(node ** list, int pos){
    node * temp = *list;
    if (pos == 1)
    {
        *list = temp->next;
        delete(temp);
        return;
    }
    for (int i = 0; i < pos - 2; i++){
        temp = temp->next;
    }
    node * temp2 = temp->next;
    temp->next = temp2->next;
    delete(temp2);
}

void print_node_size(node ** list)
{
    int size = 0;
    node * temp = *list;
    while (temp != NULL)
    {
        size = size + sizeof((*(*list)));
        temp = temp->next;
    }
    std::cout<<"链表占用字节数:"<<size<<std::endl;
}

//双向链表实现
struct pnode
{
    int data;
    pnode *pre;
    pnode *next;
};
pnode *get_newnode(int num)
{
    pnode *newnode = new pnode;
    newnode->data = num;
    newnode->pre = NULL;
    newnode->next = NULL;
};




int main(){
    std::cout<<"int占用字节数:"<<sizeof(int)<<std::endl;
    std::cout<<"节点占用字节数:"<<sizeof(node)<<std::endl;

    node* head = NULL;
    Insert(&head, 100, 1);
    Insert(&head, 101, 1);
    Insert(&head, 102, 2);
    Insert(&head, 103, 1);
    Insert(&head, 104, 3);
    Print(head);
    print_node_size(&head);

    delete_node(&head, 1);
    Print(head);
    print_node_size(&head);

    Reverse(&head);
    Print(head);
    print_node_size(&head);

    re_Reverse(&head, head);
    Print(head);
    print_node_size(&head);

    return 0;
}

/* 头节点插入


int main() {
    node* head = NULL;
    int number, loop;
    std::cout << "输入链表大小:"<< std::endl;
    std::cin>> number;
    for (loop = 0; loop < number; loop++){
        int num;
        std::cout << "输入数值:"<< std::endl;
        std::cin>> num;
        Insert(&head, num);
        Print(head);
    }
    return 0;
}
头节点插入*/