# WP-093 - Module Runtime Descriptors

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

Foundation V1 is accepted complete by architecture decision. New work must advance the Module Runtime and must not continue cleanup-only Work Packages.

## Module Runtime roadmap

The Module Runtime should be built in bounded increments:

1. Immutable module descriptors/manifests for module-owned runtime declarations.
2. Deterministic runtime registration evidence using those descriptors.
3. Descriptor-backed validation for declared feature, command, and module-service ownership.
4. Dependency graph for declared module dependencies, only after descriptors exist.
5. Lifecycle graph derived from deterministic registration/dependency order.
6. Runtime diagnostics snapshot for modules, lifecycle state, declared contracts, and validation failures.
7. Typed module contracts for module-owned exports/imports.
8. Contract import/export binding between modules, preserving explicit composition boundaries.
9. Runtime composition boundary that lets Platform consume Module Runtime outputs without becoming a module manager.

Each WP must directly advance this milestone. Declarative UI Runtime, HUD/editor/theme/plugin/product systems remain out of scope until the Module Runtime is architecturally ready.

## Repository evidence

- `IModule` currently exposes only `Id()`, registries, and lifecycle hooks.
- `CModule` owns feature, command, and module-service registries but has no immutable declaration of what it is expected to own.
- `modules::status::IsSiriusStatusModuleComplete()` verifies concrete Status feature/command presence by inspecting implementation registries directly.
- `CPlatform` remains the composition root and must not become a generalized manager, scanner, router, or service locator.

## Scope

Add the first minimal module descriptor surface:

- introduce immutable `CModuleDescriptor`;
- expose descriptors through `IModule`;
- store descriptors in `CModule`;
- preserve the existing ID-only passive module constructor;
- make the Status module declare its owned feature and commands through a descriptor;
- keep Status completeness checking descriptor-backed while still verifying actual registries;
- add focused descriptor tests;
- update build source lists.

## Non-goals

- No dependency graph.
- No lifecycle graph.
- No diagnostics snapshot.
- No typed contract imports or exports.
- No module scanning, discovery, routing, manager, service locator, observer, or event bus.
- No DDNet, UI, console, rendering, gameplay, protocol, config, input binding, or product-system work.
- No redesign of Core, Platform, lifecycle, activation, command dispatch, or existing Status behavior.

## Ownership and boundaries

- Descriptors live under `src/sirius/platform/modules/` as module-runtime foundation.
- Modules own their descriptors.
- Platform may inspect descriptors but does not become a descriptor manager.
- Existing registries remain ownership containers; descriptors are declarations, not alternate storage.

## Acceptance criteria

- `IModule` exposes a read-only descriptor.
- `CModule` can be constructed with a descriptor.
- Existing `CModule(CModuleId)` callers remain valid and produce an ID-only descriptor.
- Status module construction uses a descriptor declaring:
  - `feature.sirius.status`;
  - `command.sirius.status.open`;
  - `command.sirius.status.close`;
  - `command.sirius.status.toggle`.
- Status completeness requires both descriptor declarations and actual registry ownership.
- No new runtime manager/router/scanner/generalized discovery is introduced.
- Focused descriptor tests cover declaration lookup and ID-only backward compatibility.
- Standard validation passes or any infrastructure-only test limitation is reported separately.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The Architect consultant was unavailable after one launch and one retry. Lead fallback inspected the repository and selected the smallest Module Runtime foundation that directly advances the new milestone.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

The descriptor is declaration-only and does not create discovery, routing, lifecycle ordering, dependency resolution, unloading, or product behavior. It reduces future registry-inspection pressure without changing ownership.

## Validation plan

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- focused C++ test path where current repository infrastructure permits it

## Approved commit message

`feat(modules): add module runtime descriptors`
