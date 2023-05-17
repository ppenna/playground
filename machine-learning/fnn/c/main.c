// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Neuron
//==============================================================================

// An artificial neuron.
struct neuron {
    unsigned n;
    double *inputs;
    double *weights;
    double bias;
    double z;
    double fz;
    double dz;
    double delta;
    double (*fx)(double);
    double (*dx)(double);
};

// Allocates a neuron.
struct neuron *neuron_create(unsigned n, double (*fx)(double),
                             double (*dx)(double))
{
    struct neuron *neuron = NULL;
    double *inputs = NULL;
    double *weights = NULL;

    // Allocate resources.
    assert((neuron = malloc(sizeof(struct neuron))) != NULL);
    assert((inputs = malloc(n * sizeof(double))) != NULL);
    assert((weights = malloc(n * sizeof(double))) != NULL);

    // Initialize.
    neuron->n = n;
    neuron->inputs = inputs;
    neuron->weights = weights;
    neuron->bias = (double)rand() / (double)RAND_MAX;
    neuron->z = 0.0;
    neuron->fz = 0.0;
    neuron->dz = 0.0;
    neuron->delta = 0.0;
    neuron->fx = fx;
    neuron->dx = dx;
    for (unsigned i = 0; i < neuron->n; i++) {
        neuron->weights[i] = (double)rand() / (double)RAND_MAX;
    }

    return (neuron);
}

// Releases the resources allocated to a neuron.
static void neuron_destroy(struct neuron *neuron)
{
    free(neuron->inputs);
    free(neuron->weights);
    free(neuron);
}

// Computes the output of a neuron.
static void neuron_compute(struct neuron *neuron)
{
    neuron->z = neuron->bias;
    for (unsigned i = 0; i < neuron->n; i++) {
        neuron->z += neuron->inputs[i] * neuron->weights[i];
    }
    neuron->fz = neuron->fx(neuron->z);
    neuron->dz = neuron->dx(neuron->z);
}

//==============================================================================
// Layer
//==============================================================================

// A layer of neurons.
struct layer {
    unsigned n;
    struct neuron **neurons;
};

// Allocates a layer of neurons.
struct layer *layer_create(unsigned n, unsigned m, double (*fx)(double),
                           double (*dx)(double))
{
    struct layer *layer = NULL;
    struct neuron **neurons = NULL;

    // Allocate resources.
    assert((layer = malloc(sizeof(struct layer))) != NULL);
    assert((neurons = malloc(n * sizeof(struct neuron *))) != NULL);

    // Initialize.
    layer->n = n;
    layer->neurons = neurons;
    for (unsigned i = 0; i < n; i++) {
        layer->neurons[i] = neuron_create(m, fx, dx);
    }

    return (layer);
}

// Releases the resources allocated to a layer of neurons.
static void layer_destroy(struct layer *layer)
{
    for (unsigned i = 0; i < layer->n; i++) {
        neuron_destroy(layer->neurons[i]);
    }
    free(layer->neurons);
    free(layer);
}

//==============================================================================
// Neural Network
//==============================================================================

// A feed-forward neural network.
struct fnn {
    unsigned n;
    struct layer **layers;
};

// Allocates a feed-forward neural network.
struct fnn *fnn_create(unsigned n, const unsigned m[], double (*fx[])(double),
                       double (*dx[])(double))
{
    struct fnn *nn = NULL;
    struct layer **layers = NULL;

    // Allocate resources.
    assert((nn = malloc(sizeof(struct fnn))) != NULL);
    assert((layers = malloc(n * sizeof(struct layer *))) != NULL);

    // Initialize.
    nn->n = n;
    nn->layers = layers;
    nn->layers[0] = layer_create(m[0], 1, fx[0], dx[0]);
    for (unsigned i = 1; i < n; i++) {
        nn->layers[i] = layer_create(m[i], m[i - 1], fx[i], dx[i]);
    }

    return (nn);
}

// Releases the resources allocated to a feed-forward neural network.
static void fnn_destroy(struct fnn *nn)
{
    for (unsigned i = 0; i < nn->n; i++) {
        layer_destroy(nn->layers[i]);
    }
    free(nn->layers);
    free(nn);
}

// Propagates an input through a feed-forward neural network.
static void fnn_propagate(struct fnn *nn, const double inputs[])
{
    for (unsigned i = 0; i < nn->layers[0]->n; i++) {
        nn->layers[0]->neurons[i]->inputs[0] = inputs[i];
        neuron_compute(nn->layers[0]->neurons[i]);
    }
    for (unsigned i = 1; i < nn->n; i++) {
        for (unsigned j = 0; j < nn->layers[i]->n; j++) {
            for (unsigned k = 0; k < nn->layers[i - 1]->n; k++) {
                nn->layers[i]->neurons[j]->inputs[k] =
                    nn->layers[i - 1]->neurons[k]->fz;
            }
            neuron_compute(nn->layers[i]->neurons[j]);
        }
    }
}

