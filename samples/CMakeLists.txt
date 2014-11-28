# CMake configuration for ttmath/samples

# Building with Visual C++ x86_64 needs to compile the asm utilities first
if (MSVC AND "x${CMAKE_VS_PLATFORM_NAME}" STREQUAL "xx64")
  set(TTMATH_MSVC64_ASM ttmathuint_x86_64_msvc.asm) 
  enable_language(ASM_MASM)
  message(STATUS "Enabled MASM to compile '${TTMATH_MSVC64_ASM}'")
  set(TTMATH_SRC_ASM ${ttmath_SOURCE_DIR}/ttmath/${TTMATH_MSVC64_ASM})
endif()

set(SAMPLES big big2 int uint parser)
foreach(sample ${SAMPLES})
	add_executable(${sample} ${sample}.cpp ${TTMATH_SRC_ASM})
	# Allow to run all utilities at once as a test
	add_test(${sample} ${sample})
endforeach()