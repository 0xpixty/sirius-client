# WP-142 — UI Surface Snapshot List

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene/Surface Runtime now projects individual surface snapshots. Before aggregate declaration-to-surface projection can exist, the runtime needs a passive immutable list value for ordered surface snapshots.

## Implementation Drift Detection

Result: no drift detected.

WP-142 only extends existing Scene/Surface snapshot value infrastructure. It does not introduce composition policy, host-slot decisions, Platform integration, DDNet integration, or active runtime ownership.

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

Add an immutable surface snapshot list value.

## Scope

- Add `CSurfaceSnapshotList`.
- Store ordered `CSurfaceSnapshot` values.
- Expose read-only snapshots, count, and emptiness.

## Non-goals

- No aggregate scene runtime.
- No aggregate projection from declarations.
- No surface conflict resolution.
- No host-slot policy or host-slot selection.
- No Platform composition.
- No scene ID policy.
- No property evaluation, layout, render, HUD, input, focus, capture, navigation, command, activation, persistence, hot reload, undo/redo, animation, editor, theme, or localization behavior.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- The list lives under `sirius::ui::scene` with the existing surface snapshot values.
- The list owns immutable surface snapshot values and exposes them read-only.
- The list is not a builder, evaluator, Platform component, host composer, service, manager, registry, or cache.

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

- Surface snapshot lists preserve surface snapshot order.
- Surface snapshot lists expose read-only snapshots.
- Surface snapshot lists expose count and emptiness.
- No aggregate projection, surface conflict resolution, host-slot selection, Platform composition, property default/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add surface snapshot list`
