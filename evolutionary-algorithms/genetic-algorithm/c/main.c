// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Genetic Algorithm
//==============================================================================

// Gene.
struct gene {
    bool *dna;           // DNA.
    unsigned dna_length; // Length of the DNA.
    unsigned fitness;    // Fitness value.
};

// Copies two genes.
void gene_copy(struct gene *dst, const struct gene *src)
{
    memcpy(dst->dna, src->dna, src->dna_length);
    dst->dna_length = src->dna_length;
    dst->fitness = src->fitness;
}

// Compares two genes.
int gene_cmp(const void *a, const void *b)
{
    const struct gene *gene1 = a;
    const struct gene *gene2 = b;

    if (gene1->fitness < gene2->fitness) {
        return (-1);
    } else if (gene1->fitness > gene2->fitness) {
        return (1);
    } else {
        return (0);
    }
}

// Crossover two genes.
int gene_crossover(struct gene *child,
                   const struct gene *gene1,
                   const struct gene *gene2)
{
    // Sanity check length of genes.
    assert(gene1->dna_length == gene2->dna_length);

    unsigned crossover_point = gene1->dna_length / 2; // Crossover point.

    // Copy first part of gene1.
    for (unsigned i = 0; i < crossover_point; i++) {
        child->dna[i] = gene1->dna[i];
    }

    // Copy second part of gene2.
    for (unsigned i = crossover_point; i < gene2->dna_length; i++) {
        child->dna[i] = gene2->dna[i];
    }

    return (0);
}

// Mutates a gene.
int gene_mutate(struct gene *gene)
{
    unsigned mutation_point = rand() & gene->dna_length; // Mutation point.

    // Mutate gene.
    gene->dna[mutation_point] = !gene->dna[mutation_point];

    return (0);
}

// Genetic algorithm data.
struct ga_config {
    unsigned dna_length;   // Length of the DNA.
    unsigned nindividuals; // Number of individuals.
    unsigned maxgen;       // Maximum number of generations.
    double selection_rate; // Selection rate.
    double mate_rate;      // Mate rate.
    double mutate_rate;    // Mutation rate.
    double elitsm_rate;    // Elitism rate.
};

// Initializes the population of a genetic algorithm.
void ga_init(struct gene *population,
             const struct ga_config *config,
             int (*fitness_fn)(struct gene *))
{
    // Initialize population.
    for (unsigned i = 0; i < config->nindividuals; i++) {
        // Initialize DNA.
        for (unsigned j = 0; j < population[i].dna_length; j++) {
            population[i].dna[j] = rand() % 2;
        }

        // Compute fitness.
        fitness_fn(&population[i]);
    }
}

// Selects individuals to mate.
void ga_selection(const struct gene **selected,
                  unsigned nselected,
                  const struct gene *population,
                  const struct ga_config *config)
{
    // Total fitness of the population.
    unsigned total_fitness = 0;

    // Compute total fitness of the population.
    for (unsigned i = 0; i < config->nindividuals; i++) {
        total_fitness += population[i].fitness;
    }

    // Select individuals using a roulette wheel.
    for (unsigned i = 0; i < nselected; i++) {
        unsigned r = rand() / RAND_MAX; // Random number.
        unsigned sum = 0;               // Sum of fitnesses.

        // Select individual.
        for (unsigned j = 0; j < config->nindividuals; j++) {
            sum += population[j].fitness / total_fitness;

            if (sum >= r) {
                selected[i] = &population[j];
                break;
            }
        }
    }
}

// Mates individuals.
void ga_mate(struct gene *children,
             unsigned nmating,
             const struct gene *const *selected)
{

    // Mate individuals.
    for (unsigned i = 0; i < nmating; i += 2) {
        // Select parents.
        unsigned parent1 = rand() % nmating;
        unsigned parent2 = rand() % nmating;

        // Mate parents.
        gene_crossover(&children[i], selected[parent1], selected[parent2]);
        gene_crossover(&children[i + 1], selected[parent2], selected[parent1]);
    }
}

// Mutates individuals.
void ga_mutate(struct gene *population,
               unsigned nmutating,
               const struct ga_config *config)
{

    // Mutate individuals.
    for (unsigned i = 0; i < nmutating; i++) {
        // Select individual to mutate.
        unsigned individual = rand() % config->nindividuals;

        // Mutate individual.
        gene_mutate(&population[individual]);
    }
}

