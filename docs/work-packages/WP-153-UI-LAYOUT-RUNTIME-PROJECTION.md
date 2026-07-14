# WP-153 — UI Layout Runtime Projection

## Status

APPROVED

## Layout Runtime gate

Question: Does this directly move us toward a complete immutable Layout Runtime Snapshot?

Answer: YES. WP-153 consumes composed immutable surface/scene snapshots and produces one immutable Layout Runtime snapshot.

## Architecture Freeze V2 drift check

WP-153 directly implements the approved Layout Runtime responsibility to receive immutable scene snapshots and publish immutable layout runtime snapshots. It does not introduce rendering, input, theme, animation, editor behavior, or new composition policy.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add aggregate Layout Runtime projection over the existing Aggregate Surface Runtime snapshot.

## Scope

- Add `ProjectUiLayoutRuntimeSnapshot()`.
- Consume immutable `CAggregateSurfaceRuntimeSnapshot`.
- Reuse single-scene layout projection for each surface with an attached scene snapshot.
- Preserve aggregate surface order in the produced layout snapshot list.
- Produce deterministic `MissingScene` layout diagnostics for surfaces without scene snapshots.
- Return immutable `CLayoutRuntimeSnapshot`.

## Non-goals

- No active layout solver expansion.
- No per-surface viewport policy.
- No partial surface recovery policy.
- No text measurement.
- No margin, padding, stack spacing, proportional split, or scroll extent calculation.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The projection is a passive bridge from the completed Aggregate Surface Runtime to the active Layout Runtime. It does not decide host placement or rendering policy. A caller provides the root bounds for this baseline; all surfaces use the same bounds until a later bounded Work Package introduces explicit per-surface viewport inputs.

## Acceptance criteria

- Aggregate surface runtime snapshots can be projected into layout runtime snapshots.
- Surfaces with scenes produce ordered layout snapshots.
- Surfaces without scenes produce deterministic `MissingScene` diagnostics.
- No DDNet adapter or rendering dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): project layout runtime snapshot`
