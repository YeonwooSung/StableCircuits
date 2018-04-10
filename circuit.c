#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "subsets.h"

//Allocate the memory to make the new wire.
Wire makeNextWire(char *name, char val, Wire prevWire) {
    Wire newWire = (Wire) malloc(sizeof(struct wire)); //allocate memory for current wire.
    prevWire->next = newWire;
    *(prevWire->isLast) = 0; //as we made new wire, change the value of *(prevWire->isLast) to 0.

    //Allocate memory to fields.
    newWire->name = (char *) malloc(10);
    newWire->val = (char *) malloc(1);
    newWire->isLast = (char *) malloc(1);

    strcpy(newWire->name, name); //set the name of the wire.

    *(newWire->val) = val; //set the value of the wire.
    *(newWire->isLast) = 1; //set the next wire is the last wire.

    return prevWire->next;
}

//Free the allocated memory, which is for Wires.
void freeWires(Wire wire) {
    if (*(wire->isLast) == 0) { //Check if the current wire is the last wire
        freeWires(wire->next); //Call itself recursively.
    }
    free(wire->val);
    free(wire->isLast);
    free(wire->name);
    free(wire);
}

//Allocate the memory to make the new gate.
Gate makeNextGate(Gate prevGate) {
    Gate newGate = (Gate) malloc(sizeof(struct gate)); //Allocate memory to the new gate.

    prevGate->next = newGate;

    //Allocate memory to fields.
    newGate->in1 = (char *) malloc(1);
    newGate->in2 = (char *) malloc(1);
    newGate->out = (char *) malloc(1);
    newGate->gateNum = (char *) malloc(1);
    newGate->isLast = (char *) malloc(1);

    *(prevGate->isLast) = 0; //set the *(prevGate->isLast) to 0.

    *(newGate->isLast) = 1; //to check if the new gate is the last gate.
    *(newGate->in1) = -1;
    *(newGate->in2) = -1;
    *(newGate->out) = -1;
    *(newGate->gateNum) = 0;

    return newGate;
}

//Free the memory, which is allocated to Gates.
void freeGates(Gate root) {

    if (*(root->isLast) == 0) { //check if the gate is last gate.
        freeGates(root->next); //Free the next gates recursively.
    }
    //free the allocated memory
    free(root->gateNum);
    free(root->in1);
    free(root->in2);
    free(root->out);
    free(root->isLast);
    free(root);
}

//Make the new node and store it in the linked list.
struct node * makeNode(struct node *prev) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node)); //allocate memory to the node.

    newNode->val = (char *) malloc(5);
    newNode->isLast = (char *) malloc(1);

    prev->next = newNode; //linke the previous node and new node.
    *(prev->isLast) = 0;
    *(newNode->isLast) = 1;
    *(newNode->val) = -1;

    return newNode; //return the new node.
}

//Free the allocated memory.
void freeNode(struct node *n) {
    if (*(n->isLast) == 0) { //check if the current node is NULL.
        freeNode(n->next); //Call itself recursively.
    }
    free(n->isLast);
    free(n->val);
    free(n); //Free the allocated memory.
}

void trim(char *input) {
    char *dst = input, *src = input;
    char *end;

    // Skip whitespace at front...
    //
    while (isspace((unsigned char)*src)) {
        ++src;
    }

    // Trim at end...
    //
    end = src + strlen(src) - 1;
    while (end > src && isspace((unsigned char)*end)) {
        *end-- = 0;
    }

    // Move if needed.
    //
    if (src != dst) {
        while ((*dst++ = *src++));
    }
}

//Check if the wire name is constructed with number and lower case letter(s).
char validateWireName(char *name) {
    if (*name == '\0') {
        return -1;
    }

    char checker = 0;

    char str[20];
    strcpy(str, name);
    int i = 0;

    while (str[i] != '\0') { //iterate the loop until the program reads all characters in the loop.
        if ( !( islower(str[i]) || isdigit(str[i])) ) {
            if (str[i] == '\n') { //check if the current character is a next line character.
                continue;
            }
            checker = 1; //if the character is neither lower letter nor number, set the value of checker as 1.
            printf("Invalid wire name: %s\n", name);
        }
        i += 1;
    }

    return checker; //Return 1 if the given name is invalid. Otherwise, return 0.
}

//Find the last wire by calling itself recursively.
Wire findLastWire(Wire wire) {
    if (*(wire->isLast) == 1) {//check if there is next wire, to check if the current wire is the last wire.
        return wire;
    }
    return findLastWire(wire->next); //Call itself recursively.
}

