#ifndef SET_H
#define SET_H
#include <iostream>
#include <sstream>

using namespace std;

struct Node {
    int key;
    int height;
    Node *left;
    Node *right;

    Node(int k, Node *l = nullptr, Node *r = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->height = 1;
    }
};

class setTree {
    public:
        setTree();
        setTree(int value);
        ~setTree();
        void insert(int value);
        Node* erase(int value);
        bool contains(int value);
        void swap(setTree& other);
        int minimum();
        int maximum();
        int successor(int value);
        int predecessor(int value);
        bool empty();
        int size();
        void bshow();
        
        void intersection(setTree& other);
        void union_ensemble(setTree& other);
        void difference(setTree& other);
    private:
        Node *root;

        Node* clear(Node* root);
        Node* rightRotation(Node *p);
        Node* leftRotation(Node *p);
        int height(Node *node);
        int balance(Node *node);
        Node* _insert(Node* root, int value);
        Node* fixup_node(Node* root, int value);
        Node* _erase(Node* root,int value);
        bool _contains(Node* root, int value);
        int _minimum(Node* root);
        int _maximum(Node* root);
        int _successor(Node* root, int value);
        int _predecessor(Node* root, int value);
        bool _empty();
        int _size(Node* root);
        void _bshow(Node *node, string heranca);

        void _intersection(Node* root, setTree& other, setTree& result);
        void _union_ensemble(Node* root, setTree& result);
        void _difference(Node* root, setTree& other, setTree& result);
};

/*========== Implementação da Classe ===========*/
setTree::setTree() {
    root = nullptr;
}

setTree::setTree(int value) {
    root = new Node(value); 
}

Node* setTree::clear(Node* root) {
    if(root != nullptr) {
        root->right = clear(root->right);
        root->left = clear(root->left);
        delete root;
    }
    return nullptr;
}

setTree::~setTree() {
    root = clear(root);
}

int setTree::height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int setTree::balance(Node *node) {
    return height(node->left) - height(node->right);
}

Node* setTree::rightRotation(Node *p) {
    Node* u = p->left;
    p->left = u->right;
    u->right = p;

    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));

    return u;
}

Node* setTree::leftRotation(Node *p) {
    Node* u = p->right;
    p->right = u->left;
    u->left = p;

    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));

    return u;
}

Node* setTree::fixup_node(Node* root, int value) {
    root->height = 1 + max(height(root->left), height(root->right));

    int bal = balance(root);

    if(bal > 1 && value < root->left->key) {
        return rightRotation(root);
    } else if(bal > 1 && value > root->left->key) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    } else if(bal < -1 && value > root->right->key) {
        return leftRotation(root);
    } else if(bal < -1 && value < root->right->key) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
  return root;
}

Node* setTree::_insert(Node* root, int value) {
    if(root == nullptr) {
        return new Node{value, nullptr, nullptr};
    }
    if(root->key == value) {
        return root;
    }
    if(value < root->key) {
        root->left = _insert(root->left, value);
    } else {
        root->right = _insert(root->right, value);
    }
    root = fixup_node(root, value);

  return root;
}

void setTree::insert(int value) {
    root = _insert(root, value);
}

bool setTree::_contains(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }
    if (root->key == value) {
        return true;
    }
    if (root->key < value) {
        return _contains(root->right, value);
    } else {
        return _contains(root->left, value);
    }
}


bool setTree::contains(int value) {
    return _contains(root, value);
}

int setTree::_minimum(Node* root) {
    if(root->left == nullptr) {
        return root->key;
    } else {
        return _minimum(root->left);
    }
}

int setTree::_maximum(Node* root) {
    if(root->right == nullptr) {
        return root->key;
    } else {
        return _maximum(root->right);
    }
}

int setTree::minimum() {
    return _minimum(root);
}

int setTree::maximum() {
    return _maximum(root);
}

/*
===============================================

Conceito de sucessor e predecessor em árvores:

Sucessor = o menor valor maior que um determinado nó.
Predecessor = o maior valor menor que um determinado nó.

===============================================
*/

int setTree::_successor(Node* root, int value) {
    Node* atual = root;
    Node* succes = nullptr;

    while (atual != nullptr) {
        if (atual->key > value) {
            succes = atual;
            atual = atual->left;
        } else if (atual->key < value) {
            atual = atual->right;
        } else {
            if (atual->right != nullptr) {
                atual = atual->right;
                while (atual->left != nullptr) {
                    atual = atual->left;
                }
                return atual->key;
            }
            break;
        }
    }

    if (succes != nullptr) {
        return succes->key;
    } else {
        throw invalid_argument("No successor found or value not in the set.");
    }
}

