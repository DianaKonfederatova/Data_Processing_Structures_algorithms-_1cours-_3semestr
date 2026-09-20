#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

struct vertex {
    int data;
    vertex *left;
    vertex *right;
    vertex() : data(0), left(nullptr), right(nullptr) {}
    vertex(int value) : data(value), left(nullptr), right(nullptr) {}
};

std::vector<int> A;

vertex* ISDP(int L, int R ){

    if (L > R){

        return nullptr;

    }else{
        int m = (L + R) / 2;
        vertex* p = new vertex;          
        p->data = A[m];     
        p -> left = ISDP(L, m-1);
        p -> right = ISDP(m+1, R);

        return p;
    }


}

void clear(vertex* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void top_down(vertex* node){

    if(node == nullptr){
        return;
    }

    std::cout << node -> data << " ";
    top_down(node -> left);
    top_down(node -> right);

}

void left_to_right(vertex* node) {
    if (node == nullptr) return;
    left_to_right(node->left);
    std::cout << node->data << " ";
    left_to_right(node->right);
}

int size_tree(vertex* node) {
    if (node == nullptr) return 0;
    return 1 + size_tree(node->left) + size_tree(node->right);
}

int height(vertex* node) {
    if (node == nullptr) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

int control_sum(vertex* node) {
    if (node == nullptr) return 0;
    return node->data + control_sum(node->left) + control_sum(node->right);
}

int sum_of_path_lengths(vertex* node, int level = 0) {
    if (node == nullptr) return 0;
    return level + sum_of_path_lengths(node->left, level + 1)
               + sum_of_path_lengths(node->right, level + 1);
}

float height_middle(int size, int sum_path) {
    if (size == 0) return 0.0f;
    return float(sum_path) / size;
}

int main() {

    for (int i = 1; i <= 100; ++i) {
        A.push_back(i);
    }

    vertex* root = ISDP(0, A.size() - 1);

    std::cout << "Обход сверху вниз:\n";
    top_down(root);
    std::cout << "\n";

    std::cout << "Обход дерева слева направо:\n";
    left_to_right(root);
    std::cout << "\n\n";

    int size = size_tree(root);
    std::cout << "Размер дерева: " << size << "\n";

    std::cout << "Контрольная сумма: " << control_sum(root) << "\n";

    std::cout << "Высота дерева: " << height(root) << "\n";

    int sum_path = sum_of_path_lengths(root);
    printf("Средняя высота: %.2f\n", height_middle(size, sum_path));

    clear(root);

    return 0;
}