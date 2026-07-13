# WP-115 — UI Property Dependency Graph Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-115 directly implements the approved Property Runtime dependency graph layer as passive value/snapshot infrastructure. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

Architecture references:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERSISTENCE.md`
- `docs/architecture/SIRIUS-UI-EDITOR.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

## Goal

Introduce passive UI Property Runtime dependency graph value objects.

WP-115 builds directly on WP-109 through WP-114 by adding dependency source/target/edge vocabulary and immutable graph snapshots that later graph-building, validation, invalidation, and evaluation layers can consume.

## Scope

- Add property dependency source kind vocabulary.
- Add property dependency target kind vocabulary.
- Add immutable dependency references.
- Add immutable dependency edges from source reference to target reference.
- Add immutable dependency graph snapshots preserving deterministic edge order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No graph building from declarations.
- No dependency traversal.
- No topological sorting.
- No cycle detection.
- No missing-dependency validation.
- No invalidation propagation.
- No property evaluation.
- No operation application.
- No mutation of storage, generation, invalidation, or diagnostic snapshots.
- No diagnostic generation.
- No scene, layout, render, theme, localization, editor, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- New types live only under `sirius::ui::property`.
- Dependency graph records are passive values, not graph builders or evaluators.
- Graph snapshots are immutable-by-interface.
- The layer may depend on existing property identity value types.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- builds dependency edges from declarations;
- validates missing dependencies;
- detects cycles;
- sorts or traverses the graph;
- performs invalidation propagation;
- evaluates properties;
- applies operations;
- emits diagnostics;
- introduces callback/event/listener behavior;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Theme, Localization, Editor, or HUD;
- changes the existing WP-109 through WP-114 public responsibilities;
- adds a manager, service locator, scanner, router, generalized registry, or global mutable state.

## Acceptance criteria

- Dependency source vocabulary can represent property, snapshot, theme token, localization resource, profile document, animation track, and runtime interaction sources.
- Dependency target vocabulary can represent property and generated property targets.
- Dependency references are immutable after construction and carry stable string identity plus kind.
- Dependency edges are immutable after construction and pair one source reference with one target reference.
- Graph snapshots are immutable after construction and preserve deterministic edge order.
- No graph building, traversal, cycle detection, missing-dependency validation, invalidation propagation, evaluation, operation application, diagnostics generation, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Is WP-115 strictly passive graph vocabulary/snapshot infrastructure?
- Does it avoid graph construction, traversal, sorting, validation, and evaluation?
- Does it preserve future dependency graph/evaluation layers instead of implementing them early?
- Are ownership, lifetime, and layering unchanged?
- Is Architecture Freeze V2 preserved?

## Approved commit message

`feat(ui): add property dependency graph baseline`
