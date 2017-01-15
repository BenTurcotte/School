Assignment 3 for CIS2520 F16
Author: Ben Turcotte


===============================================================================
RUN INSTRUCTIONS:

To compile
- navigate to HEAP_Bturcott/
- copy the follwoing line & paste it into command line:
	$ gcc -std=c99 HEAP_Bturcott.c -o runme

To run :
- Type "./runme <fileName>” 

===============================================================================
NOTES
- A file called “f.dat” must exist in the home directory
- The file is assumed to be formatted properly
- Improper file format will yield undesirable results
- Properly implements a heap data structure
- Uses array representation of a heap
- I have made the decision to print my heap one object per row. The key
	is the first member to be printed, followed by the
	corresponding information content (see sample output). I hope
	that this decision will not have a negative impact on my mark.


===============================================================================
SAMPLE OUTPUT:

$ ./runme ""
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