// Back-propagates an error through a feed-forward neural network.
static void fnn_backpropagate(struct fnn *nn, const double outputs[])
{
    for (unsigned i = 0; i < nn->layers[nn->n - 1]->n; i++) {
        double e = (outputs[i] - nn->layers[nn->n - 1]->neurons[i]->fz);

        nn->layers[nn->n - 1]->neurons[i]->delta =
            e * nn->layers[nn->n - 1]->neurons[i]->dz;
    }

    // Traverses all hidden layers in reverse order.
    for (unsigned i = nn->n - 2; i > 0; i--) {
        struct layer *current_layer = nn->layers[i];
        struct layer *next_layer = nn->layers[i + 1];

        // Traverse all neurons in the current layer.
        for (unsigned j = 0; j < current_layer->n; j++) {

            double dw = 0.0;

            // Traverse all neurons in the next layer.
            for (unsigned k = 0; k < next_layer->n; k++) {
                dw += next_layer->neurons[k]->delta *
                      next_layer->neurons[k]->weights[j];
            }

            current_layer->neurons[j]->delta =
                dw * current_layer->neurons[j]->dz;
        }
    }
}

// Updates the weights of a feed-forward neural network.
static void fnn_update(struct fnn *nn, double alpha)
{
    // Traverse all layers.
    for (unsigned i = 1; i < nn->n; i++) {
        struct layer *current_layer = nn->layers[i];
        struct layer *previous_layer = nn->layers[i - 1];

        // Traverse all neurons in the current layer.
        for (unsigned j = 0; j < current_layer->n; j++) {

            // Traverse all neurons in the previous layer.
            for (unsigned k = 0; k < previous_layer->n; k++) {
                current_layer->neurons[j]->weights[k] +=
                    alpha * current_layer->neurons[j]->delta *
                    previous_layer->neurons[k]->fz;

                current_layer->neurons[j]->bias +=
                    alpha * current_layer->neurons[j]->delta;
            }
        }
    }
}

// Trains a feed-forward neural network.
void fnn_train(struct fnn *nn, double *input, double *desired_outputs,
               double alpha)
{
    fnn_propagate(nn, input);
    fnn_backpropagate(nn, desired_outputs);
    fnn_update(nn, alpha);
}

// Collects the output of a feed-forward neural network.
void fnn_output(struct fnn *nn, double *output)
{
    struct layer *output_layer = nn->layers[nn->n - 1];
    for (unsigned i = 0; i < output_layer->n; i++) {
        output[i] = output_layer->neurons[i]->fz;
    }
}

// Prints a feed-forward neural network.
static void fnn_print(struct fnn *nn)
{
    for (unsigned i = 0; i < nn->n; i++) {
        printf("Layer %u:\n", i);
        for (unsigned j = 0; j < nn->layers[i]->n; j++) {
            printf("  Neuron %u:\n", j);
            printf("    bias:      %.4f\n", nn->layers[i]->neurons[j]->bias);
            printf("    weights: { ");
            for (unsigned k = 0; k < nn->layers[i]->neurons[j]->n; k++) {
                printf("%.4f ", nn->layers[i]->neurons[j]->weights[k]);
            }
            printf("}\n");
        }
    }
}

//==============================================================================
// Test
//==============================================================================

// Computes the logistic function.
static double logistic_fx(double x)
{
    return (1.0 / (1.0 + exp(-x)));
}

// Computes the derivative of the logistic function.
static double logistic_dx(double x)
{
    return (logistic_fx(x) * (1.0 - logistic_fx(x)));
}

// Computes the rectified linear unit function.
static double relu_fx(double x)
{
    return (x > 0.0 ? x : 0.0);
}

// Computes the derivative of the rectified linear unit function.
static double relu_dx(double x)
{
    return (x > 0.0 ? 1.0 : 0.0);
}

// Test function.
void test(unsigned nepochs, double alpha, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    struct fnn *nn = NULL;
    const unsigned num_layers = 4;
    const unsigned num_neurons[] = {2, 3, 3, 2};
    double (*fx[])(double) = {logistic_fx, relu_fx, relu_fx, logistic_fx};
    double (*dx[])(double) = {logistic_dx, relu_dx, relu_dx, logistic_dx};

    unsigned training_set_size = 4;
    double input_examples[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };
    double output_examples[4][2] = {
        {0, 0},
        {0, 1},
        {0, 1},
        {1, 0},
    };

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    nn = fnn_create(num_layers, num_neurons, fx, dx);

    // Train feed-forward network using gradient descent.
    tstart = clock();
    for (unsigned it = 0; it < nepochs; it++) {
        for (unsigned i = 0; i < training_set_size; i++) {
            fnn_train(nn, input_examples[i], output_examples[i], alpha);
        }
    }
    tend = clock();

    // Report time.
    printf("FNN training: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        fnn_print(nn);

        for (unsigned i = 0; i < training_set_size; i++) {
            double outputs[2];
            fnn_propagate(nn, input_examples[i]);
            fnn_output(nn, outputs);
            printf("Input:  %.4f %.4f\n",
                   input_examples[i][0],
                   input_examples[i][1]);
            printf("Output: %.4f %.4f\n", outputs[0], outputs[1]);
        }
    }

    // Release resources.
    fnn_destroy(nn);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for feed-forward neural network.\n", argv[0]);
    printf("Usage: %s [--verbose] <number of epochs> <learning rate> "
           "<dimension>\n",
           argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned nepochs = 0;
    double alpha = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 3) || (argc > 4)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 3) {
        sscanf(argv[1], "%u", &nepochs);
        sscanf(argv[2], "%u", &alpha);
    } else if ((argc == 4) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &nepochs);
        sscanf(argv[3], "%u", &alpha);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(nepochs, alpha, verbose);

    return (EXIT_SUCCESS);
}
