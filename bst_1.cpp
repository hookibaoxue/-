// 二叉搜索树 C++ 实现
#include <iostream>
using namespace std;

#include <queue>

struct tree_node{
	int data;
	tree_node * left_node;
	tree_node * right_node;
};

tree_node * get_new_node(int data){
	tree_node * temp = new tree_node();//new带括号，创建时会初始化
	temp->data = data;
	temp->left_node = NULL;
	temp->right_node = NULL;
	return temp;
}

tree_node * tree_insert_node(tree_node * root, int data){
	if (root == NULL)
		root = get_new_node(data);
	else if (data <= root->data)
		root->left_node = tree_insert_node(root->left_node, data);
	else
		root->right_node = tree_insert_node(root->right_node, data);

	return root;
}

bool search_for_node(tree_node * root, int search_num){
	if (root == NULL)
		return false;
	if (root->data == search_num)
		return true;
	else if (search_num <= root->data)
		return search_for_node(root->left_node, search_num);
	else
		return search_for_node(root->right_node, search_num);
}

//最小值，查找树最左的值left_node  最大值则是反过来，查找树最右的值right_node
// 查找迭代实现
int find_min_num_iteration(tree_node * root){
	if (root == NULL)
	{
		cout<<"this tree is empty!"<<endl;
		return -1;
	}

	while (root->left_node != NULL)
		root = root->left_node;
	
	return root->data;
}

//查找递归实现
int find_min_num_recursion(tree_node * root){
	if (root == NULL)
		cout<<"this tree is empty!"<<endl;
		return -1;

	if(root->left_node == NULL)
		return root->data;
	
	return find_min_num_recursion(root->left_node);
}

// 树的高度
int find_tree_height(tree_node * root){
	if (root == NULL)
		return -1;

	return (max(find_tree_height(root->left_node), find_tree_height(root->right_node)) + 1);
}

// 树的层次遍历
void level_order(tree_node * root){
	queue<tree_node *> queue_obj;
	if (root == NULL)
		return;

	//借助队列先进先出的特点，先发现的节点压入队列，再将其子节点压入队列（子节点出队前，将子节点的子节点压入队列），这样就有了层次顺序
	queue_obj.push(root); //根节点压入队列
	while (!queue_obj.empty()){
		tree_node * temp_node = queue_obj.front();//获得当前队列，队首元素节点
		cout<<temp_node->data<<" ";
		if (temp_node->left_node != NULL)
			queue_obj.push(temp_node->left_node);//如果当前节点有左节点将其压入队列
		if (temp_node->right_node != NULL)
			queue_obj.push(temp_node->right_node);//如果当前节点有右节点将其压入队列

		queue_obj.pop();//将队首节点移出队列
	}

	cout<<endl;
}

//判断树是否是二叉搜索树
//判断左子树是否比该节点值小
bool bst_left_check(tree_node * root, int value){
	if (root == NULL)
		return true;

	bool ret = (root->data <= value) && bst_left_check(root->left_node, value) && bst_left_check(root->right_node, value);
	if (ret)
		return true;
	else
		return false;
}

//判断右子树是否比该节点值大
bool bst_right_check(tree_node * root, int value){
	if (root == NULL)
		return true;

	bool ret = (root->data > value) && bst_right_check(root->left_node, value) && bst_right_check(root->right_node, value);
	if (ret)
		return true;
	else
		return false;	
}

bool is_bst_check(tree_node * root){
	if (root == NULL)
		return true;
	
	bool ret = is_bst_check(root->left_node) && is_bst_check(root->right_node) && bst_left_check(root->left_node, root->data) && bst_right_check(root->right_node, root->data);
	if (ret)
		return true;
	else
		return false;	
}

//二叉树判断改进版本1（利用二叉搜索树特性，节点的左节点数值比节点小（可能相等），节点的右节点数值比节点大（可能相等），判断左子树和右子树都是是bst，整颗数都是bst，利用递归处理）
bool bst_check(tree_node * root, int minvalue, int maxvalue){
	if (root == NULL)
		return true;

	if (root->data < minvalue || root->data > maxvalue )
		return false;
	
	return bst_check(root->left_node, minvalue, root->data) && bst_check(root->right_node, root->data, maxvalue);
}

bool is_bst_check_better(tree_node * root){
	if (root == NULL)
		return true;

	return bst_check(root, INT_MIN, INT_MAX);
}

