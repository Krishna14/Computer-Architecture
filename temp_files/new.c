uint8_t CustomPredictor(uint32_t pc, uint32_t gHistoryRegister_custom, uint8_t *BHT) {
    uint32_t Global_mask = 0;
    uint32_t Local_mask = 0;
    for(int i=0;i<ghistoryBits;i++)
        Global_mask += (1 << i);
    for(int i=0;i<lhistoryBits;i++)
        Local_mask += (1 << i);
    //Going to be used to index into the local History Tables
    uint32_t pc_masked = pc & Global_mask; 
    uint32_t gHistoryRegister_masked = gHistoryRegister_custom & Global_mask;
    uint32_t XOR_index = compute_XOR(pc_masked, gHistoryRegister_masked);
    uint32_t XOR_index_masked = XOR_index & Global_mask;
    uint8_t Prediction_Global = (*(BHT + XOR_index_masked) >> 1);
    //Local Prediction scheme
    uint16_t index_localHistoryTable = *(localHistoryTable_custom + pc_masked);
    uint16_t actualIndex_LHT = index_localHistoryTable & Local_mask;
    uint8_t Prediction_Local = (*(localPredictionTable + actualIndex_LHT) >> 1);
    //Selection based on which one is right
    uint32_t selector = (*(selectorTable_custom + XOR_index_masked) >> 1);
    uint8_t Prediction = (selector) ? Prediction_Global : Prediction_Local;
    
    return Prediction;
}

void init_predictor() {
    if (bpType == CUSTOM) {
        gHistoryRegister_custom = 0;
        int size_BHT = (1 << gHistoryBits);
        int size_LHT = (1 << gHistoryBits);
        BHT = (uint8_t *) malloc(size_BHT * sizeof(uint8_t));
        LHT = (uint8_t *) malloc(size_LHT * sizeof(uint8_t));
        for(int i=0;i<size_BHT;i++)
            *(BHT+i) = 1;
        for(int i=0;i<size_LHT;i++)
            *(localPredictionTable +i) = 1;
    }
}


