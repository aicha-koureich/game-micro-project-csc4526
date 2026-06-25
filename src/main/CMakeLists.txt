add_executable(main
  main.cpp
)

target_link_libraries(main PUBLIC lib_core pugixml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_custom_target(copy-res ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/res)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res
                   DEPENDS ${CMAKE_SOURCE_DIR}/res
                   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                           ${CMAKE_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res)
add_dependencies(main copy-res)

if(APPLE)
    # ── macOS (ld) ────────────────────────────────────────────────────────────
    target_link_options(main PRIVATE
            -Wl,-force_load,$<TARGET_FILE:lib_core>
    )

elseif(WIN32)
    # ── Windows ───────────────────────────────────────────────────────────────
    if(MSVC)
        # Cas 1 : Visual Studio / MSVC
        target_link_options(main PRIVATE
                /WHOLEARCHIVE:$<TARGET_FILE:lib_core>
        )
    elseif(MINGW OR CYGWIN OR CMAKE_COMPILER_IS_GNUCC)
        # Cas 2 : MinGW / GCC sur Windows
        target_link_options(main PRIVATE
                -Wl,--whole-archive
                $<TARGET_FILE:lib_core>
                -Wl,--no-whole-archive
        )
    endif()

else()
    # ── Linux / Autres (GNU ld / lld) ─────────────────────────────────────────
    target_link_options(main PRIVATE
            -Wl,--whole-archive
            $<TARGET_FILE:lib_core>
            -Wl,--no-whole-archive
    )
endif()