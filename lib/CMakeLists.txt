
set(SOURCES
    Gadgets/Operators.cxx
    Gadgets/JointAnalysis.cxx
    )

set(SCCSources
    SCCS/PrintSCC.cpp
    )

add_subdirectory(RangeCoordinator)

add_llvm_loadable_module(Gadgets ${SOURCES})
add_llvm_library(LLVMGadgets ${SOURCES})

add_llvm_loadable_module(SCCAnalysis ${SCCSources})
add_llvm_library(LLVMSCCAnalysis ${SCCSources})

llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )

target_link_libraries(LLVMGadgets ${llvm_libs})
target_link_libraries(Gadgets ${llvm_libs})

target_link_libraries(LLVMSCCAnalysis ${llvm_libs})
target_link_libraries(SCCAnalysis ${llvm_libs})



