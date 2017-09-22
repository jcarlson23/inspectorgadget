
set(SOURCES
	RangeCoordinator

add_llvm_loadable_module(GadgetRangeCoordinator ${SOURCES})
add_llvm_Library(LLVMGadgetRangeCoordinator ${SOURCES})

llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )

target_link_libraries(LLVMGadgetRangeCoordinator ${llvm_libs})
target_link_libraries(GadgetRangeCoordinator ${llvm_libs})



