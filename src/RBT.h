//
// Created by xboxl on 05/10/2022.
//

#ifndef INC_20221004_SOKETRAER_RBT_H
#define INC_20221004_SOKETRAER_RBT_H

#define ROTATE_LR 1
#define ROTATE_RL 2
#define ROTATE_LEFT 3
#define ROTATE_RIGHT 4
#define TOGGLE_RED 5

#include <memory>
#include <iostream>

template <typename T>
struct RBTNode{
    bool isRed;
    T data;
    std::shared_ptr<RBTNode<T>> left;
    std::shared_ptr<RBTNode<T>> right;

    explicit RBTNode(T d):
        isRed {true}, data {d}, left {nullptr}, right {nullptr}{}
};

template <typename T>
class RBT{
public:
    RBT():
        root {nullptr}, size {0}{}
    void insert(T data);
    void remove(T data);
    void printTree();


private:
    // Insert and rotation functions
    void insertNode(T& data, std::shared_ptr<RBTNode<T>>& curr, std::shared_ptr<RBTNode<T>>& tmp, uint8_t& lastRotation);
    void removeNode(T& data, std::shared_ptr<RBTNode<T>>& curr, std::shared_ptr<RBTNode<T>>& tmp, uint8_t& lastRotation);
    void checkRotation(std::shared_ptr<RBTNode<T>>& curr, std::shared_ptr<RBTNode<T>>& tmp, uint8_t& lastRotation);
    void rotateLR(std::shared_ptr<RBTNode<T>>& curr);
    void rotateRL(std::shared_ptr<RBTNode<T>>& curr);
    std::shared_ptr<RBTNode<T>> rotateLeft(std::shared_ptr<RBTNode<T>> curr);
    std::shared_ptr<RBTNode<T>> rotateRight(std::shared_ptr<RBTNode<T>> curr);
    void toggleRed(std::shared_ptr<RBTNode<T>>& curr);
    void print(std::shared_ptr<RBTNode<T>>& curr);
    const uint8_t getShape(std::shared_ptr<RBTNode<T>>& curr) const;

    // Private members
    std::shared_ptr<RBTNode<T>> root;
    size_t size;
};

