// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_STATES 5
#define NUM_ACTIONS 2
#define ALPHA 0.5
#define GAMMA 0.4
#define EPSILON 0.5
#define MAX_EPISODES 10

struct transition {
    int next_state;
    float reward;
};

struct agent {
    unsigned nstates;
    unsigned nactions;
    float qTable[NUM_STATES][NUM_ACTIONS];
};

float qvalue_get(struct agent *agent, unsigned state, unsigned action)
{
    assert(agent != NULL);
    assert(state < agent->nstates);
    assert(action < agent->nactions);
    return (agent->qTable[state][action]);
}

void qvalue_set(struct agent *agent, unsigned state, unsigned action,
                float value)
{
    assert(agent != NULL);
    assert(state < agent->nstates);
    assert(action < agent->nactions);
    agent->qTable[state][action] = value;
}

void updateQTable(struct agent *agent, int state, int action, int nextState,
                  float reward)
{
    int maxNextAction = 0;
    for (unsigned a = 1; a < agent->nactions; a++) {
        if (qvalue_get(agent, nextState, a) >
            qvalue_get(agent, nextState, maxNextAction)) {
            maxNextAction = a;
        }
    }
    float currentQ = agent->qTable[state][action];
    float maxNextQ = agent->qTable[nextState][maxNextAction];
    agent->qTable[state][action] =
        currentQ + ALPHA * (reward + GAMMA * maxNextQ - currentQ);
}

// Initialize q-table.
void initQTable(struct agent *agent, unsigned nstates, unsigned nactions)
{
    agent->nstates = nstates;
    agent->nactions = nactions;

    for (unsigned s = 0; s < agent->nstates; ++s) {
        for (unsigned a = 0; a < agent->nactions; ++a) {
            agent->qTable[s][a] = 0;
        }
    }
}

// Return action with max Q-value
int bestAction(struct agent *agent, int state)
{
    unsigned maxAction = 0;
    for (unsigned a = 1; a < agent->nactions; a++) {
        if (agent->qTable[state][a] > agent->qTable[state][maxAction]) {
            maxAction = a;
        }
    }
    return maxAction;
}

int randomAction(struct agent *agent, int state)
{
    (void)agent;
    (void)state;
    // Return random action
    return (rand() % agent->nactions);
}

int chooseAction(struct agent *agent, int state)
{
    // Choose action using epsilon-greedy strategy
    if ((double)rand() / RAND_MAX < EPSILON) {
        // Explore: choose random action
        return randomAction(agent, state);
    } else {
        // Exploit: choose action with max Q-value
        return bestAction(agent, state);
    }
}
void qtable_print(struct agent *agent)
{
    // Print learned Q-table
    for (unsigned s = 0; s < agent->nstates; ++s) {
        printf("State %d: [ ", s);
        for (unsigned a = 0; a < agent->nactions; ++a) {
            printf("%.8f ", agent->qTable[s][a]);
        }
        printf("]\n");
    }
}

struct agent AGENT;

struct agent *qlearning(unsigned nepochs,
                        struct transition (*perform)(int, int))
{
    initQTable(&AGENT, NUM_STATES, NUM_ACTIONS);

    // Run Q-learning
    for (unsigned epoch = 0; epoch < nepochs; epoch++) {

        // Start in initial state.
        unsigned currentState = 0;

        while (currentState != (AGENT.nstates - 1)) {

            int action = chooseAction(&AGENT, currentState);

            // Execute action.
            struct transition t = perform(currentState, action);

            updateQTable(&AGENT, currentState, action, t.next_state, t.reward);

            // Take action.
            currentState = t.next_state;
        }
    }

    return (&AGENT);
}

//==============================================================================

struct transition performAction(int currentState, int action)
{
    // Stop.
    unsigned nextState = currentState;

    if ((action == 0) && currentState > 0) {
        // Move left.
        nextState--;
    } else if ((action == 1) && (currentState < NUM_STATES - 1)) {
        // Move Right;
        nextState++;
    }

    // Assign reward.
    float reward = (nextState == NUM_STATES - 1) ? 1.0 : 0.0;

    struct transition t = {nextState, reward};
    return t;
}

void runAgent(struct agent *agent)
{
    // Run agent->
    unsigned currentState = 0;
    printf("Agent path:\n");
    while (currentState != (agent->nstates - 1)) {
        int action = 0;

        if (agent->qTable[currentState][0] > agent->qTable[currentState][1]) {
            action = -1;
        } else if (agent->qTable[currentState][0] <
                   agent->qTable[currentState][1]) {
            action = 1;
        } else {
            printf("Agent did not learn. Taking random action\n");
            action = randomAction(agent, currentState);
        }

        if (currentState > 0 && action == -1) {
            printf("Move to left\n");
            currentState--;
        } else if ((currentState < NUM_STATES) && (action == 1)) {
            currentState++;
            printf("Move to right\n");
        }
    }
}

int main()
{
    struct agent *agent = NULL;

    // Set random seed for reproducibility
    srand(0);

    agent = qlearning(MAX_EPISODES, performAction);
    runAgent(agent);

    return (0);
}
