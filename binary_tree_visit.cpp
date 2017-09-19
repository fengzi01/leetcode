// 二叉树搜索
#include<stdio.h>
#include<stdlib.h>
#include<queue> 
#include<stack>

// Definition for a binary tree node.
typedef struct TreeNode* tree_node_t;

struct TreeNode {
    int val;
    tree_node_t left;
    tree_node_t right;

    int left_space,right_space,pre_space;
};

tree_node_t create_tree_node(int *nums,int len,int idx);
void print_tree_node(tree_node_t node);
tree_node_t calc_space(tree_node_t node);

// 创建二叉树
tree_node_t create_tree(int *nums,int size) {
    // 递归创建根节点
    tree_node_t root = create_tree_node(nums,size,0);
    if (NULL==root) {
        printf("create tree fail");
    }
    return root;
}

tree_node_t create_tree_node(int *nums,int len,int idx) {
    if (idx >= len || nums[idx] < 0) {
        return NULL;
    }
    tree_node_t node = (tree_node_t)malloc(sizeof(*node));
    node->val = nums[idx];

    node->left = create_tree_node(nums,len,2*idx+1);
    node->right = create_tree_node(nums,len,2*idx+2);

    return node;
}

// 打印二叉树
void print_tree(tree_node_t root) {
    if (root == NULL) {
        return;
    }

    tree_node_t node;
    std::queue<tree_node_t> queue;
    int cur_level_cnt = 1,next_level_cnt = 0;
    
    calc_space(root);
    queue.push(root);

    while(!queue.empty()) {
        node = queue.front();
        queue.pop();

        cur_level_cnt--;

        print_tree_node(node);

        if (node->left) {
            calc_space(node->left);
            queue.push(node->left);
            next_level_cnt++;
        }
        if (node->right) {
            calc_space(node->right);
            queue.push(node->right);
            next_level_cnt++;
        }

        if (0 == cur_level_cnt) {
            printf("\n");
            cur_level_cnt = next_level_cnt;
            next_level_cnt = 0;
        }
    }
}

void print_tree_node(tree_node_t node) {
    if (NULL == node) {
        return;
    }
    int left_space,right_space;
    int i;

    left_space = node->left_space + node->pre_space;
    right_space = node->right_space;

    for (i=0;i<left_space;i++) {
        printf(" ");
    }

    printf("%d",node->val);
    for (i=0;i<right_space;i++) {
        printf(" ");
    }
}

tree_node_t calc_space(tree_node_t node) {
    if (node->left == NULL && node->right == NULL) {
        node->left_space = 0;
        node->right_space = 0;
    } else {
        if (node->right != NULL) {
            node->right->pre_space = 1;
            node->right_space = calc_space(node->right)->left_space 
                + 1 
                + calc_space(node->right)->right_space;
        }
        if (node->left != NULL) {
            node->left->pre_space = node->pre_space;
            node->left_space = calc_space(node->left)->left_space 
                +1
                +calc_space(node->left)->right_space;
        }
    }

    return node;
}

// 释放二叉树
void free_tree(tree_node_t root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// bfs遍历二叉树
void bfs_visit_tree(tree_node_t root) {
    if (root == NULL) {
        return;
    }

    tree_node_t node;
    std::queue<tree_node_t> queue;
    int cur_level_cnt = 1,next_level_cnt = 0;
    queue.push(root);

    while(!queue.empty()) {
        node = queue.front();
        queue.pop();

        cur_level_cnt--;

        printf("%d ",node->val);
        if (node->left) {
            queue.push(node->left);
            next_level_cnt++;
        }
        if (node->right) {
            queue.push(node->right);
            next_level_cnt++;
        }

        if (0 == cur_level_cnt) {
            printf("\n");
            cur_level_cnt = next_level_cnt;
            next_level_cnt = 0;
        }
    }
}

// dfs遍历二叉树
void dfs_visit_tree(tree_node_t root) {
    if (root == NULL) {
        return;
    } else {
         printf("val:%d\n",root->val);
         dfs_visit_tree(root->left);
         dfs_visit_tree(root->right);
    }
   
    // 栈实现
    // std::stack<tree_node_t> stack;
    // tree_node_t node;

    // stack.push(root);
    // while(!stack.empty()) {
    //     node = stack.top();
    //     printf("val:%d\n",node->val);
    //     stack.pop();
    //     if (node->right) {
    //         stack.push(node->right);
    //     }
    //     if (node->left) {
    //         stack.push(node->left);
    //     }
    // }
}

int main() {
    int size = 7;
    int i;

    int nums[] = {1,2,3,4,5,6,7};

    tree_node_t root = create_tree(nums,size);
    dfs_visit_tree(root);
    printf("----------------\n");
    bfs_visit_tree(root);
    printf("----------------\n");
    print_tree(root);

    // free(nums);
    free_tree(root);
}
