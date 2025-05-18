# 定义要扫描的所有章节
set(CHAPTERS "Chapter2" 
"Chapter4" 
"Chapter5" 
"Chapter6"
"Chapter7"
"Chapter8"
)  # 可以继续添加 Chapter4, Chapter5...

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
            # 生成唯一目标名：ChapterX_ProgramY（例如 Chapter2_Program1）
            set(target_name "${chapter}_${prog_name}")
            message(STATUS "添加可执行目标: ${target_name} (源目录: ${program_dir})")

            # 创建可执行文件
            add_executable(${target_name} ${sources})
            target_link_libraries(${target_name} PRIVATE common_lib ${COMMON_LIBS})
        endif()
    endforeach()
endforeach()