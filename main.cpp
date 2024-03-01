
#include "includes.inc"

#include <iostream>

/*
class B {
public:
    virtual std::istream& operator>>(std::istream& is) = 0;
};

class A : public B {
public:
    std::istream& operator>>(std::istream& is) override;
};

std::istream& A::operator>>(std::istream& is) {
    // Doing stuff
    return is;
}
// Definition des Eingabeoperators für Objekte der Klasse A
std::istream& operator>>(std::istream& is, A& obj) {
    return obj.operator>>(is);
}

 */


int main() {
    FiniteStateMachine fsm;

    std::cin >> fsm;

	return 0;
}
