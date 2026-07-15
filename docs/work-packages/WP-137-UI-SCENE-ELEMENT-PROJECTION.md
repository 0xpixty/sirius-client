# WP-137 — UI Scene Element Projection

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Declaration Runtime is complete. Scene Runtime now needs the first passive evaluation step from validated declaration values into immutable scene values. WP-137 projects element declarations into scene element snapshots without building a full scene evaluator.

## Implementation Drift Detection

Result: no drift detected.

WP-137 directly implements the approved Scene Runtime responsibility to produce immutable scene element snapshot values from declarations. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility beyond the bounded Scene Runtime projection helper.

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

Add the first passive Scene Runtime declaration projection helper for element snapshots.

## Scope

- Add `ProjectUiSceneElements(const CUiElementDeclarationList &)`.
- Preserve declaration element order exactly.
- Preserve element ID, optional parent ID, kind, accessibility role, stable order index, accessibility label, and accessibility description.
- Set projected scene element disabled state to `false` until interaction/state evaluation exists.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No full scene evaluator.
- No scene ID or surface snapshot construction.
- No property runtime projection.
- No declaration validation.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, persistence, hot reload, undo/redo, or animation behavior.
- No Platform composition.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Projection lives under `sirius::ui::scene`.
- The helper consumes declaration values by const reference and returns scene element snapshot values by value.
- The helper owns no runtime state and is not a builder, evaluator object, Platform component, service, manager, registry, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- evaluates properties;
- builds complete scenes or surfaces;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Empty element declaration lists project to an empty scene element vector.
- Non-empty element declaration lists project to scene element snapshots in declaration order.
- Projected scene elements preserve ID, optional parent ID, kind, accessibility role, stable order index, label, and description.
- Projected scene elements are not disabled by default.
- No full scene evaluator, property projection/evaluation, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): project scene elements`
