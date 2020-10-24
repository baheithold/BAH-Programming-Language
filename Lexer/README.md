# Lexer and Scanner

## Introduction

## Lexical Analysis
Lexical analysis is the first stage of implementing a programming language. Lexical analysis is the process of identifying tokens in a file of characters. The analyzer is also tasked with categorizing those tokens as to they represent. This subsystem is made up of four modules: `types`, `lexeme`, `lexer`, and `scanner`.

## Types
The `types` module contains definitions for keywords, types, operators, punctuation, and various other useful constructs. The `types` module is used by the `lexer` and the `scanner` modules during lexical analysis of a file.

## Lexeme

## Lexer

## Scanner
The `scanner` repeatedly calls the `lex` function from the `lexer` and displays the resulting lexemes.
