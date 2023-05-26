// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Node
//==============================================================================

// Type of elements that are stored in the red-black tree.
typedef int type_t;

enum Color {
    RED,
    BLACK
};

// A node of a red-black tree.
struct node {
    type_t value;
    enum Color color;
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Creates a red-black tree node.
struct node *node_create(type_t value)
{
    struct node *new_node = NULL;

    // Allocate resources.
    assert((new_node = malloc(sizeof(struct node))) != NULL);

    // Initialize.
    new_node->value = value;
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return (new_node);
}

// Destroys a red-black tree node.
void node_destroy(struct node *node)
{
    free(node);
}

//==============================================================================
// Red-Black Tree
//==============================================================================

// A red-black tree.
struct rb_tree {
    unsigned size;
    struct node *root;
};

// Asserts the color property of the red-black tree.
static void rb_tree_check_color(struct node *node)
{
    if (node != NULL) {
        if (node->color == RED) {
            assert((node->left == NULL) || (node->left->color == BLACK));
            assert((node->right == NULL) || (node->right->color == BLACK));
        }
        rb_tree_check_color(node->left);
        rb_tree_check_color(node->right);
    }
}

// Asserts the order property of the red-black tree.
static type_t rb_tree_check_order(struct node *node)
{
    type_t max = 0;

    if (node != NULL) {
        max = node->value;
        if (node->left != NULL) {
            type_t tmp = rb_tree_check_order(node->left);
            assert(tmp < node->value);
        }
        if (node->right != NULL) {
            type_t tmp = rb_tree_check_order(node->right);
            assert(tmp > node->value);
            max = tmp;
        }
    }

    return (max);
}

// Asserts properties of the red-black tree.
static void rb_tree_check(struct rb_tree *tree)
{
    rb_tree_check_color(tree->root);
    rb_tree_check_order(tree->root);
}

// Creates a red-black tree.
static struct rb_tree *rb_tree_create(void)
{
    struct rb_tree *t = NULL;

    // Allocate resources.
    assert((t = malloc(sizeof(struct rb_tree))) != NULL);

    // Initialize.
    t->size = 0;
    t->root = NULL;

    return (t);
}

// Destroys a red-black tree.
static void rb_tree_destroy(struct rb_tree *t)
{
    free(t);
}

// Rotates a node to the left.
static void rb_tree_rotate_left(struct rb_tree *t, struct node *b)
{
    struct node *a = b->right;
    struct node *parent = b->parent;

    // Update left subtree.
    b->right = a->left;
    if (b->right != NULL) {
        b->right->parent = b;
    }

    // Update right subtree.
    a->left = b;
    b->parent = a;
    a->parent = parent;

    // Update root.
    if (parent == NULL) {
        t->root = a;
    } else {
        if (parent->left == b) {
            parent->left = a;
        } else {
            parent->right = a;
        }
    }
}

// Rotates a node to the right.
static void rb_tree_rotate_right(struct rb_tree *t, struct node *a)
{
    struct node *b = a->left;
    struct node *parent = a->parent;

    // Update left subtree.
    a->left = b->right;
    if (a->left != NULL) {
        a->left->parent = a;
    }

    // Update right subtree.
    b->right = a;
    a->parent = b;
    b->parent = parent;

    // Update root.
    if (parent == NULL) {
        t->root = b;
    } else {
        if (parent->left == a) {
            parent->left = b;
        } else {
            parent->right = b;
        }
    }
}

// Fixes violations in a red-black tree.
static void rb_tree_fix_insert(struct rb_tree *t, struct node *child)
{
    while ((child != t->root) && (child->color == RED) &&
           (child->parent->color == RED)) {
        struct node *parent = child->parent;
        struct node *grandparent = parent->parent;

        // Check if we need to fix either the left or right subtree.
        if (parent == grandparent->left) {
            // Fix left subtree.

            struct node *uncle = grandparent->right;

            // Check for violation.
            if ((uncle != NULL) && (uncle->color == RED)) {
                // Fix red-violation: a red node cannot have a red child.

                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                child = grandparent;
            } else {
                // Fix black-violation.

                // Check if we need to fix right subtree.
                if (parent->right == child) {
                    rb_tree_rotate_left(t, parent);
                    child = parent;
                    parent = child->parent;
                }
                rb_tree_rotate_right(t, grandparent);

                // Swap colors.
                enum Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;

                child = parent;
            }
        } else {
            // Fix right subtree.

            struct node *uncle = grandparent->left;

            if ((uncle != NULL) && (uncle->color == RED)) {
                // Handle red-violation: a red node cannot have a red child.

                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                child = grandparent;
            } else {
                // Fix black-violation.

                // Check if we need to fix left subtree.
                if (parent->left == child) {
                    rb_tree_rotate_right(t, parent);
                    child = parent;
                    parent = child->parent;
                }
                rb_tree_rotate_left(t, grandparent);

                // Swap colors.
                enum Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;

                child = parent;
            }
        }
    }

    if (t->root != NULL) {
        t->root->color = BLACK;
    }
}

// Inserts a node into a red-black tree.
static void rb_tree_insert(struct rb_tree *t, type_t value)
{
    struct node *parent = NULL;
    struct node *current = t->root;
    struct node *new_node = NULL;

    // Find insertion point.
    while (current != NULL) {
        parent = current;
        current = (value < current->value) ? current->left : current->right;
    }

    // Create node.
    assert((new_node = node_create(value)) != NULL);

    // Insert node.
    if (parent == NULL) {
        // Inserting root node.
        t->root = new_node;
    } else {
        // Inserting leaf nde.
        new_node->parent = parent;
        if (value < parent->value) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    rb_tree_fix_insert(t, new_node);

    rb_tree_check(t);
}

// Removes a value from the red-black tree.
// This algorithm should be improved to fix violations.
static void rb_tree_remove(struct rb_tree *tree, type_t value)
{
    struct node *node = rb_tree_search(tree, value);

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

        // TODO: fix violations.
    }
}

// Prints an red-black tree node.
static struct node *rb_tree_print_node(struct node *node)
{
    if (node != NULL) {
        struct node *left = rb_tree_print_node(node->left);
        struct node *right = rb_tree_print_node(node->right);
        printf("    [ %2d, (%2d) %2d (%c), %2d ]\n",
               (left != NULL) ? left->value : -1,
               node->parent != NULL ? node->parent->value : -1,
               node->value,
               (node->color == RED) ? 'R' : 'B',
               (right != NULL) ? right->value : -1);
    }

