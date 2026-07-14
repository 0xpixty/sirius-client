# WP-173 — UI Input Routing Result

## Status

APPROVED

## Input Runtime gate

Question: Does this directly move us toward a complete immutable Input Runtime Snapshot?

Answer: YES. WP-173 adds the passive immutable input routing result value required by the approved input model before deterministic routing can be implemented.

## Architecture Freeze V2 drift check

WP-173 directly implements the approved Declarative UI Input Runtime routing-result value boundary. It does not perform hit testing, route events, mutate focus/capture, or change ownership, lifetime, layering, public API responsibility, runtime responsibility, or introduce an undocumented abstraction.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add passive immutable UI input routing result snapshots.

## Scope

- Add route disposition vocabulary.
- Add focus transition vocabulary.
- Add capture transition vocabulary.
- Add immutable routing result records for input event ID, handled/unhandled disposition, optional target surface, optional target element, optional action intent, focus/capture transition, diagnostics, and stable order.
- Add read-only handled/diagnostic/error helpers.

## Non-goals

- No DDNet adapter translation.
- No `IInput`, `CUi`, `CUIRect`, `IGraphics`, `ITextRender`, or `CRenderTools` dependency.
- No hit testing.
- No routing algorithm.
- No focus ownership mutation.
- No capture ownership mutation.
- No navigation routing.
- No action-intent resolution.
- No bindings or activation dispatch.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, generalized factories, or global mutable state.

## Design

Routing results are passive immutable values. They can describe a future routing decision without performing that decision. Action intent references remain UI action-intent IDs and do not dispatch activation or commands.

## Acceptance criteria

- Routing result disposition, focus transition, and capture transition vocabularies exist.
- Routing result snapshots expose read-only event, disposition, optional target surface/element, optional action intent, focus/capture transition, diagnostics, and stable order.
- Routing result snapshots expose passive handled/diagnostic/error helpers.
- No DDNet adapter, binding, routing algorithm, hit testing, focus mutation, capture mutation, or action-intent behavior is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add input routing results`
