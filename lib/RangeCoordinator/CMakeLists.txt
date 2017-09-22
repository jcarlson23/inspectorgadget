
set(SOURCES RangeCoordinator.cpp)

add_llvm_loadable_module(GadgetRange ${SOURCES})
add_llvm_Library(LLVMGadgetRange ${SOURCES})

llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support)

target_link_libraries(LLVMGadgetRange ${llvm_libs})
target_link_libraries(GadgetRange ${llvm_libs})



