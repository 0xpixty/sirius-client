# WP-146 — UI Aggregate Surface Diagnostics

Status: approved for implementation.

## Aggregate Surface Runtime direction check

Question: Does this directly move us toward Aggregate Surface Runtime?

Answer: yes.

Aggregate Surface Runtime must fail deterministic conflicts with deterministic diagnostics. WP-146 adds passive diagnostic value infrastructure before conflict detection and aggregate composition behavior.

## Implementation Drift Detection

Result: no drift detected.

WP-146 adds diagnostics only. It does not compose surfaces, assign statuses, derive scene IDs, resolve conflicts, choose priorities, integrate Platform, or touch DDNet.

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

Add passive Aggregate Surface Runtime diagnostics.

## Scope

- Add aggregate surface diagnostic severity vocabulary.
- Add aggregate surface diagnostic codes for:
  - unknown failures;
  - unsupported host slot;
  - host slot conflict.
- Add immutable diagnostic records with optional primary surface, secondary surface, and host-slot context.
- Add immutable diagnostic snapshot with read-only diagnostics, count, emptiness, and error presence.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No aggregate surface projection.
- No deterministic Scene ID derivation changes.
- No aggregate composition status assignment.
- No host-slot conflict detection.
- No host-slot conflict resolution.
- No hidden priority system.
- No automatic host-slot inference.
- No Platform composition.
- No property default application or property evaluation.
- No layout, render, HUD, input, focus, capture, navigation, command, activation, persistence, hot reload, undo/redo, animation, editor, theme, or localization behavior.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Diagnostics live under `sirius::ui::scene`.
- Diagnostics are immutable values and expose read-only state.
- Diagnostics are not a logger, event stream, manager, service, registry, router, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- resolves host-slot conflicts;
- uses priority or last-wins behavior;
- infers host slots;
- mutates or integrates Platform;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Aggregate surface diagnostic records preserve severity, code, message, optional surface contexts, optional host-slot context, and stable order.
- Aggregate surface diagnostic snapshots expose read-only diagnostics, count, emptiness, and error presence.
- No aggregate projection, status assignment, conflict detection/resolution, host-slot inference, Platform composition, DDNet integration, hidden priority system, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add aggregate surface diagnostics`
