# WP-118 — UI Property Runtime Snapshot

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-118 directly implements the approved Property Runtime snapshot layer as an immutable aggregate snapshot over the lower Property Runtime foundations. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first immutable aggregate UI Property Runtime snapshot.

WP-118 closes the initial Property Runtime foundation by composing the already-approved passive metadata, storage, diagnostics, generation, invalidation, dependency graph, and evaluation snapshots into one read-only value suitable for later Scene Runtime consumption.

## Scope

- Add an immutable aggregate property runtime snapshot type.
- Store metadata records and lower property snapshots by value.
- Preserve deterministic metadata record order.
- Expose read-only accessors for each lower snapshot.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No property runtime builder.
- No expression execution.
- No dependency graph construction, traversal, topological sorting, or cycle detection.
- No source lookup, binding resolution, theme resolution, localization resolution, animation resolution, or profile lookup.
- No property mutation, storage mutation, operation application, generation mutation, invalidation propagation, or diagnostic generation.
- No scene, layout, render, theme, localization, editor, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- New types live only under `sirius::ui::property`.
- The aggregate snapshot owns copied immutable value snapshots and exposes them read-only.
- The snapshot is not a runtime owner, builder, evaluator, store, service, manager, or cache.
- The layer may depend only on existing Property Runtime value/snapshot headers.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- builds, evaluates, resolves, mutates, propagates, or validates property state;
- creates a mutable store, builder, manager, cache, service, or lookup surface;
- performs dependency traversal, sorting, or cycle detection;
- emits diagnostics;
- introduces callback/event/listener behavior;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Theme, Localization, Editor, or HUD;
- changes the existing WP-109 through WP-117 public responsibilities;
- adds a manager, service locator, scanner, router, generalized registry, or global mutable state.

## Acceptance criteria

- Aggregate snapshot stores metadata records, storage snapshot, diagnostic snapshot, generation snapshot, invalidation snapshot, dependency graph snapshot, and evaluation snapshot.
- Aggregate snapshot is immutable after construction and exposes only const/read-only accessors.
- Metadata record order is preserved exactly as provided.
- No builder, evaluator, mutation API, dependency traversal/sorting/validation, source lookup/resolution, diagnostic generation, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Is WP-118 strictly passive aggregate snapshot infrastructure?
- Does it avoid builders, evaluators, mutation, traversal, sorting, validation, and source resolution?
- Does it preserve future Scene Runtime consumption instead of implementing scene behavior early?
- Are ownership, lifetime, and layering unchanged?
- Is Architecture Freeze V2 preserved?

## Approved commit message

`feat(ui): add property runtime snapshot`
