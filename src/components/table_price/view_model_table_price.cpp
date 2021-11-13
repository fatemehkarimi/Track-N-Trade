#include "view_model_table_price.h"
#include <iostream>

PriceTableViewModel::PriceTableViewModel() {

}

void PriceTableViewModel::setPair(std::shared_ptr <Pair> pair) {
    this->pair = pair;
}