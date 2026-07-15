# WP-131 — UI Declaration Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-131 directly implements the approved Declarative UI Runtime declaration inspectability layer as passive immutable aggregate snapshots. It does not register, compose, validate, evaluate, or host declarations.

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

Introduce passive aggregate UI declaration snapshots.

WP-131 adds immutable declaration snapshots that group a surface declaration with ordered element and property declaration lists, plus an immutable declaration snapshot list for future module/platform composition work.

## Scope

- Add immutable per-surface UI declaration snapshots.
- Add immutable aggregate UI declaration snapshots preserving ordered surface declaration snapshots.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No declaration registration plan.
- No module ownership binding.
- No Module Runtime descriptor, definition, dependency, or contract changes.
- No Platform composition.
- No surface composition.
- No validation, diagnostics generation, or conflict resolution.
- No declaration evaluation into scene snapshots.
- No property evaluation or property storage mutation.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global declaration registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Declaration aggregate readiness types live only under `sirius::ui::declaration`.
- Declaration snapshots own immutable declaration values and expose them read-only.
- Declaration snapshots are not registries, validators, evaluators, Platform composition records, module descriptors, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- registers declarations;
- binds declarations to module IDs or Module Runtime descriptors;
- composes surfaces;
- validates declaration consistency or tree structure;
- generates diagnostics;
- evaluates declarations into scene snapshots;
- mutates property storage or evaluates properties;
- creates layout or render commands;
- handles input, focus, capture, navigation, command, or activation behavior;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, or HUD behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global declaration registry, or global mutable state.

## Acceptance criteria

- Per-surface declaration snapshots preserve one surface declaration plus ordered element and property declaration lists with read-only accessors.
- Aggregate declaration snapshots preserve ordered per-surface declaration snapshots with read-only accessors.
- Declaration snapshots do not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, or HUD dependencies.
- No registration, module ownership binding, composition, validation, diagnostics generation, declaration evaluation, property evaluation, property mutation, layout/render behavior, input/focus/capture/navigation behavior, command/activation behavior, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global declaration registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add declaration snapshot baseline`
