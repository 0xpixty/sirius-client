# WP-152 — UI Single Scene Layout Projection

## Status

APPROVED

## Layout Runtime gate

Question: Does this directly move us toward a complete immutable Layout Runtime Snapshot?

Answer: YES. WP-152 consumes an immutable scene snapshot and produces an immutable layout snapshot through deterministic baseline measurement and arrangement.

## Architecture Freeze V2 drift check

WP-152 directly implements the approved Layout Runtime responsibility to receive immutable scene snapshots and produce immutable layout snapshots. It does not introduce rendering, input, themes, animation, editor behavior, or a new layout architecture.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Add a passive single-scene layout projection baseline.

## Scope

- Add `ProjectUiLayoutSnapshot()`.
- Consume an immutable `CSceneSnapshot`.
- Accept caller-provided root layout bounds.
- Preserve scene element order and stable element order indexes.
- Map scene element kinds to existing layout kind vocabulary.
- Deterministically arrange root/top-level elements to the root bounds.
- Deterministically arrange child elements to zero-size baseline bounds until richer constraints are introduced.
- Produce immutable `CLayoutSnapshot`.

## Non-goals

- No aggregate layout runtime projection.
- No active layout solver.
- No text measurement.
- No margin, padding, stack spacing, proportional split, or scroll extent calculation.
- No diagnostics generation.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The projection is intentionally small. It establishes the Layout Runtime's passive scene-to-layout boundary without pretending that full layout solving exists.

Root or top-level elements fill the caller-provided root bounds. Child elements receive deterministic zero-size baseline bounds. Their constraints are fixed to the measured size, which makes the initial measurement and arrangement deterministic while leaving richer constraint evaluation to later bounded Work Packages.

## Acceptance criteria

- A scene snapshot can be projected into a layout snapshot.
- Root/top-level bounds are deterministic and caller-provided.
- Child baseline bounds are deterministic.
- Element order is preserved.
- No DDNet adapter or rendering dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): project single scene layout`
