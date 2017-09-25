### Working Notes for Inspector Gadget

Just an example session of debugging the pass.


```
$ lldb opt
(lldb) target create "opt"
Current executable set to 'opt' (x86_64).
(lldb) run -load lib/RangeCoordinator/libGadgetRange.so --branch-visit ../programs/operators_ssa.bc
Process 50089 launched: '/Users/jaredcarlson/Projects/llvm-4-debug-build/bin/opt' (x86_64)
WARNING: You're attempting to print out a bitcode file.
This is inadvisable as it may cause display problems. If
you REALLY want to taste LLVM bitcode first-hand, you
can force output with the `-f' option.

  br i1 %cmp, label %if.then, label %if.else
  %cmp = icmp slt i32 %argc, 2
  br label %if.end
  br label %if.end
```