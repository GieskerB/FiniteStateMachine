#include <utility>

#include "../../include/machine/MachineType.hpp"

const MachineType MachineType::FINITE_AUTOMATON {".fa",0};
const MachineType MachineType::TURING_MACHINE {".tm",1};

bool MachineType::operator==(const MachineType &other) const {
    return m_index == other.m_index;
}

MachineType::MachineType(std::string file_ending, int index) : m_file_ending(std::move(file_ending)), m_index(index) {}