# WP-138 — UI Scene Property Metadata Projection

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene snapshots carry Property Runtime snapshot data. WP-138 adds the next passive Scene Runtime projection step by extracting declared property metadata in stable declaration order, without evaluating property values.

## Implementation Drift Detection

Result: no drift detected.

WP-138 directly implements the approved Scene Runtime path from declarations toward immutable scene snapshots. It does not introduce property evaluation, storage mutation, default application, Platform composition, or any new runtime ownership model.

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

Add passive Scene Runtime projection for declared property metadata.

## Scope

- Add `ProjectUiScenePropertyMetadata(const CUiPropertyDeclarationList &)`.
- Preserve declaration property order exactly.
- Return property metadata snapshot records by value.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No full scene evaluator.
- No scene ID or surface snapshot construction.
- No property storage projection.
- No default value application.
- No property evaluation, dependency graph construction, generation mutation, invalidation, diagnostics generation, operations, persistence, theme, localization, animation, editor, or hot reload behavior.
- No declaration validation.
- No layout, render, HUD, input, focus, capture, navigation, command, or activation behavior.
- No Platform composition.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Projection lives under `sirius::ui::scene`.
- The helper consumes declaration values by const reference and returns property metadata snapshot values by value.
- The helper owns no runtime state and is not a builder, evaluator object, Platform component, service, manager, registry, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- applies property defaults;
- evaluates properties;
- builds complete scenes or surfaces;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Empty property declaration lists project to an empty metadata vector.
- Non-empty property declaration lists project metadata records in declaration order.
- Projected records preserve the declaration metadata snapshots.
- No full scene evaluator, property storage/default/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): project scene property metadata`
