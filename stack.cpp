#include <iostream>
#define MAX_SIZE 11
int array[MAX_SIZE];
int TOP = -1;
void ele_push(char str)
{
    int next_pos = TOP + 1;
    while (array[next_pos] != 0)
    {
        next_pos = next_pos + 1;
    };
    
    
    if (next_pos > MAX_SIZE)
    {
        return;
    };


    array[next_pos] = str;
    TOP = next_pos;
}

char ele_pop()
{
    char ret = ' ';
    if (TOP <= -1)
    {
        return ret;
    };
    
    ret = array[TOP];
    TOP = TOP - 1;
    return ret;
}

void str_print()
{
    // int len = sizeof(array)/sizeof(*array);
    std::cout<<"字符串内容:"<<std::endl;
    for (int i = 0; i < TOP; i++)
    {
        std::cout.put(array[i]);
    };
    std::cout<<std::endl;
};

int main()
{
    char strs[] = { '{', '(', '(', ')',  '(',')', ')', '}'};
    int len = sizeof(strs)/sizeof(*strs);
    for (int i = 0; i <= len; i++)
    {
        if (strs[i] == '{' || strs[i] == '(')
        {
            ele_push(strs[i]);
        }
        else if (strs[i] == '}' || strs[i] == ')')
        {
            if (ele_pop() == '{')
            {
                if (strs[i] != '}')
                {
                    std::cout<<"匹配错误"<<std::endl;
                    return 0;
                }
                
            }
            else if (ele_pop() == '(')
            {
                if (strs[i] != ')')
                {
                    std::cout<<"匹配错误"<<std::endl;
                    return 0;
                }
            }
        };
    }
std::cout<<"匹配成功"<<std::endl;
    str_print();

    ele_pop();
    str_print();

    return 0;
}