int setTree::successor(int value) {
    return _successor(root, value);
}

int setTree::_predecessor(Node* root, int value) {
    Node* pred = nullptr;
    Node* atual = root;

    while(atual != nullptr) {
        if(atual->key < value) {
            pred = atual;
            atual = atual->right;
        } else if(atual->key > value) {
            atual = atual->left;
        } else {
            if(atual->left != nullptr) {
                atual = atual->left;
                while(atual->right != nullptr) {
                    atual = atual->right;
                }
                return atual->key;
            }
            break;
        }
    }

    if(pred != nullptr) {
        return pred->key;
    } else {
        throw invalid_argument("Predecessor nao encontrado");
    }
}

int setTree::predecessor(int value) {
    return _predecessor(root, value);
}

void setTree::_bshow(Node *node, string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        cout << "#" << endl;
        return;
    }
    cout << node->key << endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->left, heranca + "l");
}

void setTree::bshow(){
    _bshow(root, "");
}

Node* setTree::_erase(Node* root, int value) {
    if (root == nullptr) {
        return nullptr; // Se a raiz é nula, não há nada para remover
    }

    if (value < root->key) {
        root->left = _erase(root->left, value);
    } else if (value > root->key) {
        root->right = _erase(root->right, value);
    } else {
        // Nó encontrado
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                // Nó sem filhos
                temp = root;
                root = nullptr;
            } else {
                // Nó com um filho
                *root = *temp; // Cópia do conteúdo do filho não vazio
            }
            delete temp;
        } else {
            // Nó com dois filhos
            Node* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->key = temp->key;
            root->right = _erase(root->right, temp->key);
        }
    }

    if (root == nullptr) {
        return root;
    }

    return fixup_node(root, value);
}


bool setTree::_empty() {
    return root == nullptr ? true : false;
}

int setTree::_size(Node* root) {
    if(root == nullptr) {
        return 0;
    }
    return 1 + _size(root->left) + _size(root->right);
}

bool setTree::empty() {
    return _empty();
}

int setTree::size() {
    return _size(root);
}

Node* setTree::erase(int value) {
    return _erase(root, value);
}

void setTree::swap(setTree& other) {
    Node* temp = this->root;
    this->root = other.root;
    other.root = temp;
}

void setTree::_intersection(Node* root, setTree& other, setTree& result) {
    if(root != nullptr) {
        _intersection(root->left, other, result);
        if(other.contains(root->key)) {
            result.insert(root->key);
        }
        _intersection(root->right, other, result);
    }
}

void setTree::_union_ensemble(Node* root, setTree& result) {
    if(root != nullptr) {
        _union_ensemble(root->left, result);
        result.insert(root->key);
        _union_ensemble(root->right, result);
    }
}

void setTree::_difference(Node* root, setTree& other, setTree& result) {
    if(root != nullptr) {
        _difference(root->left, other, result);
        if(!other.contains(root->key)) {
            result.insert(root->key);
        }
        _difference(root->right, other, result);
    }
}

void setTree::intersection(setTree& other) {
    // irei ver os elementos em comum que as árvores possuem
    // coloca os valores em um vetor
    // depois eu crio uma árvore com os valores em comum 
    // imprimo a árvore 
    setTree treeIntersection;
    _intersection(root, other, treeIntersection);
    treeIntersection.bshow();
}

void setTree::union_ensemble(setTree& other) {
    // percorro a árvore da classe e a árvore other
    // adiciono seus valores em outra árvore
    // imprimo a árvore que representa a união
    setTree treeUnion;
    _union_ensemble(root, treeUnion);
    _union_ensemble(other.root, treeUnion);
    treeUnion.bshow();
    treeUnion.~setTree();
}

void setTree::difference(setTree& other) {
    // S - T
    // imprimo S - T
    setTree differenceST;
    _difference(root, other, differenceST);
    cout << "S - T: " << endl;
    cout << endl;
    differenceST.bshow();
    differenceST.~setTree();

    // T - S
    // imprmo T - S
    setTree differenceTS;
    _difference(other.root, *this, differenceTS);
    cout << "T - S: " << endl;
    cout << endl;
    differenceTS.bshow();
    differenceTS.~setTree();
}


#endif