#---------------------------------------------------------------------------------------
# Set tools
#---------------------------------------------------------------------------------------
#set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT})
#set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objdump${TOOLCHAIN_EXT})
#set(CMAKE_SIZE ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT})

SET(CMAKE_OBJCOPY "${TOOLCHAIN_ROOT_PATH}/bin/fromelf.exe")

#---------------------------------------------------------------------------------------
# Prints the section sizes
#---------------------------------------------------------------------------------------
function(print_section_sizes TARGET)
    set(ASM_FILE ${PROJECT_BINARY_DIR}/${TARGET}.asm)
    add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -z ${TARGET}
            COMMAND ${CMAKE_OBJCOPY} -c --cpu=${CMAKE_SYSTEM_PROCESSOR} $<TARGET_FILE:${TARGET}> --output=${ASM_FILE}
    )
endfunction()

#---------------------------------------------------------------------------------------
# Creates output in hex format
#---------------------------------------------------------------------------------------
function(create_hex_output TARGET)
    set(HEX_FILE ${PROJECT_BINARY_DIR}/${TARGET}.hex)
    add_custom_target(${TARGET}.hex ALL DEPENDS ${TARGET} COMMAND ${CMAKE_OBJCOPY} --i32 $<TARGET_FILE:${TARGET}> --output=${HEX_FILE})
endfunction()

#---------------------------------------------------------------------------------------
# Creates output in binary format
#---------------------------------------------------------------------------------------
function(create_bin_output TARGET)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${TARGET}.bin)
    add_custom_target(${TARGET}.bin ALL DEPENDS ${TARGET}  COMMAND ${CMAKE_OBJCOPY} --bin $<TARGET_FILE:${TARGET}> --output=${BIN_FILE})
endfunction()
