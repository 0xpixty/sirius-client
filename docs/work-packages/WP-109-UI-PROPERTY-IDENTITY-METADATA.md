# WP-109 — UI Property Identity, Type Descriptors, and Metadata Snapshots

Status: approved for implementation.

## Goal

Introduce the first bottom-up Sirius Declarative UI Runtime implementation slice: inert UI Property Runtime value types for stable property identity, typed value descriptors, default descriptors, and immutable property metadata snapshots.

This Work Package establishes vocabulary only. It must not introduce property storage, mutation operations, diagnostics, generations, invalidation, dependency graphs, evaluation, scene/layout/render systems, theme runtime, localization runtime, editor runtime, HUD runtime, DDNet adapter integration, or module composition changes.

## Scope

- Add UI/property identity value objects under `src/sirius/ui/property/`:
  - module scope ID;
  - surface ID;
  - property owner ID;
  - property name ID;
  - complete property ID scoped by module, surface, owner, and property name.
- Add typed property value descriptors:
  - primitive value kind;
  - semantic value kind.
- Add metadata-supporting enums for owner, optionality, access, persistence, default, and evaluation stage.
- Add policy metadata enums for inheritance, theme, localization, animation, and editor behavior.
- Add an immutable property metadata snapshot value object.
- Register new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No property storage.
- No property operations.
- No diagnostics runtime.
- No generation counters.
- No invalidation.
- No dependency graph.
- No expression or binding evaluation.
- No property snapshots containing live values.
- No UI scene, layout, render, theme, localization, editor, or HUD runtime.
- No DDNet UI/render/input types.
- No manager, scanner, service locator, generalized lookup API, dynamic discovery, or module-facing mutation API.
- No redesign of Module Runtime, Declarative UI Runtime, or Property Runtime architecture.

## Ownership and boundaries

- New types live under `sirius::ui::property`.
- Property IDs carry a UI-local module scope ID string value. They do not include Module Runtime headers or depend on Platform implementation.
- The slice is passive and value-based. It does not compose modules, scan declarations, or expose runtime lookup.
- DDNet remains absent from public UI property APIs.

## Acceptance criteria

- Property identity is stable and value-based, with no pointer, index, render-order, or localized-text identity.
- Metadata snapshots are immutable after construction and expose read-only accessors.
- Typed value descriptors cover the approved first-class primitive and semantic property categories.
- The implementation compiles as part of `game-client`.
- The implementation does not introduce storage, operations, diagnostics, generations, invalidation, dependency graph, evaluation, rendering, editor, or adapter integration.
- Architecture Freeze v2 is preserved.

## Validation

- `git diff --check`
- Debug `game-client` build when available
- RelWithDebInfo `game-client` build when available
- Focused source inspection for forbidden APIs and dependency leaks

## Review checklist

- New APIs are passive value/snapshot APIs only.
- No DDNet types leak into Sirius UI property declarations.
- No global mutable state or singleton registry exists.
- No lookup-anything-by-string or service-location API exists.
- No production behavior changes outside compile-time availability of the new value types.

## Approved commit message

`feat(ui): add property identity metadata baseline`
