# WP-141 — UI Surface Snapshot Projection

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene Runtime now projects element, property, and scene snapshots. WP-141 projects a single declared surface into an immutable surface snapshot while keeping composition status caller-provided so host policy and Platform composition remain outside this Work Package.

## Implementation Drift Detection

Result: no drift detected.

WP-141 directly implements the approved Scene/Surface Runtime value publication path from declarations. It does not choose host slots, resolve surface conflicts, integrate with Platform, or render through DDNet.

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

Add passive projection from a single surface declaration snapshot to an immutable surface snapshot with an attached scene snapshot.

## Scope

- Add `ProjectUiSurfaceSnapshot(const CUiSurfaceDeclarationSnapshot &, CUiSceneId, ESurfaceCompositionStatus)`.
- Preserve declared surface ID, host intent, host slot ID, layer, and stable order index.
- Use caller-provided scene ID.
- Use caller-provided surface composition status.
- Attach the projected scene snapshot from `ProjectUiSceneSnapshot()`.

## Non-goals

- No aggregate scene runtime.
- No surface conflict resolution.
- No host-slot policy or host-slot selection.
- No Platform composition.
- No scene ID policy beyond caller-provided identity.
- No default value application.
- No property evaluation, dependency graph construction, generation mutation, invalidation, diagnostics generation, operations, persistence, theme, localization, animation, editor, or hot reload behavior.
- No declaration validation.
- No layout, render, HUD, input, focus, capture, navigation, command, or activation behavior.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Projection lives under `sirius::ui::scene`.
- The helper consumes declaration values by const reference and returns an immutable surface snapshot by value.
- The helper owns no runtime state and is not a builder, evaluator object, Platform component, host composer, service, manager, registry, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- resolves surface conflicts;
- chooses host slots;
- mutates or integrates Platform;
- applies property defaults;
- evaluates properties;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Surface declaration snapshots project to immutable surface snapshots with attached scene snapshots.
- Projected surface snapshots preserve declared surface ID, host intent, host slot ID, layer, and stable order index.
- Projected surface snapshots preserve caller-provided status and scene ID.
- No surface conflict resolution, host-slot selection, Platform composition, property default/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): project surface snapshots`
