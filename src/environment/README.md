# Environments

## Implementing environments and scope
The purpose of an environment is two fold: to hold the bindings between variables and their values and to implement scope. The `environment` structure is simply a list of parallel lists. A new environment is created using the `createEnvironment` function. The new environment created by `createEnvironment` has no bindings and is represented internally as two empty lists in a list.

The environment subsystem provides six basic operation:
* `createEnvironment` creates and returns an empty environment. The new empty environment consists of one empty table in the list of tables.
* `lookupEnvironment` searches for a variable starting from the most local table and proceeding to the most outer table. The value of the first occurrence of the queried variable is returned.
* `updateEnvironment` rebinds a new value to the queried identifier. The value of the first occurrence of the queried identifier is updated to the new value. The new value is returned by the function.
* `insertEnvironment` inserts an identifier and a value into the most local table. This function returns the value inserted.
* `extendEnvironment` extends a given environment with a list of identifiers and values. The new environment created by the function is returned with the identifiers and values placed in a table at the head of the given environment. The given environment remains unmodified.
* `printEnvironment` prints the environment to a file pointer. A flag parameter is provided that allows the caller to set whether the function only prints the local environment or prints the entired enclosing environment.

## Looking up and updating variables

## Inserting a new variable

## Extending an environment
