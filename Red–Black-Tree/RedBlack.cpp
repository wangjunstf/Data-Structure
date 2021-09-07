#include <iostream>
#include "RedBlack.h"


int main(){
    cout<<aa<<endl;
    vector<pair<int, E_COLOR>> inOrderTab{{26, BLACK}, {17, RED}, {14, BLACK}, {10, RED}, {7, BLACK}, {3, RED}, {0, BLACK}, {0, BLACK}, {0, BLACK}, {12, BLACK}, {0, BLACK}, {0, BLACK}, {16, BLACK}, {15, RED}, {0, BLACK}, {0, BLACK}, {0, BLACK}, {21, BLACK}, {19, BLACK}, {0, BLACK}, {20, RED}, {0, BLACK}, {0, BLACK}, {23, BLACK}, {0, BLACK}, {0, BLACK}, {41, BLACK}, {30, RED}, {28, BLACK}, {0, BLACK}, {0, BLACK}, {38, BLACK}, {35, RED}, {0, BLACK}, {0, BLACK}, {39, RED}, {0, BLACK}, {0, BLACK}, {47, BLACK}, {0, BLACK}, {0, BLACK}};

    RBTree rbTree(inOrderTab);
    cout<<"前序遍历:";
    rbTree.preOrder(rbTree.T->root);
    cout<<endl;

    TreeNode *minimum = rbTree.minimum(rbTree.T,rbTree.T->root);
    TreeNode *maximum = rbTree.maximum(rbTree.T,rbTree.T->root);

    cout << "最小值: "<<minimum->key;
    cout << " 最大值: "<<maximum->key<<endl;

    cout << "根节点的前驱" << rbTree.predecessor(rbTree.T,rbTree.T->root)->key<<endl;
    cout << "根节点的前驱" << rbTree.successor(rbTree.T,rbTree.T->root)->key<<endl;
    
    TreeNode *p1 = rbTree.search(rbTree.T,rbTree.T->root,47);
    TreeNode *p2 = rbTree.search(rbTree.T,rbTree.T->root, 38);
    cout<<"用 p1 取代了 p2 之后: "<<endl;
    rbTree.transplant(rbTree.T, p2,p1);

    // cout << "中序遍历:" ;
    // rbTree.inOrder(rbTree.T->root);
    // cout << endl;

    //TreeNode *node = rbTree.search(rbTree.T->root,30);
    //rbTree.leftRotate(rbTree.T,node);
    // cout << "将节点 30 左旋后的结果:"<<endl;
    // cout << "前序遍历:";
    // rbTree.preOrder(rbTree.T->root);
    // cout << endl;

    // cout << "中序遍历:" ;
    // rbTree.inOrder(rbTree.T->root);
    // cout << endl;

    // TreeNode *node2 = rbTree.search(rbTree.T->root, 38);
    // rbTree.rightRotate(rbTree.T, node2);
    // cout << "将节点 38 左旋后的结果:" << endl;
    // cout << "前序遍历:";
    // rbTree.preOrder(rbTree.T->root);
    // cout << endl;
    
    // cout << "中序遍历:";
    // rbTree.inOrder(rbTree.T->root);
    // cout << endl;

    // TreeNode *node1 = new TreeNode(40);
    // rbTree.insert(rbTree.T,node1);

    TreeNode *p = rbTree.search(rbTree.T, rbTree.T->root, 14);
    rbTree.remove(rbTree.T,p);
    cout<<"删除"<<p->key<<endl;
    cout << "前序遍历:";
    rbTree.preOrder(rbTree.T->root);

    cout << endl;
}
