#include <iostream>

using namespace std;

template <class T>
struct CNode
{
    CNode(): key(0), left(0), right(0) {}
    CNode(T& k): key(k), left(0), right(0) {}
    T key;
    CNode* left;
    CNode* right;
};

template <class T>
class Tree
{
public:
    Tree(): root(0) {}
    ~Tree();
    void Add(T& val);
    void Remove(T& val);
    void inOrderPrint();
    int Height();
private:
    CNode<T>* root;
    void inOrder(CNode<T>* root);
    void del(CNode<T>* root);
    int height(CNode<T>* root);
    CNode<T>* findmin(CNode<T>* p);
    CNode<T>* removemin(CNode<T>* p);
    CNode<T> *remove(CNode<T>* p, T& k);
};

int main()
{
    Tree<int> tree;
    int n = 0;
    cin >> n;
    int value = 0;
    for(int i = 0; i < n; i++) {
        cin >> value;
        tree.Add(value);
    }
    tree.inOrderPrint();
    //cout << tree.Height();
    return 0;
}

template <class T>
void Tree<T>::Add(T& val)
{
    if(root == 0) {
        root = new CNode<T>(val);
        return;
    }
    CNode<T>* toInsert = root;
    CNode<T>* prev = 0;
    bool isleft = true;
    while(true) {
        if(toInsert == 0) {
            toInsert = new CNode<T>(val);
            if(prev != 0) {
                if(isleft == true) {
                    prev->left = toInsert;
                } else {
                    prev->right = toInsert;
                }
            }
            break;
        } else {
            prev = toInsert;
            if(val > toInsert->key) {
                toInsert = toInsert->right;
                isleft = false;
            } else {
                toInsert = toInsert->left;
                isleft = true;
            }
        }        
    }  
}

template <class T>
Tree<T>::~Tree()
{
    del(root);
}

template <class T>
void Tree<T>::del(CNode<T> *root)
{
    if(root != 0) {
        del(root->left);
        del(root->right);
        delete root;
    }
}

template <class T>
void Tree<T>::inOrderPrint()
{
    inOrder(root);
}

template <class T>
void Tree<T>::inOrder(CNode<T> *root)
{
    if(root == 0) return;
    
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

template <class T>
int Tree<T>::Height()
{
    return height(root);
}

template <class T>
int Tree<T>::height(CNode<T> *root)
{
    if(root == 0) {
        return 0;
    }
    return max(height(root->left), height(root->right)) + 1;
}

template <class T>
void Tree<T>::Remove(T &val)
{
    root = remove(root, val);
}

template <class T>
CNode<T>* Tree<T>::remove(CNode<T> *p, T& k)
{
    if(p == 0) return 0;
    if(k < p->key) {
        p->left = remove(p->left, k);
    } else if(k > p->key) {
        p->right = remove(p->right, k);
    } else {
        //нашли
        CNode<T>* q = p->left;
        CNode<T>* r = p->right;
        delete p;
        if(r == 0) {
            return q;
        }
        CNode<T>* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return min;
    }
    return p;
}

template <class T>
CNode<T>* Tree<T>::findmin(CNode<T> *p)
{
    return p->left ? findmin(p->left) : p;
}

template <class T>
CNode<T>* Tree<T>::removemin(CNode<T> *p)
{
    if(p->left == 0) {
        return p->right;
    } else {
        p->left = removemin(p->left);
        return p;
    }
}

