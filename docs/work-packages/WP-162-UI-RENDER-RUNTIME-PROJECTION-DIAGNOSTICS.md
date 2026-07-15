# WP-162 — UI Render Runtime Projection Diagnostics

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots with deterministic diagnostics?

Answer: YES. WP-162 wires render command-list validation into Render Runtime projection so the immutable runtime snapshot carries deterministic diagnostics.

## Architecture Freeze V2 drift check

WP-162 directly implements the approved Render Runtime failure model without changing Render Runtime ownership, lifetime, layering, or public responsibilities.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`

No implementation drift detected.

## Goal

Attach deterministic render validation diagnostics to Render Runtime projection output.

## Scope

- Validate each projected command-list snapshot during Render Runtime projection.
- Preserve projected command-list ordering.
- Accumulate command-list diagnostics in deterministic projection order.
- Store accumulated diagnostics in the returned immutable `CRenderRuntimeSnapshot`.

## Non-goals

- No layout diagnostic translation.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, `CUIRect`, or `CRenderTools` calls.
- No texture, font, text-container, quad-container, batching, or adapter cache behavior.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, persistence, or resource ownership behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

`ProjectUiRenderRuntimeSnapshot` remains a passive read-only projection helper. Each layout snapshot is projected into a command-list snapshot, the command list is validated, and diagnostics are appended before the command list is stored.

The stable-order offset uses the number of diagnostics already accumulated, matching the deterministic offset pattern used by earlier runtime projection diagnostics.

## Acceptance criteria

- Render Runtime projection validates each projected command list.
- Render Runtime snapshots contain accumulated render diagnostics.
- Command-list ordering remains unchanged.
- Diagnostics are deterministic in projection order.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): include render projection diagnostics`
