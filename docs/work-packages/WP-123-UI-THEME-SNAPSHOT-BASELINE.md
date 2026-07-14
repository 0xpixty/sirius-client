# WP-123 — UI Theme Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-123 directly implements the approved Declarative UI Runtime Theme layer as passive theme identity, token, state, accessibility, and immutable theme snapshot infrastructure. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

Architecture references:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERSISTENCE.md`
- `docs/architecture/SIRIUS-UI-EDITOR.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

## Goal

Introduce the first passive UI Theme Runtime snapshot vocabulary.

WP-123 starts the Theme Runtime layer after the Render Runtime foundation by adding stable theme/token identity values, approved token categories, state dimensions, accessibility modifiers, immutable token snapshots, and immutable theme snapshots.

## Scope

- Add stable theme ID and theme token ID value types.
- Add theme version value type.
- Add passive theme token category vocabulary.
- Add passive theme state dimension vocabulary.
- Add passive theme accessibility modifier vocabulary.
- Add immutable theme token snapshots with stable payloads.
- Add immutable theme snapshots with token records, fallback chain, and accessibility modifiers.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No theme resolution engine.
- No token alias resolution.
- No style application to properties, scenes, layouts, or render commands.
- No diagnostics generation.
- No theme switching behavior.
- No animation behavior.
- No persistence, editor, hot reload, undo/redo, marketplace, external CSS, or scriptable styling.
- No DDNet renderer state, font loading, text measurement, graphics, CUi, CUIRect, or adapter integration.
- No Platform composition changes.
- No Module Runtime changes.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global current theme, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Theme Runtime types live only under `sirius::ui::theme`.
- Theme snapshots own immutable value records and expose them read-only.
- Theme token payloads are stable strings paired with explicit categories; typed resolution belongs to later bounded work.
- Theme snapshots are not resolvers, style engines, global registries, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- resolves token aliases or state variants;
- mutates or applies theme-derived property values;
- generates diagnostics;
- switches active themes;
- loads fonts/resources or measures text;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Localization, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, global current theme, or global mutable state.

## Acceptance criteria

- Theme IDs and token IDs are stable string value types with read-only accessors and equality.
- Theme version values are immutable after construction and expose read-only accessors.
- Token category vocabulary represents color, spacing, radius, border, typography, opacity, elevation/glow, animation duration/easing, icon reference, and state overlay.
- State dimension vocabulary represents normal, hovered, focused, pressed, captured, disabled, selected, error, warning, and success.
- Accessibility modifier vocabulary represents reduced motion, high contrast, minimum text size, focus indicator, and color-blind-safe semantic tokens.
- Theme token snapshots preserve token ID, category, state dimension, stable payload, required flag, and stable order index.
- Theme snapshots preserve theme ID, version, token record order, fallback chain order, accessibility modifier order, and read-only accessors.
- No resolver, style application, diagnostics generation, theme switching, animation, persistence/editor/hot reload, DDNet integration, Platform composition, Module Runtime change, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global current theme, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add theme snapshot baseline`
