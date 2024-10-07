#pragma once
#include <string>

class MachineType {

public:

    const static MachineType FINITE_AUTOMATON;
    const static MachineType TURING_MACHINE;

    const std::string m_file_ending;
    const int m_index;

    bool operator== (const MachineType& other) const;

private:

    MachineType(std::string,int);

};