# WP-158 — UI Render Runtime Snapshot

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots?

Answer: YES. WP-158 packages immutable render command-list snapshots and diagnostics into one immutable Render Runtime snapshot.

## Architecture Freeze V2 drift check

WP-158 directly implements the approved Render Runtime snapshot model without command generation or DDNet adapter translation.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add immutable Render Runtime snapshot packaging.

## Scope

- Add immutable collection snapshot for ordered render command-list snapshots.
- Add immutable Render Runtime snapshot.
- Expose read-only command-list and diagnostic accessors.
- Expose passive diagnostic/error helpers.

## Non-goals

- No render command generation.
- No render command validation generation.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, or `CRenderTools` calls.
- No texture, font, text-container, or quad-container ownership.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The Render Runtime snapshot is passive. It packages existing immutable command-list snapshots and render diagnostics so later command projection can publish one read-only runtime result without coupling to DDNet.

## Acceptance criteria

- Render command-list collections expose read-only ordered command lists.
- Render runtime snapshots expose read-only command lists and diagnostics.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add render runtime snapshot`
