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
  wordType PC = getPC();
  byteType byte = getByteFromMemory(PC);
  printf("\nbyte: %x\n", byte);
  getNibbles(byte, icode, ifun);
  printf("icode: %x, ifun %x\n",*icode, *ifun);

  // HALT
  if(*icode == HALT){
    printf("halt");
    *valP = PC + 1; 
  // NOP
  }else if (*icode == NOP){
    printf("nop\n");
    *valP = PC + 1;
  // RRMOVQ
  }else if(*icode == RRMOVQ){
    printf("rrmovq\n");
    byteType args = getByteFromMemory(PC + 1);
    getNibbles(args, rA, rB);
    *valP = PC + 2;
  }
  // IRMOVQ 
  else if (*icode == IRMOVQ){
    printf("IRMOVQ\n");
    byte = getByteFromMemory(PC + 1);
    getNibbles(byte, rA, rB);
    *valC = getWordFromMemory(PC + 2);
    *valP = PC + 10;
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
    *valA = rA;
    printf("ra: %x, rb: %x\n",rA, rB);
  }
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
  // RRMOVQ
  if(icode == RRMOVQ){
    *valE = 0 + valA;
  }
  // IRMOVQ
  if(icode == IRMOVQ){
    *valE = 0 + valC;
    printf("valE: %lx", *valE);
  }
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
 
}

void writebackStage(int icode, int rA, int rB, wordType valE, wordType valM) {
  if (icode == IRMOVQ ||
      icode == RRMOVQ ){
    setRegister(rB,valE);
  }
}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {
  setPC(valP);

  if(icode == HALT){
    setStatus(STAT_HLT);
  }
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