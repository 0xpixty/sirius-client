# WP-150 — UI Layout Runtime Diagnostics

## Status

APPROVED

## Architecture Freeze V2 drift check

WP-150 directly implements the approved Layout Runtime diagnostic foundation before adding layout projection or solving.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add passive Layout Runtime diagnostics for future layout validation and projection.

## Scope

- Add layout diagnostic severity vocabulary.
- Add initial diagnostic codes:
  - `Unknown`;
  - `MissingScene`;
  - `UnsupportedLayoutKind`;
  - `InvalidBounds`;
  - `InvalidSizeConstraints`.
- Add immutable diagnostic records with optional surface, scene, and element context.
- Add immutable diagnostic snapshots with count, emptiness, and error-presence helpers.

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

The diagnostic snapshot mirrors other UI runtime diagnostic channels. It remains passive and immutable so future layout projection can report invalid scene/layout state without owning recovery or rendering policy.

## Acceptance criteria

- Layout diagnostic records expose immutable severity, code, message, context IDs, and stable order.
- Layout diagnostic snapshots expose read-only diagnostics, count, emptiness, and error presence.
- No layout solving or DDNet adapter integration is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add layout runtime diagnostics`
