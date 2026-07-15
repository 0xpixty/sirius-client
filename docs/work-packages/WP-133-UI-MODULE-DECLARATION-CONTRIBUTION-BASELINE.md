# WP-133 — UI Module Declaration Contribution Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-133 directly implements the approved Module Runtime ownership boundary for UI declarations as passive immutable contribution values. It does not register, sort, validate, compose, or discover UI declarations.

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

Introduce passive module-owned UI declaration contribution records.

WP-133 adds immutable contribution values pairing an owning Module Runtime module ID with an aggregate UI declaration snapshot and the already-determined Module Runtime order index. This prepares deterministic composition while preserving the rule that UI declarations enter through Module Runtime ownership rather than scanning or global lookup.

## Scope

- Add immutable UI module declaration contribution records.
- Add immutable contribution snapshots preserving ordered contribution records.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No module descriptor, definition, dependency, lifecycle, or contract changes.
- No registration plan.
- No sorting.
- No duplicate detection.
- No validation.
- No diagnostics generation.
- No Platform composition.
- No surface composition.
- No declaration discovery or scanning.
- No declaration evaluation, property evaluation, scene/layout/render/theme/localization/editor/HUD/input/focus/capture/navigation/command/activation behavior.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global contribution registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Contribution readiness types live under `sirius::ui::declaration` because they describe UI declaration ownership, not Platform composition behavior.
- Contribution records own immutable declaration snapshots and expose them read-only.
- Contribution records may refer to Module Runtime module IDs by value.
- Contribution records are not module descriptors, registries, composition results, validators, services, managers, or caches.
- The layer must not include DDNet, adapter, Feature, Command, Binding, Layout, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- changes Module Runtime descriptors, definitions, dependencies, lifecycle, or contracts;
- registers, sorts, validates, composes, or discovers declarations;
- scans modules or enumerates arbitrary registries;
- generates diagnostics;
- evaluates declarations into scene snapshots;
- mutates property storage or evaluates properties;
- creates layout or render commands;
- handles input, focus, capture, navigation, command, or activation behavior;
- integrates with Platform composition, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, or HUD behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global contribution registry, or global mutable state.

## Acceptance criteria

- UI module declaration contributions preserve owning module ID, declaration snapshot, and Module Runtime order index with read-only accessors.
- Contribution snapshots preserve ordered contribution records and expose read-only accessors.
- No Module Runtime behavior changes, registration plan, sorting, validation, diagnostics generation, Platform composition, DDNet adapter integration, declaration discovery/scanning, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global contribution registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add module declaration contribution baseline`
