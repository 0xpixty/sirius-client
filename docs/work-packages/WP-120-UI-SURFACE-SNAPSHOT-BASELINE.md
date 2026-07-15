# WP-120 — UI Surface Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-120 directly implements the approved Declarative UI Runtime Surface/Scene layer as passive surface host-intent, layer, status, and immutable surface snapshot infrastructure. It composes the WP-119 scene snapshot by value when present and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce passive UI Surface Runtime snapshot vocabulary.

WP-120 builds on WP-119 by adding surface host intent, layer, composition status, host slot identity, and immutable surface snapshots suitable for later Platform-owned UI composition and DDNet adapter hosting.

## Scope

- Add stable UI host slot ID value type.
- Add passive surface host intent vocabulary.
- Add passive surface layer vocabulary.
- Add passive surface composition status vocabulary.
- Add immutable surface snapshots with surface ID, host intent, host slot ID, layer, status, stable order index, and optional scene snapshot.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No surface composition engine.
- No module-owned UI declarations or descriptor integration.
- No scene builder or evaluator.
- No layout constraints, measurement, layout pass, or geometry.
- No render commands.
- No input, focus, capture, navigation, activation, or hosting behavior.
- No theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Surface Runtime types live only under `sirius::ui::scene` for the initial Scene/Surface layer.
- Surface snapshots own immutable value records and expose them read-only.
- Surface snapshots may contain an optional `CSceneSnapshot` by value.
- Surface snapshots are not builders, composition engines, layout engines, renderers, input handlers, host adapters, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- composes surfaces from module declarations;
- chooses actual DDNet host slots;
- evaluates scenes or properties;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Host slot IDs are stable string value types with read-only accessors and equality.
- Surface host intent vocabulary can represent menu, HUD, overlay, editor, modal, tooltip, and custom surfaces.
- Surface layer vocabulary can represent background, content, overlay, modal, tooltip, and debug surfaces.
- Surface status vocabulary can represent hosted, hidden, degraded, rejected, and unavailable surfaces.
- Surface snapshots are immutable after construction and preserve surface ID, host intent, host slot ID, layer, status, stable order index, and optional scene snapshot.
- No composition engine, module descriptor integration, DDNet host selection, scene/property evaluation, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add surface snapshot baseline`
