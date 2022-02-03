cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(interview-preparation-kit-in-cxx VERSION 0.0.1 LANGUAGES CXX)

############################################################################################

# Options
include(CMakePackageConfigHelpers)
include(CMakePrintHelpers)
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)

############################################################################################

# CMake Options

# Set required C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_HEADERS_IN_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

############################################################################################

# Compiler Options
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # https://clang.llvm.org/docs/ClangCommandLineReference.html
  add_compile_options(
    # "-Wall"
    # "-Wextra"
  )

  add_compile_options(
    "-Wno-c++98-compat"
    "-Wno-c++98-compat-pedantic"
  )

  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    # Using clang with clang-cl front end
  elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    # Using clang with regular front end
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
  add_compile_options(
    "-Wall"
    "-Wextra"
    "-Werror"
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options?view=msvc-160
  add_compile_definitions(
    UNICODE
    _UNICODE

    _SCL_SECURE_NO_WARNINGS
    _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
    _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
  )

  add_compile_options(
    "/W4"
    "/WX"

    "/utf-8"

    # Enable parallel compilation (https://docs.microsoft.com/en-us/cpp/build/reference/mp-build-with-multiple-processes?view=msvc-160)
    "/MP"
    # Flag for catch the null pointer exception (https://docs.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model?view=msvc-160)
    "/EHs"
  )
endif()

############################################################################################

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(src)

############################################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

macro(wrapper_test dir)
    get_property(subdirectories
      DIRECTORY ${dir}
      PROPERTY SUBDIRECTORIES
    )

    foreach(subdir ${subdirectories})
      wrapper_test(${targets} ${subdir})
    endforeach()

    get_property(current_target
      DIRECTORY ${dir}
      PROPERTY BUILDSYSTEM_TARGETS
    )

    if (TARGET ${current_target})
      target_link_libraries(${current_target}
        PRIVATE
          GTest::gtest
          GTest::gtest_main
      )

      add_test(
        NAME ${current_target}
        COMMAND ${current_target}
      )

      install(
        TARGETS ${current_target}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT Testing
      )
    endif()
endmacro()

wrapper_test(${CMAKE_CURRENT_SOURCE_DIR}/src/leetcode)

############################################################################################

install(FILES LICENSE DESTINATION licenses)

set(CPACK_PACKAGE_VENDOR "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")

include(CPack)
