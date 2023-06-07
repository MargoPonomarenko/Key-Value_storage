# Key-Value_storage
The main goal of the project is to create a key-value storage system that manages data by putting, getting, updating, and deleting it. The storage supports several data types, such as strings, doubles, and vectors of strings.

## Description
An additional piece of business logic is the ability to manage the data life cycle and automatically delete outdated information that has not been used for a specified period of time. The project is implemented as a DLL library that allows you to store data locally and can be connected to another project to use its functionality.
[Here](https://docs.google.com/document/d/1jWaxV8nOFNxoqLmteZJdnjIW9B0O0P9KGE37pW4EZG4/edit?usp=sharing) you can check out the design document for this project.

## Building the app and running tests
```bash
# run from a directory that contains a .pro file
$ qmake

# for running tests
$ ./tst_keyvaluestorageteste -test
```
