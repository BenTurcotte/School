Ben Turcotte - 0832217 - Assignment 3 for CIS2520 F16

=================================================================================
RUN INSTRUCTIONS:

To compile, type "make" (not case-sensitive) into command line then press <enter>.

To run my program for part 1:
- Type " ./runme q1 “<infix expression>” ” into command line and press <enter>.

To run my program for part 2:
- Type "./runme q2”

=================================================================================
NOTES
On part 1:
- The infix arithmetic expression must be within a set of brackets
	Legall:		./runme q1 “(((3.05+7.12)*5.20)+(8.11/(4.44-2.87)))"
	Illegal:	./runme q1 “((3.05+7.12)*5.20)+(8.11/(4.44-2.87))"
- The tree doesn’t print well/properly
- Inorder, Preorder, and Post order will all work provided the input adheres
	to the above format.
- Does not evaluate the expression
- Does not allow variable values to be updated
- Properly implements a binary tree data structure.

On part 2:
- A file called “f.dat” must exist in the home directory
- The file is assumed to be formatted properly
- Improper file format will yield undesirable results
- Properly implements a heap data structure
- Uses array representation of a heap
- I am a bit concerned about the printing portion of part 2. The instructions
	on the assignment are ambiguous. There are two instructions that
	contradict each other:

	(1) “The program treats each row of the array as an object, with the
		sum of the first three integers being the key, and the other
		seven integers being the information content.”

	(2) “The program finally displays the heap as a 20x10 array, a row
		for an object”

	By instruction (1), our object will have 8 members: the key, and the
		seven integers that make up the information content. However,
		by instruction(2), we are expected to print one object per
		row in a 20x10 array. This is problematic because our objects
		do not contain 10 members. They contain 8. It is impossible
		for us to print the 20x10 row that we are asked for.

	I have made the decision to print my heap one object per row. The key
		is the first member to be printed, followed by the
		corresponding information content (see sample output). I hope
		that this decision will not have a negative impact on my mark.

All of the code I am submitting is completely original. I expect some
	unconventional implementations as a by-product of my persistence
	with respect to trying to problem solve on my own. I look forward
	to finding what areas to improve on.

=================================================================================
SAMPLE OUTPUT PART 1:

$ ./runme q1 "(((3.05+7.12)*5.20)+(8.11/(4.44-2.87)))"

---------- MENU ----------
(1) Display
(2) Preorder
(3) Inorder
(4) Postorder
(5) Update
(6) Calculate
(7) Quit

2
User entered: 2
  + 3.05 7.12 * 5.20 + / 8.11 - 4.44 2.87 
---------- MENU ----------
(1) Display
(2) Preorder
(3) Inorder
(4) Postorder
(5) Update
(6) Calculate
(7) Quit

3
User entered: 3
(((3.05+7.12)*5.20))+(8.11/(4.44-2.87))))
---------- MENU ----------
(1) Display
(2) Preorder
(3) Inorder
(4) Postorder
(5) Update
(6) Calculate
(7) Quit

4
User entered: 4
3.05 7.12 + 5.20 *  8.11 4.44 2.87 - / +  
---------- MENU ----------
(1) Display
(2) Preorder
(3) Inorder
(4) Postorder
(5) Update
(6) Calculate
(7) Quit

7
User entered: 7

=================================================================================
SAMPLE OUTPUT PART 2:

$ ./runme q2
Key: 260  Info:  0	63	24	54	20	20	24
Key: 203  Info:  88	39	30	44	59	49	72
Key: 208  Info:  11	21	4	8	97	93	14
Key: 139  Info:  23	14	81	82	0	38	4
Key: 186  Info:  93	57	6	29	91	92	39
Key: 137  Info:  53	36	54	69	68	38	43
Key: 178  Info:  86	42	44	48	64	41	1
Key: 90   Info:  59	4	84	10	42	43	2
Key: 114  Info:  90	74	56	64	75	67	55
Key: 176  Info:  40	29	84	24	61	87	20
Key: 185  Info:  46	69	42	74	68	79	28
Key: 65   Info:  44	59	87	32	36	36	46
Key: 77   Info:  88	15	39	88	69	31	49
Key: 137  Info:  21	9	69	5	30	20	91
Key: 139  Info:  96	70	98	85	13	25	47
Key: 54   Info:  82	52	53	5	3	68	64
Key: 57   Info:  99	29	99	79	45	59	19
Key: 110  Info:  32	33	54	60	33	51	87
Key: 80   Info:  68	49	68	74	32	9	30
Key: 127  Info:  65	40	39	44	49	32	60