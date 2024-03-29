# FiniteStateMachine
This is an attempt to create and simulate different types of finite p_target_state machines in C++

### Finite p_target_state machines that are planed:
* DeterministicFiniteMachine
* StackMachine
* TuringMachine
  * If possible we will also give the use the option to create a non m_deterministic version for each Machine

Erstellen eines solchen Atomaten:

* DFA: 5 Tupel
  * Zustände
  * Alphabet
  * Übergangsfunktionen
  * Startzusand
  * Endzustände
    * X -> yY

* PDA: 7 Tupel
  * Zustände
  * Wortalphabet
  * Kelleralphabet
  * Übergangsfunktionen
  * KellerZeichen
  * Startzusand
  * Endzustände

* Turing 7 Tupel
  * Zustände
  * Wortalphabet
  * Kelleralphabet
  * Übergangsfunktionen
  * KellerZeichen
  * Startzusand
  * Endzustände




<!-- Headings -->
# Heading 1
## Heading 2
### Heading 3
#### Heading 4
##### Heading 5
###### Heading 6

<!-- Italics -->
*This text* is italic
_This text_ is italic

<!-- Strong -->
**This text** is bold
__This text__ is bold

<!-- Strikethrough -->
~~This text~~ is strikethrough

<!-- Horizontal Rule -->
---
___

<!-- Blockquote -->
> This is a quote

<!-- Links -->
[Youtube](http://www.youtube.com)
[Youtube](http://www.youtube.com "YouTube")

<!-- UL -->
* Item 1
* Item 2
* Item 3
  * Nested Item 1
  * Nested Item 2

<!-- OL -->
1. Item 1
1. Item 2
1. Item 3

<!-- Inline Code Block -->
`This is a paragraph`

<!-- Images -->
![Markdown Logo](https://markdown-here.com/img/icon256.png)

<!-- Github Markdown -->
<!-- Code Blocks -->

```javascript
  function add(num1, num2) {
    return num1 + num2;
  }
```

```cpp
 int main() {
    for (int i = 0; i< 10; i++) {
        std::cout << "Hellom World!" << std::endl;
    }
    return 0;
 }
```

<!-- Tables -->
| Name     | Email          |
| -------- | -------------- |
| TEST     | test@gmail.com |
| LOOOL    | lol@gmail.com  |

<!-- Task List -->
* [x] Task 1
* [x] Task 2
* [ ] Task 3