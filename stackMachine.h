/*
 * Stack Machine
 * Until a stopping instruction is read, it will continually read segments
 * of code and execute the cooresponding instruction while maintaining a
 * runtime stack
 */
#ifndef STACK_MACHINE
#define STACK_MACHINE

#include <stdio.h>

//List of internal operations
//Will be used to interpret and execute the segment of code read
enum codeOps {STOP, GOTO, LT, GT, EQ, ADD, SUB, MUL, DIV, POW, STORE};

//List of external operations
//A copy of the internal operations list
char *opName[] = {"stop", "goto", "lt", "gt", "eq", "add", "sub", "mul", "div", "pow", "store"};

//A structure defining an instruction
//op:	operation insturction
//arg:	argument
struct instruction {
	enum codeOps op;
	int arg;
};

//Code segment to be interpreted
struct instruction code[999];
//Stack to maintain data
int stack[999];

//Registers
//Program Counter - points to address of instruction currently executing
int pc = 0;
//Instruction Register - holds the current instruction executing
struct instruction ir;
//Activation Record - points to the begining of current activation record
int ar = 0;
//Top - points to the top of the stack
int top = 0;

//Fetch and Execute
//Continually fetches the next instruction until stop instruction is met
//Manipulates the stack based on the instruction read
void fetchAndExecute() {
	do{
		//Fetch instruction at pc then increment pc
		ir = code[pc++];

		//Execute instruction
		switch(ir.op){
			case STOP:
				printf("STOPPING\n");
				break;
			case GOTO:
				pc = ir.arg;
				break;
			case LT:
				if(stack[top-1] < stack[top])
					stack[--top] = 1;
				else
					stack[--top] = 0;
				break;
			case GT:
				if(stack[top-1] > stack[top])
					stack[--top] = 1;
				else
					stack[--top] = 0;
				break;
			case EQ:
				if(stack[top-1] == stack[top])
					stack[--top] = 1;
				else
					stack[--top] = 0;
				break;
			case ADD:
				stack[top-1] = stack[top-1] + stack[top];
				top--;
				break;
			case SUB:
				stack[top-1] = stack[top-1] - stack[top];
				top--;
				break;
			case MUL:
				stack[top-1] = stack[top-1] * stack[top];
				top--;
				break;
			case DIV:
				stack[top-1] = stack[top-1] / stack[top];
				top--;
				break;
			case POW:
				stack[top-1] = stack[top-1] * stack[top];
				top--;
				break;
			case STORE:
				stack[ir.arg] = stack[top--];
				break;
			default:
				printf("ERROR - stackMachine.h\n");
				break;
		}
	}while(ir.op != STOP);
}

#endif
