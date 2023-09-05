#ifndef INCLUDE_MACHINE_DFM_TRANSITION_HPP
#define INCLUDE_MACHINE_DFM_TRANSITION_HPP

#include "Transition.hpp";

/*
 * DFM Transiton initialising the isValid Method in the cpp
 * Also adding a Constructor which does not need any flags
 */
class DFM_Transition : public Transition {

public:
    DFM_Transition(char letter, State *state);

};


#endif
