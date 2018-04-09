### Submission for SecGram 2018

This is to capture high level thoughts that I want to put in the proposal for the GramSec (or maybe it's SecGram) 2018.

#### Introduction

Here we want to encapsulate the use of NCL (Non Deterministic Constrain Logic) gadgets as a means to understand
complexity.  We need to introduce the concept of a __gadget__, as well various kind of gadgets typically found in
real life code.

* Switch/CHOICE
* Latch...

#### Gadgets For Security

Gadgets can encapsulate units of logical flow,and their interactions estimate complexity quite well.  This complexity
is related to security as well as a means for understanding where testing should occurr.  We want to present two
applications that we are currently looking to leverage complexity for.

The first is to identify gadget complexity for code auditing and understanding.  This is looking for __Logic Bombs__ and
and related issues.

The second is to target testing, via fuzzing, or other means to look for flaws.  This is attempting to hook the code
and idnetifying which gadget has been touched via fuzzing.  This is a primary reason for leveraging the LLVM IR form
of the code as an intermediate.

### Graphical Representation of Gadgets

These gadgets are well suited for Graphical representations and investigation.  