#include "symtable.h"
SymbolTable::SymbolTable()
{
    size=0;
}

SymbolTable::~SymbolTable()
{
   if(root != nullptr){
     delete root;
     root=nullptr;
   }
    
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    if(size==0){
        root=new SymEntry(k,v);
        size++;  }
    else{
        size++;
        SymEntry* node=new SymEntry(k,v);
        SymEntry* temp=root;
        while(temp != nullptr){
            if(temp->key > k){
                if(temp->left==nullptr){
                    temp->left=node; break;}
                else{temp=temp->left;  } }
            else{
                if(temp->right==nullptr){
                    temp->right=node;break; }
                else{temp=temp->right;  }  }
        }
    }
}

void SymbolTable::remove(string k)
{   if (root == nullptr) {
        return;    }
    SymEntry* parent = nullptr;
    SymEntry* current = root;
    while (current != nullptr) {
        if (k == current->key) {
            break;
        }
        parent = current;

        if (k < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        return; 
    }
    size--;
    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            delete root->val;
            delete root;
            root = nullptr;
        } else if (current == parent->left) {
            delete current->val;
            delete current;
            parent->left = nullptr;
        } else {
            delete current->val;
            delete current;
            parent->right = nullptr;
        }
    } else if (current->left != nullptr && current->right != nullptr) {
        SymEntry* successorParent = current;
        SymEntry* successor = current->right;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }
        current->key = successor->key;
        delete current->val;
        current->val = successor->val;
        if (successorParent == current) {
            successorParent->right = successor->right;
        } else {
            successorParent->left = successor->right;
        }
        delete successor;
    } else {
        SymEntry* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {
            delete root->val;
            delete root;
            root = child;
        } else if (current == parent->left) {
            delete current->val;
            delete current;
            parent->left = child;
        } else {
            delete current->val;
            delete current;
            parent->right = child;
        }
    }
}

UnlimitedRational* SymbolTable::search(string k)
{
    SymEntry* temp=root;
        while(temp != nullptr){
            if(temp->key== k){
                return temp->val;
            }
            else if(temp->key > k){
                temp=temp->left;}
            else{
                temp=temp->right;  }
        }
    return new UnlimitedRational(new UnlimitedInt("1"),new UnlimitedInt("1"));
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry* SymbolTable::get_root()
{
    return root;
}
