# WP-160 — UI Render Runtime Projection

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots?

Answer: YES. WP-160 projects a full immutable Layout Runtime snapshot into one immutable Render Runtime snapshot.

## Architecture Freeze V2 drift check

WP-160 directly implements the approved Render Runtime pipeline boundary: immutable layout runtime data becomes immutable abstract render runtime data. It does not translate commands to DDNet or add new ownership/lifetime policy.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`

No implementation drift detected.

## Goal

Add the Render Runtime projection boundary over the existing layout-to-command projection.

## Scope

- Add a projection function from immutable `CLayoutRuntimeSnapshot` to immutable `CRenderRuntimeSnapshot`.
- Preserve layout runtime ordering by projecting each layout snapshot in order.
- Package projected command lists in `CRenderCommandListCollectionSnapshot`.
- Return an empty render diagnostic snapshot until render validation is introduced by a later bounded Work Package.

## Non-goals

- No render command validation generation.
- No layout diagnostic translation.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, `CUIRect`, or `CRenderTools` calls.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, persistence, or resource ownership behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

`ProjectUiRenderRuntimeSnapshot` is a passive composition helper. It consumes an immutable Layout Runtime snapshot, projects each contained layout snapshot through the single-layout render projection, and packages the resulting command lists into one immutable Render Runtime snapshot.

Render diagnostics remain empty in this slice because command validation and failure classification are intentionally separate responsibilities.

## Acceptance criteria

- A layout runtime snapshot can be projected into a render runtime snapshot.
- Layout ordering is preserved in command-list ordering.
- The projection does not inspect or mutate layout diagnostics.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): project render runtime snapshots`
