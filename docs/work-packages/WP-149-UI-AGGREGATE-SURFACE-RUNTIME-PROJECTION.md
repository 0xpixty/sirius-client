# WP-149 — UI Aggregate Surface Runtime Projection

## Status

APPROVED

## Architecture Freeze V2 drift check

WP-149 directly implements the approved Aggregate Surface Runtime policies for deterministic Scene IDs, explicit host-slot validation, deterministic conflict diagnostics, and the minimal `Pending -> Composed -> Failed` lifecycle.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Project immutable UI declaration snapshots into a complete immutable Aggregate Surface Runtime snapshot.

## Scope

- Add aggregate projection from `CUiDeclarationSnapshot`.
- Run declaration validation.
- Run aggregate surface host-slot validation.
- Derive each surface scene ID from stable surface declaration identity.
- Preserve declaration order while projecting surface snapshots.
- Assign the minimal final composition status:
  - `Composed` when declaration and surface-runtime diagnostics are clean.
  - `Failed` when declaration diagnostics or surface-runtime errors exist.
- Return immutable `CAggregateSurfaceRuntimeSnapshot`.

## Non-goals

- No partial recovery policy.
- No optional-surface omission.
- No conflict resolution.
- No priority, last-wins, or implicit ordering policy.
- No host-slot inference.
- No Platform composition.
- No DDNet adapter integration.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

`ProjectAggregateUiSurfaceRuntimeSnapshot()` consumes the immutable aggregate declaration snapshot and produces an immutable aggregate surface runtime snapshot.

The projection treats aggregate composition as a single minimal lifecycle decision. It does not attempt to keep non-conflicting surfaces active after an aggregate failure because no partial-recovery or optional-omission policy has been approved for this layer. This preserves deterministic failure behavior and avoids hidden priorities.

## Acceptance criteria

- Scene IDs are derived only from stable surface declaration identity.
- Declaration and aggregate surface diagnostics are included in the result.
- Surface snapshots preserve declaration order.
- Clean aggregate composition yields `Composed` surface snapshots.
- Failed aggregate composition yields `Failed` surface snapshots with diagnostics.
- No conflict resolution, host-slot inference, or priority policy is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): project aggregate surface runtime`
