# WP-112 — UI Property Diagnostics Baseline

Status: approved for implementation.

## Goal

Introduce passive UI Property Runtime diagnostics value objects.

WP-112 builds directly on WP-109 identity/metadata, WP-110 storage, and WP-111 operations. It defines diagnostic vocabulary and immutable diagnostic snapshots that later validation, operation application, dependency, evaluation, serialization, theme, localization, editor, and hot-reload layers can emit.

## Scope

- Add property diagnostic severity vocabulary.
- Add property diagnostic code vocabulary aligned with the approved Property System architecture.
- Add immutable diagnostic records with message text and optional property/operation context.
- Add immutable diagnostic snapshots preserving deterministic diagnostic order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No diagnostic generation or validation engine.
- No operation application.
- No mutable property store.
- No generation counters.
- No invalidation.
- No dependency graph.
- No expression or binding evaluation.
- No serialization/migration implementation.
- No theme or localization resolution.
- No undo/redo or editor runtime.
- No scene, layout, render, or HUD runtime.
- No Platform composition or Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, dynamic discovery, router, callback registry, or global mutable state.

## Ownership and boundaries

- New types live under `sirius::ui::property`.
- Diagnostics are passive values, not logging, event dispatch, callbacks, exceptions, or validation execution.
- Optional context may reference property IDs and operation IDs only.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, or Adapter headers.

## Acceptance criteria

- Diagnostics can represent architecture-approved property failure categories as passive codes.
- Diagnostic records are immutable after construction.
- Diagnostic snapshots are immutable after construction and preserve deterministic order.
- Diagnostics do not validate, mutate, publish events, log automatically, throw exceptions, increment generations, invalidate dependencies, evaluate properties, or apply operations.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Are diagnostics passive values only?
- Does the API avoid logging/event/callback/global behavior?
- Are optional property/operation contexts value references only?
- Are DDNet, Platform, Module Runtime, Feature, Command, Binding, and Adapter boundaries preserved?
- Is Architecture Freeze v2 preserved?

## Approved commit message

`feat(ui): add property diagnostics baseline`
