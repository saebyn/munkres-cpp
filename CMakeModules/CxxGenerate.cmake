macro (cxxtest_generate outFile inFiles)
    set (${outFile} "${CMAKE_CURRENT_BINARY_DIR}/cxxtestsuite.cpp")
    add_custom_command (
        OUTPUT  ${${outFile}}
        COMMAND ${CXXTESTGEN} --runner=ErrorPrinter --output ${${outFile}} ${inFiles}
        DEPENDS ${inFiles}
    )
    #message (STATUS "Process file:" ${inFiles})
    #message (STATUS "Out file:    " ${${outFile}})
    set_source_files_properties (${${outFile}} PROPERTIES GENERATED TRUE)
    add_custom_target (CxxTestGenerate ALL DEPENDS ${${outFile}})
endmacro (cxxtest_generate)