//Find the last gate by calling itself recursively.
Gate findLastGate(Gate gate) {
    if (*(gate->isLast) == 1) {//check if the current gate is the last gate.
        return gate;
    }
    return findLastGate(gate->next);
}

// Check if the wire with the given name is created already. And modify the value of the counter, which depicts the index of the wire.
void findWire(Wire wire, char *name, char *counter, char *checker) {

    if (strcmp(wire->name, name) == 0) {
        return;
    } else {
        *counter += 1; //increase the value of the counter by 1.

        if (*(wire->isLast) == 1) { //Check if the wire is the last one.
            *checker = 1; //change the value of the checker to 1. This means that the program need to make a new wire with the given name.
            return;
        }
        findWire(wire->next, name, counter, checker); //call itself recursively to check if the wire with the given name is created already.
    }

}

//Get the value of the particular wire.
char getTheValueOfWireByName(Wire wire, char *name) {
    if (strcmp(wire->name, name) == 0) { //checks the name of the wire by comparing the name of the wire with the given string
        //return the corresponding wire's value.
        return *(wire->val);
    } else {
        return getTheValueOfWireByName(wire->next, name);
    }
}

//Get the corresponding wire.
Wire getTheWireByName(Wire wire, char *name) {
    if (strcmp(wire->name, name) == 0) { //checks the name of the wire by comparing the name of the wire with the given string
        //return the corresponding wire.
        return wire;
    } else {
        return getTheWireByName(wire->next, name); //Call itself recursively to check the next wire.
    }
}

// Tokenize the input line, and iterate tokens to set fields of wire and gate until the token is NULL.
Name iterateTokenUntilNull(char *str, Gate gate, Wire wire, Name name) {
    char *token = strtok(str, " "); // Use the strtok function to tokenize the given string.
    char result = 0; //To validate the gate's name.
    char indexFlag = 0; //The aim of this variable is to check the index of the wire in the input line.

    char inGateFlag = 0; //The aim of this variable is to check whether the current gate is IN or not.
    char *inGateResult = (char *) malloc(20);

    long storeWireMemAddress = (long) wire;

    while (token) {

        if (isupper(*token)) { //Check if the token string starts with the upper case letter.
            trim(token); //trim the white space character.

            result = checkIfNand(token); //If so, check if it's a gate name.

            if (result != 0) { //If it's a gate name
                *(gate->gateNum) = result; //set the value of the gate number as a value of result.

                if (result == 3) { //check if the current gate is IN.
                    inGateFlag = 1; //if so, set the value of the inGateFlag as 1.
                }

            } else { //If it's not a gate name
                puts("\n<warning> Gates: EQ, NOT, NOR, OR, NAND, XOR, AND, IN\n");
                break;
            }
        } else {
            trim(token); //trim the white space character.
            //check the wires.
            if (validateWireName(token) == 0) {

                char counter = 0;

                char checker = 0;

                Wire temp = (Wire) storeWireMemAddress; //make the temporal Wire variable to check if the wire with the given name is created already.
                findWire(temp, token, &counter, &checker);

                if (checker == 1) {
                    makeNextWire(token, 0, findLastWire(wire));
                }

                //Use the switch to check if the wire is the output wire of the gate or one of the input wires of the gate.
                switch (indexFlag) {
                    case 0 : *(gate->out) = counter; //if the indexFlag is 0, set the output wire as a value of (*counter).
                        strcpy(inGateResult, token);
                        break;
                    case 2 : *(gate->in1) = counter; //if the indexFlag is 2, set the first input wire as a value of (*counter).
                        break;
                    case 3 : *(gate->in2) = counter; //if the indexFlag is 3, set the second input wire as a value of (*counter).
                        break;
                    default : puts("Too many wires to the single gate"); //As a default case, print out the warning message.
                }
            }
        }

        token = strtok(NULL, " ");

        indexFlag += 1; //Increase the indexFlag to go to the next index.
    }

    if (inGateFlag == 1) {
        name = makeNode(name);
        if (sizeof(inGateFlag) == 1) {
            *name->val = *inGateResult;
            *(name->val + 1) = '\0'; //add the terminator
        } else {
            strcpy(name->val, inGateResult);
        }
    }

    free(inGateResult);
    return name;
}

