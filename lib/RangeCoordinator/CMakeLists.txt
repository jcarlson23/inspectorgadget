
#set(SOURCES RangeCoordinator.cpp)
#
#add_llvm_loadable_module(GadgetRange ${SOURCES})
#
#llvm_map_components_to_libnames(llvm_libs bitwriter ipo irreader instcombine instrumentation target linker analysis scalaropts )
#llvm_map_components_to_libnames(llvm_libs analysis)
#
#target_link_libraries(GadgetRange ${llvm_libs})

add_library(GadgetRange MODULE
			RangeCoordinator.cpp
			)

target_compile_features(GadgetRange PRIVATE cxx_range_for cxx_auto_type)

set_target_properties(GadgetRange PROPERTIES
				  COMPILE_FLAGS "-fno-rtti"
				  )

if(APPLE)
	set_target_properties(GadgetRange PROPERTIES
					  LINK_FLAGS "-undefined dynamic_lookup"
					  )
endif(APPLE)




