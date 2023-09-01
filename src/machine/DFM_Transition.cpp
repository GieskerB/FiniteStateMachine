#ifndef INCLUDE_MACHINE_DFM_TRANSITION_CPP
#define INCLUDE_MACHINE_DFM_TRANSITION_CPP

#include "../../include/machine/DFM_Transition.hpp";


DFM_Transition::DFM_Transition(char letter, State *state) :
    Transition(letter, state, '\0', '\0', '\0') {

}

bool Transition::isValid(char letter, char flag) const {
    return this->letter == letter;
}


#endif
