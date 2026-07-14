# WP-132 — UI Declaration Diagnostic Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-132 directly implements the approved Declarative UI Runtime declaration diagnostics vocabulary as passive immutable values. It does not generate, validate, route, log, or act on diagnostics.

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

Introduce passive UI declaration diagnostic records for future validation and composition work.

WP-132 adds diagnostic severity/code vocabulary, optional declaration context references, immutable diagnostic records, and immutable diagnostic snapshots. It prepares structured failure reporting without implementing validation or composition.

## Scope

- Add passive UI declaration diagnostic severity vocabulary.
- Add passive UI declaration diagnostic code vocabulary.
- Add immutable UI declaration diagnostic records with optional surface, element, property, and action-intent context.
- Add immutable UI declaration diagnostic snapshots preserving ordered diagnostic records.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No diagnostics generation.
- No validation.
- No duplicate detection.
- No tree checking.
- No property checking.
- No composition failure behavior.
- No logging or event emission.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No declaration registration, scene evaluation, layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global diagnostic registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Declaration diagnostic readiness types live only under `sirius::ui::declaration`.
- Diagnostic snapshots own immutable diagnostic records and expose them read-only.
- Diagnostic records may refer to Action, Scene, and Property identity values by value.
- Diagnostic records are not validators, loggers, dispatchers, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- validates declarations;
- generates diagnostics from declarations;
- logs, emits, routes, or dispatches diagnostics;
- checks duplicate IDs, tree structure, properties, actions, or host-slot conflicts;
- composes surfaces or evaluates declarations;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, or HUD behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global diagnostic registry, or global mutable state.

## Acceptance criteria

- Declaration diagnostic severity and code vocabulary exists as passive enum values.
- Declaration diagnostic records preserve severity, code, message, optional surface ID, optional element ID, optional property ID, optional action-intent ID, and stable order index with read-only accessors.
- Declaration diagnostic snapshots preserve ordered diagnostic records and expose read-only accessors.
- No validation, diagnostics generation, logging, event emission, composition, evaluation, Platform composition, Module Runtime change, DDNet adapter integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global diagnostic registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add declaration diagnostic baseline`
