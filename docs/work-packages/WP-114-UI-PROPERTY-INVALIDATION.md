# WP-114 — UI Property Invalidation Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-114 directly implements the approved Property Runtime invalidation layer as passive value/snapshot infrastructure. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

Architecture references:

- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`
- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERSISTENCE.md`
- `docs/architecture/SIRIUS-UI-EDITOR.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

## Goal

Introduce passive UI Property Runtime invalidation value objects.

WP-114 builds directly on WP-109 through WP-113 by adding the vocabulary and immutable snapshots needed to represent scoped property invalidation. It must not perform invalidation, propagate dependency dirtiness, apply operations, evaluate properties, generate diagnostics, or mutate generations.

## Scope

- Add property invalidation scope vocabulary.
- Add property invalidation reason vocabulary.
- Add immutable invalidation records pairing scope, reason, target property ID, and generation stamp.
- Add immutable invalidation snapshots preserving deterministic invalidation-record order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No dirty tracking engine.
- No invalidation propagation.
- No dependency graph.
- No graph traversal.
- No topological sorting.
- No property evaluation.
- No operation application.
- No mutation of storage snapshots.
- No mutation of generation snapshots.
- No diagnostic generation.
- No scene, layout, render, theme, localization, editor, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- New types live only under `sirius::ui::property`.
- Invalidation records are passive values, not controllers.
- Invalidation snapshots are immutable-by-interface.
- The layer may depend on existing property identity and generation value types.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- turns invalidation into executable behavior;
- adds a mutable invalidation store;
- increments generation counters;
- applies operations;
- validates values;
- emits diagnostics;
- adds dependency graph edges or traversal;
- introduces callback/event/listener behavior;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Theme, Localization, Editor, or HUD;
- changes the existing WP-109 through WP-113 public responsibilities;
- adds a manager, service locator, scanner, router, generalized registry, or global mutable state.

## Acceptance criteria

- Invalidation scope vocabulary covers the architecture-approved scopes:
  - local property;
  - subtree;
  - surface;
  - theme-token;
  - localization;
  - snapshot-source;
  - profile/document.
- Invalidation reason vocabulary maps to the existing generation categories and approved external invalidation sources.
- Invalidation records are immutable after construction and reference exactly one target property ID.
- Invalidation records carry a generation stamp without mutating or producing generations themselves.
- Invalidation snapshots are immutable after construction and preserve deterministic record order.
- No dependency graph, propagation, evaluation, operation application, diagnostics generation, mutation API, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Is WP-114 strictly passive vocabulary/snapshot infrastructure?
- Does it build only on property IDs and generation stamps?
- Does it avoid dirty tracking and propagation?
- Does it preserve future dependency graph/evaluation layers instead of implementing them early?
- Are ownership, lifetime, and layering unchanged?
- Is Architecture Freeze V2 preserved?

## Approved commit message

`feat(ui): add property invalidation baseline`
