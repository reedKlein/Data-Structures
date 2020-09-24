#include <iostream>
using namespace std;

template <typename T>
class BinaryTree{ 
    private:
    struct node {
        struct node* left;
        struct node* right;
        T key;
        int height;
    };
    node* root;
    int height (node* n) {
        if (!n){
            return 0;
        }
        return n->height;
    }
    int max (int a, int b)
    {
        return (a>b)? a : b;
    }

    node * minValueNode(node* node)  
    {  
    node* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
    } 

    node* newNode(T key){
        node* newNode = new Node();
        node->key = keyk
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }
    node* rightRotate(node* y){
        node* x = y->left;
        node* T2 = x->right;

        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1; 
        x->height = max(height(x->left), height(x->right)) + 1;  
        
        return x;
    }
    node* leftRotate(node* x){
        node* y = x->right;
        node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left),height(x->right)) + 1;
        y->height = max(height(y->left),height(y->right)) + 1;
        return y;
    }

    int getBalance(node* n){
        if (!n)
        {
            return 0;
        }
        return height(N->left) - height(N->right);
    }

    node* insert(node* node, T key){
        if (!node)
        {
            return newNode(key);
        }
        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            return node;
        }

		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);

        if (balance> 1 && key > node->right->key)
        {
            return rightRotate(node);
        }

        if (balance < -1 && key > node->right->key)
        {
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->key)  
        {  
            node->left = leftRotate(node->left);  
            return rightRotate(node);  
        }  

        if (balance < -1 && key < node->right->key)  
        {  
            node->right = rightRotate(node->right);  
            return leftRotate(node);  
        } 
    
        return node; 
    
    }
    
    int Find(T key){
        if(root->key == this->key){
			return root->key;
		}
		node *temp = root;
        while(temp->left != null && this->key < temp->key || temp->right != null && this->key > temp->right){
            if(this->key < temp->key){
                temp = temp->left;
			}
            else{
                temp = temp->right;
			}
		}
        if(temp->key == this->key){
            return temp->key
		}
        //throw error NotFound
	}

    node* remove(node* root, T key) {
        if (!root){
            return root;
        }
        if(key < root->key ){
            root->left = remove(root->left, key);
        }
        else if (key > root->key){
            root->right = remove(root->right, key)
        }
        else {
            if(!root->left || !root->right) {
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
            if(!(root->left) || !(root->right))
            {
                node* temp = root->left ? root->left : root->right
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
        
        root->height = 1+max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
        {
            return rightRotate(root);
        }

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
        {
            return leftRotate(root));
        }
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    public:
    BinaryTree() {
        root = nullptr;
    }
    ~BinaryTree() {
        //TODO: Destructor
    }
};