// 二叉搜索树改进版本2（bst特性节点数值是排序好的，利用中序遍历，判断当前节点与前一个节点的值，当前节点的值必须要比前节点的值要大）
//中序遍历
bool inorder_node(tree_node *root, tree_node *pre_ptr){
	if (root == NULL)
		return INT_MIN;
	
	if(!inorder_node(root->left_node, pre_ptr))
		return false;

	if (pre_ptr != nullptr && root->data < pre_ptr->data)
	{
		return false;
	}
	
	pre_ptr = root;
	return inorder_node(root->right_node, pre_ptr);
}

bool check_inorder_bst(tree_node *root){
	bool ret = inorder_node(root, nullptr);
	cout<<" ret is :";
	return ret;
}

// 删除节点
/*
1.删除的节点是叶子节点  父节点移除叶子节点引用，并将该叶子节点在内存中释放
2.删除的节点只有一个子树 父节点的指向修改成将该节点的子树节点 并将该节点在内存中释放
3.删除的节点有左右子树  通过找到该节点的右子树中最小值节点(或：左子树的最大值)，
	将该节点的数据修改最小值节点数据。这样操作将删除节点的场景变为了1 或者 2.依照1 或 2的删除节点方式处理重复节点即可
*/

tree_node * find_min_node(tree_node * root){
	if (root == nullptr)
		return root;

	while (root->left_node != nullptr)
		root = root->left_node;
	
	return root;
}

tree_node * delete_node(tree_node * root, int num){
	if (root == nullptr) return root;

	if (root->data == num)
	{
		//场景1
		if (root->left_node == nullptr && root->right_node == nullptr)
		{
			delete(root);
			root = nullptr;
		}
		//场景2
		else if (root->left_node == nullptr)
		{
			tree_node * temp = root;
			root = root->right_node;
			delete(temp);
		}
		else if (root->right_node == nullptr)
		{
			tree_node * temp = root;
			root = root->left_node;
			delete(temp);
		}
		//场景3
		else
		{
			tree_node * min_temp = find_min_node(root->right_node);// 右子树最小节点
			root->data = min_temp->data;// 赋值修改节点数据
			root->right_node = delete_node(root->right_node, min_temp->data);
		}
	}
	else if (root->data > num)
	{
		root->left_node = delete_node(root->left_node, num);
	}
	else
	{
		root->right_node = delete_node(root->right_node, num);
	}

	return root;
}

// 中序遍历(前中后的区别，以根节点所处位置计算，根左右:前序遍历, 左根右:中序遍历  左右根:后序遍历)
void print_inorder(tree_node * root){
	if (root == nullptr)
		return;

	print_inorder(root->left_node);
	cout<<" "<<root->data;
	print_inorder(root->right_node);
}

int main(){
	tree_node * TREE_ROOT = NULL;
	int a[] = {10, 20, 3, 11, 12, 6, 5, 121, 11, 11};
	int length = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < length; i++)
	{
		TREE_ROOT = tree_insert_node(TREE_ROOT, a[i]);
	}
	
	while (true)
	{
		int num;
		cout<<"please cin your number:";
		cin>>num;
		cout<<"search for your number result is:"<<search_for_node(TREE_ROOT, num)<<endl;
		cout<<"iteration min num is:"<<find_min_num_iteration(TREE_ROOT)<<endl;
		cout<<"recursion min num is:"<<find_min_num_recursion(TREE_ROOT)<<endl;
		cout<<"tree height is:"<<find_tree_height(TREE_ROOT)<<endl;
		level_order(TREE_ROOT);

		cout<<"tree is bst:?"<<is_bst_check(TREE_ROOT)<<endl;
		cout<<"better func tree is bst:?"<<is_bst_check_better(TREE_ROOT)<<endl;
		cout<<"better 2 func tree is bst:?"<<check_inorder_bst(TREE_ROOT)<<endl;
		cout<<endl;
	
		print_inorder(TREE_ROOT);
		cout<<endl;
		cout<<"delete node num:"<<delete_node(TREE_ROOT, 11)<<endl;
		print_inorder(TREE_ROOT);
		cout<<endl;
		
		cout<<"Do you need to continue searching? 0:not  1:yes"<<endl;
		int flag;
		cin>>flag;
		if (flag != 1)
			break;
	}

	return 0;
}
