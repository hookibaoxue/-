// 队列
#include <iostream>
using namespace std;

//////////////////数组实现start/////////////////////////
#define MAXSIZE 10
int QUEUE[MAXSIZE] = {};//队列
int FRONT = -1, REAR = -1;
bool queue_is_empty()
{
    if (FRONT == -1 && REAR == -1)
        return true;
    else    
        return false;
};
bool queue_is_full()
{
    return ((REAR + 1) % MAXSIZE == FRONT);
};

void push_ele(int num)
{
    if (queue_is_full())
        return;
    
    if (FRONT == -1 && REAR == -1)
    {
        FRONT = REAR = (REAR + 1) % MAXSIZE;
    }
    else
        REAR = (REAR + 1) % MAXSIZE;
    
    QUEUE[REAR] = num;
};

int pop_ele()
{
    int temp = 0;
    if (queue_is_empty())
    {
        return temp;
    }
    if (FRONT == REAR)
    {
        temp = QUEUE[FRONT];
        FRONT = REAR = -1;
    }
    else
    {
        temp = QUEUE[FRONT];
        FRONT = (FRONT + 1) % MAXSIZE;
    }

    return temp;
};

////////////////////数组实现end/////////////////////////////

struct queue_node
{
    int data;
    queue_node * next;
};
queue_node * front = NULL;
queue_node * rear = NULL;
void enable_enum(int num)
{
    queue_node * temp = new queue_node;
    temp->data = num;
    temp->next = NULL;

    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
};

void deable_enum()
{
    if (front == NULL)
        return;
    else
    {
        queue_node * temp = front;
        front = front->next;
        delete(temp);
    }
};

queue_node * get_front()
{
    return front;
};

bool list_queue_is_empty()
{
    return (front == NULL && rear == NULL);
};

void Print(queue_node *head){
    if (head != NULL){
        cout << "链表拥有数据:"<<" ";
        queue_node * temp = head;
        while (temp != NULL)
        {
            cout <<temp->data<<" ";
            temp = temp->next;
        }

        cout << endl;
    }
};

int main()
{

    // 数组队列测试
    for (int i = 0; i < MAXSIZE + 1; i++)
    {
        int temp_num = i + 1;
        push_ele(temp_num);
    }
    for (int i = FRONT; i < MAXSIZE; i++)
    {
        cout <<QUEUE[i]<<" ";
    }
    cout<<endl;
    pop_ele();
    pop_ele();
    for (int i = FRONT; i < MAXSIZE; i++)
    {
        cout <<"i:"<<i<<" "<<QUEUE[i]<<" ";
    }
    // // 链表队列测试
    // enable_enum(10);
    // enable_enum(20);
    // enable_enum(40);
    // enable_enum(50);
    // Print(front);
    // deable_enum();
    // Print(front);
    // deable_enum();
    // Print(front);
    // cout<<get_front()->data<<endl;
    // cout<<list_queue_is_empty()<<endl;
    return 0;
}