template <typename T>
void RBT<T>::insert(T data) {
    std::shared_ptr<RBTNode<T>> tmp;
    uint8_t lastRotation {0};
    insertNode(data, root, tmp, lastRotation);
    ++size;
}
template <typename T>
void RBT<T>::remove(T data) {
    std::shared_ptr<RBTNode<T>> tmp;
    uint8_t lastRotation {0};
    insertNode(data, root, tmp, lastRotation);
    --size;
}
template <typename T>
void RBT<T>::insertNode(T& data, std::shared_ptr<RBTNode<T>>& curr, std::shared_ptr<RBTNode<T>>& tmp,
                        uint8_t& lastRotation) {
    if (curr) {
        if (data <= curr->data) {
            insertNode(data, curr->left, tmp, lastRotation);
        } else {
            insertNode(data, curr->right, tmp, lastRotation);
        }

        checkRotation(curr, tmp, lastRotation);
    }
    else {
        curr = std::make_shared<RBTNode<T>>(data);
        if (curr == root) curr->isRed = false;
    }
}
template <typename T>
void RBT<T>::removeNode(T &data, std::shared_ptr<RBTNode<T>> &curr, std::shared_ptr<RBTNode<T>> &tmp,
                        uint8_t &lastRotation) {

}
template <typename T>
void RBT<T>::checkRotation(std::shared_ptr<RBTNode<T>> &curr, std::shared_ptr<RBTNode<T>>& tmp, uint8_t &lastRotation) {

    if (lastRotation == ROTATE_LEFT) {
        curr->left = tmp;
        lastRotation = 0;
    }
    else if (lastRotation == ROTATE_RIGHT) {
        curr->right = tmp;
        lastRotation = 0;
    }

    switch (getShape(curr)) {
        case TOGGLE_RED:
            toggleRed(curr);
            break;

        case ROTATE_LR:
            rotateLR(curr);
            tmp = rotateLeft(curr);
            lastRotation = ROTATE_LEFT;
            break;

        case ROTATE_LEFT:
            tmp = rotateLeft(curr);
            lastRotation = ROTATE_LEFT;
            break;

        case ROTATE_RL:
            rotateRL(curr);
            tmp = rotateRight(curr);
            lastRotation = ROTATE_RIGHT;
            break;

        case ROTATE_RIGHT:
            tmp = rotateRight(curr);
            lastRotation = ROTATE_RIGHT;
            break;

        default:
            break;
    }
}
template <typename T>
void RBT<T>::rotateLR(std::shared_ptr<RBTNode<T>>& curr) {
    // Single rotation
    std::cout << "Rotate LR called\n";
    std::shared_ptr<RBTNode<T>> children {curr->left->right->left};
    curr->left->right->left = curr->left;
    curr->left = curr->left->right;
    curr->left->left->right = children;
}
template <typename T>
std::shared_ptr<RBTNode<T>> RBT<T>::rotateLeft(std::shared_ptr<RBTNode<T>> curr) {
    //Single rotation
    std::cout << "Rotate left called\n";
    std::shared_ptr<RBTNode<T>> tmp {curr->left};
    std::shared_ptr<RBTNode<T>> children {curr->left->right};
    curr->left->right = curr;
    if (curr == root) root = curr->left;
    curr->isRed = true;
    curr->left->isRed = false;
    curr->left = children;
    return tmp;
}
template <typename T>
void RBT<T>::rotateRL(std::shared_ptr<RBTNode<T>> &curr) {
    //Single rotation
    std::cout << "Rotate RL called\n";
    std::shared_ptr<RBTNode<T>> children {curr->right->left->right};
    curr->right->left->right = curr->right;
    curr->right = curr->right->left;
    curr->right->right->left = children;
}
template <typename T>
std::shared_ptr<RBTNode<T>> RBT<T>::rotateRight(std::shared_ptr<RBTNode<T>> curr) {
    //Single rotation
    std::cout << "Rotate right called\n";
    std::shared_ptr<RBTNode<T>> tmp {curr->right};
    std::shared_ptr<RBTNode<T>> children {curr->right->left};
    curr->right->left = curr;
    if (curr == root) root = curr->right;
    curr->isRed = true;
    curr->right->isRed = false;
    curr->right = children;
    return tmp;
}
template <typename T>
void RBT<T>::toggleRed(std::shared_ptr<RBTNode<T>> &curr) {
    std::cout << "Toggle red called\n";
    if (curr != root) curr->isRed = !curr->isRed;
    curr->left->isRed = false;
    curr->right->isRed = false;
}
template <typename T>
const uint8_t RBT<T>::getShape(std::shared_ptr<RBTNode<T>> &curr) const {
    uint8_t result {0};
    if (curr->left && curr->left->right) {
        if (curr->left->isRed && curr->left->right->isRed) {
            result = ROTATE_LR;
        }
    }
    if (curr->left && curr->left->left) {
        if (curr->left->isRed && curr->left->left->isRed) {
            result = ROTATE_LEFT;
        }
    }
    if (curr->right && curr->right->left) {
        if (curr->right->isRed && curr->right->left->isRed) {
            result = ROTATE_RL;
        }
    }
    if (curr->right && curr->right->right) {
        if (curr->right->isRed && curr->right->right->isRed) {
            result = ROTATE_RIGHT;
        }
    }

    if (curr->left && curr->right) {
        if (curr->left->isRed && curr->right->isRed && result) {
            result = TOGGLE_RED;
        }
    }

    return result;
}
template <typename T>
void RBT<T>::printTree() {
    print(root);
}
template <typename T>
void RBT<T>::print(std::shared_ptr<RBTNode<T>> &curr) {
    std::cout << curr->data << "\tisRed: " << curr->isRed << std::endl;
    std::cout << "Root: " << root->data << std::endl;

//Traverses entire tree left to right
    if(curr->left) print(curr->left);
    if(curr->right) print(curr->right);
}



#endif //INC_20221004_SOKETRAER_RBT_H
