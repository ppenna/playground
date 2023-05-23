// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// NUmber of characters in the alphabet.
#define RADIX 256

// A trie node.
struct node {
    char ch;                      // Character.
    struct node *parent;          // Parent node.
    struct node *children[RADIX]; // Children nodes.
};

// A trie.
struct trie {
    struct node root; // Root entry.
};

// Creates a trie node.
struct node *node_create(char ch, struct node *parent)
{
    struct node *n = NULL;

    // Allocate resources.
    assert((n = malloc(sizeof(struct node))) != NULL);

    // Initialize data structure.
    n->ch = ch;
    n->parent = parent;
    for (int i = 0; i < RADIX; i++) {
        n->children[i] = NULL;
    }

    return (n);
}

// Destroys a trie node.
void node_destroy(struct node *n)
{
    // Sanity check.
    assert(n != NULL);

    // Free resources.
    free(n);
}

// Creates a trie.
struct trie *trie_create(void)
{
    struct trie *t = NULL;

    // Allocate resources.
    assert((t = malloc(sizeof(struct trie))) != NULL);

    // Initialize data structure.
    t->root.parent = NULL;
    for (int i = 0; i < RADIX; i++) {
        t->root.children[i] = NULL;
    }

    return (t);
}

// Destroys a trie.
void trie_destroy(struct trie *t)
{
    // Sanity check.
    assert(t != NULL);

    // Free resources.
    free(t);
}

// Inserts a string into a trie.
void trie_insert(struct trie *t, const char *str)
{
    struct node *parent = &t->root;

    // Sanity check.
    assert(t != NULL);
    assert(str != NULL);

    // Insert string into trie.
    for (int i = 0; str[i] != '\0'; i++) {
        // Find insertion point.
        if (parent->children[(int)str[i]] != NULL) {
            parent = parent->children[(int)str[i]];
            printf("skip: ch=%c, parent=%c\n", (int)str[i], parent->ch);
            continue;
        }

        struct node *n = node_create(str[i], parent);

        // Insert node into trie.
        parent->children[(int)str[i]] = n;

        // Update parent.
        parent = n;
    }
}

// Searches for a string in a trie.
bool trie_find(struct trie *t, const char *str)
{
    struct node *current = &t->root;

    // Sanity check.
    assert(t != NULL);
    assert(str != NULL);

    // Search for string in trie.
    for (int i = 0; str[i] != '\0'; i++) {
        if (current == NULL || current->children[(int)str[i]] == NULL) {
            return (false);
        }

        current = current->children[(int)str[i]];
    }

    return (true);
}

// Removes a string from a trie.
void trie_remove(struct trie *t, const char *str)
{
    struct node *current = &t->root;

    // Sanity check.
    assert(t != NULL);
    assert(str != NULL);

    // Search for string in trie.
    for (int i = 0; str[i] != '\0'; i++) {
        if (current == NULL || current->children[(int)str[i]] == NULL) {
            return;
        }

        current = current->children[(int)str[i]];
    }

    // Remove string from trie.
    while (current != &t->root) {
        struct node *parent = current->parent;

        // Check if node has any children, and stop if so.
        for (int i = 0; i < RADIX; i++) {
            if (current->children[i] != NULL) {
                return;
            }
        }

        // Remove node from trie.
        parent->children[(int)current->ch] = NULL;
        node_destroy(current);

        // Update parent.
        current = parent;
    }
}

// Recursively prints a trie.
static void trie_print(struct node *n, char *str, int level)
{
    // Sanity check.
    assert(n != NULL);
    assert(str != NULL);

    // Print children.
    for (int i = 0; i < RADIX; i++) {
        if (n->children[i] != NULL) {
            str[level] = n->children[i]->ch;
            str[level + 1] = '\0';
            printf("str (%d): %s\n", level, str);
            trie_print(n->children[i], str, level + 1);
        }
    }
}

// Tests function.
static void test(char *const words[], int nwords, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct trie *t = trie_create();

    // Insert words into trie.
    tstart = clock();
    for (int i = 0; i < nwords; i++) {
        if (verbose) {
            printf("Inserting \"%s\"...\n", words[i]);
        }
        trie_insert(t, words[i]);
    }
    tend = clock();
    if (verbose) {
        printf("Insertion: %f us\n", (tend - tstart) / MICROSECS);
    }

    // Print trie.
    if (verbose) {
        char str[1024] = {0};
        printf("Trie:\n");
        trie_print(&t->root, str, 0);
    }

    // Search for words in trie.
    tstart = clock();
    for (int i = 0; i < nwords; i++) {
        if (verbose) {
            printf("Searching for \"%s\"...\n", words[i]);
        }
        assert(trie_find(t, words[i]) == true);
    }
    tend = clock();
    if (verbose) {
        printf("Search: %f us\n", (tend - tstart) / MICROSECS);
    }

    // Remove words from trie.
    tstart = clock();
    for (int i = 0; i < nwords; i++) {
        if (verbose) {
            printf("Removing \"%s\"... \n", words[i]);
        }
        trie_remove(t, words[i]);
    }
    tend = clock();
    if (verbose) {
        printf("Removal: %f us\n", (tend - tstart) / MICROSECS);
    }

    // Print trie.
    if (verbose) {
        char str[1024] = {0};
        printf("Trie:\n");
        trie_print(&t->root, str, 0);
    }
    // Free resources.
    trie_destroy(t);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for tries.\n", argv[0]);
    printf("Usage: %s [--verbose] <words>\n", argv[0]);
    exit(EXIT_FAILURE);
}

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned nwords = 0;
    char *const *words;
    bool verbose = false;

    // Check for missing arguments.
    if (argc < 2) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        nwords = argc - 1;
        words = &argv[1];
    } else if ((argc > 3) && (!strcmp(argv[1], "--verbose"))) {
        nwords = argc - 2;
        words = &argv[2];
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(words, nwords, verbose);

    return (EXIT_SUCCESS);
}
