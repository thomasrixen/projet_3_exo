# Description

This repository contains solutions to exercices provided by the course LEPL1503 - Projet 3 @ UCLouvain

I do *NOT* recommend to use these solutions only to clear the exercices.

These solutions are only provided to unlock you if you're really blocked in an exercice and you don't see how to solve it.

You should always try the exercices by yourself and understand how the code works instead of just copying the answers, this is your responsability as a student, not mine.

# Compilation : 

To compile a C code into an executable :

``` bash
make <src_filename>

ex : make week2    // create the executable week2 from src/week2.c
```

# Run 

 You can run the files from the exe directory after compiling it
 
# File organization

```bash
|
|-- bash_code                     : exercices about shell manipulation
|-- exe                           : directory containing the executables files
|-- makefile_exercice             : directory containing the exercice about modules in C
|-- src                           : directory containing the C source code
|-- supp                          : bonus exercices (about bit_manipulation)
|-- test                          : directory to test code
|-- Makefile                      : generate files
```

# Exercices solutions

<p style="text-align: center;">
|Exercice   | Solution_File|
|:---------|:---------:|
|[S1] Absolute value|[week1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week1.c)
|[S1] Factorial|[week1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week1.c)
|[S1] Through the array|[week1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week1.c)
|[S2] Printing data|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] strcat|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] strlen|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] strcasecmp|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] Palindrome|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] Reading arguments|[arguments.c](https://github.com/Aperence/projet_3_exo/blob/master/src/arguments.c)
|[S2] Swap my integers|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S2] Echange de valeurs de fractions|[week2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week2.c)
|[S3] Improved strcpy|[week3_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_1.c)
|[S3] Coder calloc en utilisant malloc|[week3_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_1.c)
|[S3] Sleepy malloc|[week3_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_1.c)
|[S3] Simple linked list|[week3_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_1.c)
|[S3] Simple Binary Search Tree|[week3_2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_2.c)
|[S3] Le programme test|[test.c](https://github.com/Aperence/projet_3_exo/blob/master/src/test.c)
|[S3] Structures and pointers to structures|[week3_2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week3_2.c)
|[S4] Simple stack|[week4_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week4_1.c)
|[S4] Comparing functions|[week4_1.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week4_1.c)
|[S4] Filtering a linked list|[week4_2.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week4_2.c)
|[S4] Advanced queue|[queue.c](https://github.com/Aperence/projet_3_exo/blob/master/src/queue.c)
|[S4] Ordered linked list|[week4_3.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week4_3.c)
|[S5] File exists|[week5.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week5.c)
|[S5] Save struct into file|[week5.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week5.c)
|[S5] Reading integers in a binary file|[week5.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week5.c)
|[S5] Get and set on array stored in binary file|[week5.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week5.c)
|[S5] File copy|[week5.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week5.c)
|[S6] Sort my points|[week6.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week6.c)
|[S6] Protect the variable|[week6.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week6.c)
|[S6] Do my work|[week6.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week6.c)
|[S6] Shared ressource|[week6.c](https://github.com/Aperence/projet_3_exo/blob/master/src/week6.c)
|[SS2] Bitwise operation: high order bits|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS2] Bitwise operation: extract low order bits|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS2] Bitwise operation: setting a bit|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS2] Bitwise operation: cycling bits|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS2] Bitwise operation: counting set bits|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS2] Bitwise operation: resetting the highest order bit|[bit_manip.c](https://github.com/Aperence/projet_3_exo/blob/master/supp/bit_manip.c)
|[SS] Décomposition d'un programme en modules - Makefile|[makefile_exercice](https://github.com/Aperence/projet_3_exo/tree/master/makefile_exercice)
 
 </p>
