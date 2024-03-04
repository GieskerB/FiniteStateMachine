#include "../../include/machine/Machine.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>



void Machine::add_letter(const std::string & new_letter) {
    if(new_letter.size() != 1) {
        throw std::runtime_error("Letters must not have a size unequals tp one!\n");
    }
    m_alphabet.push_back(new_letter[0]);
}

Machine::Machine() :
        m_initial_state_index{-1}, m_deterministic{true} {

}

Machine::~Machine() = default;

void remove_spaces(std::string& str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

std::set<std::string> separate_by_comma(const std::string & line) {
    std::set<std::string> sections{};
    const size_t size = line.size();
    int left_index{0}, right_index{0};
    while (right_index < size) {
        if(line[right_index] == ',') {
            sections.insert(line.substr(left_index, right_index - left_index));
            left_index = right_index+1;
        }
        ++right_index;
    }
    sections.insert(line.substr(left_index, right_index - left_index));

    return sections;
}