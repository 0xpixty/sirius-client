# WP-171 — UI Input Snapshot Validation

## Status

APPROVED

## Input Runtime gate

Question: Does this directly move us toward a complete immutable Input Runtime Snapshot?

Answer: YES. WP-171 adds deterministic validation for immutable UI input snapshots so the Input Runtime can produce stable diagnostics before any routing, focus, capture, or adapter translation is introduced.

## Architecture Freeze V2 drift check

WP-171 directly implements the approved Declarative UI Input Runtime validation boundary over immutable input snapshots and diagnostics. It does not change ownership, lifetime, layering, public API responsibility, runtime responsibility, or introduce an undocumented abstraction.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add deterministic validation for immutable UI input snapshots.

## Scope

- Validate empty input event IDs.
- Validate duplicate non-empty input event IDs in snapshot order.
- Validate supported input device kinds.
- Validate supported input event kinds.
- Validate supported input button states.
- Validate finite logical input positions.
- Return immutable input diagnostic snapshots with stable diagnostic ordering.

## Non-goals

- No DDNet adapter translation.
- No `IInput`, `CUi`, `CUIRect`, `IGraphics`, `ITextRender`, or `CRenderTools` dependency.
- No input routing result.
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

Validation is a passive read-only function over `CUiInputSnapshot`. It preserves snapshot event order, emits diagnostics in deterministic discovery order, and uses the caller-provided stable-order offset for future aggregate composition.

## Acceptance criteria

- Empty event IDs produce deterministic diagnostics.
- Duplicate non-empty event IDs produce deterministic diagnostics.
- Unsupported device/event/button-state values produce deterministic diagnostics.
- Non-finite logical positions produce deterministic diagnostics.
- Validation returns immutable input diagnostic snapshots.
- No DDNet adapter, binding, routing, focus, capture, or action-intent behavior is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): validate input snapshots`
