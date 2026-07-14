# WP-155 — UI Layout Runtime Projection Diagnostics

## Status

APPROVED

## Layout Runtime gate

Question: Does this directly move us toward a complete immutable Layout Runtime Snapshot?

Answer: YES. WP-155 makes aggregate Layout Runtime projection include deterministic diagnostics for the immutable layout snapshots it produces.

## Architecture Freeze V2 drift check

WP-155 directly implements the approved Layout Runtime responsibilities to produce immutable layout runtime snapshots and expose deterministic diagnostics. It does not introduce rendering, input, theme behavior, animation, editor behavior, or a new layout architecture.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Attach deterministic layout snapshot diagnostics to aggregate Layout Runtime projection.

## Scope

- Add offset-aware layout snapshot validation.
- Preserve the existing zero-offset validation entry point.
- Run layout snapshot validation during aggregate layout runtime projection.
- Append produced layout diagnostics after any missing-scene diagnostics.
- Preserve deterministic diagnostic order.

## Non-goals

- No active layout solver expansion.
- No layout mutation or correction.
- No text measurement.
- No margin, padding, stack spacing, proportional split, or scroll extent calculation.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

Layout Runtime projection remains passive. It projects each surface scene into a layout snapshot, validates the produced snapshot, appends diagnostics with stable order offsets, and returns one immutable runtime snapshot.

## Acceptance criteria

- Aggregate Layout Runtime projection includes validation diagnostics.
- Existing single-snapshot validation remains available.
- Diagnostic stable order remains deterministic across missing-scene and validation diagnostics.
- No DDNet adapter or rendering dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): include layout projection diagnostics`
