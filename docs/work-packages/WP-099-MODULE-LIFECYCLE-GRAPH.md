# WP-099 - Module Lifecycle Graph

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

WP-098 added an inert module dependency graph. WP-099 derives lifecycle order values from that graph.

This prepares lifecycle integration without changing `CModuleLifecycle` behavior yet.

## Repository evidence

- `CModuleDependencyGraph` provides module dependency edges.
- `CModuleLifecycle` still initializes modules in registration order and shuts them down in reverse initialized order.
- Current built-in modules have no dependencies, so graph-derived order should preserve existing behavior when no dependencies constrain order.

## Scope

- Add `CModuleLifecycleGraph`.
- Add `BuildModuleLifecycleGraph(const CModuleDependencyGraph&)`.
- Produce:
  - initialization order with dependencies before consumers;
  - shutdown order as reverse initialization order.
- Preserve registration order as the deterministic tie-break when dependencies do not constrain order.
- Reject dependency cycles.
- Add focused lifecycle graph tests and CMake source entries.

## Non-goals

- No integration into `CModuleLifecycle`.
- No Platform lifecycle behavior change.
- No diagnostics snapshot.
- No typed contracts.
- No import/export resolution.
- No module manager.
- No scanner/discovery system.
- No runtime unloading.
- No service locator/global lookup.
- No UI, HUD editor, theme system, plugin SDK, gameplay module, DDNet, rendering, protocol, config, or input work.

## Ownership and boundaries

- Lifecycle graph is an immutable value derived from a dependency graph.
- It does not own modules, registries, definitions, or Platform state.
- It does not mutate lifecycle state.

## Acceptance criteria

- Dependencies initialize before consumers.
- Shutdown order is reverse initialization order.
- Registration order is preserved when no dependency constrains order.
- Dependency cycles are rejected.
- Existing Platform/module lifecycle behavior is unchanged.
- No manager/router/scanner/service-location mechanism is introduced.
- Focused lifecycle graph tests are wired into CMake for GTest-enabled environments.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The WP directly follows the dependency graph and stops before lifecycle integration.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

The graph is inert. It cannot affect runtime lifecycle until a later approved integration WP consumes it.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): derive module lifecycle graph`
