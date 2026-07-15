# WP-156 — UI Deterministic Stack Layout Arrangement

## Status

APPROVED

## Layout Runtime gate

Question: Does this directly move us toward a complete immutable Layout Runtime Snapshot?

Answer: YES. WP-156 improves deterministic measurement and arrangement for immutable scene snapshots by deriving child layout bounds from scene parent relationships.

## Architecture Freeze V2 drift check

WP-156 refines the existing Layout Runtime projection without changing ownership, layering, public runtime responsibilities, or introducing rendering/input/theme/editor behavior.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

No implementation drift detected.

## Goal

Replace the zero-size child layout baseline with deterministic stack-style arrangement.

## Scope

- Derive child layout bounds from immutable scene parent IDs.
- Preserve scene element order as the deterministic sibling order.
- Arrange siblings as equal vertical slices of their parent bounds.
- Keep root/top-level elements filling caller-provided root bounds.
- Keep constraints fixed to measured bounds for this baseline.

## Non-goals

- No text measurement.
- No margin or padding.
- No configurable stack direction or spacing.
- No proportional split policy beyond equal deterministic slices.
- No scroll content extent calculation.
- No layout mutation or correction.
- No DDNet `CUIRect` integration.
- No rendering, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, animation, or persistence behavior.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The projection remains passive. Bounds are calculated from immutable scene data and caller-provided root bounds. Root and top-level elements fill the root bounds. Child elements are measured and arranged as equal vertical slices of their parent bounds using scene order as the deterministic sibling order.

This is intentionally the smallest useful arrangement behavior. It gives Layout Runtime a deterministic non-zero child arrangement without introducing style, text measurement, or a general solver.

## Acceptance criteria

- Child elements receive deterministic parent-derived bounds.
- Sibling order follows immutable scene order.
- Constraints remain fixed to measured bounds.
- No DDNet adapter or rendering dependency is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): arrange layout children deterministically`
