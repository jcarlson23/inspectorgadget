

llvm_map_components_to_libnames(llvm_libs BitWriter Core IPO IrReader InstCombine Instrumentation Target Linker Analysis ScalarOpts Support )

add_executable( inspector inspector.cxx )

target_link_libraries( inspector LLVMGadgets ${llvm_libs} )

set_target_properties( inspector PROPERTIES
                           RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )




