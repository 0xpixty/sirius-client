# WP-100 — Module Lifecycle Graph Ordering

## Status

APPROVED by Sirius Lead fallback after repository inspection.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by making the already-approved module lifecycle graph participate in runtime module startup and shutdown order.

It follows the accepted sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts

## Goal

Make `CModuleLifecycle` consume an explicit `CModuleLifecycleGraph` so modules initialize in graph order and shut down in the reverse of the actual initialized order.

## Scope

- Add a graph-aware `CModuleLifecycle::Initialize(...)` overload.
- Resolve lifecycle graph module IDs through the existing `CModuleRegistry`.
- Reject lifecycle graphs that do not match the registered module set.
- Track initialized module pointers in the actual lifecycle order.
- Shut down initialized modules by unwinding the tracked initialized order.
- Preserve the existing registration-order initialize path for callers that do not yet provide a lifecycle graph.
- Have `CPlatform` build dependency and lifecycle graphs from the explicit module registration plan during module configuration.
- Have `CPlatform::Start()` initialize modules through the graph-aware lifecycle path.
- Add focused mechanical tests for graph-ordered initialization and reverse shutdown.

## Non-goals

- No runtime unloading.
- No dynamic discovery.
- No module scanning.
- No module manager.
- No service locator.
- No generalized router, observer, or event system.
- No UI, HUD editor, theme system, Plugin SDK, replay tools, or other product systems.
- No typed contract import/export model yet.
- No runtime diagnostics snapshot yet.
- No change to feature, command, binding, DDNet adapter, or Status snapshot behavior.

## Acceptance criteria

1. `CModuleLifecycle` can initialize from a `CModuleLifecycleGraph`.
2. Graph initialization resolves modules by ID through the existing registry.
3. Graph initialization rejects missing, duplicate, or incomplete lifecycle orders.
4. Shutdown unwinds the actual initialized module order rather than assuming registration-order indexes.
5. Existing dependency-free Platform modules preserve current startup behavior.
6. `CPlatform` builds the dependency graph and lifecycle graph from the explicit registration plan.
7. No forbidden architecture mechanism is introduced.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CModuleLifecycleGraph|BuildModuleDependencyGraph|BuildModuleLifecycleGraph|ServiceLocator|scanner|router|observer|manager" src/sirius src/test docs/work-packages/WP-100-MODULE-LIFECYCLE-GRAPH-ORDERING.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added to the repository, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: lifecycle execution could accidentally remain tied to registration-order indexes. Mitigation: lifecycle now tracks the initialized modules directly and unwinds that vector.
- Main risk: graph and registry can diverge. Mitigation: graph-aware initialization rejects missing or duplicate resolved modules and requires lifecycle order size to match registry count.
- Boundary risk: this could become a module manager. Mitigation: no new owner is introduced; Platform remains the explicit composition root, and `CModuleLifecycle` remains only lifecycle execution.

## Suggested commit message

`feat(modules): order lifecycle by module graph`
