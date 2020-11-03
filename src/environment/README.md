# Environments

## Implementing environments and scope
The purpose of an environment is two fold: to hold the bindings between variables and their values and to implement scope. The environment is implemented internally using a list of parallel lists. A new environment is created using the `createEnvironment` function. The new environment created by `createEnvironment` has no bindings and is represented internally as two empty lists in a list.

** The use of `table` in this document refers to the list of parallel lists used in the environment structure to store the bindings between identifiers and values;

The environment subsystem provides six basic operation:
* `createEnvironment` creates and returns an empty environment. The new empty environment consists of one empty table in the list of tables.
* `lookupEnvironment` searches for a variable starting from the most local table and proceeding to the most outer table. The value of the first occurrence of the queried variable is returned.
* `updateEnvironment` rebinds a new value to the queried identifier. The value of the first occurrence of the queried identifier is updated to the new value. The new value is returned by the function.
* `insertEnvironment` inserts an identifier and a value into the most local table. This function returns the value inserted.
* `extendEnvironment` extends a given environment with a list of identifiers and values. The new environment created by the function is returned with the identifiers and values placed in a table at the head of the given environment. The given environment remains unmodified.
* `printEnvironment` prints the environment to a file pointer. A flag parameter is provided that allows the caller to set whether the function only prints the local environment or prints the entired enclosing environment.

## Looking up and updating variables
Looking up the value of an identifier is as simple as finding the identifier/value binds within the tables. The tables are searched for the corresponding identifier from the most local table to the most outer table. If no identifier is found, then an undefined identifier error is thrown.

Updating the value of an identifier works in the same way as looking up a value except that the value is changed in the update function.

## Inserting a new variable
A new identifier and value binding is inserted into the most local environment at the time of definition. Internally, the most local environment is the first table (the first two lists) in the environments list. The new binding is added to the head of the parallel lists. An advantage of adding new bindings to the head of the parallel lists, is that this placement allows for redefinitions of identifiers to shadow previous definitions within the same scope.

## Extending an environment
Extending an environment takes place when nesting scopes inside of other scopes. This might happen when, for instance, functions are defined with formal parameters. Environment extension is accomplished by first creating a new empty environment. The next step is to populate the new environment with the identifier/value bindings defined in the new environment. The final step is to link the new environment with its enclosing environment.
