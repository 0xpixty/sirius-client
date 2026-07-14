# WP-126 — UI HUD Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-126 directly implements the approved Declarative UI Runtime HUD-readiness layer as passive HUD surface and HUD snapshot infrastructure. It also aligns the existing surface layer vocabulary with the approved architecture by adding the missing HUD layer value. It does not migrate DDNet HUD rendering and does not change ownership, lifetime, layering responsibility, public API responsibility, or runtime responsibility beyond the approved passive snapshot surface.

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

Introduce the first passive UI HUD Runtime readiness snapshot vocabulary.

WP-126 starts the HUD Runtime layer after the Editor Runtime foundation by adding immutable HUD surface snapshots and immutable HUD snapshots that can carry already-produced surface, layout-safe-area, and render-command-list snapshots without producing or applying them.

## Scope

- Add the approved `Hud` surface layer value to the surface snapshot layer vocabulary.
- Add immutable HUD surface snapshots carrying a composed surface snapshot, logical safe-area bounds, passive visibility state, optional interaction flag, and stable order index.
- Add immutable HUD snapshots carrying the target host slot ID, ordered HUD surface snapshots, and ordered render command-list snapshots.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No DDNet HUD migration.
- No HUD rendering.
- No render command generation.
- No DDNet adapter translation.
- No platform surface composition.
- No module descriptor or contract integration.
- No feature, command, binding, activation, input, focus, capture, navigation, layout, theme, localization, editor, or property evaluation behavior.
- No safe-area calculation.
- No HUD customization UI.
- No persistence, profile switching, hot reload, animation, plugin, docking, or editor behavior.
- No mutation of active runtime property, scene, surface, layout, render, theme, localization, editor, feature, or DDNet state.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global HUD state, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- HUD Runtime readiness types live only under `sirius::ui::hud`.
- HUD snapshots own immutable value records and expose them read-only.
- HUD snapshots may aggregate Scene/Surface, Layout, and Render Runtime snapshot values by value.
- HUD snapshots are not HUD renderers, DDNet HUD adapters, surface composers, input handlers, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Theme, Localization, Editor, or Property headers directly.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- migrates or calls DDNet HUD/menu/rendering code;
- generates render commands;
- computes safe areas or layout;
- composes Platform surfaces;
- discovers modules or UI declarations;
- handles input, focus, capture, or navigation;
- evaluates properties, themes, localization, animation, profiles, persistence, or hot reload;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Theme, Localization, Editor, or Property Runtime behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, global HUD state, or global mutable state.

## Acceptance criteria

- Surface layer vocabulary includes the approved HUD layer value.
- HUD surface snapshots preserve a composed surface snapshot, logical safe-area bounds, visibility state, optional interaction flag, and stable order index with read-only accessors.
- HUD snapshots preserve a host slot ID, ordered HUD surface snapshots, ordered render command-list snapshots, and read-only accessors.
- No DDNet HUD migration, rendering, render command generation, adapter translation, Platform composition, Module Runtime change, feature/command/binding/input/focus/capture/navigation behavior, safe-area calculation, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global HUD state, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add hud snapshot baseline`
