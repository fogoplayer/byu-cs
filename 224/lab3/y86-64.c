#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define DEBUG = true;

const int MAX_MEM_SIZE  = (1 << 13);

void getNibbles(byteType byte, int *n1, int *n2){
  *n1 = (byte >> 4) & 0x0f;
  *n2 = byte & 0x0f;
}

void fetchStage(int *icode, int *ifun, int *rA, int *rB, wordType *valC, wordType *valP) {
#ifdef DEBUG
  printf("---------\n");
#endif
  wordType PC = getPC();
  byteType byte = getByteFromMemory(PC);
  getNibbles(byte, icode, ifun);

  if (*icode == HALT){
#ifdef DEBUG
      printf("HALT\n");
#endif    
  }
  // NOP
  else if (*icode == NOP){
#ifdef DEBUG
      printf("nop\n");
#endif
    *valP = PC + 1;
  // RRMOVQ
  // OPq
  // PUSHQ
  // POPQ
  }else if (*icode == RRMOVQ ||
            *icode == OPQ    ||
            *icode == PUSHQ  ||
            *icode == POPQ){
#ifdef DEBUG
      printf("rrmovq | OPQ | PUSH | POP %x\n", *icode);
#endif
    byteType args = getByteFromMemory(PC + 1);
    getNibbles(args, rA, rB);
    *valP = PC + 2;
  }
  // IRMOVQ 
  // RMMOVQ
  // MRMOVQ
  else if  (*icode == IRMOVQ ||
            *icode == RMMOVQ ||
            *icode == MRMOVQ){
#ifdef DEBUG
    printf("IRMOVQ | RMMOVQ | MRMOVQ\n");
#endif
    byteType args = getByteFromMemory(PC + 1);
    getNibbles(args, rA, rB);
    *valC = getWordFromMemory(PC + 2);
    *valP = PC + 10;
  // JXX
  }else if(*icode == JXX){
    *valC = getWordFromMemory(PC + 1);
    *valP = PC + 9;
  }


  //Temp to just keep things moving
  else {
    *valP = PC + 1;
  }

  return;
}

void decodeStage(int icode, int rA, int rB, wordType *valA, wordType *valB) {
  // RRMOVQ
  if(icode == RRMOVQ){
    *valA = getRegister(rA);
  }
  // RMMOVQ
  // OPQ
  else if (icode == RMMOVQ ||
           icode == OPQ) {
    *valA = getRegister(rA);
    *valB = getRegister(rB);
  }
  // MRMOVQ
  else if (icode == MRMOVQ){
    *valB = getRegister(rB);
  }
  // PUSHQ
  else if (icode == PUSHQ) {
    *valA = getRegister(rA);
    *valB = getRegister(RSP);
  }
  // POPQ
  else if (icode == POPQ) {
    *valA = getRegister(RSP);
    *valB = getRegister(RSP);
  }
#ifdef DEBUG
  printf("ra: %x, rb: %x\n",rA, rB);
#endif
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
  // RRMOVQ
  if(icode == RRMOVQ){
    *valE = 0 + valA;
  }
  // IRMOVQ
  else if(icode == IRMOVQ){
    *valE = 0 + valC;
  }
  // RMMOVQ
  // MRMOVQ
  else if(icode == RMMOVQ) {
    *valE = valB + valC;
  }
  // OPQ
  else if(icode == OPQ) {
    bool overflow = 0; // FALSE

    if(ifun == ADD){
      *valE = valB + valA;
      overflow = ((valA < 0) == (valB < 0)) && ((*valE < 0) != (valA < 0)); // I think this is only valid for addition, but I'll have to fix that later (Maybe fixed?)
    }else if(ifun == SUB){
      *valE = valB - valA;
      overflow = ((valA < 0) == (valB < 0)) && ((*valE < 0) != (valA < 0));
    }else if(ifun == AND){
      *valE = valB & valA;
    }else if(ifun == XOR){
      *valE = valB ^ valA;
    }

    setFlags(
      (*valE < 0), // SF
      (*valE == 0), // ZF
      overflow //OF
    );
  }
  // PUSHQ
  else if(icode == PUSHQ) {
    *valE = valB - 8;
  }
  // POPQ
  else if(icode == POPQ) {
    *valE = valB + 8;
  }
  // JXX
  else if(icode == JXX){
    *Cnd = Cond(ifun);
  }
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
  // RMMOVQ
  if(icode == RMMOVQ) {
    setWordInMemory(valA, valE);
  }

  // MRMOVQ
  else if(icode == MRMOVQ) {
    *valM = getWordFromMemory(valE);
  }

  // PUSHQ
  else if(icode == PUSHQ){
    setWordInMemory(valE,valA);
  }

  // POPQ
  else if (icode == POPQ) {
    *valM = getWordFromMemory(valA);
  }
}

void writebackStage(int icode, int rA, int rB, wordType valE, wordType valM) {
  if (icode == IRMOVQ ||
      icode == RRMOVQ ||
      icode == OPQ){
    setRegister(rB,valE);
  }

  // PUSHQ
  else if (icode == PUSHQ){
    setRegister(RSP, valE);
  }
  // POPQ
  else if (icode == POPQ){
    setRegister(RSP, valE);
    setRegister(rA, valM);
  }
}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {
  setPC(Cnd ? Cnd : valP );

  if(icode == HALT){
    setStatus(STAT_HLT);
  }
#ifdef DEBUG
  // printf("Registers:\n");
  // for(int i = 0; i < 15; i++){
  //   printf("Register %x: %ld\n", i, getRegister(i));
  // }
#endif
}

void stepMachine(int stepMode) {
  /* FETCH STAGE */
  int icode = 0, ifun = 0;
  int rA = 0, rB = 0;
  wordType valC = 0;
  wordType valP = 0;
 
  /* DECODE STAGE */
  wordType valA = 0;
  wordType valB = 0;

  /* EXECUTE STAGE */
  wordType valE = 0;
  bool Cnd = 0;

  /* MEMORY STAGE */
  wordType valM = 0;

  fetchStage(&icode, &ifun, &rA, &rB, &valC, &valP);
  applyStageStepMode(stepMode, "Fetch", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  decodeStage(icode, rA, rB, &valA, &valB);
  applyStageStepMode(stepMode, "Decode", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  executeStage(icode, ifun, valA, valB, valC, &valE, &Cnd);
  applyStageStepMode(stepMode, "Execute", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  memoryStage(icode, valA, valP, valE, &valM);
  applyStageStepMode(stepMode, "Memory", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  writebackStage(icode, rA, rB, valE, valM);
  applyStageStepMode(stepMode, "Writeback", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  pcUpdateStage(icode, valC, valP, Cnd, valM);
  applyStageStepMode(stepMode, "PC update", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  incrementCycleCounter();
}

/** 
 * main
 * */
int main(int argc, char **argv) {
  int stepMode = 0;
  FILE *input = parseCommandLine(argc, argv, &stepMode);

  initializeMemory(MAX_MEM_SIZE);
  initializeRegisters();
  loadMemory(input);

  applyStepMode(stepMode);
  while (getStatus() != STAT_HLT) {
    stepMachine(stepMode);
    applyStepMode(stepMode);
#ifdef DEBUG
    printMachineState();
    printf("\n");
#endif
  }
  printMachineState();
  return 0;
}