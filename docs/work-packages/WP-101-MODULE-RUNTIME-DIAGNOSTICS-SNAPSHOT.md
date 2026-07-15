# WP-101 — Module Runtime Diagnostics Snapshot

## Status

APPROVED by Sirius Lead fallback after repository inspection and the approved WP-097 through WP-100 architecture audit.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by adding the first read-only diagnostics snapshot after descriptors, definitions, deterministic registration, dependency graph, lifecycle graph, and lifecycle ordering are in place.

It follows the accepted sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts

## Goal

Expose a minimal immutable diagnostics snapshot for the current Module Runtime state without adding UI, commands, logging, routing, managers, service-location, or product features.

## Scope

- Add Module Runtime diagnostics value objects under `sirius::platform::modules`.
- Snapshot the registered module list in registration order.
- Include each module ID.
- Include declared dependency IDs from the existing immutable descriptor.
- Include descriptor ownership validation state using the existing validation function.
- Include whether lifecycle graph order is available for each module.
- Include initialization and shutdown order indexes from the existing lifecycle graph.
- Include overall module lifecycle initialized state.
- Add a narrow read-only `CPlatform::ModuleRuntimeDiagnosticsSnapshot()` query.
- Add focused source-level tests for snapshot content and lifecycle initialized state.

## Non-goals

- No UI, HUD, console command, renderer, DDNet adapter query, or product feature.
- No dynamic discovery.
- No runtime unloading.
- No scanner.
- No manager.
- No service locator.
- No generalized router, observer, or event system.
- No logging sink.
- No diagnostics event stream.
- No typed contracts yet.
- No import/export resolution.
- No change to module startup, shutdown, activation, commands, bindings, Status behavior, or DDNet behavior.

## Acceptance criteria

1. A `CModuleRuntimeDiagnosticsSnapshot` value exists.
2. The snapshot is immutable/read-only to consumers.
3. The snapshot reports module IDs and declared dependency IDs.
4. The snapshot reports descriptor ownership validation state.
5. The snapshot reports lifecycle graph order indexes when a lifecycle graph is available.
6. The snapshot reports overall module lifecycle initialized state.
7. `CPlatform` exposes only a narrow read-only query for the snapshot.
8. No forbidden architecture mechanism is introduced.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CModuleRuntimeDiagnosticsSnapshot|ModuleRuntimeDiagnosticsSnapshot|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-101-MODULE-RUNTIME-DIAGNOSTICS-SNAPSHOT.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added and wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: diagnostics becomes a manager-shaped runtime API. Mitigation: the snapshot is a passive value built from existing registry/descriptor/lifecycle state; it does not provide lookup or mutation.
- Main risk: Platform public API pressure grows. Mitigation: the Platform query is narrow, read-only, and returns a snapshot by value.
- Main risk: failure diagnostics remain incomplete. Mitigation: this WP records the stable snapshot surface first; future WPs can add structured failure reasons without changing ownership or lifecycle behavior.

## Suggested commit message

`feat(modules): add runtime diagnostics snapshot`
