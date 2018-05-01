 #include <iostream>
 #include <climits>
 #include <utility>
 #include <vector>
 
 #define COUNT 7
 

class node {
public:
    int value;
    node* left;
    node* right;
    node();
    node(int);
};

class tree {
public:
    node* head;
    tree();
    tree(int);
    void addElement(int);
    //bool inTree(int);
    std::pair<bool, node*> inTree(int);
    void removeElement(int);
    std::vector<int> traverse();
    void traverseHelper(node*, std::vector<int>&);
    //void removeElement(int);
};

node::node(){
    this->value = INT_MAX;
    this->left = nullptr;
    this->right = nullptr;
};

node::node(int num) {
    this->value = num;
    this->left = nullptr;
    this->right = nullptr;    
};


tree::tree() {
    this->head = new node();
};

tree::tree(int first) {
    this->head = new node(first);
};

void tree::addElement(int num) {
    node* current_node = this->head;
    node* vanguard_node = this->head;
    
    if(this->head->value == INT_MAX) {
        this->head->value = num;
    } else {
        if (this->head->value >= num) {
            vanguard_node = current_node->left;
        } else {
            vanguard_node = current_node->right;
        };
        
        while(vanguard_node != nullptr) {
            if( vanguard_node->value >= num) {
                current_node = vanguard_node;
                vanguard_node = vanguard_node->left;
            } else {
                current_node = vanguard_node;
                vanguard_node = vanguard_node->right;
            };
        };
        
        //std::cout << current_node->value << std::endl;
        if (current_node->value >= num) {
            current_node->left = new node(num);
        } else {
            current_node->right = new node(num);
        };        
    };
};

std::pair<bool, node*> tree::inTree(int num) {
    node* current_node = this->head;
    node* vanguard_node = this->head;
    
    if (current_node->value == num) {
        return { true, current_node };
    };
        
    if (current_node != nullptr) {
       if (this->head->value >= num) {
            vanguard_node = current_node->left;
        } else {
            vanguard_node = current_node->right;
        };       
    } else {
        return { false, nullptr };
    }
    
    while(vanguard_node != nullptr) {
        if(vanguard_node->value > num) {
            current_node = vanguard_node;
            vanguard_node = vanguard_node->left;
        } else if (vanguard_node->value < num) {
            current_node = vanguard_node;
            vanguard_node = vanguard_node->right;
        } else if (vanguard_node->value == num) {
            return { false, current_node };            
        };
    };
    return { false, nullptr };
    
    
};

