#
# This file is part of the Chronus Quantum (ChronusQ) software package
# SPDX-License-Identifier: GPL-2.0-or-later
#

message("\n == LibXC ==")

# 1) Try a preinstalled package first (exports Libxc::xc)
find_package(Libxc CONFIG QUIET)

include(FetchContent)

# Helper: resolve a usable target into _LibXC_TARGET
function(_cq_resolve_libxc_target)
  if (TARGET Libxc::xc)
    set(_LibXC_TARGET Libxc::xc PARENT_SCOPE)
  elseif (TARGET xc)
    # In-tree build typically exposes 'xc'; create alias if missing
    if (NOT TARGET Libxc::xc)
      add_library(Libxc::xc ALIAS xc)
    endif()
    set(_LibXC_TARGET Libxc::xc PARENT_SCOPE)
  else()
    set(_LibXC_TARGET "" PARENT_SCOPE)
  endif()
endfunction()

# 2) If not found, fetch & build LibXC in-tree
_cq_resolve_libxc_target()
if (NOT _LibXC_TARGET)
  # Avoid refetching if already populated
  FetchContent_GetProperties(libxc)
  if (NOT libxc_POPULATED)
    # Optional knobs you can adjust if needed:
    # set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
    # set(ENABLE_FORTRAN OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
      libxc
      GIT_REPOSITORY https://gitlab.com/libxc/libxc.git
      GIT_TAG        6.2.0
    )
    FetchContent_MakeAvailable(libxc)
  endif()
  _cq_resolve_libxc_target()
endif()

# 3) Fail clearly if still unresolved
if (NOT _LibXC_TARGET)
  message(FATAL_ERROR
    "LibXC is required but neither 'Libxc::xc' (installed) nor 'xc' (in-tree) "
    "targets exist. If behind a proxy, ensure FetchContent can clone "
    "https://gitlab.com/libxc/libxc.git, or install libxc with a CMake package.")
endif()

# 4) If we’re using the in-tree 'xc', add includes/tweaks safely
if (TARGET xc)
  # These vars are defined only when fetched in-tree
  if (DEFINED libxc_SOURCE_DIR AND DEFINED libxc_BINARY_DIR)
    target_include_directories(xc
      PUBLIC
        $<BUILD_INTERFACE:${libxc_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${libxc_BINARY_DIR}/src>
        $<BUILD_INTERFACE:${libxc_BINARY_DIR}>
        $<BUILD_INTERFACE:${libxc_BINARY_DIR}/gen_funcidx>
    )
  endif()

  if (CMAKE_UNITY_BUILD)
    set_target_properties(xc PROPERTIES UNITY_BUILD OFF)
    message(STATUS "Will disable unity-build for LibXC in-tree target")
  endif()
endif()

# 5) Link ChronusQ to the resolved LibXC target
target_link_libraries(cq PUBLIC ${_LibXC_TARGET})

message(" == End LibXC ==\n")

