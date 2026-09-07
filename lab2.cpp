#include <iostream>
#include <cstdlib>
#include <algorithm>

struct vertex {

    int data;
    vertex *left;
    vertex *right;
    vertex(int value) : data(value), 
    left(nullptr), right(nullptr) {}

};

void clear(vertex* node){

    if (node == nullptr){
        return;
    }

    clear(node -> left);
    clear(node -> right);

    delete node;

}

void print_and_direction(vertex* node, int direction = 0){

    if(node == nullptr){
        return;
    }

    if(direction == 1){
        std::cout << "L: " << node ->data << " ";

    }else if (direction == 2)
    {
        std::cout << "R: " << node -> data << " ";
    }else{
        std::cout << "root: " << node -> data << " ";
    }
    
    print_and_direction(node -> left, 1);
    print_and_direction(node -> right, 2);

}

void print(vertex* node){

    if(node == nullptr){
        return;
    }

    std::cout << node -> data << " ";

    print(node -> left);
    print(node -> right);

}

void top_down(vertex* node){

    if(node == nullptr){
        return;
    }

    std::cout << node -> data << " ";
    top_down(node -> left);
    top_down(node -> right);

}

void left_to_right(vertex* node){

    if(node == nullptr){
        return;
    }

    left_to_right(node -> left);
    std::cout << node -> data << " ";
    left_to_right(node -> right);

}

void bottom_to_top(vertex* node){

    if(node == nullptr){
        return;
    }

    bottom_to_top(node -> left);
    bottom_to_top(node -> right);
    std::cout << node -> data << " ";

}

int size_tree(vertex* node){

    if(node == nullptr){
        return 0;
    }else{
        int size = 1 + size_tree(node -> left) + size_tree(node -> right);
        return size;
    }

}

int height(vertex* node){

    if (node == nullptr){
        return 0;
    }else{
        int h = 1 + std::max(height(node -> left), height(node ->right));
        return h;
    }

}

int control_sum(vertex* node){

    if (node == nullptr){
        return 0;
    }else{
        int sum = node -> data + control_sum(node -> left)
        + control_sum(node -> right);
        return sum;
    }

}

int sum_of_path_lengths(vertex* node, int level = 0){

    if(node == nullptr){
        return 0;
    }else{
        int sum_of_path = level + sum_of_path_lengths(node -> left, level + 1)
        + sum_of_path_lengths(node -> right, level + 1);
        return sum_of_path;
    }
   
}

int main(){
    vertex *root = new vertex(1);
    
    root -> left = new vertex(9);

    root -> left -> left = new vertex(7);
    root -> left -> right = new vertex(10);

    root -> left -> left -> left = new vertex(6);
    root -> left -> left -> right = new vertex(8);

    std::cout << "Дерево:\n";
    print(root);
    std::cout << "\n";

    std::cout << "Дерево с пояснением направлений узлов:\n";
    print_and_direction(root);
    std::cout << "\n";

    std::cout << "Обход сверху вниз:\n";
    top_down(root);
    std::cout << "\n";

    std::cout << "Обход слева направо:\n";
    left_to_right(root);
    std::cout << "\n";

    std::cout << "Обход снизу вверх:\n";
    bottom_to_top(root);
    std::cout << "\n";

    std::cout << "Размер дерева: ";
    std::cout << size_tree(root);
    std::cout << "\n";

    std::cout << "Контрольная сумма дерева: ";
    std::cout << control_sum(root);
    std::cout << "\n";

    std::cout << "Высота дерева: ";
    std::cout << height(root);
    std::cout << "\n";

    std::cout << "Сумма длин путей: ";
    std::cout << sum_of_path_lengths(root);
    std::cout << "\n";

    clear(root);

    return 0;
}