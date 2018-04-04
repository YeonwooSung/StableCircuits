#include <stdio.h>
#include <string.h>
#include "subsets.h"

// Check if the given gate is IN. If not, this function will return 0, which is an error number.
char checkIfIn(char *gateName) {

    int val = strcmp(gateName, "IN"); //check if the gateName is equal to IN.
    char result = 0;

    if (val == 0) {
        result = 3; //If the gate name is IN, set the result as 3. Otherwise, the return value would be 0, the error number.
    }

    return result;
}

// Check if the given gate is AND. If not, this function will return 0, which is an error number.
char checkIfAnd(char *gateName) {

    int val = strcmp(gateName, "AND"); //check if the gateName is equal to AND.
    char result = 0;

    if (val == 0) {
        result = 1; //If the gate name is AND, set the result as 1. If not, the return value would be 0, the error number.
    }

    return result;
}

// Check if the given gate is EQ.
char checkIfEq(char *gateName) {

    int val = strcmp(gateName, "EQ"); //check if the gateName is equal to EQ.
    char result = 0;

    if (val == 0) {
        result = 2; //If the gate name is AND, set the result as 2.
    } else if (val > 0) {
        result = checkIfIn(gateName); //if the val is greater than 0, call the checkIfIn function.
    } else {
        result = checkIfAnd(gateName); //if the val is less than 0, call the checkIfAnd function.
    }

    return result;
}

// Check if the gate name is XOR. If not, the error number 0 will be returned.
char checkIfXor(char *gateName) {

    int val = strcmp(gateName, "XOR"); //check if the gateName is equal to XOR.
    char result = 0;

    if (val == 0) {
        result = 8; //If val is 0, set the result as 8. Otherwise, the value of the result would be 0, which is an error number.
    }

    return result;
}

// Check if the given gate is OR.
char checkIfOr(char *gateName) {

    int val = strcmp(gateName, "OR"); //check if the gateName is equal to OR.
    char result = 0;

    if (val == 0) {
        result = 7; //Set the result as 7, if the val is 0.
    } else if (val > 0) {
        result = checkIfXor(gateName); //If the val is greater than 0, call the checkIfXor function.
    }
    //If the val is less than 0, the error number 0 will be returned.

    return result;
}

// Check if the given gate is NOR. If not, it will return the error number 0.
char checkIfNor(char *gateName) {

    int val = strcmp(gateName, "NOR"); //check if the gateName is equal to NOR.
    char result = 0;

    if (val == 0) {
        result = 5; //Set the result as 5, if the val is 0. Otherwise, the value of the result would be 0.
    }

    return result;
}

// Check if the given gate is NOT.
char checkIfNot(char *gateName) {

    int val = strcmp(gateName, "NOT"); //check if the gateName is equal to NOT.
    char result = 0;

    if (val == 0) {
        result = 6;
    } else if (val > 0) {
        result = checkIfOr(gateName);
    } else {
        result = checkIfNor(gateName);
    }

    return result;
}

// Check if the given gate is NAND.
char checkIfNand(char *gateName) {

    int val = strcmp(gateName, "NAND");
    char result = 0;

    if (val == 0) {
        result = 4;
    } else if (val > 0) {
        result = checkIfNot(gateName);
    } else {
        result = checkIfEq(gateName);
    }

    return result;
}

//This is a function to process the gate NOT.
void operateNot(char *in, char *out) {
    if (*in == 0) { //check if *in is 0
        *out = 1;
    } else if (*in == 1) {
        *out = 0;
    }
}

//This is a function to process the gate AND.
void operateAnd(char *in1, char *in2, char *out) {
    if (*in1 == 1 && *in2 == 1) { //check if (*in1) is 1 and if (*in2) is 1.
        *out = 1;
    } else {
        *out = 0;
    }
}

//This is a function to process the gate OR.
void operateOr(char *in1, char *in2, char *out) {
    if (*in1 == 1 || *in2 == 1) { //check if (*in1) is 1 or if (*in2) is 1.
        *out = 1;
    } else {
        *out = 0;
    }
}

//This is a function to process the gate NOR.
void operateNor(char *in1, char *in2, char *out) {
    if (*in1 == 0 && *in2 == 0) { //check if the (*in1) is 0, or (*in2) is 0.
        *out = 1;
    } else {
        *out = 0;
    }
}

//This is a function to process the gate NAND.
void operateNand(char *in1, char *in2, char *out) {
    if (*in1 ==1 && *in2 == 1) { //check if the (*in1) and (*in2) is both 0.
        *out = 0;
    } else {
        *out = 1;
    }
}

//This is a function to process the gate EQ.
void operateEq(char *in1, char *in2, char *out) {
    if (*in1 == *in2) { //check if the (*in1) is equal to (*in2).
        *out = 1;
    } else {
        *out = 0;
    }
}

//This is a function to process the gate XOR.
void operateXor(char *in1, char *in2, char *out) {
    if (*in1 != *in2) { //check if the (*in1) is not equal to (*in2).
        *out = 1;
    } else {
        *out = 0;
    }
}
