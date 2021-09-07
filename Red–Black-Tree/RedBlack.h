/**
 * c++ 红黑树声明
 * @author 编程之禅 根据《算法导论》伪代码实现
 * @date 2021年9月4日
 * RBTREE 红黑树对象
 * RBTree 红黑树及操作对象
*/

#ifndef _RBTree_H_
#define _RBTree_H_

#include <vector>
#include <iostream>
#include <utility>
using namespace std;

enum E_COLOR
{
    BLACK,
    RED
};

struct RBTREE ;

struct TreeNode
{
    int key;
    E_COLOR color;
    TreeNode *left;
    TreeNode *right;
    TreeNode *p;

    TreeNode(E_COLOR c):color(c) {}
    TreeNode(int x) : key(x) {}
    TreeNode(int x, E_COLOR c, TreeNode *T) : key(x), left(T), right(T), p(T), color(c) {}
};

struct RBTREE
{
    TreeNode *root; // 红黑树头节点
    TreeNode *NIL;
};

class RBTree{
public:
    RBTREE *T;                  // 红黑树对象
    RBTree():T(nullptr){};      // 默认构造函数

    // 使用中序遍历构造红黑树，vector的元素为 pair 类型（键值对），key 为元素值，value 为 红黑值
    RBTree(vector<pair<int,E_COLOR>> &inorder); 

    void preOrder(TreeNode *root);                      // 前序遍历二叉树
    void inOrder(TreeNode *root);                       // 中序遍历二叉树
    TreeNode *search(RBTREE *T,TreeNode *tree, int k);
    TreeNode *minimum(RBTREE *T,TreeNode *tree);
    TreeNode *maximum(RBTREE *T,TreeNode *tree);
    TreeNode *successor(RBTREE *T, TreeNode *tree);
    TreeNode *predecessor(RBTREE *T, TreeNode *tree);
    void leftRotate(RBTREE *T, TreeNode *x);            // 左旋
    void rightRotate(RBTREE *T, TreeNode *x);           // 右旋
    void insert(RBTREE *T, TreeNode *z);
    void insertFixup(RBTREE *T, TreeNode *z);
    void transplant(RBTREE *T,TreeNode *u,TreeNode *v); // 使用 v 子树来替换 u子树，u不变
    void remove(RBTREE *T, TreeNode *z);                // 删除元素
    void removeFixup(RBTREE *T, TreeNode *x);

    ~RBTree(){};
private:
    TreeNode *rbBuild(RBTREE *T,vector<pair<int, E_COLOR>> &inorder, int &index, TreeNode *p);
};


RBTree::RBTree(vector<pair<int, E_COLOR>> &inorder)
{
    /**
     * inorder 为中序遍历结果
     * 调用 rbBuild 构造红黑树
    */
    T = new RBTREE;
    T->NIL = new TreeNode(BLACK);
    int index = 0;
    T->root = rbBuild(T,inorder, index, T->NIL);
    T->root->p = T->NIL;
}

TreeNode* 
RBTree::rbBuild(RBTREE *T,vector<pair<int, E_COLOR>> &inorder, int &index, TreeNode *p)
{
    TreeNode *root = nullptr;
    if(index<inorder.size() && inorder[index].first!=0){
        root = new TreeNode(inorder[index].first,inorder[index].second,T->NIL);
        root->p = p;
        root->left = rbBuild(T,inorder,++index,root);
        root->right = rbBuild(T,inorder, ++index, root);
    }else{
        return T->NIL;
    }
    return root;
}

void 
RBTree::preOrder(TreeNode *root)
{
    if(root!=nullptr && root->key!=0){
        preOrder(root->left);
        //cout << "[" << root->key << "," << root->color << "] ";
        cout << root->key << " ";
        preOrder(root->right);
    }
}

void 
RBTree::inOrder(TreeNode *root)
{
    if (root != nullptr && root->key != 0)
    {
        //cout << "[" << root->key << "," << root->color << "] ";
        cout<<root->key<<" ";
        inOrder(root->left);
        inOrder(root->right);
    }
}