//Generate the initial wires, zero, one, and out.
Wire generateInitialWire() {
    Wire wire = (Wire) malloc(sizeof(struct wire));

    //Allocate memory to fields.
    wire->name = (char *) malloc(20);
    wire->val = (char *) malloc(1);
    wire->isLast = (char *) malloc(1);

    strcpy(wire->name, "zero"); //set the wire name as zero.
    *(wire->val) = 0;
    *(wire->isLast) = 1;

    makeNextWire("out", 0, makeNextWire("one", 1, wire) ); //make the wire one first, then make the wire out.

    return wire; //return the generated wire.
}

//Get the value of the input wire.
void getInputWire(Wire wire, const char *index, char *val) { //Get the wires, target index, and the variable to store the value of the wire as parameters.
    char countWires = 0;

    while (*index > countWires) { //Check if the current index is less than the target index.

        wire = wire->next;
        countWires += 1;
    }
    *val = *(wire->val); //set the val as a value of the current wire.
}

//Change the value of the output wire.
void changeTheOutputWire(Wire wire, const char *index, const char *val) {

    char countWires = 0;

    while (*index != (countWires++)) { //Check if the current index is less than the target index.
        wire = wire->next;
    }

    *(wire->val) = *val; //set the value of the target wire as a value of the val.
}

//Process the circuit.
void processCircuit(Gate gate, Wire wires) {

    char in1 = 0;
    char in2 = 0;
    char out = 0;

    //Get the input wires' values.
    getInputWire(wires, gate->in1, &in1);
    getInputWire(wires, gate->in2, &in2);

    switch (*(gate->gateNum)) {
        case 0 : break; //0 is the error number, thus, get out the switch statement.
        case 1 : operateAnd(in1, in2, &out); //operate the AND gate.
            break;
        case 2 : operateEq(in1, in2, &out); //operate the EQ gate.
            break;
        case 3 : break; //Do nothing if the gate is IN.
        case 4 : operateNand(in1, in2, &out); //operate the NAND gate.
            break;
        case 5 : operateNor(in1, in2, &out); //operate the NOR gate.
            break;
        case 6 : operateNot(in1, &out); //operate the NOT gate.
            break;
        case 7 : operateOr(in1, in2, &out); //operate the OR gate.
            break;
        case 8 : operateXor(in1, in2, &out); //operate the XOR gate.
            break;
        default : puts("Error: Undefined behaviour!"); //As there are 8 gates, the program will print out the warning message for other numbers.
    }

    if (*(gate->isLast) == 0) {
        processCircuit(gate->next, wires); //Call itself recursively to process all gates.
    }

    if (*(gate->gateNum) == 3) { //check if the gate is IN.
        return; //if so, do not change anything, and terminate the function.
    }
    changeTheOutputWire(wires, gate->out, &out); //Set the value of the output wire.
}

//This function will count the total number of wires.
char countNumOfWire(Wire wire) {
    char numOfWire = 1;

    while (*(wire->isLast) == 0) { //check if the next node is NULL.
        numOfWire += 1; //If not, increase the value of the numOfWire.
        wire = wire->next;
    }

    return numOfWire;
}

//Count the number of names.
char countNumOfName(Name name) {
    if (*(name->isLast) == 1) {
        return 0;
    }
    char numOfName = 1;

    while (*(name->isLast) == 0) { //check if the next node is NULL.
        numOfName += 1; //If not, increase the value of the numOfName.
        name = name->next;
    }
    return numOfName;
}

// Print out the name of the output wire of the IN gate.
void printNames(Name name) {
    printf("%s ", name->val); //print out the name
    if (*(name->isLast) == 0) {
        printNames(name->next); //call itself recursively to print out all names in the linked list.
    }
}

//Check if the circuit is stabilised.
char isStabilised(Wire wire, Values values) {
    //iterate the while loop until it gets the last wire.
    while (*(wire->isLast) == 0) {
        if (*(wire->val) != *(values->val)) { //check if it is not stabilised.
            return 0;
        }
        wire = wire->next; //change the pointer to the next wire.
        values = values->next; //change the pointer to the next value.
    }
    if (*(wire->val) != *(values->val)) { //check if it is not stabilised.
        return 0;
    }
    return 1; //return 1 if the circuit is stabilised.
}

//make new nodes and store values in it.
void storeValues(Values values, Wire wires) {
    while (*(wires->isLast) == 0) {
        values = makeNode(values);
        *(values->val) = *(wires->val);
        wires = wires->next;
    }
    values = makeNode(values);
    *(values->val) = *(wires->val);
}

