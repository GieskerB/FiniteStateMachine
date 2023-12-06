# Turing Machine and Deterministic Finite Automaton Simulator

This project provides a simulation tool for both Turing Machines (TM) and Finite State Machines (FSM). 
The program expects an input file named "Input," which can be either a .tm file for Turing Machines or a
.fsm file for Finite State Machines.

## Input File Format

### Common Format for Both TM and FSM

- **Nonterminals (Line 1):**
    - List of nonterminal symbols separated by commas (e.g., A, B, C, D).

- **Start State (Line 2):**
    - Single nonterminal symbol representing the start state.

- **Accepting States (Line 3):**
    - List of nonterminal symbols representing the accepting states.

- **Terminals (Line 4):**
    - List of terminal symbols separated by commas.

### Turing Machine (TM) Specific Format

- **Alphabet (Line 5):**
    - List of symbols representing the tape alphabet.

- **Blank Symbol (Line 6):**
    - Symbol representing the blank (empty) space on the tape.

### Transition Rules (Enclosed in Curly Braces {})

- **Transition Rule Format (FSM):**
    - Each rule must be of the form `SourceState, InputSymbol->TargetState` (e.g., `A,a->B`).

- **Transition Rule Format (TM):**
    - Each rule must be of the form `SourceState(InputSymbol, WriteSymbol, Direction)->TargetState`(e.g., `A(b,a:L)->B`).
    - Direction can be one of `L` (left), `R` (right), or `S` (stay).

### Special Characters

The following characters are considered special and need to be escaped with a backslash`\` if you want to use
them explicitly: `{ } , - > ( ) :  L R S`. For example, to use the character `{`, write it as `\{`. Similarly, `\\`
represents the backslash character.

## Example Input File (TM)

```plaintext
A,B,C,D
A
C,D
a,b
e,f,g,#
#
{
    A(a, e:L)->B
    A(b, f:R)->A
    B(a, g:R)->C
    B(b, e:R)->D
    C(a, #:R)->C
    C(b, #:R)->D
    D(a, e:R)->B
    D(b, f:R)->A
}
```

## Example Input File (FSM)

```plaintext
A,B,C
A
C
a,b
{
    A,a->B
    A,b->A
    B,a->C
    B,b->D
    C,a->C
    C,b->D
    D,a->B
    D,b->A
}
```