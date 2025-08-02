# Regular Expression Engine in C++

_This project is currently WIP_

**Current features**
- Interactive REPL sessions: Load, show regexes and NFA's.
- NFA explorer (BFS)
- A recursive descent regex parser for the following grammar (in BNF):
  - Trivial syntax error reporting.
```
regex -> alternation
alternation -> concat | concat "|" alternation
concat -> repetition | repetition concat
repetition -> grouping | grouping*
grouping -> literal | "(" regex ")"
literal -> ALPHANUM
```
- Regex to NFA-λ conversion (Thompson's reconstruction algorithm)

**Future features**
- NFA minimization
- NFA to DFA conversion
- Regex equivalence testing
- Enhanced REPL interface, support usage as library.
- Additional regex syntax/features
  - Support additional characters
  - Escape reserved characters
  - Support optionals

**Future improvements**
- Improved parsing for literals

# Acknowledgements
- Formal theory by the `Languages and Automata` course: *Dr J.C. Rot* (Radboud University).
- Textual FSM representation and visual debugging tools: *Ivan Zuzak* and *Vedrana Jankovic*.
  - Their GitHub can be found [here](https://github.com/izuzak/noam/tree/master/webapps/fsm_simulator).
