# Turing-Machine and Finite-Automaton Simulator

This project provides a simulation tool for both Turing-Machines (TM) and Finite-Automaton (FA).
The program expects an input file named "input" which can be either a .tm file for Turing Machines
or a .fa file for Finite State Machines. But if you want you can also do the input manually over 
the console.

TM and Fa represent different types of computational models:

Turing-Machines can represent languages that are recursively enumerable.
Finite-Automaton can only represent regular languages.

## Input File Format

Each list per category must be written in one line representing each element with a comma. Empty
lines or comments (lines starting with '//') will be ignored such as spaces. So use them if you wish.

### Common Format for Both TM and FA

- **All states (Line 1):**
    - List of state names.

- **Initial state (Line 2):**
    - Specifies which state from the previous list will be marked as the "initial state". Each
      simulation with the machine will start in this state.

- **Accepting states (Line 3):**
    - Names all the states which should be marked as "accepting state". These can be multiple ones
      even in fact the initial one.

- **All symbols (Line 4):**
    - List of symbols representing the alphabet. The alphabet is the set of symbols from the language
      represented by the machine.

### Turing Machine (TM) Specific Format

- **Alphabet (Line 5):**
    - List of symbols representing the tape alphabet. Must not have the same letters as the "normal"
      alphabet.

- **Blank Symbol (Line 6):**
    - Symbol representing the blank (empty) space on the tape. Only one letter from the tape alphabet.

### Transition Rules (Enclosed in Curly Braces {})

- **Transition Rule Format (FA):**
    - Each rule must be of the form `SourceState, InputSymbol->TargetState` (e.g., `A,a->B`).

- **Transition Rule Format (TM):**
    - Each rule must be of the form `SourceState(InputSymbol, WriteSymbol, Direction)->TargetState`(
      e.g., `A(b,a:L)->B`).
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