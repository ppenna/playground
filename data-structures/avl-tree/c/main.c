// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Type of elements that are stored in the AVL tree.
typedef int type_t;

//==============================================================================
// Node
//==============================================================================

// A node in the AVL tree.
struct node {
    type_t value;        // Value stored in the node.
    unsigned height;     // Height of the node.
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
    node->height = 1;
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

// Returns the height of a node.
static unsigned node_height(struct node *node)
{
    return ((node != NULL) ? node->height : 0);
}

// Returns the balance factor of a node.
static int node_balance_factor(struct node *node)
{
    return ((node != NULL)
                ? (node_height(node->left) - node_height(node->right))
                : 0);
}

// Updates the height of a node.
static void node_update_height(struct node *node)
{
    unsigned left_height = node_height(node->left);
    unsigned right_height = node_height(node->right);
    node->height =
        ((left_height > right_height) ? left_height : right_height) + 1;
}

// Rotates a node to the left.
static struct node *node_rotate_left(struct node *a)
{
    struct node *b = a->right;
    struct node *c = b->left;
    struct node *parent = a->parent;

    // Rotate.
    a->right = c;
    b->left = a;

    // Update parents.
    a->parent = b;
    b->parent = parent;
    if (c != NULL) {
        c->parent = a;
    }

    // Update sub tree.
    if (parent != NULL) {
        if (parent->left == a) {
            parent->left = b;
        } else {
            parent->right = b;
        }
    }

    // Update heights.
    node_update_height(a);
    node_update_height(b);

    return (b);
}

// Rotates a node to the right.
static struct node *node_rotate_right(struct node *a)
{
    struct node *b = a->left;
    struct node *c = b->right;
    struct node *parent = a->parent;

    // Rotate.
    a->left = c;
    b->right = a;

    // Update parents.
    a->parent = b;
    b->parent = parent;
    if (c != NULL) {
        c->parent = a;
    }

    // Update sub tree.
    if (parent != NULL) {
        if (parent->left == a) {
            parent->left = b;
        } else {
            parent->right = b;
        }
    }

    // Update heights.
    node_update_height(a);
    node_update_height(b);

    return (b);
}

// Balances a node.
static struct node *node_balance(struct node *node)
{
    struct node *new_node = node;

    // Update height.
    node_update_height(node);

    // Balance subtree if required.
    if (node_balance_factor(node) == 2) {
        if (node_balance_factor(node->left) < 0) {
            node->left = node_rotate_left(node->left);
        }
        new_node = node_rotate_right(node);
    } else if (node_balance_factor(node) == -2) {
        if (node_balance_factor(node->right) > 0) {
            node->right = node_rotate_right(node->right);
        }
        new_node = node_rotate_left(node);
    }

    return (new_node);
}

//==============================================================================
// AVL Tree
//==============================================================================

// AVL tree.
struct avl_tree {
    struct node *root; // Root node.
    unsigned size;     // Number of nodes in the tree.
};

// Creates a new AVL tree.
static struct avl_tree *avl_tree_create(void)
{
    struct avl_tree *tree = NULL;

    // Allocate resources.
    assert((tree = malloc(sizeof(struct avl_tree))) != NULL);

    // Initialize.
    tree->root = NULL;
    tree->size = 0;

