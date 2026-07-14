# WP-136 — UI Declaration Validation

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Scene Runtime needs declaration snapshots that have passed minimum structural admissibility before later scene construction can consume them. WP-136 implements the third Declaration Runtime exit criterion — declaration validation — using the existing declaration diagnostic vocabulary.

## Implementation Drift Detection

Result: no drift detected.

WP-136 directly implements the approved Declaration Runtime responsibility to validate declarations. It stays passive and local to `sirius::ui::declaration`, returning immutable diagnostics without introducing a declaration manager, service locator, router, scanner, generic builder, reflection system, plugin discovery, generalized factory, scripting, serialization, Platform composition, or scene evaluation.

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

Add a passive minimum declaration validation helper that inspects an immutable declaration snapshot and returns immutable diagnostics.

## Scope

- Add `ValidateUiDeclarationSnapshot(const CUiDeclarationSnapshot &)`.
- Report empty surface IDs.
- Report duplicate surface IDs.
- Report empty element IDs.
- Report duplicate element IDs within a surface.
- Report missing declared parent elements within a surface.
- Report incomplete property IDs.
- Report duplicate property IDs within a surface.
- Report invalid optional surface and element owner references when present.
- Report empty action intent IDs.
- Report duplicate action intent IDs within each surface or element declaration.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No Platform composition.
- No surface composition or conflict resolution.
- No declaration diagnostics beyond minimum structural admissibility.
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

- Validation lives under `sirius::ui::declaration`.
- The helper consumes an immutable declaration snapshot by const reference and returns a diagnostic snapshot by value.
- The helper does not own runtime state and is not a runtime manager, Platform component, Module Runtime component, scanner, service, or registry with ambient access.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- scans modules or discovers declarations;
- sorts declarations;
- composes surfaces;
- resolves conflicts;
- mutates Platform or Module Runtime;
- evaluates declarations into Scene Runtime snapshots;
- applies property values or evaluates property expressions;
- introduces declaration manager/router/service-locator/generic-builder/reflection/plugin-discovery/generalized-factory/scripting/serialization behavior;
- introduces mutable runtime state, mutable caches, global registries, or global mutable state.

## Acceptance criteria

- Empty declaration snapshots validate successfully with no diagnostics.
- Empty surface IDs produce `EmptySurfaceId`.
- Duplicate surface IDs produce `DuplicateSurfaceId`.
- Empty element IDs produce `EmptyElementId`.
- Duplicate element IDs within a surface produce `DuplicateElementId`.
- Missing declared parent elements produce `MissingParentElement`.
- Incomplete property IDs produce `EmptyPropertyId`.
- Duplicate property IDs within a surface produce `DuplicatePropertyId`.
- Optional owner references that point outside the current surface produce `InvalidPropertyOwner`.
- Empty action intent IDs produce `EmptyActionIntentId`.
- Duplicate action intent IDs within a single declaration produce `DuplicateActionIntentId`.
- No Platform composition, Module Runtime behavior change, scanning, sorting, scene evaluation, manager, service locator, router, generic builder, reflection, plugin discovery, generalized factory, scripting, serialization, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): validate declaration snapshots`
