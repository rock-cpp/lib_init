
macro(init_gen_pkgconfig)
    SET(infile "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}
libdir=\${prefix}/lib/orocos
includedir=\${prefix}/include

Name: ${LIB_NAME}
Description: Init module for ${LIB_NAME}
Version: ${PROJECT_VERSION}
Requires: ${${LIB_NAME}_DEPS_PKGCONFIG} ${LOCAL_PROXY_LIB} ${LOCAL_INIT_LIB}
Libs: -L\${libdir} -l${LIB_NAME}
Cflags: -I\${includedir}")

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}.pc ${infile})
    install(
        FILES 
            ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}.pc
        DESTINATION 
            lib/pkgconfig)

endmacro()

macro(init_module)
    pkg_check_modules(LIB_INIT REQUIRED "lib_init")
    #PROJECT_NAME is defined by orogen
    SET(LIB_NAME ${PROJECT_NAME}-init)
    #parse HEADER and SOURCE etc
    cmake_parse_arguments(${LIB_NAME} "" "" "SOURCES;HEADERS;DEPS;DEPS_PKGCONFIG" ${ARGN})
#         message("Found ${${ARG_LIST}_SOURCES}")

    SET(MODULE_LIBS)
    SET(MODULE_LIBS_DIRS)
    SET(MODULE_INC_DIRS)
    SET(MODULE_CFLAGS)
    
    foreach(PKG_DEPENDENCY ${${LIB_NAME}_DEPS_PKGCONFIG})
        pkg_check_modules(${PKG_DEPENDENCY} REQUIRED ${PKG_DEPENDENCY})
        list(APPEND MODULE_LIBS ${${PKG_DEPENDENCY}_LIBRARIES})
        list(APPEND MODULE_LIBS_DIRS ${${PKG_DEPENDENCY}_LIBRARY_DIRS})
        list(APPEND MODULE_INC_DIRS ${${PKG_DEPENDENCY}_INCLUDE_DIRS})
#         message("PKGConfig ${PKG_DEPENDENCY} adds include ${${PKG_DEPENDENCY}_INCLUDE_DIRS}")
#             list(APPEND MODULE_CFLAGS ${${PKG_DEPENDENCY}_CFLAGS})
        list(APPEND MODULE_CFLAGS ${${PKG_DEPENDENCY}_CFLAGS_OTHER})
    endforeach()

    list(REMOVE_DUPLICATES MODULE_LIBS)
    list(REMOVE_DUPLICATES MODULE_LIBS_DIRS)
    list(REMOVE_DUPLICATES MODULE_INC_DIRS)
    list(REMOVE_DUPLICATES MODULE_CFLAGS)
    
#     message("Libs ${MODULE_LIBS}")
#     message("Libs dirs ${MODULE_LIBS_DIRS}")
#     message("inc dirs ${MODULE_INC_DIRS}")
#     message("cflags ${MODULE_CFLAGS}")

    link_directories(${MODULE_LIBS_DIRS})
    include_directories(${MODULE_INC_DIRS})
    add_definitions(${MODULE_CFLAGS})
    
    add_library(${LIB_NAME} SHARED ${${LIB_NAME}_SOURCES})
    
    if(${PROJECT_NAME}-proxies)
        target_link_libraries(${LIB_NAME} ${PROJECT_NAME}-proxies)
        SET(LOCAL_PROXY_LIB ${PROJECT_NAME}-proxies)
    endif()
    
    foreach(DEPENDENCY ${${LIB_NAME}_DEPS})
        target_link_libraries(${LIB_NAME} ${DEPENDENCY})
    endforeach()

    target_link_libraries(${LIB_NAME} ${MODULE_LIBS})

    init_gen_pkgconfig()
    
    install(
        FILES 
            ${${LIB_NAME}_HEADERS}
        DESTINATION 
            include/lib_init)
    install(TARGETS ${LIB_NAME}
        LIBRARY DESTINATION 
            lib/orocos)
endmacro()

macro(replay_module)
    pkg_check_modules(LIB_INIT REQUIRED "lib_init")
    #PROJECT_NAME is defined by orogen
    SET(LIB_NAME ${PROJECT_NAME}-replay)
    #parse HEADER and SOURCE etc
    cmake_parse_arguments(${LIB_NAME} "" "" "SOURCES;HEADERS;DEPS;DEPS_PKGCONFIG" ${ARGN})
#         message("Found ${${ARG_LIST}_SOURCES}")

    SET(MODULE_LIBS "")
    SET(MODULE_LIBS_DIRS "")
    SET(MODULE_INC_DIRS "")
    SET(MODULE_CFLAGS "")
    
    foreach(PKG_DEPENDENCY ${${LIB_NAME}_DEPS_PKGCONFIG})
        pkg_check_modules(${PKG_DEPENDENCY} REQUIRED ${PKG_DEPENDENCY})
        list(APPEND MODULE_LIBS ${${PKG_DEPENDENCY}_LIBRARIES})
        list(APPEND MODULE_LIBS_DIRS ${${PKG_DEPENDENCY}_LIBRARY_DIRS})
        list(APPEND MODULE_INC_DIRS ${${PKG_DEPENDENCY}_INCLUDE_DIRS})
#         message("PKGConfig ${PKG_DEPENDENCY} adds include ${${PKG_DEPENDENCY}_INCLUDE_DIRS}")
#             list(APPEND MODULE_CFLAGS ${${PKG_DEPENDENCY}_CFLAGS})
        list(APPEND MODULE_CFLAGS ${${PKG_DEPENDENCY}_CFLAGS_OTHER})
    endforeach()

    list(REMOVE_DUPLICATES MODULE_LIBS)
    list(REMOVE_DUPLICATES MODULE_LIBS_DIRS)
    list(REMOVE_DUPLICATES MODULE_INC_DIRS)
    list(REMOVE_DUPLICATES MODULE_CFLAGS)
    
#     message("Libs ${MODULE_LIBS}")
#     message("Libs dirs ${MODULE_LIBS_DIRS}")
#     message("inc dirs ${MODULE_INC_DIRS}")
#     message("cflags ${MODULE_CFLAGS}")

    link_directories(${MODULE_LIBS_DIRS})
    include_directories(${MODULE_INC_DIRS})
    add_definitions(${MODULE_CFLAGS})
    
    add_library(${LIB_NAME} SHARED ${${LIB_NAME}_SOURCES})
    
    if(${PROJECT_NAME}-proxies)
        target_link_libraries(${LIB_NAME} ${PROJECT_NAME}-proxies)
        SET(LOCAL_PROXY_LIB ${PROJECT_NAME}-proxies)
    endif()

    if(${PROJECT_NAME}-init)
        target_link_libraries(${LIB_NAME} ${PROJECT_NAME}-init)
        SET(LOCAL_INIT_LIB ${PROJECT_NAME}-init)
    endif()
    
    foreach(DEPENDENCY ${${LIB_NAME}_DEPS})
        target_link_libraries(${LIB_NAME} ${DEPENDENCY})
    endforeach()

    target_link_libraries(${LIB_NAME} ${MODULE_LIBS})

    init_gen_pkgconfig()
    
    install(
        FILES 
            ${${LIB_NAME}_HEADERS}
        DESTINATION 
            include/lib_init/log_replay)
    install(TARGETS ${LIB_NAME}
        LIBRARY DESTINATION 
            lib/orocos)
endmacro()

