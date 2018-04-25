## Inspector Gadget

This tool attempts to find non-deterministic constraint logic gadgets within LLVM IR.  The pursuit of this
work is to find gadgets within dis-similar source but similar logic.  While functional programming allows
for more automated proof capabilities the underlying logic of the program.

### Goals

The goals of this research is to find those logical similarities and subtleties that architects and
researchers would be interested for finding bugs, improper logic, and so forth.

### Building

The 'build.sh' script is useful as a driver to build either a Release and/or Debug versions of the
libraries and tools.

### Sample

A simple run of the Gadget Pass is:

```opt -load lib/RangeCoordinator/libGadgetRange.so --branch-visit < ../programs/operators_ssa.bc ```


## Architecture

The gadget discovery proess follows these steps.

* Obtain branch edges from the topologically sorted BB's.  Note that we'll actually do this
with SCCS as that makes a little more sense from a theoretical perspective as well as having builtin
functionality.
* As a default we color branches with only a single output block as "red" (weight 2).
* We catalog nodes, looking for the correct number of incoming & outgoing branches.
* This gives us a first estimate of  CHOICE, AND, OR gadgets.
* From here we enter an iterative loop to construct additional gadgets.
