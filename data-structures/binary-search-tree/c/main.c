// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Type of elements that are stored in the binary tree.
typedef int type_t;

//==============================================================================
// Node
//==============================================================================

// A node in the binary tree.
struct node {
    type_t value;        // Value stored in the node.
    struct node *left;   // Left child.
    struct node *right;  // Right child.
    struct node *parent; // Parent node.
};

// Creates a new node.
static struct node *node_create(type_t value)
{
    struct node *node = NULL;

    // Allocate resources.
    assert((node = malloc(sizeof(struct node))) != NULL);

    // Initialize.
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return (node);
}

// Destroys a node.
static void node_destroy(struct node *node)
{
    free(node);
}

//==============================================================================
// Binary Tree
//==============================================================================

// binary tree.
struct binary_tree {
    struct node *root; // Root node.
    unsigned size;     // Number of nodes in the tree.
};

// Creates a new binary tree.
static struct binary_tree *binary_tree_create(void)
{
    struct binary_tree *tree = NULL;

    // Allocate resources.
    assert((tree = malloc(sizeof(struct binary_tree))) != NULL);

    // Initialize.
    tree->root = NULL;
    tree->size = 0;

    return (tree);
}

// Destroys an binary tree.
static void binary_tree_destroy(struct binary_tree *tree)
{
    free(tree);
}

// Inserts a node into the binary tree.
static void binary_tree_insert(struct binary_tree *tree, type_t value)
{
    struct node *parent = NULL;
    struct node *node = NULL;
    struct node *current = tree->root;

    // Find insertion point.
    while (current != NULL) {
        parent = current;
        current = (value < current->value) ? current->left : current->right;
    }

    // Create node.
    assert((node = node_create(value)) != NULL);

    // Insert node.
    if (parent == NULL) {
        // Inserting root node.
        tree->root = node;
    } else {
        // Inserting leaf node.
        node->parent = parent;
        if (node->value < parent->value) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }

    // Update tree size.
    tree->size++;
}

// Searches for a node in the binary tree.
static struct node *binary_tree_search(struct binary_tree *tree, type_t value)
{
    struct node *current = tree->root;

    // Search for node.
    while (current != NULL) {
        if (value == current->value) {
            break;
        } else {
            current = (value < current->value) ? current->left : current->right;
        }
    }

    return (current);
}

// Removes a value from the binary tree.
static void binary_tree_remove(struct binary_tree *tree, type_t value)
{
    struct node *node = binary_tree_search(tree, value);

    // Check if node was found.
    if (node != NULL) {
        struct node *parent = node->parent;
        struct node *left = node->left;
        struct node *right = node->right;
        struct node *next = NULL;

        // Select a node to replace the one that is being removed.
        if (left == NULL) {
            // The node being removed has at most one child,
            // thus next node must be either the right child or none.
            next = right;
        } else if (right == NULL) {
            // The node being removed has at most one child,
            // thus next node must be either the left child or none.
            next = left;
        } else {
            // The node being removed has two children, thus next node
            // should be the leftmost node in the right subtree.
            // The rationale is that the leftmost node in the right subtree is
            // greater than all other nodes in the left subtree and smaller
            // than all other nodes in the right subtree.

            // Find next node.
            next = right;
            while (next->left != NULL) {
                next = next->left;
            }

            // Next node is not in place, thus  we need
            // to detach it from the left subtree.
            if (next->parent != node) {
                next->parent->left = next->right;
                if (next->right != NULL) {
                    next->right->parent = next->parent;
                }

                // Update right subtree.
                next->right = right;
                right->parent = next;
            }

            // Update left subtree.
            next->left = left;
            left->parent = next;
        }

        // Make 'next' the new root of the subtree.
        if (parent == NULL) {
            // Updating root node.
            tree->root = next;
        } else {
            // Updating  inner node.
            if (parent->left == node) {
                parent->left = next;
            } else {
                parent->right = next;
            }
        }

        // Update parent node for new root of the subtree.
        if (next != NULL) {
            next->parent = parent;
        }

        node_destroy(node);

        // Update tree size.
        tree->size--;
    }
}

// Prints an binary tree node.
static struct node *binary_tree_print_node(struct node *node)
{
    if (node != NULL) {
        struct node *left = binary_tree_print_node(node->left);
        struct node *right = binary_tree_print_node(node->right);
        printf("    [ %2d, %2d, %2d ]\n",
               (left != NULL) ? left->value : -1,
               node->value,
               (right != NULL) ? right->value : -1);
    }

    return (node);
}

// Prints an binary tree.
static void binary_tree_print(struct binary_tree *tree)
{
    printf("binary Tree:\n");
    printf("  size: %d\n", tree->size);
    printf("  nodes {\n");
    binary_tree_print_node(tree->root);
    printf("  }\n");
    printf("\n");
}

//==============================================================================
// Test
//==============================================================================

// Run tests.
static void test(unsigned height, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const unsigned root = (height - 1) / 2;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    // Create binary tree.
    struct binary_tree *tree = binary_tree_create();

    // Inserts nodes in the binary tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        binary_tree_insert(tree, i);
    }
    tend = clock();
    printf("%12s: %2.lf us\n",
           "binary_tree_insert()",
           (tend - tstart) / MICROSECS);

    if (verbose) {
        binary_tree_print(tree);
    }

    // Searches for nodes in the binary tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        struct node *node = binary_tree_search(tree, i);
        if (node == NULL) {
            printf("Error: node not found.\n");
            exit(EXIT_FAILURE);
        }
    }
    tend = clock();
    printf("%12s: %2.lf us\n",
           "binary_tree_search()",
           (tend - tstart) / MICROSECS);

    // Remove root node.
    binary_tree_remove(tree, root);
    if (verbose) {
        binary_tree_print(tree);
    }

    // Removes nodes from the binary tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        binary_tree_remove(tree, i);
    }
    tend = clock();
    printf("%12s: %2.lf us\n",
           "binary_tree_remove()",
           (tend - tstart) / MICROSECS);

    if (verbose) {
        binary_tree_print(tree);
    }

    // Destroys binary tree.
    binary_tree_destroy(tree);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program binary tree.\n", argv[0]);
    printf("Usage: %s [--verbose] <tree height>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned height = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%u", &height);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &height);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(height, verbose);

    return (EXIT_SUCCESS);
}
