# WP-135 — UI Declaration Composition Snapshot

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene Runtime needs one stable immutable declaration input assembled from registered module-owned UI declarations. WP-135 implements the second Declaration Runtime exit criterion — deterministic declaration composition — by flattening the explicit declaration registration plan into one aggregate declaration snapshot.

## Implementation Drift Detection

Result: no drift detected.

WP-135 directly implements the approved Declaration Runtime responsibility to compose declarations deterministically. It stays inside the declaration layer and does not introduce a declaration manager, service locator, router, scanner, generic builder, reflection system, plugin discovery, generalized factory, scripting, serialization, validation engine, diagnostics generation, Platform composition, or scene evaluation.

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

Add a deterministic UI declaration composition helper that turns a validated registration plan into one immutable declaration snapshot.

Composition order is:

1. caller-provided registration plan order;
2. each contribution's existing local declaration surface order.

## Scope

- Add `ComposeUiDeclarationSnapshot(const CUiDeclarationRegistrationPlan &)`.
- Preserve registration plan order exactly.
- Preserve each contribution's local surface order exactly.
- Return an immutable `CUiDeclarationSnapshot`.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No Platform composition.
- No surface conflict resolution.
- No declaration validation.
- No declaration diagnostics generation.
- No declaration sorting.
- No Module Runtime descriptor, definition, dependency, lifecycle, or contract changes.
- No module scanning or discovery.
- No declaration manager, service locator, router, generic builder, reflection system, plugin discovery, generalized factory, scripting, serialization, callback registry, event bus, mutable cache, global declaration registry, or global mutable state.
- No scene evaluation.
- No property evaluation or mutation.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No DDNet adapter integration.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Composition lives under `sirius::ui::declaration`.
- The helper consumes a registration plan by const reference and produces a value snapshot.
- The helper does not own runtime state and is not a runtime manager, Platform component, Module Runtime component, scanner, service, or registry with ambient access.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- scans modules or discovers declarations;
- sorts contributions or surfaces;
- resolves conflicts;
- validates declaration trees/properties/actions/host slots;
- generates diagnostics;
- mutates Platform or Module Runtime;
- evaluates declarations into Scene Runtime snapshots;
- introduces declaration manager/router/service-locator/generic-builder/reflection/plugin-discovery/generalized-factory/scripting/serialization behavior;
- introduces mutable runtime state, mutable caches, global registries, or global mutable state.

## Acceptance criteria

- Empty registration plans compose into an empty declaration snapshot.
- Non-empty registration plans compose into one declaration snapshot containing every registered contribution surface.
- Registration plan order is preserved exactly.
- Per-contribution surface order is preserved exactly.
- No Platform composition, Module Runtime behavior change, scanning, sorting, validation, diagnostics generation, scene evaluation, manager, service locator, router, generic builder, reflection, plugin discovery, generalized factory, scripting, serialization, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): compose declaration snapshots`
