# WP-145 — UI Surface Scene ID Policy

Status: approved for implementation.

## Aggregate Surface Runtime direction check

Question: Does this directly move us toward Aggregate Surface Runtime?

Answer: yes.

Aggregate Surface Runtime needs deterministic Scene IDs before it can project multiple declared surfaces without caller-provided scene identity. WP-145 implements the approved Scene ID policy as a pure value derivation from stable declaration identity.

## Implementation Drift Detection

Result: no drift detected.

WP-145 implements only deterministic Scene ID derivation from stable declaration identity. It does not introduce aggregate surface projection, composition status assignment, host-slot conflict handling, Platform composition, or DDNet integration.

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

Add deterministic hierarchical Scene ID derivation for surface declarations.

## Scope

- Add `DeriveUiSceneId(const CUiSurfaceDeclaration &)`.
- Derive the scene ID only from the declared surface ID.
- Use a stable textual hierarchy prefix.
- Keep derivation independent of registration order, runtime allocation, pointer values, vector indices, and timestamps.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No aggregate surface projection.
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

- Scene ID derivation lives under `sirius::ui::scene`.
- The helper consumes immutable declaration identity and returns a value identity.
- The helper owns no runtime state and is not a composer, manager, registry, service, router, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- uses registration order, runtime allocation, pointer values, vector indices, timestamps, random values, or global counters;
- assigns composition status;
- resolves host-slot conflicts;
- infers host slots;
- mutates or integrates Platform;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Scene IDs are derived deterministically from declared surface IDs.
- Scene ID derivation uses no order, allocation, pointer, index, timestamp, random, or counter input.
- Scene ID derivation has no side effects and owns no state.
- No aggregate projection, status assignment, conflict detection, host-slot inference, Platform composition, DDNet integration, hidden priority system, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): derive surface scene ids`
