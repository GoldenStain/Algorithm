#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <random>

struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::shared_ptr<TreeNode> createRandomTree(int depth, int probability, std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    if (depth <= 0 || dis(gen) > probability) {
        return nullptr;
    }
    auto root = std::make_shared<TreeNode>(dis(gen));
    root->left = createRandomTree(depth - 1, probability - 5, gen, dis);
    root->right = createRandomTree(depth - 1, probability - 5, gen, dis);
    return root;
}

using Node = std::shared_ptr<TreeNode>;

class RecursiveTraversal {
public:
    static void preorderTraversal(const Node root, std::ostream &os) {
        if (!root) return;
        os << root->val << std::endl;
        preorderTraversal(root->left, os);
        preorderTraversal(root->right, os);
    }

    static void inorderTraversal(const Node root, std::ostream &os) {
        if (!root) return;
        inorderTraversal(root->left, os);
        os << root->val << std::endl;
        inorderTraversal(root->right, os);
    }

    static void postorderTraversal(const Node root, std::ostream &os) {
        if (!root) return;
        postorderTraversal(root->left, os);
        postorderTraversal(root->right, os);
        os << root->val << std::endl;
    }
};

class IterativeTraversal {
public:
    static void preorderTraversal(const Node root, std::ostream &os) {
        std::vector<Node> stack;
        stack.push_back(root);
        while(!stack.empty()) {
            auto node = stack.back();
            stack.pop_back();
            os << node->val << std::endl;
            if(node->right) stack.push_back(node->right);
            if(node->left) stack.push_back(node->left);
        }
    }
    static void inorderTraversal(const Node root, std::ostream &os) {
        std::vector<Node> stack;
        auto node = root;
        while(node || !stack.empty()) {
            while(node) {
                stack.push_back(node);
                node = node->left;
            }
            node = stack.back();
            stack.pop_back();
            os << node->val << std::endl;
            node = node->right;
        }
    }
    static void postorderTraversal(const Node root, std::ostream &os) {
        std::vector<Node> stack;
        stack.push_back(root);
        Node prev = nullptr;
        while(!stack.empty()) {
            auto node = stack.back();
            if(!prev || prev->left == node || prev->right == node) {
                if(node->left) stack.push_back(node->left);
                else if(node->right) stack.push_back(node->right);
            } else if(node->left == prev) {
                if(node->right) stack.push_back(node->right);
            } else {
                os << node->val << std::endl;
                stack.pop_back();
            }
            prev = node;
        }
    }
};

bool compareResults(Node root) {
    std::stringstream ss1, ss2;
    RecursiveTraversal::preorderTraversal(root, ss1);
    IterativeTraversal::preorderTraversal(root, ss2);
    if(ss1.str() != ss2.str()) {
        std::cerr << "preorderTraversal failed" << std::endl;
        return false;
    }
    else {
        std::cout << "preorderTraversal passed" << std::endl;
    }
    ss1.str(""); ss2.str("");
    RecursiveTraversal::inorderTraversal(root, ss1);
    IterativeTraversal::inorderTraversal(root, ss2);
    if(ss1.str() != ss2.str()) {
        std::cerr << "inorderTraversal failed" << std::endl;
        return false;
    }
    else {
        std::cout << "inorderTraversal passed" << std::endl;
    }
    ss1.str(""); ss2.str("");
    RecursiveTraversal::postorderTraversal(root, ss1);
    IterativeTraversal::postorderTraversal(root, ss2);
    if(ss1.str() != ss2.str()) {
        std::cerr << "postorderTraversal failed" << std::endl;
        return false;
    }
    else {
        std::cout << "postorderTraversal passed" << std::endl;
    }
    return true;
}


int main() {
    std::mt19937 gen(114514);
    std::uniform_int_distribution<int> dis(0, 100);
    auto root = createRandomTree(10, 70, gen, dis);
    if (root) {
        std::cout << "root's value is " << root->val << std::endl;
    } else {
        std::cout << "root is nullptr" << std::endl;
    }
    compareResults(root);
}