//Check if the "out" wire is used in the circuit.
char checkIfOutWireIsUsed(Gate gate) {

    while (*(gate->isLast) == 0) {

        if (*(gate->out) == 2 || *(gate->in1) == 2 || *(gate->in2) == 2) {
            return 1;
        }

        gate = gate->next;
    }

    if (*(gate->out) == 2 || *(gate->in1) == 2 || *(gate->in2) == 2) {
        return 1;
    }

    return 0;
}

//Iterate the while loop to process the circuit to check if the circuit stabilised.
char iterateProcess(Gate gate, Wire wire, long long totalNum) {

    char stabilised = 0; //if the circuit stabilises, set this variable as 1.

    //Make the Values type variable, which will be used to check the stabilisation.
    Values values = (Values) malloc(sizeof(struct node));
    values->val = (char *) malloc(1);
    values->isLast = (char *) malloc(1);
    *(values->isLast) = 1;

    while (totalNum > 0) { //iterate the loop until the value of the totalNum is greater than 0.
        processCircuit(gate, wire); //process the circuit.

        if (totalNum == 2) { //check if this is the second last turn.

            *(values->val) = *(wire->next->next->val); //set the stabiliseChecker as a value of the "out" wire.
            if (*(wire->next->next->isLast) == 0) { //check if it's the last wire.
                storeValues(values, wire->next->next->next);
            }

        }
        totalNum -= 1;
    }

    //check if the previous turn's "out" wire's value is equal to the current value of the "out" wire.
    stabilised = isStabilised(wire->next->next, values);

    freeNode(values); //free the allocated memory.

    return stabilised; //return 1 if the circuit is stabilised.
}

//This function change all wire values to zero.
void changeAllWireValuesToZero(Wire wire) {
    while (*(wire->isLast) == 0) { //check if the current node is the last node.
        *(wire->val) = 0;
        wire = wire->next;
    }
    *(wire->val) = 0;
}

//This function change all wire values to one.
void changeAllWireValuesToOne(Wire wire) {
    while (*(wire->isLast) == 0) { //check if the current node is the last node.
        *(wire->val) = 1;
        wire = wire->next;
    }
    *(wire->val) = 1;
}

//Print the value of the all output wires of the IN gates.
void printInputValues(Wire wire, Name name) {

    char val = getTheValueOfWireByName(wire, name->val);

    printf("%d ", val); //print out the node's value.

    if (*(name->isLast) == 1) { //check if the next node is the last node.
        return;
    }

    printInputValues(wire, name->next);
}

//Print out the result of the circuit.
void printTheResult(Gate gate, Wire wire, long long totalNum) {
    if (iterateProcess(gate, wire, totalNum) == 1) {
        printf("%d\n", *(wire->next->next->val)); //print out the stabilised value.
    } else {
        printf("?\n"); //print out "?" if the circuit is not stabilised.
    }
}

//Generate the binary string to print out the n rows of the truth table
void genearteBinary(long long num, long long targetNum, char *str) {

    while (targetNum >>= 1) { //iterate the while loop with the shift operator.
        //use the bit wise operators to generate the binary string.
        *str++ = (char) !!(targetNum & num);
    }
}

//This function will be called if the circuit contains the IN gate.
//This will process the circuit with all possible inputs, and generate the suitable truth table as an output.
void processAllPossibleCircuits(Gate gate, Wire wire, Name name, long long int totalNum) {
    char totalNumOfNodes = countNumOfName(name->next); //count the number of nodes.

    if (totalNumOfNodes == 0) {
        printInputValues(wire, name->next);
        printTheResult(gate, wire, totalNum); //print the result of the circuit.
        changeAllWireValuesToZero(wire->next->next); //change all wire values to zero.

        Wire target = getTheWireByName(wire, name->next->val);
        *(target->val) = 1;

        printInputValues(wire, name->next);
        printTheResult(gate, wire, totalNum); //print the result of the circuit.
        return;
    }

    long long targetNum = (long long) pow (2, (double) totalNumOfNodes);

    //As we could run the circuit with 0 and 1 for the initial value of the wire, iterate the loop 2^(total number of nodes) times.
    long long numToIterate = (long long) pow(2, (double)totalNumOfNodes);

    Wire targetWires[totalNumOfNodes]; //A Wire type array to store all wires in it.

    //Iterate the for loop to initialize the wire array.
    for (long long i = 0; i < totalNumOfNodes; i++) {
        Name targetName = name->next;
        int index = totalNumOfNodes - 1;
        index -= i;

        for (int j = 0; j < index; j++) targetName = targetName->next;

        targetWires[i] = getTheWireByName(wire, targetName->val); //initialize all elements of the Wire array.
    }

    //Iterate the for loop n times, where the n is the total number of IN gates.
    for (long long i = 0; i < numToIterate; i++) {
        char *str = (char *) malloc((int)totalNumOfNodes + 1); //
        genearteBinary(i, targetNum, str);
        int count = 0;

        char currentIndex = totalNumOfNodes - 1;
        char indexOfWire = 0;

        while (count++ < totalNumOfNodes) {
            *(targetWires[(int)indexOfWire]->val) = *(str + currentIndex);
            currentIndex -= 1;
            indexOfWire += 1;
        }

        printInputValues(wire, name->next);
        printTheResult(gate, wire, totalNum); //print the result of the circuit.
        changeAllWireValuesToZero(wire->next->next); //change all wire values to zero.

        free(str);
    } //for loop ends.
}

