#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int key;
    struct node *left_child, *right_child;
} node_t;

int print_count = 0;

node_t *newNode(int data)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = data;
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    return new_node;
}

node_t *insert_node(node_t *node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left_child = insert_node(node->left_child, key);
    else
        node->right_child = insert_node(node->right_child, key);
    return node;
}

node_t *find_min_node(node_t *node)
{
    node_t *current = node;
    while (current && current->left_child != NULL)
        current = current->left_child;
    return current;
}

node_t *delete_node(node_t *node, int key)
{
    if (node == NULL)
        return node;
    if (key < node->key)
        node->left_child = delete_node(node->left_child, key);
    else if (key > node->key)
        node->right_child = delete_node(node->right_child, key);
    else if (key == node->key) {     //delete
        //case1: No child
        if (node->left_child == NULL && node->right_child == NULL) {
            node_t *tmp = node;
            node = node->left_child;
            free(tmp);
        }
        // case2: One child
        else if (node->left_child == NULL && node->right_child != NULL) {
            node_t *tmp = node;
            node = node->right_child;
            free(tmp);
        }
        else if (node->right_child == NULL && node->left_child != NULL) {
            node_t *tmp = node;
            node = node->left_child;
            free(tmp);
        }
        //case3: Two children
        else {
            node_t *tmp = find_min_node(node->right_child);
            node->key = tmp->key;
            node->right_child = delete_node(node->right_child, tmp->key);
        }
    }
    return node;
}

int getLevelCount(node_t *node)
{
    if (node == NULL)
        return 0;
    int leftMaxLevel = 1 + getLevelCount(node->left_child);
    int rightMaxLevel = 1 + getLevelCount(node->right_child);
    if (leftMaxLevel >= rightMaxLevel)
        return leftMaxLevel;
    else
        return rightMaxLevel;
}

void printGivenLevel(node_t *node, int level)
{
    if (node == NULL)
        return;
    if (node != NULL && level == 1) {
        if (print_count == 0)
            printf("%d", node->key);
        else
            printf("\r\n%d", node->key);
        print_count++;
    }
    else if (node != NULL && level > 1) {
        printGivenLevel(node->left_child, level - 1);
        printGivenLevel(node->right_child, level - 1);
    }
}

void printout(node_t *node)
{
    int h = getLevelCount(node);
    for (int i = 1; i <= h; i++)
        printGivenLevel(node, i);
}

int main()
{
    char buffer[4], op[3];
    int key;
    node_t *root = NULL;
    while (scanf("%s%[ \r\n]", buffer, op) != EOF) {    //scan first line to insert
        printf("buffer = %s\n",buffer);

	    key = atoi(buffer);
        root = insert_node(root, key);
        strcpy(buffer, "\0");
        if (op[0] == '\r')
            break;
    }
    while (scanf("%s ", buffer) != EOF) {   //scan second line to delete
        key = atoi(buffer);
        root = delete_node(root, key);
        strcpy(buffer, "\0");
    }
    printout(root);     //print level by level
    return 0;
}
