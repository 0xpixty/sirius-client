# WP-169 — UI Input Snapshot Baseline

## Status

APPROVED

## Input Runtime gate

Question: Does this directly move us toward a complete immutable Input Runtime Snapshot?

Answer: YES. WP-169 adds the source-neutral immutable UI input event and input snapshot vocabulary required before hit testing, focus, capture, navigation, or action-intent routing can be implemented.

## Architecture Freeze V2 drift check

WP-169 directly implements the approved Declarative UI Input Runtime value boundary. It does not expose DDNet `IInput` or `CUi` state, does not create a parallel binding system, and does not introduce routing or behavior.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add passive immutable source-neutral UI input snapshots.

## Scope

- Add stable UI input event IDs.
- Add input device kind vocabulary.
- Add input event kind vocabulary.
- Add input button state vocabulary.
- Add logical input position values.
- Add immutable UI input event snapshots.
- Add immutable UI input snapshot collections.

## Non-goals

- No DDNet adapter translation.
- No `IInput`, `CUi`, `CUIRect`, `IGraphics`, `ITextRender`, or `CRenderTools` dependency.
- No hit testing.
- No focus ownership.
- No capture ownership.
- No navigation routing.
- No action-intent routing.
- No bindings or activation dispatch.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The Input Runtime baseline is a passive value layer. Adapter and Platform input systems may later translate their existing source-neutral inputs into these UI input snapshots, but WP-169 does not add that translation or any routing behavior.

Input positions are logical UI coordinates, not DDNet `CUIRect` values or platform cursor objects.

## Acceptance criteria

- UI input event IDs are stable value objects.
- UI input event snapshots expose read-only device, kind, button state, logical position, stable payload, required flag, and stable order.
- UI input snapshots expose read-only ordered events and passive count/empty helpers.
- No DDNet adapter, binding, routing, focus, capture, or action-intent behavior is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add input snapshots`