//Read the input string by using the getline with while loop.
void readInput(Gate gate, Wire wire, Name inNames, FILE *stream) {
    char *buffer = NULL;
    size_t len = 0;

    int initChecker = 1;

    //Loop the while loop until the there is no given input line.
    while (getline(&buffer, &len, stream) != -1) { //Use the getline function to get the input string and store it in the variable "buffer".

        if (initChecker == 1) { //if the value of counter is 1, run the codes in the if statement.
            initChecker -= 1; //modify the value of the initChecker to 0.
        } else { //if the value of the counter is not 1

            gate = makeNextGate(findLastGate(gate));

        }

        inNames = iterateTokenUntilNull(buffer, gate, wire, inNames); //Tokenize the input string, and make the wire and gates.
    }

    free(buffer); //free the allocated memory.
}

//The main function, which is the starting point of the circuit program.
int main(int argc, char *argv[]) {

    FILE *stream; //to store the input stream that the program will use.

    if (argc < 2) { //check there is any command line argument.
        stream = stdin; //if there is no command line argument, use the standard input stream.
    } else {
        stream = fopen(argv[1], "r"); //Open the file stream to read the file.

        if (stream == NULL) {
            printf("File not found: %s\n", argv[1]);
            return 0;
        }
    }

    //Make the root gate.
    Gate gate = (Gate) malloc(sizeof(struct gate));

    //Allocate memory to fields.
    gate->out = (char *) malloc(1);
    gate->in1 = (char *) malloc(1);
    gate->in2 = (char *) malloc(1);
    gate->gateNum = (char *) malloc(1);
    gate->isLast = (char *) malloc(1);

    //Initialise the fields.
    *(gate->out) = -1;
    *(gate->in1) = -1;
    *(gate->in2) = -1;
    *(gate->isLast) = 1;

    //Make the initial wires by calling the generateInitialWire function.
    Wire wire = generateInitialWire();

    //Allocate the memory to make the linked list that stores the name of the output wire of the IN gate.
    Name inNames = (Name) malloc(sizeof(struct node));
    inNames->val = (char *) malloc(5);
    strcpy(inNames->val, "init");
    inNames->isLast = (char *) malloc(1);
    *(inNames->isLast) = 1;
    inNames->next = NULL; //set the next node as NULL.

    readInput(gate, wire, inNames, stream); //read the user input to make gates and wires for the circuit.

    long long totalNum = countNumOfWire(wire);
    /*
     * If there are 2^(number of wires) different states then the very last state might be the one it stablisise for.
     * Thus, I set the bound of the circuit loop as "2^(number of wires) + 1".
     */
    totalNum = (long long) pow(2, (double)totalNum) + 1;

    if (*(inNames->isLast) == 0) {
        printNames(inNames->next); //print out the names of the output wires of the IN gates.
    }
    printf("out \n"); //print out the name of the "out" wire.

    if (*(inNames->isLast) == 1) { //check if there is any output wire of the IN gate.
        printTheResult(gate, wire, totalNum);
    } else { //Otherwise (if there is more than one name of the output wire of the IN gate).
        processAllPossibleCircuits(gate, wire, inNames, totalNum);
    }

    //Free the allocated memory.
    freeNode(inNames);
    freeGates(gate);
    freeWires(wire);

    if (argc >= 2) {
        fclose(stream); //close the opened file.
    }

    return 0;
}
