# WP-159 — UI Render Layout Projection

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots?

Answer: YES. WP-159 projects immutable layout snapshots into immutable abstract render command-list snapshots.

## Architecture Freeze V2 drift check

WP-159 directly implements the approved Render Runtime boundary: Sirius UI Runtime emits abstract render commands from immutable runtime snapshots, while DDNet adapter translation remains separate.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add the first deterministic layout-to-render command-list projection.

## Scope

- Add a projection function from one immutable `CLayoutSnapshot` to one immutable `CRenderCommandListSnapshot`.
- Preserve surface ID and scene ID in the output command list.
- Emit one deterministic abstract `DebugBounds` render command for each layout element.
- Derive command IDs only from stable surface, scene, and element identities.
- Preserve layout element stable order on emitted commands.

## Non-goals

- No render runtime aggregation.
- No render command validation generation.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, `CUIRect`, or `CRenderTools` calls.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, persistence, or resource ownership behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The projection is intentionally style-free. Until theme/property visual evaluation is introduced by an approved later Work Package, each layout element becomes a passive `DebugBounds` command with transparent colors. This establishes the deterministic Render Runtime command path without inventing styling ownership.

Command IDs use:

`ui.render.debug-bounds/<surface-id>/<scene-id>/<element-id>`

The projection does not sort, infer priority, inspect DDNet state, or mutate layout snapshots.

## Acceptance criteria

- A layout snapshot can be projected into a render command-list snapshot.
- Output command lists preserve surface and scene IDs.
- Each layout element produces exactly one deterministic debug-bounds command.
- Command IDs are derived only from stable surface, scene, and element identities.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): project layout render commands`
