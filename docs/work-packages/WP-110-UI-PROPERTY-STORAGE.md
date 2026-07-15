# WP-110 — UI Property Storage Baseline

Status: approved for implementation.

## Goal

Introduce the first passive storage layer for the Sirius UI Property Runtime.

WP-110 builds directly on WP-109 property identity, type descriptors, and metadata snapshots. It provides immutable storage records and storage snapshots that can hold declared property values without introducing mutation operations, diagnostics, generations, invalidation, dependency graphs, evaluation, or UI higher layers.

## Scope

- Add a typed stored-value holder associated with a `CPropertyTypeDescriptor`.
- Add immutable property storage records keyed by `CPropertyId`.
- Add immutable property storage snapshots containing a deterministic list of storage records.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No set/reset/add/remove/reorder operations.
- No mutable property store API.
- No diagnostics runtime.
- No generation counters.
- No invalidation.
- No dependency graph.
- No expression or binding evaluation.
- No effective property snapshots.
- No serialization/migration implementation.
- No scene, layout, render, theme, localization, editor, or HUD runtime.
- No Platform composition or Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, dynamic discovery, router, callback registry, or global mutable state.

## Ownership and boundaries

- New types live under `sirius::ui::property`.
- Storage is passive and value-based.
- Stored values retain their declared type descriptor; validation and diagnostics are intentionally left to later WPs.
- Storage snapshots expose read-only record inspection and no mutation entry points.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, or Adapter headers.

## Acceptance criteria

- Stored values carry a property type descriptor and a stable payload string without interpreting or validating it.
- Storage records are immutable after construction and pair one property ID with one stored value.
- Storage snapshots are immutable after construction and preserve the provided deterministic record order.
- No mutation operations, diagnostics, generations, invalidation, dependency graph, evaluation, rendering, editor behavior, Platform composition, Module Runtime changes, DDNet adapter integration, managers, scanners, service locators, generalized lookup APIs, or global mutable state are introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Does storage remain below operations and evaluation?
- Are storage records/snapshots immutable-by-interface?
- Does the API avoid generalized lookup and mutable registry behavior?
- Are DDNet, Platform, Module Runtime, Feature, Command, Binding, and Adapter boundaries preserved?
- Is Architecture Freeze v2 preserved?

## Approved commit message

`feat(ui): add property storage baseline`
