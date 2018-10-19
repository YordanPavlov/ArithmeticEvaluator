
# Arithmetic evaluator

A parser and evaluator for simple arithmetic expressions. Supported operators are +, -, * and /.
Supported operands are single digit numbers from 0 to 9 along with other nested expressions in
parentheses.

## Dependencies

The project depends on the CPPUnit library for unit testing and the Readline library to provide
an user friendly input console. The project has been developed and tested on Ubuntu linux on
which the needed packages are called libcppunit-dev and libreadline-dev. Those packages should
installed before running the cmake step described below.

## Install

* Clone the project.
* Create a directory inside the project, for example called 'debug'.
* While insde 'debug' do 'cmake ..' to generate a Makefile.
* Build the project binary along with the unit tests with the command 'make'

## Usage

Run the program by executing its binary ./evaluator

## Unit tests

You can execute the unit test by running ./UnitTests

## Development design

The implementation consist of three main steps.

* Firstly parsing takes place, which is done in the 'Parser' class. On this phase is also the expected grammar consider and error is thrown if the
input does not match.
* The second phase is 'treeify-ing' the tokens into an AST structure, the
lower the precedence the higher a token is up the tree. Most of the action happens in BaseNode class.
* Finally the built tree is 'solved' which is the value of the whole expression.