    return (node);
}

// Prints an red-black tree.
static void rb_tree_print(struct rb_tree *tree)
{
    printf("Red-Black Tree:\n");
    printf("  nodes {\n");
    rb_tree_print_node(tree->root);
    printf("  }\n");
    printf("\n");
}
//==============================================================================
// Test
//==============================================================================

// Shuffles an array.
static void shuffle(type_t *array, unsigned size)
{
    for (unsigned i = 0; i < size; i++) {
        unsigned j = rand() % size;
        type_t tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

// Run tests.
static void test(unsigned height, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    type_t values[height];

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Initialize values.
    for (unsigned i = 0; i < height; i++) {
        values[i] = i;
    }
    shuffle(values, height);

    // Create red-black tree.
    struct rb_tree *tree = rb_tree_create();

    // Inserts nodes in the red-black tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        type_t value = values[i];

        if (verbose) {
            printf("insert: %d\n", value);
        }

        rb_tree_insert(tree, value);

        if (verbose) {
            rb_tree_print(tree);
        }
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "rb_tree_insert()", (tend - tstart) / MICROSECS);

    // Shuffle values
    shuffle(values, height);

    // Searches for nodes in the red-black tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        type_t value = values[i];
        if (verbose) {
            printf("Search: %d\n", value);
        }
        struct node *node = rb_tree_search(tree, value);
        if (node == NULL) {
            printf("Error: node not found.\n");
            exit(EXIT_FAILURE);
        }
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "rb_tree_search()", (tend - tstart) / MICROSECS);

    // Shuffle values
    shuffle(values, height);

    // Removes nodes from the red-black tree.
    tstart = clock();
    for (unsigned i = 0; i < height; i++) {
        type_t value = values[i];
        if (verbose) {
            printf("Remove: %d\n", value);
            rb_tree_print(tree);
        }

        rb_tree_remove(tree, value);

        if (verbose) {
            printf("removed: %d\n", value);
            rb_tree_print(tree);
        }
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "rb_tree_remove()", (tend - tstart) / MICROSECS);

    if (verbose) {
        rb_tree_print(tree);
    }

    // Destroys red-black tree.
    rb_tree_destroy(tree);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program red-black tree.\n", argv[0]);
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
