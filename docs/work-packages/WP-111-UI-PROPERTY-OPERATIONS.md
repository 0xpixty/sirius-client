# WP-111 — UI Property Operations Baseline

Status: approved for implementation.

## Goal

Introduce passive UI Property Runtime operation value objects.

WP-111 builds directly on WP-109 identity/metadata and WP-110 storage. It defines typed operation records that can describe future property changes without applying them, validating them, generating diagnostics, incrementing generations, invalidating dependencies, evaluating properties, or introducing editor/runtime behavior.

## Scope

- Add a stable property operation ID value object.
- Add operation kind vocabulary for first-era property operations.
- Add immutable property operation records targeted at `CPropertyId`.
- Allow operation records to optionally carry a `CPropertyStoredValue` payload.
- Add immutable property operation batches preserving deterministic operation order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No operation application to storage snapshots.
- No mutable property store.
- No diagnostics runtime.
- No generation counters.
- No invalidation.
- No dependency graph.
- No expression or binding evaluation.
- No undo/redo history.
- No editor runtime.
- No serialization/migration implementation.
- No scene, layout, render, theme, localization, or HUD runtime.
- No Platform composition or Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, dynamic discovery, router, callback registry, or global mutable state.

## Ownership and boundaries

- New types live under `sirius::ui::property`.
- Operations are passive values, not commands, callbacks, or mutation APIs.
- Operation batches preserve caller-provided order and do not validate or execute operations.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, or Adapter headers.

## Acceptance criteria

- Property operation IDs are stable value objects.
- Property operation records are immutable after construction and target exactly one property ID.
- Operation records can represent no-payload operations and payload-carrying operations without applying them.
- Operation batches are immutable after construction and expose read-only operation inspection.
- No operation application, mutable storage, diagnostics, generations, invalidation, dependency graph, evaluation, undo/redo, editor behavior, Platform composition, Module Runtime changes, DDNet adapter integration, managers, scanners, service locators, generalized lookup APIs, or global mutable state are introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Review checklist

- Are operations passive values only?
- Do operation records avoid calling into storage, editor, commands, features, or DDNet?
- Does the API avoid generalized lookup and mutation surfaces?
- Are DDNet, Platform, Module Runtime, Feature, Command, Binding, and Adapter boundaries preserved?
- Is Architecture Freeze v2 preserved?

## Approved commit message

`feat(ui): add property operation baseline`