void tree::removeElement(int num) {
    std::pair<bool, node*> result = this->inTree(num);  
    if (result.second == nullptr) {
        std::cout << "Element not found!" << std::endl;
        return;
    }
    
    // special case: remove head
    if (result.first == true) {
        node* element = result.second;
        
        if ((element->left != nullptr) && (element->right != nullptr)) {        
        // find smallest node to the right of the element to be removed i.e furthest left
        node* before_current = element->right;
        node* current_node = before_current->left;
        node* vanguard_node = (current_node == nullptr) ? nullptr : current_node->left;
        
        while (vanguard_node != nullptr) {
            before_current = current_node;
            current_node = vanguard_node;
            vanguard_node = vanguard_node->left;
        };
        // point new node's left/right to the children of the element to be removed
        node* newnode = new node(current_node->value);
        newnode->left = element->left;
        newnode->right = element->right;
        this->head = newnode;
        before_current->left = nullptr;
        delete element;
        //this->removeElement(current_node->value);    
        };
        return;
    };
    
    
    bool onleft = (result.second->left->value == num) ? true : false;
    node* element = (result.second->left->value == num) ? result.second->left : result.second->right;
    
    // simplest case: no child nodes
    if (element->left == nullptr && element->right == nullptr) {
        if (onleft) {
            result.second->left = nullptr;
        } else {
            result.second->right = nullptr;
        };
        delete element;
        return;
    };

    // one child node
    if ((element->left == nullptr) != (element->right == nullptr)) {        
        if (onleft) {
            //((result.second->left->left != nullptr) ? result.second->left->left : result.second->left->right) = element;
            node* child = (result.second->left->left != nullptr) ? result.second->left->left : result.second->left->right;
            result.second->left = child;
        } else {
            //((result.second->right->left != nullptr) ? result.second->right->left : result.second->right->right) = element;
            node* child = (result.second->right->left != nullptr) ? result.second->right->left : result.second->right->right;
            result.second->right = child;
        };
        delete element;        
        return;
    };
    
    // two child nodes
    
    if ((element->left != nullptr) && (element->right != nullptr)) {
        // find smallest node to the right of the element to be removed i.e furthest left
        node* before_current = element->right;
        node* current_node = before_current->left;
        node* vanguard_node = (current_node == nullptr) ? nullptr : current_node->left;
        while (vanguard_node != nullptr) {
            before_current = current_node;
            current_node = vanguard_node;
            vanguard_node = vanguard_node->left;
        };
        // point new node's left/right to the children of the element to be removed
        node* newnode = new node(current_node->value);
        newnode->left = element->left;
        newnode->right = element->right;
        if (onleft) {
            result.second->left = newnode;
        } else {
            result.second->right = newnode;
        };
        
        before_current->left = nullptr;
        
        //this->removeElement(current_node->value);
        return;
    };
};

std::vector<int> tree::traverse() {
    std::vector<int> result;
    
    traverseHelper(this->head, result);
    
    return result;
    
};

void tree::traverseHelper(node* next, std::vector<int>& order) {
    if (next != nullptr) {
        traverseHelper(next->left, order);
        order.push_back(next->value);
        traverseHelper(next->right, order);
    };
};

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

// Rebuild tree

node* balanceTreeHelper(std::vector<int> order, int start, int end) {
    if (start > end){
        return nullptr;
    };
    
    int mid = (start + end) / 2;
    node* newnode = new node(order[mid]);
    
    newnode->left = balanceTreeHelper(order, start, mid-1);
    newnode->right = balanceTreeHelper(order, mid+1, end);
    
    return newnode;
  
};

tree* balanceTree(tree unbalanced) {
    std::vector<int> in_order = unbalanced.traverse();
    tree* newtree = new tree();
    
    newtree->head = balanceTreeHelper(in_order, 0, in_order.size() - 1);
    
    return newtree;
};





int main(void) {
    tree test = *new tree();
    
    /*test.addElement(15);
    test.addElement(10);
    test.addElement(5);
    test.addElement(7);
    test.addElement(12);
    test.addElement(3);
    std::cout << test.head->value << std::endl;
    std::cout << test.head->left->value << std::endl;
    std::cout << test.head->left->left->value << std::endl;
    std::cout << test.head->left->left->right->value << std::endl;
    std::cout << test.head->left->right->value << std::endl;
    std::cout << test.head->left->left->left->value << std::endl;*/
    
    
    test.addElement(50);
    test.addElement(100);
    test.addElement(150);
    test.addElement(200);
    test.addElement(250);
    test.addElement(75);
    test.addElement(74);
    test.addElement(99);
    test.addElement(125);
    test.addElement(175);
    test.addElement(225);
    test.addElement(49);
    
    print2D(test.head);
    
    /*test.removeElement(50);
    std::cout << std::endl;
    print2D(test.head);
    test.removeElement(150);
    std::cout << std::endl;
    print2D(test.head);*/
    std::vector<int> result = test.traverse();
    
    //std::cout << std::boolalpha << test.inTree(175).first << std::endl;
    
    for (auto& element : result) {
        std::cout << element << ", ";
    }
    std::cout << "\n";
    
    
    tree* temp = balanceTree(test);
    print2D(temp->head);
    
    
    return 0;
}
