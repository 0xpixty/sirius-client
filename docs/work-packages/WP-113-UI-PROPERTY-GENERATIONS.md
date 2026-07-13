# WP-113 — UI Property Generations Baseline

Status: approved for implementation.

## Goal

Introduce passive UI Property Runtime generation value objects.

WP-113 builds on WP-109 through WP-112 and adds generation counters/snapshots that later invalidation, dependency, evaluation, rendering, editor, persistence, and hot-reload layers can reference. It does not implement invalidation or generate new generations by itself.

## Scope

- Add a property generation counter value object.
- Add immutable generation stamps containing declaration, effective value, metadata, dependency, and diagnostic generation counters.
- Add immutable per-property generation records pairing one property ID with one generation stamp.
- Add immutable generation snapshots preserving deterministic generation-record order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No invalidation.
- No dirty tracking.
- No generation mutation API.
- No dependency graph.
- No evaluation.
- No operation application.
- No diagnostic generation or validation engine.
- No serialization/migration implementation.
- No theme or localization resolution.
- No undo/redo or editor runtime.
- No scene, layout, render, or HUD runtime.
- No Platform composition or Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, dynamic discovery, router, callback registry, or global mutable state.

## Ownership and boundaries

- New types live under `sirius::ui::property`.
- Generations are passive values, not invalidation or lifecycle controllers.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, or Adapter headers.

## Acceptance criteria

- Generation counters are immutable value objects.
- Generation stamps contain the architecture-approved generation categories: declaration, effective value, metadata, dependency, and diagnostic.
- Generation records are immutable after construction and reference exactly one property ID.
- Generation snapshots are immutable after construction and preserve deterministic record order.
- Snapshot counters cover the architecture-approved generation categories: declaration, effective value, metadata, dependency, and diagnostic.
- No invalidation, dirty tracking, mutation API, dependency graph, evaluation, operation application, validation engine, Platform composition, Module Runtime changes, DDNet adapter integration, managers, scanners, service locators, generalized lookup APIs, or global mutable state are introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Are generations passive values only?
- Does the API avoid invalidation and dirty tracking?
- Are DDNet, Platform, Module Runtime, Feature, Command, Binding, and Adapter boundaries preserved?
- Is Architecture Freeze v2 preserved?

## Approved commit message

`feat(ui): add property generation baseline`
