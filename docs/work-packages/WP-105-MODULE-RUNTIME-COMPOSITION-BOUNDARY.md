# WP-105 — Module Runtime Composition Boundary

## Status

APPROVED by Sirius Lead fallback after repository inspection and the approved WP-101 through WP-104 architecture audit.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by packaging Module Runtime composition outputs behind one passive boundary consumed by Platform.

It completes the current minimal Module Runtime foundation sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts -> composition boundary

## Goal

Reduce Platform coupling to individual Module Runtime internals by introducing a narrow composition result that owns dependency graph, lifecycle graph, and contract resolution outputs.

## Scope

- Add `CModuleRuntimeComposition`.
- Add `BuildModuleRuntimeComposition(const CModuleRegistrationPlan &)`.
- Build dependency graph, lifecycle graph, and contract resolution behind one composition function.
- Return no composition when any required Module Runtime step fails.
- Store a single `CModuleRuntimeComposition` in `CPlatform`.
- Have `CPlatform::Start()` consume lifecycle graph through the composition result.
- Have diagnostics consume lifecycle graph and contract resolution through the composition result.
- Add focused source-level tests for successful composition and failure propagation.

## Non-goals

- No module manager.
- No service locator.
- No scanner or dynamic discovery.
- No runtime unloading.
- No module-facing contract lookup.
- No runtime binding injection.
- No routers, observers, event streams, or generalized dispatch.
- No lifecycle behavior change beyond consuming the same lifecycle graph through the composition boundary.
- No UI, HUD, console command, Theme System, Plugin SDK, replay tools, gameplay modules, or DDNet adapter work.

## Acceptance criteria

1. A passive `CModuleRuntimeComposition` value exists.
2. The composition value exposes dependency graph, lifecycle graph, and contract resolution read-only.
3. A builder creates the composition from the existing registration plan.
4. Builder failure propagates if dependency graph, lifecycle graph, or contract resolution cannot be built.
5. `CPlatform` stores one composition result instead of separate raw lifecycle/contract composition fields.
6. `CPlatform` behavior remains unchanged for current dependency-free and contract-free modules.
7. No forbidden architecture mechanism is introduced.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CModuleRuntimeComposition|BuildModuleRuntimeComposition|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-105-MODULE-RUNTIME-COMPOSITION-BOUNDARY.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added and wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: composition boundary becomes a manager. Mitigation: it is a passive immutable-ish value and builder, with no module ownership, lookup API, scanning, unloading, or mutation.
- Main risk: Platform behavior changes. Mitigation: Platform consumes the same lifecycle graph and contract resolution outputs as before through a narrower boundary.
- Main risk: next product systems start too early. Mitigation: this WP stays within Module Runtime and does not touch UI/product subsystems.

## Suggested commit message

`feat(modules): add runtime composition boundary`
