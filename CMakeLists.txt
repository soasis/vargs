# =============================================================================
#
# ztd.vargs
# Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
# Contact: opensource@soasis.org
#
# Commercial License Usage
# Licensees holding valid commercial ztd.vargs licenses may use this file
# in accordance with the commercial license agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and Shepherd's Oasis, LLC.
# For licensing terms and conditions see your agreement. For
# further information contact opensource@soasis.org.
#
# Apache License Version 2 Usage
# Alternatively, this file may be used under the terms of Apache License
# Version 2.0 (the "License") for non-commercial use; you may not use this
# file except in compliance with the License. You may obtain a copy of the
# License at
#
# 		https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ============================================================================>


cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21)
# # Project kickstart
# Includes a bunch of basic flags and utilities shared across projects
# See more at the github repository link below
include(FetchContent)
FetchContent_Declare(ztd.cmake
	GIT_REPOSITORY https://github.com/soasis/cmake
	GIT_TAG main)
FetchContent_MakeAvailable(ztd.cmake)
set(CMAKE_PROJECT_INCLUDE ${ZTD_CMAKE_PROJECT_PRELUDE})

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(ztd.vargs
  VERSION 0.0.0
  DESCRIPTION "Code to access\"Varargs\" without the cruft of an inital first parameter."
  HOMEPAGE_URL "https://ztdvargs.readthedocs.io/en/latest/"
  LANGUAGES C CXX ASM_MASM)

if (ZTD_VARGS_READTHEDOCS)
	# ReadTheDocs seems unable to handle the include at the project level: something must be going wrong?
	include(CheckCXXCompilerFlag)
	include(CheckCCompilerFlag)
	include(CheckIPOSupported)
	include(CMakePackageConfigHelpers)
	include(CMakeDependentOption)
	include(CMakePrintHelpers)
	include(GNUInstallDirs)
	include(FeatureSummary)
	include(FetchContent)
	include(CTest)
endif()

# # # Top-Level Directories
# Check if this is the top-level project or not
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(ZTD_IS_TOP_LEVEL_PROJECT YES)
else()
	set(ZTD_IS_TOP_LEVEL_PROJECT NO)
endif()

string(CONCAT ztd-vargs-is-top-level $<STREQUAL:${PROJECT_NAME},${CMAKE_PROJECT_NAME}>)

