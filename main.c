#include <stdio.h>
#include <stdlib.h>

struct transi {
    int curr_state;
    char input;
    int next_state;
};

void print_trace(int* trace, int trace_length) {
    printf("Trace: ");
    for(int i = 0; i < trace_length; i++) {
        printf("%d ", trace[i]);
        if (i < trace_length-1) {
            if (trace[i+1] < 0) {
                printf("-- - -> ");
            } else {
                printf("-- %c -> ", trace[i+1]);
            }
        }
    }
}

void get_automata(int* num_states, int* num_vt, int* num_term, int* num_transition, int** terminals_state, struct transi** transitions) {
    printf("Enter the automata:\n");
    printf("N° of states: ");
    scanf("%d", num_states);
    printf("N° of vt symbols: ");
    scanf("%d", num_vt);
    printf("N° of terminals states: ");
    scanf("%d", num_term);

    // Allocating enough memory for the terminal states array
    *terminals_state = (int *)malloc(*num_term * sizeof(int));
    printf("Terminal States: ");
    for (int i=0; i<*num_term; i++) {
        scanf("%d", &(*terminals_state)[i]);
    }

    printf("N° of transitions: ");
    scanf("%d", num_transition);

    // Allocating enough memory for transitions
    *transitions = (struct transi*) malloc(*num_transition * sizeof(struct transi));
    printf("Enter the transitions (current state - character - next state):\n");
    for(int i=0; i<*num_transition; i++){
        scanf("%d %c %d", &(*transitions)[i].curr_state, &(*transitions)[i].input, &(*transitions)[i].next_state);
        // state - character - state
    }
}

void display_transitions(int num_transition, struct transi* transitions, int num_vt, int num_states) {
    printf("\nTransitions:\n");
    for(int i=0;i<num_transition;i++){
        printf("f(%d, %c) = %d\n", transitions[i].curr_state, transitions[i].input, transitions[i].next_state);
    }

    // Display the table of transitions
    printf("\nTable of Transitions:\n\n");
    printf("  | ");
    //Display headers
    for (char c='a';c<'a'+num_vt;c++){
        printf("%c   ", c);
    }
    printf("\n");

    for (int i=0;i<num_states;i++){
        printf("%d | ", i);
        //loop print a,b,c..... num_vt times
        for (char c='a';c<'a'+num_vt;c++){
            int next_state = -1;
            for (int j=0;j<num_transition;j++){
                if (transitions[j].curr_state == i && transitions[j].input == c){
                    next_state = transitions[j].next_state;
                    break;
                }
            }
            if (next_state == -1){
                printf("    ");
            }
            else{
                printf("%d   ", next_state);
            }
        }
        printf("\n");
    }
}

void test_input(int curr_state, struct transi* transitions, int num_transition, int* terminals_state, int num_term) {
    printf("\nEnter a string to test: ");
    char input[100];
    scanf("%s", input);
    int trace[100];
    int trace_length = 0;
    trace[trace_length++] = curr_state;

    // Loop over the characters in the input string
    for (int i = 0; input[i] != '\0'; i++)
    {
        printf("%d -- %c -> ", curr_state, input[i]);

        // Find the next state using the transition table
        int j;
        for (j = 0; j < num_transition; j++) {
            if (transitions[j].curr_state == curr_state && transitions[j].input == input[i]) {
            curr_state = transitions[j].next_state;
            break;
            }
        }

        // Print the current state
        printf("%d\n", curr_state);

        if (j == num_transition) {
            // No transition found for the current state and input character
            printf("input rejected\n");
            return;
            }
        trace[trace_length++] = curr_state;
    }

    // Check if the final state is one of the terminal states
    for (int i = 0; i < num_term; i++) {
        if (curr_state == terminals_state[i]) {
            printf("input string accepted\n");
            print_trace(trace, trace_length);
            return;
        }
    }

    // Final state is not one of the terminal states
    printf("input string rejected\n");
    print_trace(trace, trace_length);
}
int main() {
    int num_states, num_vt, num_term, num_transition, *terminals_state;
    struct transi *transitions;

    get_automata(&num_states, &num_vt, &num_term, &num_transition, &terminals_state, &transitions);
    display_transitions(num_transition, transitions, num_vt, num_states);
    test_input(0, transitions, num_transition, terminals_state, num_term);

    // Free the dynamically allocated memory
    free(terminals_state);
    free(transitions);

    return 0;
}
