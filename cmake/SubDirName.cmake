# 获取目录下的子目录名
# subdirnamelist 子目录名称列表，输出变量，调用处定义，填充时不能加${}
# targetdir      目标路径，为全路径
macro(SUBDIRNAMELIST_MACRO subdirnamelist targetdir)
    file(GLOB children ${targetdir}/* ${targetdir}/*/* ${targetdir}/*/*/*) # 获取目标路径下的内容，深度为1
    set(dirlist "")
    foreach(child ${children})
        file(RELATIVE_PATH child_name ${targetdir} ${child}) # 通过相对路径计算获取名称
        if(IS_DIRECTORY ${targetdir}/${child_name})
            list(APPEND dirlist ${child_name})
        endif()
    endforeach()
    list(APPEND ${subdirnamelist} ${dirlist})
endmacro()
 
# 获取目录下是否有CMakeLists
# hascmakelist 是否含有CMakeLists.txt，输出变量，调用处定义，填充时不能加${}
# targetdir    目标路径，为全路径
macro(CHECK_DIR_HAS_CMAKELIST hascmakelist targetdir)
    set(${hascmakelist} FALSE)
    if(IS_DIRECTORY ${targetdir})
        if(EXISTS ${targetdir}/CMakeLists.txt)
            set(${hascmakelist} TRUE)
        endif()
    else()
        message(FATAL_ERROR "Invalid dir para: targetdir = ${targetdir}")
    endif()
endmacro()
 
# 为含有CMakeList的子目录添加add_subdirectory调用
# 自动识别调用处所在目录有哪些子目录，并为还有CMakeLists.txt的子目录添加add_sundirectory调用
macro(AUTO_ADD_SUBDIRECTORY source_dir)
    set(subdirnamelisttemp "")
    SUBDIRNAMELIST_MACRO(subdirnamelisttemp ${source_dir})
    # message(STATUS "macro add_subdir subdirnamelisttemp = ${subdirnamelisttemp}")
    foreach(subdir ${subdirnamelisttemp})
        # message(STATUS "macro add_subdir subdir = ${subdir}")
        set(hascmakelisttemp FALSE)
        CHECK_DIR_HAS_CMAKELIST(hascmakelisttemp ${source_dir}/${subdir})
        # message(STATUS "macro add_subdir hascmakelisttemp = ${hascmakelisttemp}")
        if(${hascmakelisttemp})
            message(STATUS "macro add_subdir go to add_subdir = ${subdir}")
            add_subdirectory(${subdir})
        endif()
    endforeach()
endmacro()

AUTO_ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR})