    return (tree);
}

// Destroys an AVL tree.
static void avl_tree_destroy(struct avl_tree *tree)
{
    free(tree);
}

// Balances an AVL tree, starting from a given node.
static void avl_tree_balance(struct avl_tree *tree, struct node *node)
{
    while (node != NULL) {
        node = node_balance(node);
        if (node->parent == NULL) {
            // Update the root of the tree, because when
            // rotating, the root may change.
            tree->root = node;
            break;
        }
        node = node->parent;
    }
}

// Asserts the weight property of the AVL tree.
static unsigned avl_tree_check_height(struct avl_tree *tree, struct node *node)
{
    unsigned height = 0;

    // Compute height.
    if (node != NULL) {
        unsigned left_height = avl_tree_check_height(tree, node->left);
        unsigned right_height = avl_tree_check_height(tree, node->right);

        if (left_height > right_height) {
            assert((left_height - right_height) < 2);
        } else {
            assert((right_height - left_height) < 2);
        }

        height =
            ((left_height > right_height) ? left_height : right_height) + 1;
    }

    return (height);
}

// Asserts the order property of the AVL tree.
static type_t avl_tree_check_order(struct node *node)
{
    type_t max = 0;

    if (node != NULL) {
        max = node->value;
        if (node->left != NULL) {
            type_t tmp = avl_tree_check_order(node->left);
            assert(tmp < node->value);
        }
        if (node->right != NULL) {
            type_t tmp = avl_tree_check_order(node->right);
            assert(tmp > node->value);
            max = tmp;
        }
    }

    return (max);
}

// Asserts properties of the AVL tree.
static void avl_tree_check(struct avl_tree *tree)
{
    avl_tree_check_height(tree, tree->root);
    avl_tree_check_order(tree->root);
}

// Inserts a node into the AVL tree.
static void avl_tree_insert(struct avl_tree *tree, type_t value)
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

        // Balance tree.
        avl_tree_balance(tree, parent);
    }

    // Update tree size.
    tree->size++;

    avl_tree_check(tree);
}

// Searches for a node in the AVL tree.
static struct node *avl_tree_search(struct avl_tree *tree, type_t value)
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

// Removes a value from the AVL tree.
static void avl_tree_remove(struct avl_tree *tree, type_t value)
{
    struct node *node = avl_tree_search(tree, value);

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

        // Find starting point for rebalancing.
        if (next != NULL) {
            // Start from new root of the subtree.
            parent = next;
            // Start from the root of the right subtree.
            if (next->right != NULL) {
                parent = next->right;
            }
        }

        avl_tree_balance(tree, parent);

        // Update tree size.
        tree->size--;
    }

    avl_tree_check(tree);
}

// Prints an AVL tree node.
static struct node *avl_tree_print_node(struct node *node)
{
    if (node != NULL) {
        struct node *left = avl_tree_print_node(node->left);
        struct node *right = avl_tree_print_node(node->right);
        printf("    [ %2d, %2d, %2d ]\n",
               (left != NULL) ? left->value : -1,
               node->value,
               (right != NULL) ? right->value : -1);
    }

    return (node);
}

// Prints an AVL tree.
static void avl_tree_print(struct avl_tree *tree)
{
    printf("AVL Tree:\n");
    printf("  size: %d\n", tree->size);
    printf("  nodes {\n");
    avl_tree_print_node(tree->root);
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

    // Create AVL tree.
    struct avl_tree *tree = avl_tree_create();

    // Inserts nodes in the AVL tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        avl_tree_insert(tree, i);
    }
    tend = clock();
    printf(
        "%12s: %2.lf us\n", "avl_tree_insert()", (tend - tstart) / MICROSECS);

    if (verbose) {
        avl_tree_print(tree);
    }

    // Searches for nodes in the AVL tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        struct node *node = avl_tree_search(tree, i);
        if (node == NULL) {
            printf("Error: node not found.\n");
            exit(EXIT_FAILURE);
        }
    }
    tend = clock();
    printf(
        "%12s: %2.lf us\n", "avl_tree_search()", (tend - tstart) / MICROSECS);

    // Remove root node.
    avl_tree_remove(tree, root);
    if (verbose) {
        avl_tree_print(tree);
    }

    // Removes nodes from the AVL tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        avl_tree_remove(tree, i);
    }
    tend = clock();
    printf(
        "%12s: %2.lf us\n", "avl_tree_remove()", (tend - tstart) / MICROSECS);

    if (verbose) {
        avl_tree_print(tree);
    }

    // Destroys AVL tree.
    avl_tree_destroy(tree);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program AVL tree.\n", argv[0]);
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
