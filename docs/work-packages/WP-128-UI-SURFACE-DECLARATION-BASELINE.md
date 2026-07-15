# WP-128 — UI Surface Declaration Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-128 directly implements the approved Declarative UI Runtime surface declaration model as passive immutable metadata and policy values. It does not compose, evaluate, register, or host surfaces and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI surface declaration vocabulary.

WP-128 adds immutable surface declaration values carrying surface identity, host intent, host slot, layer, modality, visibility, focus-scope, persistence, required/optional state, declared action intents, and stable ordering. This establishes the declaration-side counterpart to the existing passive surface snapshots without introducing composition behavior.

## Scope

- Add passive surface modality policy vocabulary.
- Add passive surface visibility policy vocabulary.
- Add passive surface focus-scope policy vocabulary.
- Add passive surface persistence policy vocabulary.
- Add immutable UI surface declarations over existing surface identity/host/layer values and action-intent snapshots.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No module ownership binding.
- No Module Runtime descriptor, definition, dependency, or contract changes.
- No surface registration plan.
- No Platform composition.
- No host-slot conflict resolution.
- No declaration evaluation.
- No scene, layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, or property evaluation behavior.
- No DDNet adapter integration.
- No validation or diagnostics generation.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global surface registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Surface declaration readiness types live only under `sirius::ui::declaration`.
- Surface declarations own immutable value records and expose them read-only.
- Surface declarations may refer to Scene/Surface identity and Action Intent snapshot values by value.
- Surface declarations are not Platform composition records, module descriptors, renderable scenes, DDNet host slots, validators, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, HUD, or Property headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- binds declarations to module IDs or Module Runtime descriptors;
- registers, composes, evaluates, validates, or hosts surfaces;
- resolves host-slot conflicts;
- generates diagnostics;
- creates scenes, layout, or render commands;
- handles input, focus, capture, navigation, command, or activation behavior;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, HUD, or Property Runtime behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global surface registry, or global mutable state.

## Acceptance criteria

- Surface declaration policies represent modality, visibility, focus scope, and persistence intent as passive vocabulary.
- Surface declarations preserve surface ID, host intent, host slot ID, layer, policy values, required flag, declared action-intent snapshots, and stable order index with read-only accessors.
- Surface declarations do not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, HUD, or Property dependencies.
- No module ownership binding, registration, composition, evaluation, validation, diagnostics generation, host-slot conflict resolution, input/focus/capture/navigation behavior, command/activation behavior, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global surface registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add surface declaration baseline`
