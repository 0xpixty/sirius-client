# WP-127 — UI Action Intent Identity Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-127 directly implements the approved Declarative UI Runtime action-intent identity primitive as passive value and snapshot infrastructure. It does not resolve, route, dispatch, or execute UI actions and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI action-intent identity vocabulary.

WP-127 adds stable action-intent IDs, passive action-intent kind vocabulary, immutable action-intent snapshots, and immutable action-intent snapshot lists so future declaration, scene, input, and command/activation integration can refer to UI actions without bypassing Sirius ownership boundaries.

## Scope

- Add stable UI action-intent ID value type.
- Add passive action-intent kind vocabulary.
- Add immutable UI action-intent snapshots with display label, required flag, and stable order index.
- Add immutable UI action-intent snapshot lists.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No input routing.
- No hit testing.
- No focus, capture, or navigation behavior.
- No command or activation resolution.
- No command dispatch or activation execution.
- No feature mutation.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No UI declaration evaluation.
- No scene, layout, render, theme, localization, editor, or HUD behavior changes.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global action registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Action-intent readiness types live only under `sirius::ui::action`.
- Action-intent snapshots own immutable value records and expose them read-only.
- Action-intent IDs are neutral UI identities, not command IDs, activation IDs, DDNet input IDs, callbacks, or function pointers.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Localization, Editor, HUD, or Property headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- resolves action intents to commands or activations;
- dispatches commands or activations;
- mutates feature state;
- handles input, hit testing, focus, capture, or navigation;
- evaluates UI declarations or scenes;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Scene, Layout, Render, Theme, Localization, Editor, HUD, or Property Runtime behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global action registry, or global mutable state.

## Acceptance criteria

- UI action-intent IDs are stable string value types with read-only accessors and equality.
- Action-intent kind vocabulary represents command, activation, navigation, focus, and custom intents without depending on Platform or DDNet types.
- Action-intent snapshots preserve action-intent ID, kind, display label, required flag, and stable order index with read-only accessors.
- Action-intent snapshot lists preserve ordered action-intent snapshots and expose read-only accessors.
- No input routing, command/activation resolution, dispatch, execution, feature mutation, Platform composition, Module Runtime change, DDNet adapter integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global action registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add action intent identity baseline`
