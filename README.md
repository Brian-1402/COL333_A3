# Hidden organizations finder

COL333 Assignment 3

## Directory structure

### bin/

- Contains minisat binary and compiled binaries made by compile.sh.

### data/

- Test data for help in our testing and debugging.

### debug/

- TA provided data generator programs.

### scripts/

- Contains run1,2,3.sh, compile.sh.
- These work as specified by the assignment instructions, and should be brought outside this folder when submitting.
- But for personal running, we can use the makefile to call these scripts with input and output placed according to the way we want, like outputting .satinput etc. to a temp/ directory instead of to the current directory.

### src/

- The main executable code.

### temp/

- Created during makefile runtime.
- Contains .satinput, .satoutput.

## Submission file structure

_Tentatively,_

- bin/
  - `compiled executables`
  - minisat
- src/
  - `cpp files`
- compile.sh
- minisat (again, if needed by TA)
- run1.sh
- run2.sh
- run3.sh
- writeup.txt
