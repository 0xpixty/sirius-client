# WP-134 — UI Declaration Registration Plan

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene Runtime needs a stable, validated declaration snapshot input. WP-134 implements the first Declaration Runtime exit criterion — deterministic declaration registration — over the existing module-owned declaration contribution values.

## Implementation Drift Detection

Result: no drift detected.

WP-134 directly implements the approved Declaration Runtime responsibility to register declarations deterministically. It remains a small explicit registration plan and does not introduce a declaration manager, service locator, router, scanner, generic builder, reflection system, plugin discovery, generalized factory, scripting, serialization, Platform composition, or scene evaluation.

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

Add a deterministic UI declaration registration plan.

The plan stores explicit module-owned UI declaration contributions in caller-provided registration order and rejects empty module IDs, empty declaration contributions, and duplicate module IDs.

## Scope

- Add `CUiDeclarationRegistrationPlan`.
- Preserve caller-provided registration order.
- Reject empty owning module IDs.
- Reject empty declaration contributions.
- Reject duplicate owning module IDs.
- Expose read-only access to contributions in registration order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No Platform composition.
- No surface composition.
- No declaration validation beyond registration-plan admissibility.
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

- The registration plan lives under `sirius::ui::declaration`.
- The plan owns explicit contribution values and exposes them read-only.
- The plan is not a runtime manager, Platform component, Module Runtime component, scanner, service, or registry with ambient access.
- The plan may consume module-owned declaration contribution values by value.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- scans modules or discovers declarations;
- sorts contributions;
- composes surfaces;
- validates declaration trees/properties/actions/host slots;
- generates diagnostics;
- mutates Platform or Module Runtime;
- evaluates declarations into Scene Runtime snapshots;
- introduces declaration manager/router/service-locator/generic-builder/reflection/plugin-discovery/generalized-factory/scripting/serialization behavior;
- introduces mutable runtime state beyond the private vector owned by the plan.

## Acceptance criteria

- `CUiDeclarationRegistrationPlan::Add()` accepts a non-empty module contribution with a unique module ID.
- `Add()` rejects empty module IDs.
- `Add()` rejects empty declaration contributions.
- `Add()` rejects duplicate module IDs.
- Registration order is preserved exactly as contributions are added.
- The plan exposes contribution count, module ID presence, and read-only contributions in registration order.
- No Platform composition, Module Runtime behavior change, scanning, sorting, validation, diagnostics generation, scene evaluation, manager, service locator, router, generic builder, reflection, plugin discovery, generalized factory, scripting, serialization, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add declaration registration plan`
