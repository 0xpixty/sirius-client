# WP-143 — UI Single Surface Runtime Snapshot

Status: approved for implementation.

## Single Surface Runtime direction check

Question: Does this directly move us toward Single Surface Runtime?

Answer: yes.

Aggregate surface composition policies are explicitly deferred. WP-143 introduces the first Single Surface Runtime value by pairing one projected immutable surface snapshot with declaration diagnostics for that same surface.

## Implementation Drift Detection

Result: no drift detected.

WP-143 directly follows the approved bottom-up path: Declaration Runtime is complete, Scene Runtime can project a single surface, and Single Surface Runtime now needs a passive result snapshot for one surface. It does not introduce aggregate surface projection, global Scene ID policy, aggregate composition status policy, Platform composition, or DDNet integration.

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

Add a passive immutable Single Surface Runtime snapshot and projection helper.

## Scope

- Add `CSingleSurfaceRuntimeSnapshot`.
- Store one immutable `CSurfaceSnapshot`.
- Store immutable declaration diagnostics for that surface.
- Expose read-only accessors and diagnostic presence.
- Add `ProjectSingleUiSurfaceRuntimeSnapshot(const CUiSurfaceDeclarationSnapshot &, CUiSceneId, ESurfaceCompositionStatus)`.
- Use existing single-surface projection and declaration validation helpers.
- Keep scene ID and composition status caller-provided.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No aggregate surface projection.
- No global Scene ID policy.
- No aggregate composition status policy.
- No surface conflict resolution.
- No host-slot policy or host-slot selection.
- No Platform composition.
- No property default application or property evaluation.
- No layout, render, HUD, input, focus, capture, navigation, command, activation, persistence, hot reload, undo/redo, animation, editor, theme, or localization behavior.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Single Surface Runtime snapshot lives under `sirius::ui::scene` alongside existing scene/surface values.
- The helper consumes one surface declaration snapshot by const reference and returns a value snapshot.
- The helper owns no runtime state and is not a manager, service, registry, Platform component, host composer, DDNet adapter, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- projects more than one surface;
- assigns scene IDs internally;
- chooses composition statuses internally;
- resolves surface conflicts;
- chooses host slots;
- mutates or integrates Platform;
- applies property defaults;
- evaluates properties;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- A single surface declaration snapshot can project to a Single Surface Runtime snapshot.
- The runtime snapshot exposes the projected surface snapshot read-only.
- The runtime snapshot exposes declaration diagnostics read-only.
- The helper preserves caller-provided scene ID and composition status.
- No aggregate projection, global Scene ID policy, aggregate status policy, surface conflict resolution, host-slot selection, Platform composition, property default/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add single surface runtime snapshot`
