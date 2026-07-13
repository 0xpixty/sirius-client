# WP-116 — UI Property Evaluation Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-116 directly implements the approved Property Runtime evaluation layer as passive evaluation order/result/snapshot infrastructure. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce passive UI Property Runtime evaluation value objects.

WP-116 builds on WP-109 through WP-115 by adding deterministic evaluation stage/order vocabulary, immutable evaluation records, and immutable evaluation snapshots that later evaluator, validation, diagnostics, and final property snapshot layers can consume.

## Scope

- Add property evaluation stage vocabulary matching the approved Property System evaluation order.
- Add property evaluation status vocabulary.
- Add immutable evaluation order records.
- Add immutable evaluation result records carrying a property ID, stage, status, optional effective stored value, and generation stamp.
- Add immutable evaluation snapshots preserving deterministic record order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

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
- Evaluation records and snapshots are passive values, not evaluator engines.
- Evaluation snapshots are immutable-by-interface.
- The layer may depend on existing property identity, stored value, and generation value types.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- evaluates expressions;
- builds, sorts, traverses, or validates dependency graphs;
- resolves bindings, theme tokens, localization resources, animation tracks, profile documents, or feature snapshots;
- mutates property storage, generations, invalidations, diagnostics, operations, or metadata;
- emits diagnostics;
- introduces mutable evaluator caches;
- introduces callback/event/listener behavior;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Theme, Localization, Editor, or HUD;
- changes the existing WP-109 through WP-115 public responsibilities;
- adds a manager, service locator, scanner, router, generalized registry, or global mutable state.

## Acceptance criteria

- Evaluation stage vocabulary represents declarations/metadata, persistence/profile values, theme token resolution, localization resolution, inherited values, explicit effective values, computed expressions, animation outputs, generated layout/text/render properties, and diagnostics/diffs.
- Evaluation status vocabulary can represent not evaluated, succeeded, fallback used, skipped, and failed outcomes.
- Evaluation order records are immutable after construction and carry stage plus stable order index.
- Evaluation result records are immutable after construction and carry property ID, stage, status, optional effective stored value, and generation stamp.
- Evaluation snapshots are immutable after construction and preserve deterministic result order.
- No expression execution, dependency graph construction/traversal/sorting/validation, source lookup, binding/theme/localization/animation/profile resolution, mutation, diagnostic generation, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Is WP-116 strictly passive evaluation vocabulary/result/snapshot infrastructure?
- Does it avoid expression execution, graph traversal/sorting/validation, and source resolution?
- Does it preserve future evaluator and snapshot layers instead of implementing them early?
- Are ownership, lifetime, and layering unchanged?
- Is Architecture Freeze V2 preserved?

## Approved commit message

`feat(ui): add property evaluation baseline`
