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
    void inOrderPrint();
    int Height();
private:
    CNode<T>* root;
    void inOrder(CNode<T>* root);
    void del(CNode<T>* root);
    int height(CNode<T>* root);
};

template <class T>
struct CTreapNode
{
    CTreapNode(): key(0), priority(0), left(0), right(0) {}
    CTreapNode(T k, int prior): key(k), priority(prior), left(0), right(0) {}
    T key;
    int priority;
    CTreapNode* left;
    CTreapNode* right;
};

template <class T>
class Treap
{
public:
    Treap(): root(0) {}
    ~Treap();
    void Add(T& val, int prior);
    int Height();
    void Remove(T& val);
private:
    CTreapNode<T>* root;
    void del(CTreapNode<T>* root);
    int height(CTreapNode<T>* root);
    CTreapNode<T>* merge(CTreapNode<T>* left, CTreapNode<T>* right);
    void split(CTreapNode<T>* currentNode, int key, CTreapNode<T>*& left, CTreapNode<T>*& right);
};

int main()
{
    Tree<int> tree;
    Treap<int> treap;
    int n = 0;
    cin >> n;
    int value = 0;
    int priority = 0;
    for(int i = 0; i < n; i++) {
        cin >> value >> priority;
        tree.Add(value);
        treap.Add(value, priority);
    }
    
    cout << tree.Height() - treap.Height();
    
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
    bool isLeft = true;
    while(true) {
        if(toInsert == 0) {
            toInsert = new CNode<T>(val);
            if(prev != 0) {
                if(isLeft == true) {
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
                isLeft = false;
            } else {
                toInsert = toInsert->left;
                isLeft = true;
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


//Treap:
template <class T>
void Treap<T>::split(CTreapNode<T> *currentNode, int key, CTreapNode<T> *&left, CTreapNode<T> *&right)
{
    if( currentNode == 0 ) {
        left = 0;
        right = 0;
    } else if( currentNode->key <= key ) {
        split(currentNode->right, key, currentNode->right, right);
        left = currentNode;
    } else {
        split(currentNode->left, key, left, currentNode->left);
        right = currentNode;
    }
}

template <class T>
CTreapNode<T>* Treap<T>::merge(CTreapNode<T>* left, CTreapNode<T>* right)
{
	if( left == 0 || right == 0 ) {
		return left == 0 ? right : left;
	}
	if( left->priority > right->priority ) {
		left->right = merge(left->right, right);
		return left;
	}
	right->left = merge(left, right->left);
	return right;
}

template <class T>
void Treap<T>::Add(T &val, int prior)
{
    //Находим узел, останавливаемся как только prior > node->prior
    if(root == 0) {
        root = new CTreapNode<T>(val, prior);
        return;
    }
    CTreapNode<T>* toInsert = root;
    CTreapNode<T>* prev = 0;
    bool isLeft = true;
    while(true) {
        if(toInsert == 0) {
            toInsert = new CTreapNode<T>(val, prior);
            if(prev != 0) {
                if(isLeft == true) {
                    prev->left = toInsert;
                } else {
                    prev->right = toInsert;
                }
            }
            return;
        } else {
            if(prior > toInsert->priority) {
                break;
            }
            prev = toInsert;
            if(val > toInsert->key) {
                toInsert = toInsert->right;
                isLeft = false;
            } else {
                toInsert = toInsert->left;
                isLeft = true;
            }
        }        
    }
    
    //нашли
    //разрезаем по найденному
    
    CTreapNode<T>* splitLeft = 0;
    CTreapNode<T>* splitRight = 0;
    split(toInsert, val, splitLeft, splitRight);
    
    CTreapNode<T>* node = new CTreapNode<T>(val, prior);
    node->left = splitLeft;
    node->right = splitRight;
    
    if(prev != 0) {
        if(isLeft == true) {
            prev->left = node;
        } else {
            prev->right = node;
        }
    } else{
        root = node;
    }
}

template <class T>
Treap<T>::~Treap()
{
    del(root);
}

template <class T>
void Treap<T>::del(CTreapNode<T> *root)
{
    if(root != 0) {
        del(root->left);
        del(root->right);
        delete root;
    }
}

template <class T>
int Treap<T>::Height()
{
    return height(root);
}

template <class T>
int Treap<T>::height(CTreapNode<T> *root)
{
    if(root == 0) {
        return 0;
    }
    return max(height(root->left), height(root->right)) + 1;
}

template <class T>
void Treap<T>::Remove(T &val)
{
    CTreapNode<T>* toRemove = root;
    CTreapNode<T>* prev = 0;
    bool isLeft = true;
    while(true) {
        if(toRemove == 0) return;
        if(toRemove->key > val) {
            prev = toRemove;
            toRemove = toRemove->left;
            isLeft = true;
        } else if(toRemove->key < val) {
            prev = toRemove;
            toRemove = toRemove->right;
            isLeft = false;
        } else {
            //нашли удаляемый узел
            CTreapNode<T>* res = merge(toRemove->left, toRemove->right);
            if(!prev) {
                root = res;
            } else {
                if(isLeft) {
                    prev->left = res; 
                } else {
                    prev->right = res;
                }
            }
            delete toRemove;
        }
    }
}
