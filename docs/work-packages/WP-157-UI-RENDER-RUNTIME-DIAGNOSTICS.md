# WP-157 — UI Render Runtime Diagnostics

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots?

Answer: YES. WP-157 adds passive Render Runtime diagnostics so future command generation and validation can report deterministic failures without DDNet adapter calls.

## Architecture Freeze V2 drift check

WP-157 directly implements the approved Render Runtime diagnostic channel. It does not introduce DDNet rendering, adapter translation, input behavior, themes, animation, editor behavior, or a new rendering architecture.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add passive immutable Render Runtime diagnostics.

## Scope

- Add render diagnostic severity vocabulary.
- Add initial diagnostic codes:
  - `Unknown`;
  - `MissingLayout`;
  - `EmptyCommandId`;
  - `UnsupportedCommandKind`;
  - `InvalidBounds`;
  - `InvalidColor`;
  - `InvalidClipStack`.
- Add immutable diagnostic records with optional surface, scene, element, and command context.
- Add immutable diagnostic snapshots with read-only diagnostics, count, emptiness, and error-presence helpers.

## Non-goals

- No render command generation.
- No render command validation generation.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, or `CRenderTools` calls.
- No texture, font, text-container, or quad-container ownership.
- No layout mutation.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The diagnostic snapshot mirrors other UI runtime diagnostic channels. It remains passive and immutable so future render command projection can publish command lists and explain command failures without owning DDNet resources.

## Acceptance criteria

- Render diagnostic records expose immutable severity, code, message, context IDs, command ID, and stable order.
- Render diagnostic snapshots expose read-only diagnostics, count, emptiness, and error presence.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add render runtime diagnostics`
