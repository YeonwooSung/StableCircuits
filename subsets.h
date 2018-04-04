#ifndef SUBSETS_H // header file wrapper.
#define SUBSETS_H

//The structure for gate.
typedef struct gate {
    char *gateNum;
    char *out;
    char *in1;
    char *in2;
    char *isLast; //check if the current gate is the last gate.
    struct gate *next;
} *Gate;

struct node {
    char *val;
    char *isLast;
    struct node *next;
};

typedef struct node *Name;

//The prototype of the checkIfNand function, to check the name of the gate in the circuit.c file.
char checkIfNand(char *);

typedef struct wire {
    char *name; //The name of the wire.
    char *val; //The value of the wire.
    char *isLast; //Check if the current gate is the last gate.
    struct wire *next; //Pointer to the next wire.
} *Wire;

//Prototypes of the functions that will process the circuit.
void operateNot(char , char *);
void operateEq(char , char , char *);
void operateAnd(char , char , char *);
void operateOr(char , char , char *);
void operateNor(char , char , char *);
void operateNand(char , char , char *);
void operateXor(char , char , char *);

#endif //PRACTICAL4_SUBSETS_H
