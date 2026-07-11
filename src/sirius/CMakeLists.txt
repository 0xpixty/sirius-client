set_src(SIRIUS_CLIENT GLOB_RECURSE src/sirius
  # tidy-alphabetical-start
  adapters/ddnet/ddnet_platform_host.cpp
  adapters/ddnet/ddnet_platform_host.h
  core/runtime/core_runtime.cpp
  core/runtime/core_runtime.h
  core/runtime/core_runtime_configuration.h
  core/runtime/core_runtime_state.h
  platform/platform.cpp
  platform/platform.h
  platform/platform_bootstrap.cpp
  platform/platform_bootstrap.h
  platform/platform_configuration.h
  # tidy-alphabetical-end
)

set(SIRIUS_CLIENT ${SIRIUS_CLIENT} PARENT_SCOPE)
set(CHECKSUM_SRC ${CHECKSUM_SRC} PARENT_SCOPE)
