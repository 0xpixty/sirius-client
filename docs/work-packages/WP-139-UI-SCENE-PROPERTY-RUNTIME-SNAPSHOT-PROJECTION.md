# WP-139 — UI Scene Property Runtime Snapshot Projection

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene snapshots require a `CPropertyRuntimeSnapshot` payload. WP-139 adds a passive projection that wraps declared property metadata into a Property Runtime snapshot while leaving storage, diagnostics, generations, invalidations, dependency graph, and evaluation channels empty.

## Implementation Drift Detection

Result: no drift detected.

WP-139 directly implements the approved Scene Runtime path toward immutable scene snapshots. It does not apply defaults, evaluate properties, mutate property storage, generate diagnostics, or introduce runtime ownership changes.

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

Add passive Scene Runtime projection from property declarations to a Property Runtime snapshot suitable for initial scene snapshot construction.

## Scope

- Add `ProjectUiScenePropertyRuntimeSnapshot(const CUiPropertyDeclarationList &)`.
- Preserve declaration property metadata order through `ProjectUiScenePropertyMetadata()`.
- Return a `CPropertyRuntimeSnapshot` with metadata records populated.
- Return empty storage, diagnostics, generations, invalidations, dependency graph, and evaluation snapshots.

## Non-goals

- No full scene evaluator.
- No scene ID or surface snapshot construction.
- No default value application.
- No property storage projection beyond an explicitly empty snapshot.
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
- The helper consumes declaration values by const reference and returns an immutable Property Runtime snapshot by value.
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

- Empty property declaration lists project to an empty Property Runtime snapshot.
- Non-empty property declaration lists project metadata records in declaration order.
- Storage, diagnostics, generations, invalidations, dependency graph, and evaluation snapshots remain empty.
- No full scene evaluator, default application, property value/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): project scene property runtime snapshot`
