# WP-098 - Module Dependency Graph

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

WP-097 added dependency declarations to descriptors. WP-098 builds the first inert dependency graph value from the deterministic registration plan.

Lifecycle graph work remains separate and must not be folded into this WP.

## Repository evidence

- `CModuleRegistrationPlan` provides a deterministic list of definitions.
- `CModuleDescriptor` now carries dependency module IDs.
- `CModuleLifecycle` still initializes modules in registration order.
- Dependency graph work needs a validated graph value before lifecycle ordering can be changed.

## Scope

- Add `CModuleDependencyNode`.
- Add `CModuleDependencyGraph`.
- Add `BuildModuleDependencyGraph(const CModuleRegistrationPlan&)`.
- Graph nodes preserve registration-plan order.
- Graph build rejects:
  - empty module IDs;
  - empty dependency IDs;
  - missing dependencies;
  - self-dependencies;
  - duplicate dependency edges per module.
- Add focused graph tests and CMake source entries.

## Non-goals

- No lifecycle graph.
- No lifecycle ordering change.
- No topological sort.
- No runtime diagnostics snapshot.
- No typed contracts.
- No import/export resolution.
- No module manager.
- No scanner/discovery system.
- No runtime unloading.
- No service locator/global lookup.
- No UI, HUD editor, theme system, plugin SDK, gameplay module, DDNet, rendering, protocol, config, or input work.

## Ownership and boundaries

- Dependency graph is an immutable value built from registration-plan definitions.
- It does not own modules or definitions.
- It does not mutate the registration plan or module registry.
- Platform runtime behavior is unchanged in this WP.

## Acceptance criteria

- A graph can be built from a valid registration plan.
- Graph node order matches registration-plan order.
- Graph node dependency queries are read-only.
- Missing, empty, self, and duplicate dependency edges are rejected.
- No lifecycle behavior changes.
- No manager/router/scanner/service-location mechanism is introduced.
- Focused graph tests are wired into CMake for GTest-enabled environments.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The WP directly follows dependency declarations and stops before lifecycle graph policy.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

The graph is inert and read-only. The lack of topological sorting is intentional; lifecycle ordering is the next bounded roadmap step.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): add module dependency graph`
