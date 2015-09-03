## Complexity Barrier ##

"Software complexity(and therefore that of bugs) grows to the limits of our ability to manage that complexity."

Boris Beizer, Software Testing Techniques. Second edition. 1990

## Operation ##

When you execute a monkey test, this is consider one test -- the test find a failure of this monkey test finds a new kernel crash or a diagnostic check (fsck) fails.  The monkey test try to exercise the API of the software under test in many random ways -- each exercise attempt will be defined as an operation.  Operations will be stored in a pool.  A list of operations is a subset of operations from the pool.


## Pesticide Paradox ##

“Every method you use to prevent or find bugs leaves a residue of subtler bugs against which those methods are ineffectual.”

Boris Beizer, Software Testing Techniques. Second edition. 1990