TreeNode* 
RBTree::search(RBTREE *T,TreeNode *tree, int k)
{
    if (tree->key == k || tree == nullptr)
    {
        return tree;
    }
    if (k < tree->key)
    { // k 小于根节点，说明 k 只可能在左子树上，递归搜索左子树
        return search(T,tree->left, k);
    }
    else
    {
        return search(T,tree->right, k);
    }
}

TreeNode *
RBTree::minimum(RBTREE *T,TreeNode *tree)
{
    while (tree->left != T->NIL)
    {
        tree = tree->left;
    }
    return tree;
}

TreeNode *
RBTree::maximum(RBTREE *T,TreeNode *tree)
{
    while (tree->right != T->NIL)
    {
        tree = tree->right;
    }
    return tree;
}

TreeNode *
RBTree::successor(RBTREE *T,TreeNode *tree)
{
    if (tree->right != nullptr)
    {
        return minimum(T,tree->right);
    }
    TreeNode *y = tree->p;
    //cout << "y->val: " << y->val << endl;
    while (y != nullptr && tree == y->right)
    {
        tree = y;
        y = y->p;
        //cout <<"y->val: "<<y->val<<endl;
    }
    return y;
}

TreeNode *
RBTree::predecessor(RBTREE *T,TreeNode *tree)
{
    if (tree->left != nullptr)
    {
        return maximum(T,tree->left);
    }
    TreeNode *y = tree->p;
    while (y != nullptr && y->left != tree)
    {
        tree = y;
        y = y->p;
    }
    return y;
}

void 
RBTree::leftRotate(RBTREE *T, TreeNode *x){
    // 假设 x.right != NIL 且根节点的父节点为 NIL
    TreeNode *y = x->right;  
    x->right = y->left;           // 将 y 的左子树作为 x 的右子树
    if(y->left!=T->NIL){          
        y->left->p = x;
    }
    y->p = x->p;                  // 设置 y 的父节点
    if(x->p==T->NIL)              // 如果 x 为根节点，则将 y 作为根节点
        T->root = y;
    else if (x==x->p->left)       // 否则的话，判断 x 为左节点还是右节点
        x->p->left = y;
    else 
        x->p->right = y;
    y->left = x;                  // 将 x 作为 y 的 左孩子
    x->p = y;                     // 这样就完成了 左旋转，二叉树搜索树的性质不变
}

void 
RBTree::rightRotate(RBTREE *T, TreeNode *x){
    // 假设 x 的左节点不等于 NIL
    TreeNode *y =  x->left;    // y->left 可以作为空节点使用
    x->left = y->right;        // 用 x 的右孩子替代 y 的左孩子
    if(y->right!=T->NIL){
        y->right->p = x;
    }

    if(x->p==T->NIL){
        T->root = y;
    }else if(x->p->left==x){
        x->p->left = y;
    }else{
        x->p->right = y;
    }

    y->right = x;
    x->p = y;

}

void 
RBTree::insert(RBTREE *T, TreeNode *z)
{
    TreeNode *y = T->NIL;
    TreeNode *x = T->root;
    while (x != T->NIL)
    {
        y = x; // 记录父节点
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->p = y;
    if (y == T->NIL)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->color = RED;
    z->left = T->NIL;
    z->right = T->NIL;
    insertFixup(T,z);
}

void 
RBTree::insertFixup(RBTREE *T, TreeNode *z){
    while(z->p->color == RED){
        // 第一大类 z 的父节点作为左孩子
        if(z->p == z->p->p->left){        
            TreeNode *y = z->p->p->right;   // z 的叔节点
            if(y->color==RED){
                // case1: 叔叔节点是红色
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color=RED;
                z = z->p->p;
                continue;
            }

            // case2: 叔叔是黑色 且当且节点是右孩子
            if(z==z->p->right){
                
                z = z->p;
                leftRotate(T,z);
            }

            // case3: 叔叔是黑色，且当亲节点是左孩子
            z->p->color = BLACK;
            z->p->p->color = RED;
            rightRotate(T,z->p->p);
        }else { // 第二大类 z 的父节点作为右孩子
            TreeNode *y = z->p->p->left;

            // case1: 叔叔节点为红色
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
                continue;
            }
            
            // case2: 叔叔节点为黑色 且当前节点是左孩子
            if(z==z->p->left){
                z = z->p;
                rightRotate(T,z);
            }

            // case3: 叔叔节点为黑色 且当前节点是右孩子
            z->p->color = BLACK;
            z->p->p->color = RED;
            leftRotate(T, z->p->p);
        }
    }
    T->root->color = BLACK;     // 将根节点设置为黑色。
}

