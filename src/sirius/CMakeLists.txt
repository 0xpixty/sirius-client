set_src(SIRIUS_CLIENT GLOB_RECURSE src/sirius
  # tidy-alphabetical-start
  adapters/ddnet/ddnet_platform_host.cpp
  adapters/ddnet/ddnet_platform_host.h
  core/config/config_changed_event.h
  core/config/config_registry.cpp
  core/config/config_registry.h
  core/events/event_channel.h
  core/events/event_dispatcher.cpp
  core/events/event_dispatcher.h
  core/events/event_subscription.h
  core/interfaces/runtime_component.h
  core/interfaces/service.h
  core/logging/log_level.h
  core/logging/log_message.h
  core/logging/logger.cpp
  core/logging/logger.h
  core/runtime/core_runtime.cpp
  core/runtime/core_runtime.h
  core/runtime/core_runtime_configuration.h
  core/runtime/core_runtime_state.h
  core/runtime/runtime_component_registry.cpp
  core/runtime/runtime_component_registry.h
  core/runtime/runtime_context.cpp
  core/runtime/runtime_context.h
  core/runtime/runtime_lifecycle.cpp
  core/runtime/runtime_lifecycle.h
  core/services/service_registry.cpp
  core/services/service_registry.h
  core/tasks/task.h
  core/tasks/task_dispatcher.cpp
  core/tasks/task_dispatcher.h
  core/tasks/task_queue.cpp
  core/tasks/task_queue.h
  platform/platform.cpp
  platform/platform.h
  platform/platform_bootstrap.cpp
  platform/platform_bootstrap.h
  platform/platform_configuration.h
  platform/commands/command.h
  platform/commands/command_id.h
  platform/commands/command_registry.cpp
  platform/commands/command_registry.h
  platform/features/feature_context.cpp
  platform/features/feature_context.h
  platform/features/feature.h
  platform/features/feature_id.h
  platform/features/feature_lifecycle.cpp
  platform/features/feature_lifecycle.h
  platform/features/feature_registry.cpp
  platform/features/feature_registry.h
  platform/modules/module.h
  platform/modules/module_context.cpp
  platform/modules/module_context.h
  platform/modules/module_id.h
  platform/modules/module_lifecycle.cpp
  platform/modules/module_lifecycle.h
  platform/modules/module_registry.cpp
  platform/modules/module_registry.h
  # tidy-alphabetical-end
)

set(SIRIUS_CLIENT ${SIRIUS_CLIENT} PARENT_SCOPE)
set(CHECKSUM_SRC ${CHECKSUM_SRC} PARENT_SCOPE)
