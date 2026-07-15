# WP-144 — UI Surface Runtime Policy Vocabulary

Status: approved for implementation.

## Aggregate Surface Runtime direction check

Question: Does this directly move us toward Aggregate Surface Runtime?

Answer: yes.

The Aggregate Surface Runtime policies are now architecturally defined. WP-144 updates the passive Surface Runtime vocabulary so later aggregate composition can use the approved policies without inventing alternative states or host-slot identities.

## Implementation Drift Detection

Result: no drift detected.

WP-144 implements the approved policy vocabulary only. It does not introduce aggregate surface projection, scene ID derivation, host-slot conflict handling, Platform composition, DDNet integration, or hidden priority systems.

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

Align Surface Runtime vocabulary with the approved aggregate policies.

## Scope

- Replace the old passive surface composition status vocabulary with:
  - `Pending`
  - `Composed`
  - `Failed`
- Add named host-slot identity helpers for:
  - `BeforeHUD`
  - `HUD`
  - `Overlay`
  - `Menu`
  - `Modal`
  - `Debug`
- Add a read-only helper to check whether a host slot is one of the approved initial host-slot identities.

## Non-goals

- No aggregate surface projection.
- No deterministic Scene ID derivation.
- No aggregate composition status assignment.
- No host-slot conflict detection.
- No host-slot exclusivity matrix.
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

- The policy vocabulary lives under `sirius::ui::scene` with the existing surface snapshot values.
- Host-slot helpers return stable value identities and do not allocate or consult runtime state.
- The vocabulary is not a runtime manager, composer, registry, service, router, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- introduces statuses beyond `Pending`, `Composed`, and `Failed`;
- infers host slots from surface type, layer, host intent, or runtime context;
- resolves host-slot conflicts;
- assigns scene IDs;
- mutates or integrates Platform;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Surface composition status vocabulary contains only `Pending`, `Composed`, and `Failed`.
- Named host-slot helper values are stable and explicit.
- Host-slot validation helper recognizes only the approved initial host slots.
- Existing single-surface projection remains caller-driven for status.
- No aggregate projection, Scene ID derivation, conflict detection, host-slot inference, Platform composition, DDNet integration, hidden priority system, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add surface runtime policy vocabulary`
