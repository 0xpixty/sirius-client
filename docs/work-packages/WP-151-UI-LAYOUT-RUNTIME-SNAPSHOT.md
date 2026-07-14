# WP-151 — UI Layout Runtime Snapshot

## Status

APPROVED

## Architecture Freeze V2 drift check

WP-151 directly implements the approved Layout Runtime snapshot model without introducing layout solving or DDNet integration.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add immutable Layout Runtime snapshot packaging for ordered per-surface layout snapshots and layout diagnostics.

## Scope

- Add immutable `CLayoutSnapshotList`.
- Add immutable `CLayoutRuntimeSnapshot`.
- Expose read-only layout and diagnostic accessors.
- Expose passive diagnostic/error helpers.

## Non-goals

- No layout solving.
- No layout validation generation.
- No scene or surface projection.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The runtime snapshot is passive. It packages existing immutable per-surface layout snapshots and diagnostics so future projection can publish a single Layout Runtime result without widening unrelated layers.

## Acceptance criteria

- Layout snapshot list exposes read-only ordered layout snapshots.
- Layout runtime snapshot exposes read-only layouts and diagnostics.
- No layout solving or DDNet adapter integration is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add layout runtime snapshot`
