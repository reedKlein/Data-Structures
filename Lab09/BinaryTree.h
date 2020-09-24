#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class BinaryTree {
private:
    struct node {
        struct node* left;
        struct node* right;
        T key;
    };
public:

    vector<T> ret_vector;
    node* root;
    int findHeight(node* temp) {
        int height = 0;
        if (temp != NULL) {
            int l_height = findHeight(temp->left);
            int r_height = findHeight(temp->right);
            int max_height = max(l_height, r_height);
            height = max_height + 1;
        }
        return height;
    }
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    void getAllAscending(node* n) {

        if (n == 0) {
            return;
        }

        getAllAscending(n->left);

        ret_vector.push_back(n->key);

        getAllAscending(n->right);

    }

    void getAllDescending(node* n) {

        if (n == 0) {
            return;
        }

        getAllDescending(n->right);

        ret_vector.push_back(n->key);

        getAllDescending(n->left);

    }

    node* minValueNode(node* n)
    {
        node* current = n;

        /* loop down to find the leftmost leaf */ 
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    node* newNode(T key) {
        node* newNode = new node();
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    node* rr_rotate(node* parent) {
        node* temp;
        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        cout << "Right-Right Rotation";
        return temp;
    }
    node* ll_rotate(node* parent) {
        node* temp;
        temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        cout << "Left-Left Rotation";
        return temp;
    }
    node* lr_rotate(node* parent) {
        node* temp;
        temp = parent->left;
        parent->left = rr_rotate(temp);
        cout << "Left-Right Rotation";
        return ll_rotate(parent);
    }
    node* rl_rotate(node* parent) {
        node* temp;
        temp = parent->right;
        parent->right = ll_rotate(temp);
        cout << "Right-Left Rotation";
        return rr_rotate(parent);
    }

    int difference(node* temp) {
        int l_height = findHeight(temp->left);
        int r_height = findHeight(temp->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    node* balance(node* n) {
        int bal_factor = difference(n);
        if (bal_factor > 1) {
            if (difference(n->left) > 0)
                n = ll_rotate(n);
            else
                n = lr_rotate(n);
        }
        else if (bal_factor < -1) {
            if (difference(n->right) > 0)
                n = rl_rotate(n);
            else
                n = rr_rotate(n);
        }
        return n;
    }

    node* insert(node* n, T key) {
        if (root == NULL) {
            root = new node;
            root->key = key;
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        else if (n == NULL) {
            n = new node;
            n->key = key;
            n->left = NULL;
            n->right = NULL;
            return n;
        }
        else if (key < n->key) {
            n->left = insert(n->left, key);
            n = balance(n);
        }
        else if (key.m_word >= n->key.m_word) {
            n->right = insert(n->right, key);
            n = balance(n);
        }
        return n;

    }

    node* Find(T key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->key == key) {
            return root;
        }
        node* temp = root;
        while ((temp->left != nullptr && key < temp->key) || (temp->right != nullptr && key > temp->key)) {
            if (key < temp->key) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        if (temp->key == key) {
            return temp;
        }
        return nullptr;
    }

    node* remove(node* root, T key) {
        if (!root) {
            return root;
        }
        if (key < root->key) {
            root->left = remove(root->left, key);
        }
        else if (key > root->key) {
            root->right = remove(root->right, key);
        }
        else {
            if (!root->left || !root->right) {
                node* temp = root->left ? root->left : root->right;

                if (!temp) {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                }
                delete temp;
            }
            else
            {
                node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = remove(root->right, temp->key);
            }

        }

        if (!root)
        {
            return root;
        }

        if (key < root->key)
        {
            root->left = remove(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = remove(root->right, key);
        }
        else
        {
            if (!(root->left) || !(root->right))
            {
                node* temp = root->left ? root->left : root->right;
                    if (!temp)
                    {
                        temp = root;
                        root = NULL;
                    }
                    else
                    {
                        *root = *temp;
                    }
                delete temp;


            }
            else
            {
                node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = remove(root->right, temp->key);
            }

        }

        if (!root)
        {
            return root;
        }


        if ((root->right != nullptr && key > root->right->key) || (root->left != nullptr && key < root->left->key)) {
            balance(root);
        }

        return root;
    }

    void destructorFunct(node* n) {
        if (n) {
            destructorFunct(n->left);
            destructorFunct(n->right);
            delete n;
        }
    }

    BinaryTree() {
        root = nullptr;
    }
    ~BinaryTree() {
        destructorFunct(root);
    }
};