void 
RBTree::transplant(RBTREE *T, TreeNode *u, TreeNode *v){
    if(u->p==T->NIL){
        T->root = v;
    }else if(u == u->p->left){
        u->p->left = v;
    }else
        u->p->right = v;

    v->p = u->p;
}

void 
RBTree::remove(RBTREE *T, TreeNode *del){
    TreeNode *orig = del;               // del 为需要移除的节点  orig 记录 del 的节点，或即将取代 del 的节点信息
    E_COLOR orig_color = del->color;    // orig_color del 的颜色 或 取代 del 的节点颜色
    TreeNode *replace = nullptr;        // replace 为删除 del 之后，取代它的点 或者 orig 节点仅有的的右孩子
    if(del->left==T->NIL){
        replace = del->right;
        transplant(T,del,del->right);
    }else if(del->right==T->NIL){
        replace = del->left;
        transplant(T,del,del->left);
    }else {
        orig = minimum(T,del->right); // 获取 del 右子树最小节点，该节点一定无左子树，删除 del 节点，用 orig 节点取代
        orig_color = orig->color;
        replace = orig->right;         // 记录 orig  节点仅有的的右孩子

        if (orig->p == del)
        {
            replace->p = orig;
        }
        else // orig 并不是 del 的直接孩子节点，否则直接取代
        {
            transplant(T, orig, orig->right); // 用 orig 的右子树替代 orig
            orig->right = del->right;         // del 的右子树赋值给 origin 的右子树
            orig->right->p = orig;
        }
        transplant(T, del, orig);                  // 用 origin 替换 del
        orig->left = del->left;                    // 将 del 的左子树替代 ori 的左子树
        orig->left->p = orig;
        orig->color = del->color;                  // 将已经删除节点的颜色 del 赋值给 orig
    }

    if (orig_color == BLACK)         
    {
        removeFixup(T,replace);
    }
}

void 
RBTree::removeFixup(RBTREE *T, TreeNode *x){
    while(x!=T->NIL && T->root && x->color==BLACK){
        if(x == x->p->left){
            TreeNode *w = x->p->right;
            if(w->color==RED){
                // 情况1 x 的兄弟节点为红色

                // 交换 w 和 w 的父节点的颜色
                w->color = BLACK;
                x->p->color = RED;

                // 左旋，为保持红黑平衡
                leftRotate(T,x->p);
                w = w->p->right;
            }

            if(w->left->color==BLACK && w->right->color==BLACK){
                // 情况2 w 的左右孩子都为黑色
                w->color = RED;
                x =x->p;
            }else{
                if(w->right->color == BLACK){
                // 情况 3 w 的右孩子为黑色，则 w 的左孩子为红色

                // 交换 w 和 其左孩子的颜色
                w->left->color = BLACK;
                w->color = RED;

                // 右旋，保证 w 子树的每条简单路径的黑色节点数相同
                rightRotate(T,w);
                w = x->p->right;

                // 经过了情况3 必然来到 情况 4，
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(T,x->p);
                x = T->root;
                }

            }
        }else{
            TreeNode *w = x->p->left;
            if(w->color == RED){
                // 情况1 x 的兄弟节点为红色

                // 改变 w 和 w 的节点
                w->color = BLACK;
                x->p->color = RED;
                // 左旋，为保持红黑平衡
                rightRotate(T, x->p);
                w = x->p->left;
            }

            if(w->left->color==BLACK && w->right->color == BLACK){
                // 情况2 w 的左右孩子都为黑
                w->color = RED;
                x = x->p;
            }else{
                if(w->left->color==BLACK){
                    // 情况3 w 左孩子为红，右孩子为黑
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T,w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(T,x->p);
                x==T->root;
            }
        }
    }
    x->color = BLACK;
}


#endif // !_RBTree_H_