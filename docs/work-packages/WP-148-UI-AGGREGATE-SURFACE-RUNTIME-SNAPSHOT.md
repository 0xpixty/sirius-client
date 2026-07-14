# WP-148 — UI Aggregate Surface Runtime Snapshot

## Status

APPROVED

## Architecture Freeze V2 drift check

WP-148 directly implements the approved Declarative UI Runtime snapshot model for Aggregate Surface Runtime packaging.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add an immutable Aggregate Surface Runtime snapshot that packages ordered surface snapshots with declaration diagnostics and aggregate surface-runtime diagnostics.

## Scope

- Add `CAggregateSurfaceRuntimeSnapshot`.
- Store immutable `CSurfaceSnapshotList`.
- Store immutable declaration diagnostics.
- Store immutable surface-runtime diagnostics.
- Expose read-only accessors and passive diagnostic/error helpers.

## Non-goals

- No aggregate surface projection.
- No scene ID derivation.
- No composition status assignment.
- No host-slot validation.
- No conflict detection or resolution.
- No priority, last-wins, or implicit ordering policy.
- No host-slot inference.
- No Platform composition.
- No DDNet adapter integration.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

`CAggregateSurfaceRuntimeSnapshot` is a passive immutable value object. It does not construct surfaces, validate declarations, or decide aggregate composition status. It exists so the next bounded Work Package can project declarations into a complete aggregate runtime snapshot without widening public APIs.

## Acceptance criteria

- Aggregate snapshot exposes read-only surface, declaration diagnostic, and surface diagnostic snapshots.
- Error helpers remain passive and do not mutate or resolve runtime state.
- No projection or composition policy is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add aggregate surface runtime snapshot`
