# WP-161 — UI Render Command Validation

## Status

APPROVED

## Render Runtime gate

Question: Does this directly move us toward immutable Render Runtime command snapshots with deterministic diagnostics?

Answer: YES. WP-161 adds passive validation for abstract render command-list snapshots and produces immutable render diagnostics.

## Architecture Freeze V2 drift check

WP-161 directly implements the approved Render Runtime failure model for unsupported command, invalid bounds, invalid color, and invalid clip-stack diagnostics. It does not translate commands to DDNet or add new ownership/lifetime policy.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`

No implementation drift detected.

## Goal

Add deterministic render command-list validation.

## Scope

- Validate render command IDs.
- Validate supported render command kinds.
- Validate finite render bounds with non-negative width and height.
- Validate color channels are finite and in `[0, 1]`.
- Validate clip stack balance for push/pop clip commands.
- Return immutable `CRenderDiagnosticSnapshot` values.
- Support a stable-order offset overload for aggregate runtime validation.

## Non-goals

- No render runtime projection integration.
- No DDNet adapter translation.
- No `IGraphics`, `ITextRender`, `CUi`, `CUIRect`, or `CRenderTools` calls.
- No texture, font, text-container, quad-container, batching, or adapter cache behavior.
- No theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, persistence, or resource ownership behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

Validation is passive and read-only. It inspects immutable command-list snapshots and produces immutable diagnostics without mutating commands or owning rendering resources.

Clip validation is intentionally minimal: `PushClip` increments a local depth, `PopClip` decrements it, popping depth zero is invalid, and non-zero depth at the end is invalid.

## Acceptance criteria

- Empty render command IDs produce deterministic diagnostics.
- Unsupported command kinds produce deterministic diagnostics.
- Non-finite coordinates, non-finite size, or negative size produce deterministic diagnostics.
- Non-finite or out-of-range colors produce deterministic diagnostics.
- Unbalanced clip stacks produce deterministic diagnostics.
- No DDNet adapter or graphics dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): validate render command snapshots`
