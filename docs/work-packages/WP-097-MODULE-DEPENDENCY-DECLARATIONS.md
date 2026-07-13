# WP-097 - Module Dependency Declarations

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

Descriptors, definitions, deterministic registration, and descriptor-backed ownership validation are complete. The next roadmap target is dependency/lifecycle graph work.

WP-097 adds only the declaration value surface required before a dependency graph can exist.

## Repository evidence

- `CModuleDescriptor` already owns immutable declarations for features, commands, and module services.
- `CModuleRegistrationPlan` provides deterministic definition order.
- `CModuleLifecycle` still initializes modules in registration order.
- No dependency declarations exist yet, so graph work would otherwise invent edges without repository-backed input.

## Scope

- Extend `CModuleDescriptor` with immutable dependency module IDs.
- Add `DependencyIds()`.
- Add `DeclaresDependency()`.
- Preserve existing constructors by making dependency declarations optional.
- Keep all current modules dependency-free.
- Update focused descriptor tests.

## Non-goals

- No dependency graph construction.
- No dependency validation.
- No lifecycle graph or ordering change.
- No diagnostics snapshot.
- No typed contracts.
- No import/export resolution.
- No module manager.
- No scanner/discovery system.
- No runtime unloading.
- No service locator/global lookup.
- No UI, HUD editor, theme system, plugin SDK, gameplay module, DDNet, rendering, protocol, config, or input work.

## Ownership and boundaries

- Dependency declarations live in `CModuleDescriptor`.
- They are immutable module metadata.
- They do not cause module lookup, construction, lifecycle ordering, or dependency resolution.
- Platform behavior is unchanged.

## Acceptance criteria

- `CModuleDescriptor` can carry dependency module IDs.
- Existing descriptor constructors and module construction remain valid.
- Dependency declarations are queryable without exposing mutable state.
- Existing modules remain dependency-free.
- No graph, manager, scanner, discovery, service-location, lifecycle, diagnostics, contract, UI, or product mechanism is introduced.
- Focused descriptor tests are updated for dependencies.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The WP directly advances the next roadmap stage while avoiding premature graph or lifecycle policy.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

Dependency IDs are inert declarations. They cannot change runtime behavior until a later approved graph/validation WP consumes them.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): declare module dependencies`
