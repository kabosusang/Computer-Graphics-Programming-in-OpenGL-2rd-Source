# 定义要扫描的所有章节
set(CHAPTERS "Chapter2" "Chapter3")  # 可以继续添加 Chapter4, Chapter5...

# 遍历每个 ChapterX 目录
foreach(chapter ${CHAPTERS})
    # 查找当前章节下的所有 Program* 子目录
    file(GLOB program_dirs LIST_DIRECTORIES true "${chapter}/Program*")

    # 遍历每个 Program 目录
    foreach(program_dir ${program_dirs})
        # 提取目录名（如 "Program1"）
        get_filename_component(prog_name ${program_dir} NAME)

        # 自动查找该 Program 下的所有 .cpp 文件
        file(GLOB sources "${program_dir}/*.cpp")

        # 如果有 .cpp 文件才创建可执行目标
        if(sources)
            message(STATUS "添加可执行目标: ${chapter}/${prog_name}")
            add_executable(${prog_name} ${sources})
            target_link_libraries(${prog_name} PRIVATE common_lib ${COMMON_LIBS})
        endif()
    endforeach()
endforeach()

