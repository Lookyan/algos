#include <iostream>

using namespace std;

struct CAVLNode {
        int Key;
        int Height; // Высота поддерева.
        int Count; //кол-во узлов в поддереве
        CAVLNode* Left;
        CAVLNode* Right;
        CAVLNode( int key ) : Key( key ), Height( 1 ), Count(1), Left( 0 ), Right( 0 ) {}
        int SafeHeight() { return this == 0 ? 0 : Height; }
        int SafeCount() { return this == 0 ? 0 : Count; }
};

class CAVLTree {
public:
        CAVLTree() : root( 0 ) {}
        ~CAVLTree();
        int Height() const { return root->SafeHeight(); }
        void Add( int key );
        void Remove( int key );
        int getIndex(int key);
        int indexOf(CAVLNode* p, int keyToFind);
        int Kth(int key);
private:
        CAVLNode* root;
        static void add( CAVLNode*& vertex, int key );
        static void balance( CAVLNode*& vertex );
        static void fixHeight( CAVLNode* vertex );
        static void fixCount(CAVLNode* vertex);
        static CAVLNode* rotateLeft( CAVLNode* vertex );
        static CAVLNode* rotateRight( CAVLNode* vertex );
        static int bfactor(CAVLNode* vertex);
        static CAVLNode* findmin(CAVLNode* p);
        static CAVLNode* removemin(CAVLNode* p);
        static CAVLNode* remove(CAVLNode* p, int k);
        static void del(CAVLNode* root);
        int kth(CAVLNode* node, int key);
};

CAVLTree::~CAVLTree()
{
    del(root);
}

void CAVLTree::del(CAVLNode *root)
{
    if(root != 0) {
        del(root->Left);
        del(root->Right);
        delete root;
    }
}

void CAVLTree::Add( int key ) {
        add( root, key );
}

void CAVLTree::add( CAVLNode*& vertex, int key ) {
        if( vertex == 0 ) {
                vertex = new CAVLNode( key );
                return;
        }
        if( vertex->Key <= key ) {
                add( vertex->Right, key );
        } else {
                add( vertex->Left, key );
        }
        balance( vertex );
}

void CAVLTree::balance(CAVLNode *&vertex)
{
    fixHeight(vertex);
    if( bfactor(vertex) == 2 ) {
        if( bfactor(vertex->Right) < 0 ) {
            vertex->Right = rotateRight(vertex->Right);
        }
        vertex = rotateLeft(vertex);
    }
    
    if( bfactor(vertex) == -2 ) {
        if( bfactor(vertex->Left) > 0  ) {
            vertex->Left = rotateLeft(vertex->Left);
        }
        vertex = rotateRight(vertex);
    }
    
    // балансировка не нужна
}

int CAVLTree::bfactor(CAVLNode *vertex)
{
    return vertex->Right->SafeHeight() - vertex->Left->SafeHeight();
}

void CAVLTree::fixHeight(CAVLNode *vertex)
{
    int heightLeft = vertex->Left->SafeHeight();
    int heightRight = vertex->Right->SafeHeight();
    vertex->Height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
    fixCount(vertex);
}

void CAVLTree::fixCount(CAVLNode *vertex)
{
    int countLeft = vertex->Left->SafeCount();
    int countRight = vertex->Right->SafeCount();
    vertex->Count = countLeft + countRight + 1;
}

CAVLNode* CAVLTree::rotateRight(CAVLNode *vertex)
{
    CAVLNode* q = vertex->Left;
    vertex->Left = q->Right;
    q->Right = vertex;
    fixHeight(vertex);
    fixHeight(q);
    return q;
}

CAVLNode* CAVLTree::rotateLeft(CAVLNode *vertex)
{
    CAVLNode* p = vertex->Right;
    vertex->Right = p->Left;
    p->Left = vertex;
    fixHeight(vertex);
    fixHeight(p);
    return p;
}

CAVLNode* CAVLTree::findmin(CAVLNode *p)
{
    return p->Left ? findmin(p->Left) : p;
}

CAVLNode* CAVLTree::removemin(CAVLNode *p)
{
    if(p->Left == 0) {
        return p->Right;
    } else {
        p->Left = removemin(p->Left);
        balance(p);
        return p;
    }
}

void CAVLTree::Remove(int key)
{
    root = remove(root, key);
}

CAVLNode* CAVLTree::remove(CAVLNode* p,int k)
{
    if(p == 0) return 0;
    if(k < p->Key) {
        p->Left = remove(p->Left, k);
    } else if(k > p->Key) {
        p->Right = remove(p->Right, k);
    } else {
        //нашли
        CAVLNode* q = p->Left;
        CAVLNode* r = p->Right;
        delete p;
        if(r == 0) {
            return q;
        }
        CAVLNode* min = findmin(r);
        min->Right = removemin(r);
        min->Left = q;
        balance(min);
        return min;
    }
    balance(p);
    return p;
}

int CAVLTree::indexOf(CAVLNode *node, int keyToFind)
{
    if ( node->Key == keyToFind ) {
        return node->Left->SafeCount();
    }
    if ( keyToFind > node->Key )
        return 1 + node->Left->SafeCount() + indexOf(node->Right, keyToFind);
    else { // if ( keyToFind < node->Key )
        return indexOf(node->Left, keyToFind);
    }
}

int CAVLTree::getIndex(int key)
{
    return indexOf(root, key);
}

int CAVLTree::Kth(int key)
{
    return kth(root, key);
}

int CAVLTree::kth(CAVLNode* node, int key)
{
    if ( key == node->Left->SafeCount() )
        return node->Key;
    if ( key < node->Left->SafeCount() )
        return kth(node->Left, key);
    if ( key > node->Left->SafeCount() )
        return kth(node->Right, key - node->Left->SafeCount() - 1);
}

int main()
{
    CAVLTree tree;
    int n = 0;
    cin >> n;
    int action = 1;
    int value = 0;
    int k = 0;
    for(int i = 0; i < n; i++) {
        cin >> action >> value;
        if(action == 1) {
            tree.Add(value);
            cout << k - tree.getIndex(value) << endl;
            k++;
        } else {
            int val = tree.Kth(value);
            tree.Remove(val);
            k--;
        }
    }
    
    return 0;
}

