#include "Transition.hpp"
#include "../util/DynArray.hpp"

#include <iostream>

class State {

private:

    std::string name;
    bool initial;
    bool final;
    DynArray<Transition> transitions;

public:

    State();
    ~State();

    std::string getName() const;

    bool isInitial() const;
    bool isFinal() const;

    State &getFollowState(char letter);
    DynArray<State> getFollowStates(char letter);

    State &getRandomState();
};

