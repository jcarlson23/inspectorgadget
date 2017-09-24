
set(SOURCES RangeCoordinator.cpp)

add_llvm_loadable_module(GadgetRange ${SOURCES})

#target_link_libraries(LLVMGadgetRange ${llvm_libs})