# Modify bad flags / change defaults if we are the top level
if (ZTD_IS_TOP_LEVEL_PROJECT)
	if (CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	endif()

	if (NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_CXX_STANDARD 17)
	endif()

	if (NOT DEFINED CMAKE_C_STANDARD)
		set(CMAKE_C_STANDARD 23)
	endif()

	if (ZTD_VARGS_BENCHMARKS OR ZTD_VARGS_EXAMPLES OR ZTD_VARGS_TESTS OR ZTD_VARGS_SCRATCH)
		# normal flags
		check_compiler_flag(disable-permissive MSVC /permissive- GCC -pedantic)
		# Warning flags
		check_compiler_flag(warn-pedantic MSVC /permissive- GCC -pedantic)
		check_compiler_flag(warn-all MSVC /W4 GCC -Wall)
		check_compiler_flag(warn-errors MSVC /WX GCC -Werror)
		check_compiler_flag(warn-extra GCC -Wextra CLANG -Wextra)
		check_compiler_flag(utf8-literal-encoding MSVC /execution-charset:utf-8 GCC -fexec-charset=utf-8)
		check_compiler_flag(utf8-source-encoding MSVC /source-charset:utf-8 GCC -finput-charset=utf-8)
		check_compiler_flag(extra-constexpr-depth MSVC /constexpr:depth2147483647 GCC -fconstexpr-depth=2147483647 CLANG -fconstexpr-depth=2147483647)
		check_compiler_flag(extra-constexpr-steps MSVC /constexpr:steps2147483647 GCC -fconstexpr-ops-limit=2147483647 CLANG -fconstexpr-steps=2147483647)
		check_compiler_flag(template-debugging-mode GCC -ftemplate-backtrace-limit=0)
	endif()
endif()

# # Options
option(ZTD_VARGS_CI "Whether or not we are in continuous integration mode" OFF)
option(ZTD_VARGS_TESTS "Enable build of tests" OFF)
option(ZTD_VARGS_DOCUMENTATION "Enable build of documentation" OFF)
option(ZTD_VARGS_DOCUMENTATION_NO_SPHINX "Turn off Sphinx usage (useful for ReadTheDocs builds)" OFF)
option(ZTD_VARGS_EXAMPLES "Enable build of examples" OFF)
option(ZTD_VARGS_BENCHMARKS "Enable build of benchmarks" OFF)
option(ZTD_VARGS_GENERATE_SINGLE "Enable generation of a single header and its target" OFF)
option(ZTD_VARGS_USE_VARGS "Enable generation of a single header and its target" OFF)

# # Dependencies
# ztd.idk
FetchContent_Declare(ztd.idk
	GIT_REPOSITORY https://github.com/soasis/idk.git
	GIT_TAG main)
FetchContent_MakeAvailable(ztd.idk)

# # Main Library
file(GLOB ztd.vargs.includes CONFIGURE_DEPENDS include/*.hpp)

file(GLOB_RECURSE ztd.vargs.sources
	LIST_DIRECTORIES FALSE
	CONFIGURE_DEPENDS
	source/*.c source/*.cpp)
file(GLOB_RECURSE ztd.vargs.sources.asm
	LIST_DIRECTORIES FALSE
	CONFIGURE_DEPENDS
	source/*.asm)

add_library(ztd.vargs ${ztd.vargs.sources} ${ztd.vargs.sources.asm})
add_library(ztd::vargs ALIAS ztd.vargs)
target_include_directories(ztd.vargs
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>)
target_link_libraries(ztd.vargs
	PUBLIC
	ztd::idk)
target_include_directories(ztd.vargs
	PRIVATE ${PROJECT_SOURCE_DIR}/source/include)
target_compile_options(ztd.vargs PRIVATE ${ztd-vargs-disable-permissive})
target_sources(ztd.vargs PRIVATE ${ztd.vargs.includes})
install(DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(TARGETS ztd.vargs
	PUBLIC_HEADER
	RUNTIME
	ARCHIVE
	LIBRARY
)

# # Config / Version packaging
# Version configurations
configure_package_config_file(
	cmake/ztd.vargs-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.vargs/ztd.vargs-config.cmake"
	INSTALL_DESTINATION lib/cmake/ztd.vargs
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.vargs/ztd.vargs-config-version.cmake"
	COMPATIBILITY SameMajorVersion)

export(TARGETS ztd.vargs
	FILE
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.vargs/ztd.vargs-targets.cmake")


if (ZTD_VARGS_GENERATE_SINGLE)
	add_subdirectory(single)
endif()

# # Benchmarks, Tests, Examples
if (ZTD_VARGS_TESTS)
	include(CTest)
	add_subdirectory(tests)
endif()

if (ZTD_VARGS_DOCUMENTATION)
	add_subdirectory(documentation)
endif()
if (ZTD_VARGS_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()
if (ZTD_VARGS_EXAMPLES)
	add_subdirectory(examples)
endif()

# For quick debugging and development only: don't peek! 🙈
mark_as_advanced(ZTD_VARGS_SCRATCH)
if (ZTD_VARGS_SCRATCH)
	add_executable(scratch main.cpp)
	target_link_libraries(scratch PRIVATE ztd::vargs)
	target_compile_options(scratch
		PRIVATE
		${--template-debugging-mode}
		${--disable-permissive}
		${--warn-pedantic}
		${--warn-all}
		${--warn-extra}
		${--warn-errors})
	target_compile_features(scratch PRIVATE cxx_std_20)
endif()
