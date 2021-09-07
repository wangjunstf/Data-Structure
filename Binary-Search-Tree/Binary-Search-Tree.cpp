#include <iostream>
#include <vector>
#include <stack>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode() : val(0), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct BinaryTree   // 二叉树
{
    TreeNode *root;
};

TreeNode *treeBuild(vector<int> &tab, int &index, TreeNode *parent)
{
    TreeNode *root = nullptr;
    if(index<tab.size() && tab[index]!=0){
        root = new TreeNode(tab[index]);
        root->parent = parent;
        root->left = treeBuild(tab, ++index,root);
        root->right = treeBuild(tab, ++index,root);
    }
    return root;
}


TreeNode *treeSearch(TreeNode *tree, int k)
{
    if (tree->val == k || tree == nullptr)
    {
        return tree;
    }
    if (k < tree->val)
    { // k 小于根节点，说明 k 只可能在左子树上，递归搜索左子树
        return treeSearch(tree->left, k);
    }
    else
    {
        return treeSearch(tree->right, k);
    }
}


void inorder(TreeNode *tree)
{
    if (tree == nullptr){
        return;
    }
    inorder(tree->left);
    cout << tree->val << " ";
    inorder(tree->right);
}

// 获取二叉查找树最小值
TreeNode *treeMinimum(TreeNode *tree)
{
    while (tree->left != nullptr)
    {
        tree = tree->left;
    }
    return tree;
}

TreeNode *treeMaxmum(TreeNode *tree)
{
    while (tree->right != nullptr)
    {
        tree = tree->right;
    }
    return tree;
}

TreeNode *treeSuccessor(TreeNode *tree)
{
    if (tree->right != nullptr)
    {
        return treeMinimum(tree->right);
    }
    TreeNode *y = tree->parent;
    //cout << "y->val: " << y->val << endl;
    while (y != nullptr && tree == y->right)
    {
        tree = y;
        y = y->parent;
        //cout <<"y->val: "<<y->val<<endl;
    }
    return y;
}

TreeNode *treePredecessor(TreeNode *tree)
{
    if (tree->left != nullptr)
    {
        return treeMaxmum(tree->left);
    }
    TreeNode *y = tree->parent;
    while (y != nullptr && y->left != tree)
    {
        tree = y;
        y = y->parent;
    }
    return y;
}

void treeInsert(TreeNode *root, TreeNode *z)
{
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while (x != nullptr)
    {
        y = x;
        if (z->val < x->val)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr) // 如果树为空树
        root = z;
    else if (z->val < y->val)
        y->left = z;
    else
        y->right = z;
}

void transplant(BinaryTree *T, TreeNode *u, TreeNode *v)
{
    // 用 v 子树来替换 u 子树，该函数允许 v 为空的情况
    if (u->parent == nullptr){
        // 处理 u 是 T 的树根的情况
        //root = v;
        T->root =v;
    } else if (u == u->parent->left)
    { // 如果 u 为右孩子
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != nullptr)
    {
        v->parent = u->parent;
    }
}

void treeDelete(BinaryTree *T, TreeNode *z)
{
    TreeNode *y = nullptr;
    if(z->left==nullptr)
        transplant(T,z,z->right);
    else if(z->right==nullptr)
        transplant(T,z,z->left);
    else {
        y = treeMinimum(z->right);
        if(y->parent!=z){
            transplant(T,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T,z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    z->left=nullptr;
    z->right=nullptr;
    z->parent=nullptr;
}




int main(){
    vector<int>tab{15,6,3,2,0,0,4,0,0,7,0,13,9,0,0,0,18,17,0,0,20,0,0};
    int index=0;
    BinaryTree *T = new BinaryTree;
    T->root = treeBuild(tab,index,nullptr);
    cout<<"原二叉搜索树(中序遍历)：";
    inorder(T->root);
    cout<<endl;
    // cout<<"maxmum: "<<treeMaxmum(T->root)->val<<endl;
    // cout << "minimum: " << treeMinimum(T->root)->val << endl;
    // int num = 15;
    // TreeNode *p = treeSearch(T->root,num);
    // cout << num << " 的前驱: " << treePredecessor(p)->val << endl;
    // cout << num << " 的后继: " << treeSuccessor(p)->val<<endl;

    
    TreeNode *pdel1 = treeSearch(T->root, 6);
    TreeNode *pdel2 = treeSearch(T->root, 18);
    TreeNode *pdel3 = treeSearch(T->root, 15);

    cout << "删除节点6 ";
    treeDelete(T,pdel1);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    cout << "删除节点18 " ;
    treeDelete(T, pdel2);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    cout << "删除节点15 ";
    treeDelete(T, pdel3);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    cout << "插入节点15 ";
    treeInsert(T->root, pdel3);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    cout << "插入节点18 ";
    treeInsert(T->root, pdel2);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    cout << "插入节点6 ";
    treeInsert(T->root, pdel1);
    cout << "中序遍历：";
    inorder(T->root);
    cout << endl;

    return 0;
}