Best to view this in a window with a width of at least 80 characters.


Author: Ben Turcotte
Bturcott - 0832217 - Assignment 4 for CIS2520 F16


DESCRIPTION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

This program implements the AVL tree data structure. It allows initialization
  from a file, manually insertion (one-by-one), manual removal, height & size
  updates, key search, & search all above a given frequancy.

The program was originally written for my Data Structures (CIS*2520) A4.


COMPILATION :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Navigate to home directory ("AVL_Bturcott").

To compile
- Type "make" (not case-sensitive) into cmd then press <enter>.

To run
- Type "./runme" into cmd then press <enter>.


REFERENCES ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

- I found code on github for an avl tree implementation. I made modified
    versions of a few of the functions that the author, Tony Thompson, wrote.
    These functions involved inserting and rebalancing.

    link: https://gist.github.com/tonious/1377768#file-avl-c


NOTES :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

- It wasn't all that clear as to weather the size of the tree was the sum of
    the frequencies of each node or if it was just the number of nodes. My
    program treats size as the number of nodes.
    
    i.e. Given a tree with two nodes with frequencies of 3 and 5, the size of
         the tree would be 2 (not 8).

- Program should work with all .txt files where each key is separated by a
    space or a newline character.

- If your testing file does not work, I have included the two files that I have
    used to test the program: smallData.txt & A4Data.txt

- Removal function is a bit djanky looking but it works.

- main() is at the very bottom.

- If the frequency of the node-to-be-removed is 1, it's key & updated frequency
    of 0 is printed to the screen, then the node is deleted.

- If a match is not found for removal, a "node_not_found" message will be
    printed to the screen.

- Upon quitting the program, all dynamically allocated memory is freed.


SAMPLE OUTPUT :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Two different test runs are provided:
  - one only uses the data file provided by our prof
  - one uses that file in conjunction with user-inserted (menu option 3) keys


-------------------------------------------------- JUST WITH PROVIDED DATA FILE

Bens-MacBook-Pro-4:Bturcott_A4 Ben$ make
gcc -Wall -std=c99 avltree.c -o runme
Bens-MacBook-Pro-4:Bturcott_A4 Ben$ ./runme
::::::::::::::::::::::::::::::::
          Ben Turcotte
       Bturcott - 0832217
::::::::::::::::::::::::::::::::

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 1
filename: A4Data.txt

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 24, size: 1483

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 6
frequency: 2500
key: flr117, frequency: 7458
key: flr1453, frequency: 3085
key: flr1857, frequency: 3072
key: flr1971, frequency: 2702
key: flr2255, frequency: 3645
key: flr2910, frequency: 9790
key: flr549, frequency: 5590
key: wrn104, frequency: 2715

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 6
frequency: 25000
no_such_key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 4
remove key: wrn104
key: wrn104, frequency: 2714

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: wrn94
key: wrn94, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 4
remove key: wrn94
key: wrn94, frequency: 0

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: wrn94
no_such_key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 24, size: 1482

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 7
Bens-MacBook-Pro-4:Bturcott_A4 Ben$


------------------------------------------------------------ TESTING EVERYTHING

Bens-MacBook-Pro-4:Bturcott_A4 Ben$ make
gcc -Wall -std=c99 avltree.c -o runme
Bens-MacBook-Pro-4:Bturcott_A4 Ben$ ./runme
::::::::::::::::::::::::::::::::
          Ben Turcotte
       Bturcott - 0832217
::::::::::::::::::::::::::::::::

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: 1
key: 1, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: 2
key: 2, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: 3
key: 3, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: 1
key: 1, frequency: 2

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: newKey
key: newKey, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 3, size: 4

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 4
remove key: 3
key: 3, frequency: 0

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 2, size: 3

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: 3
no_such_key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 4
remove key: 3
no_such_key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: newKey
key: newKey, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 1
filename: A4Data.txt

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 24, size: 1486

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: flr830
key: flr830, frequency: 414

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 6
frequency: 3000
key: flr117, frequency: 7458
key: flr1453, frequency: 3085
key: flr1857, frequency: 3072
key: flr2255, frequency: 3645
key: flr2910, frequency: 9790
key: flr549, frequency: 5590

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 6
frequency: 30000
no_such_key

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: anotherKey
key: anotherKey, frequency: 1

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 3
insert key: newKey
key: newKey, frequency: 2

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 24, size: 1487

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 2
find key: flr830
key: flr830, frequency: 414

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 4
remove key: flr830
key: flr830, frequency: 413

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 5
height: 24, size: 1487

1. Initialization
2. Find
3. Insert
4. Remove
5. Check height & size
6. Find all
7. Exit
avl/> 7
Bens-MacBook-Pro-4:Bturcott_A4 Ben$ 