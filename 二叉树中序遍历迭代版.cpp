/*
Author: Snickeen
Email : ff@snickeen.com
Date  : 201908143
*/
#include<iostream>
#include<stack>
using namespace std;

// 二叉树节点
struct TreeNode{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode():key(0),left(NULL),right(NULL){}
    TreeNode(int k):key(k),left(NULL),right(NULL){}
};

// 二叉树
class BinTree{
    struct TreeNode *ROOT; //树根

    // 非递归版二叉树中序遍历，不建议这样写，如果存储指针的话，会破坏掉当前树的结构
    stack<TreeNode*> ss;
    void inTravel2(TreeNode *root){
        if(root == NULL)return ;
        ss.push(root);
        while(!ss.empty()){
            TreeNode* t=ss.top();ss.pop();
            //cout << t->key << "--" << endl;
            if(t->left==NULL && t->right==NULL){
                cout << t->key << " ";
                continue;
            }
            if(t->right != NULL) ss.push(t->right);
            TreeNode *tmp = t->left;
            t->left = t->right = NULL;
            ss.push(t);
            if(tmp != NULL) ss.push(tmp);
        }
        cout << endl;
    }

    // 节点插入
    TreeNode* insert1(TreeNode* root, int k){
        if(root == NULL){
            TreeNode* t = new TreeNode();
            t->key = k;
            return t;
        }
        if(k < root->key) root->left = insert1(root->left, k);
        if(k > root->key) root->right= insert1(root->right,k);
        return root;
    }

    // 递归版中序遍历
    void in_dfs(TreeNode* root){
        if(root == NULL) return ;
        if(root->left != NULL) in_dfs(root->left);
        cout << root->key << " ";
        if(root->right != NULL) in_dfs(root->right);
    }

    // 非递归版二叉树的中序遍历，这个应该是一种正确姿势了
    stack<TreeNode> s;
public:
    void inTravel(TreeNode *root){
        if(root == NULL){cout<<endl;return ;} //
        s.push(*root);
        while(!s.empty()){
            TreeNode t=s.top();s.pop();
            if(t.left==NULL && t.right==NULL){
                cout << t.key << " ";
                continue;
            }
            if(t.right != NULL) s.push(*(t.right));
            TreeNode tmp(t.key); //
            s.push(tmp);
            if(t.left != NULL) s.push(*(t.left));
        }
        cout << endl;
    }

    void Insert(int k){ROOT=insert1(ROOT,k);} //节点插入
    void InTravel_dfs(){ in_dfs(ROOT); cout << endl;} // 递归版中序遍历
    void InTravel_no_dfs_2(){inTravel2(ROOT);} //不建议使用，因为只能用一次
    void InTravel_no_dfs(){inTravel(ROOT);} //非递归版中序遍历的正确姿势
};

BinTree t;

int main()
{
    int a[22]={4,8,5,3,2,9,6,1,7,0,10};
    for(int i=0;i<11;i++)
        t.Insert(a[i]);
    cout<<"Case 2: no dfs: "; t.InTravel_no_dfs(); //inTravel();
    cout<<"Case 1:    dfs: "; t.InTravel_dfs();
    //cout<<"Case 3: "; t.InTravel_no_dfs_2(); //栈里放指针的话改变了树中的关系
    //cout<<"Case 1: "; t.InTravel_dfs();

    // 邓公有另一种思路，这里先略掉，回头有心情了再补

    return 0;
}
