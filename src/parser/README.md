# Syntactical Analysis

## Introduction
A `recognizer` is similar to a scanner. Like a scanner, a `recognizer` repeatedly calls the _lex_ function to parse through the data stream. The way in which a recognizer differs from a scanner is that a `recognizer` checks each lexeme produced by the _lex_ function against the grammar. Ultimately, a `recognizer` reports whether or not the entire text is syntactically correct. A recursive descent `recognizer` is composed of a set of functions, each of which corresponds to a rule in the grammar. A `parser*` is a special type of `recognizer` that also builds an abstract representation, called an abstract syntax tree, of the data stream.

## Transforming the grammar
The process for transforming a grammar into a set of recursive descent functions is rather straightforward. Each rule in the grammar becomes a single function that implments that grammar rule. The terms _lhs_ and _rhs_ denote the left-hand side and the right-hand side of the grammar rule, respectively, with the colon serving as the line of demarcation.
* the _lhs_ side of a rule becomes the name of the implementing function - the terminals and non-terminals of the _rhs_ guide the implementation of the body of the function
* each terminal on the _rhs_ corresponds to a call to a function named _match_ - _match_ is used to ensure the given terminal is pending in the data stream
* a vertical bar on the _rhs_ indicates a need to call a predicate function named _check_ or a _pending_ function - these predicate functions are used to see which alternative is present in the data stream
* each non-terminal on the _rhs_ corresponds to a call to the function named by that non-terminal

## Lexical interface functions
The following functions are considered lexical interface functions because they deal with the lexemes that make up the input stream and isolate the recognizer from the details of the lexical analyzer. These functions are used when creating the recursive descent recognizer.
* `advance` move to the next lexeme in the input stream
* `match` like _advance_ but forces the current lexeme to be matched
* `matchNoAdvance` same as _match_ but does not advance the input stream
* `check` check whether or not the current lexeme is of the given type



#
*_not yet implemented_
