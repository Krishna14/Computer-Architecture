//Data structures required for Tournament branch predictor
#include<stdio.h>

uint16_t *LHT;  //This is store the history of the local branches taken
uint8_t *LPT;   //Local Prediction Table of Saturating counters
uint32_t pc;    //Used to index into the LHT

uint8_t *GPT;   //Global Prediction Table
uint8_t *CPT;   //Choice Prediction Table
uint32_t GHR;   //Global History Register

int lhistoryBits;
int ghistoryBits;
int pcIndexBits;

uint32_t pc_mask = 0;
uint32_t global_mask = 0;
uint32_t local_mask = 0;

for(int i=0;i<lhistoryBits;i++) {
    local_mask += (1 << i);
}
for(int i=0;i<ghistoryBits;i++) {
    global_mask += (1 << i);
}
for(int i=0;i<pcIndexBits;i++) {
    pc_mask += (1 << i++);
}

void init_predictor() {
    GHR = 0;    //Masking
    size_GPT = (1 << ghistoryBits);
    size_LPT = (1 << lhistoryBits);
    size_LHT = (1 << pcIndexBits);

    for(int i=0;i<size_GPT;i++) {
        *(GPT + i) = 1;
        *(CPT + i) = 2;
    }

    for(int i=0;i<size_LHT;i++) {
        *(LHT + i) = 0;
    }

    for(int i=0;i<size_LPT;i++) {
        *(LPT + i) = 1;
    }
}

