# WP-119 — UI Scene Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-119 directly implements the approved Declarative UI Runtime Scene layer as passive scene identity, element metadata, and immutable scene snapshot infrastructure. It consumes the completed Property Runtime snapshot as read-only scene data and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI Scene Runtime snapshot vocabulary.

WP-119 starts the Scene Runtime layer after the Property Runtime layer completion by adding stable surface, scene, and element identity values plus immutable element and scene snapshots suitable for later layout/render/input/focus layers.

## Scope

- Add stable UI surface ID, scene ID, and element ID value types.
- Add passive scene element kind vocabulary.
- Add passive accessibility role vocabulary.
- Add immutable scene element snapshots with stable ordering and optional parent identity.
- Add immutable scene snapshots with surface identity, scene identity, element records, and aggregate property runtime snapshot.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No scene builder or evaluator.
- No surface composition.
- No view declaration factories.
- No widget behavior.
- No layout constraints, measurement, layout pass, or geometry.
- No render commands.
- No input, focus, capture, navigation, or activation handling.
- No theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- New Scene Runtime types live only under `sirius::ui::scene`.
- Scene snapshots own immutable value records and expose them read-only.
- Scene snapshots may consume `sirius::ui::property::CPropertyRuntimeSnapshot` by value.
- Scene snapshots are not builders, evaluators, layout engines, renderers, input handlers, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- evaluates declarations or properties;
- builds scene trees from module declarations;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Surface, scene, and element IDs are stable string value types with read-only accessors and equality.
- Scene element snapshots are immutable after construction and preserve element ID, optional parent ID, kind, accessibility role, stable order index, label, description, and disabled state.
- Scene snapshots are immutable after construction and preserve surface ID, scene ID, element record order, and the aggregate property runtime snapshot.
- No scene builder/evaluator, surface composition, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add scene snapshot baseline`
