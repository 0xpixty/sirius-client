# WP-170 — UI Input Diagnostics

## Status

APPROVED

## Input Runtime gate

Question: Does this directly move us toward a complete immutable Input Runtime Snapshot?

Answer: YES. WP-170 adds the passive diagnostic vocabulary required before deterministic input snapshot validation can report invalid events without introducing routing or behavior.

## Architecture Freeze V2 drift check

WP-170 directly implements the approved Declarative UI Input Runtime diagnostic boundary. It keeps Input Runtime source-neutral and does not alter ownership, lifetime, layering, public API responsibility, runtime responsibility, or introduce an undocumented abstraction.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add passive immutable UI input diagnostics.

## Scope

- Add input diagnostic severity vocabulary.
- Add input diagnostic code vocabulary for event identity, device kind, event kind, button state, position, and duplicate event identity issues.
- Add immutable input diagnostic records.
- Add immutable input diagnostic snapshots with read-only count, empty, and error helpers.

## Non-goals

- No DDNet adapter translation.
- No `IInput`, `CUi`, `CUIRect`, `IGraphics`, `ITextRender`, or `CRenderTools` dependency.
- No input validation generation.
- No hit testing.
- No focus ownership.
- No capture ownership.
- No navigation routing.
- No action-intent routing.
- No bindings or activation dispatch.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, generalized factories, or global mutable state.

## Design

Input diagnostics are passive immutable values that can later be produced by deterministic validation. Diagnostics optionally reference a UI input event ID and preserve stable order for deterministic reporting.

## Acceptance criteria

- Input diagnostic severity and code vocabularies exist.
- Input diagnostic records expose read-only severity, code, message, optional event ID, and stable order.
- Input diagnostic snapshots expose read-only diagnostics and passive count/empty/error helpers.
- No DDNet adapter, binding, routing, focus, capture, validation generation, or action-intent behavior is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add input diagnostics`
