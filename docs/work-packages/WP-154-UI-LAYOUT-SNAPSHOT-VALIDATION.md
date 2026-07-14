# WP-154 — UI Layout Snapshot Validation

## Status

APPROVED

## Layout Runtime gate

Question: Does this directly move us toward a complete immutable Layout Runtime Snapshot?

Answer: YES. WP-154 exposes deterministic diagnostics for immutable layout snapshots, one of the Layout Runtime exit criteria.

## Architecture Freeze V2 drift check

WP-154 directly implements the approved Layout Runtime diagnostic responsibility. It validates already-produced immutable layout snapshots without introducing a solver, renderer, input model, theme behavior, animation, or editor behavior.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add deterministic validation for immutable layout snapshots.

## Scope

- Add `ValidateUiLayoutSnapshot()`.
- Validate layout kind support.
- Validate finite non-negative layout bounds width/height.
- Validate finite non-negative size constraints.
- Validate ordered constraints: minimum <= preferred <= maximum on both axes.
- Produce immutable layout diagnostics with surface, scene, and element context.
- Preserve layout element order when producing diagnostics.

## Non-goals

- No active layout solver.
- No layout mutation or correction.
- No aggregate layout validation.
- No text measurement.
- No margin, padding, stack spacing, proportional split, or scroll extent calculation.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

Validation is passive. It inspects immutable layout snapshots and emits immutable diagnostics. It does not rewrite invalid values, choose fallbacks, or decide whether a surface remains active.

## Acceptance criteria

- Layout snapshots can be validated deterministically.
- Invalid bounds produce `InvalidBounds` diagnostics.
- Invalid constraints produce `InvalidSizeConstraints` diagnostics.
- Diagnostics preserve layout element order.
- No DDNet adapter or rendering dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): validate layout snapshots`
