#include <stdio.h>

int main() {

    return 0;
}

uint8_t PerceptronPredictor(uint32_t pc, uint32_t globalHistoryRegister, uint8_t *Perceptrons) {
    
    uint32_t width_PerceptronTable; 
    uint16_t pc_mask = 0;
    for(int i=0;i<ghistoryBits;i++) {
        pc_mask += 1 << i;
    }
    uint32_t pc_index = pc & pc_mask;
    uint8_t weight = *(Perceptrons + pc_index);
    int dot_product = 0;
    for(int i=0;i<ghistoryBits;i++) {
        uint8_t Perceptron_i = Perceptron & (1 << i);
        uint8_t weight_i = weight & (1 << i);
        dot_product +=  (Perceptron_i >= 0) ? 1*weight_i : -1*weight_i;
    }
    if (dot_product >= 0)
        Prediction_perceptron = 1;
    else
        Prediction_perceptron = 0;
    
    return Prediction_perceptron;
}

void train_perceptron(uint32_t pc, uint8_t outcome, int dot_product) {
    
    int theta;
    uint8_t sign_bit_dot_product = dot_product >> 31;
    if ((sign_bit_dot_product != outcome) || (dot_product <= theta)) {
        for(int i=0;i<width_PerceptronTable;i++) {
            uint8_t GHR_i = GHR & (1 << i);
            *(Perceptrons + i) += *(Perceptrons + i) * (outcome * GHR_i);
        }
    }
}
