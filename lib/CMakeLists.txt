
set(SOURCES
    Gadgets/Operators.cxx)

add_subdirectory(RangeCoordinator)

add_llvm_loadable_module(Gadgets ${SOURCES})
add_llvm_Library(LLVMGadgets ${SOURCES})

llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )

target_link_libraries(LLVMGadgets ${llvm_libs})
target_link_libraries(Gadgets ${llvm_libs})