// Runs the genetic algorithm.
unsigned ga_run(struct gene *population,
                const struct ga_config *config,
                int (*fitness_fn)(struct gene *))
{
    bool found = false;                   // Found solution?
    unsigned generation = config->maxgen; // Current generation.
    unsigned nselected = config->nindividuals * config->selection_rate;
    unsigned nmating = config->nindividuals * config->mate_rate;
    unsigned nelitism = config->nindividuals * config->elitsm_rate;
    unsigned nmutating = config->nindividuals * config->mutate_rate;
    const struct gene **selected = NULL;
    struct gene *children = NULL;

    assert((selected = malloc(sizeof(struct gene *) * nselected)) != NULL);
    assert((children = malloc(sizeof(struct gene) * nmating)) != NULL);
    for (unsigned i = 0; i < nmating; i++) {
        children[i].dna_length = config->dna_length;
        assert((children[i].dna =
                    malloc(sizeof(unsigned) * children[i].dna_length)) != NULL);
    }

    // Sanity check number of individuals.
    assert((nmating + nelitism) <= config->nindividuals);

    // Initialize population.
    ga_init(population, config, fitness_fn);

    // Sort population.
    qsort(population, config->nindividuals, sizeof(struct gene), gene_cmp);

    // Run genetic algorithm.
    for (unsigned i = 0; i < config->maxgen; i++) {
        // Select individuals to mate.
        ga_selection(selected, nselected, population, config);

        // Mate individuals.
        ga_mate(children, nmating, selected);

        // Copy elitism.
        for (unsigned j = 0; j < nelitism; j++) {
            gene_copy(&population[j],
                      &population[config->nindividuals - j - 1]);
        }

        // Copy children.
        for (unsigned j = 0; j < nmating; j++) {
            gene_copy(&population[nelitism + j], &children[j]);
        }

        // Mutate individuals.
        ga_mutate(population, nmutating, config);

        // Compute fitness.
        for (unsigned j = 0; j < config->nindividuals; j++) {
            found = fitness_fn(&population[j]);
        }

        // Sort population.
        qsort(population, config->nindividuals, sizeof(struct gene), gene_cmp);

        if (found) {
            generation = i;
            break;
        }
    }

    // Free memory.
    free(selected);
    for (unsigned i = 0; i < nmating; i++) {
        free(children[i].dna);
    }
    free(children);

    return (generation);
}

//==============================================================================
// Test
//==============================================================================

// Length of a DNA.
#define DNA_LENGTH 8

// Computes the fitness of a gene.
int fitness_fn(struct gene *gene)
{
    unsigned fitness = 1;

    // Compute fitness.
    for (unsigned i = 0; i < gene->dna_length; i++) {
        fitness += (gene->dna[i]) ? 1 : 0;
    }

    gene->fitness = fitness;

    return (gene->fitness == (gene->dna_length + 1));
}

// Test function.
static void test(bool verbose,
                 unsigned nindividuals,
                 unsigned maxgen,
                 double selection_rate,
                 double mate_rate,
                 double mutate_rate,
                 double elitsm_rate)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    unsigned generations = 0;
    struct ga_config config;
    config.dna_length = DNA_LENGTH;
    config.nindividuals = nindividuals;
    config.maxgen = maxgen;
    config.selection_rate = selection_rate;
    config.mate_rate = mate_rate;
    config.mutate_rate = mutate_rate;
    config.elitsm_rate = elitsm_rate;
    struct gene *population = malloc(sizeof(struct gene) * nindividuals);

    // Creates population.
    for (unsigned i = 0; i < nindividuals; i++) {
        population[i].dna_length = DNA_LENGTH;
        population[i].dna = malloc(sizeof(unsigned) * population[i].dna_length);
    }

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Cluster data.
    tstart = clock();
    generations = ga_run(population, &config, fitness_fn);
    tend = clock();

    // Report time.
    printf("Genetic Algorithm: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Best Solution (in %u/%u generations): ", generations, maxgen);
        for (unsigned i = 0; i < config.dna_length; i++) {
            printf("%d ", population[nindividuals - 1].dna[i]);
        }
        printf("\n");
    }

    // Release resources.
    for (unsigned i = 0; i < nindividuals; i++) {
        free(population[i].dna);
    }
    free(population);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for genetic algorithm.\n", argv[0]);
    printf("Usage: %s %s %s %s %s %s %s %s\n",
           argv[0],
           "[--verbose]",
           "<number of individuals>",
           "<max number of generations>",
           "<selection rate>",
           "<mate rate>",
           "<mutation rate>",
           "<elitism rate>");
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned nindividuals = 0;   // Number of individuals.
    unsigned maxgen = 0;         // Maximum number of generations.
    double selection_rate = 0.0; // Selection rate.
    double mate_rate = 0.0;      // Mate rate.
    double mutate_rate = 0.0;    // Mutation rate.
    double elitsm_rate = 0.0;    // Elitism rate.
    bool verbose = false;        // Verbose mode?

    // Parse command line arguments.
    if (argc == 7) {
        sscanf(argv[1], "%u", &nindividuals);
        sscanf(argv[2], "%u", &maxgen);
        sscanf(argv[3], "%lf", &selection_rate);
        sscanf(argv[4], "%lf", &mate_rate);
        sscanf(argv[5], "%lf", &mutate_rate);
        sscanf(argv[6], "%lf", &elitsm_rate);
    } else if ((argc == 8) && (!strcmp(argv[1], "--verbose"))) {
        verbose = true;
        sscanf(argv[2], "%u", &nindividuals);
        sscanf(argv[3], "%u", &maxgen);
        sscanf(argv[4], "%lf", &selection_rate);
        sscanf(argv[5], "%lf", &mate_rate);
        sscanf(argv[6], "%lf", &mutate_rate);
        sscanf(argv[7], "%lf", &elitsm_rate);
    } else {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Run it!
    test(verbose,
         nindividuals,
         maxgen,
         selection_rate,
         mate_rate,
         mutate_rate,
         elitsm_rate);

    return (EXIT_SUCCESS);
}
