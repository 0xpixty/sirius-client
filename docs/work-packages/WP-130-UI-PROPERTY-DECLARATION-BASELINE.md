# WP-130 — UI Property Declaration Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-130 directly implements the approved Property Runtime declaration bridge for Declarative UI declarations as passive immutable values. It does not evaluate, validate, attach, inherit, resolve, or apply properties.

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

Introduce passive UI property declaration records for surface and element declarations.

WP-130 adds immutable property declaration values carrying Property Runtime metadata, optional default stored value, optional surface owner reference, optional element owner reference, and stable ordering. This establishes the declaration-side bridge to Property Runtime without implementing property validation, dependency graph construction, evaluation, persistence, theme/localization resolution, or mutation.

## Scope

- Add immutable UI property declarations over existing Property Runtime metadata and stored-value snapshots.
- Add optional surface and element owner references using existing UI identity values.
- Add immutable UI property declaration lists preserving deterministic declaration order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No property validation.
- No duplicate-property detection.
- No default value application.
- No property storage mutation.
- No property dependency graph construction.
- No property evaluation.
- No theme, localization, inheritance, persistence, animation, editor, or hot reload resolution.
- No attachment mutation of existing surface or element declaration classes.
- No scene, layout, render, HUD, input, focus, capture, navigation, command, or activation behavior.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No diagnostics generation.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global property declaration registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Property declaration readiness types live only under `sirius::ui::declaration`.
- Property declarations own immutable value records and expose them read-only.
- Property declarations may refer to Scene identity values and Property Runtime metadata/stored-value snapshots by value.
- Property declarations are not property stores, evaluators, validators, graph builders, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- validates property declarations;
- applies default values;
- mutates property storage;
- builds dependency graphs;
- evaluates property values;
- resolves theme/localization/inheritance/persistence/animation/editor sources;
- mutates existing surface or element declarations;
- creates scenes, layout, render commands, or HUD output;
- handles input, focus, capture, navigation, command, or activation behavior;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, or HUD behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global property declaration registry, or global mutable state.

## Acceptance criteria

- Property declarations preserve metadata snapshot, optional default stored value, optional surface owner ID, optional element owner ID, and stable order index with read-only accessors.
- Property declaration lists preserve ordered property declarations and expose read-only accessors.
- Property declarations do not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD dependencies.
- No validation, default application, property mutation, dependency graph construction, evaluation, theme/localization/inheritance/persistence/animation/editor resolution, surface/element declaration mutation, diagnostics generation, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global property declaration registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add property declaration baseline`
