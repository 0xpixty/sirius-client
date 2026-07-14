# WP-122 — UI Render Command Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-122 directly implements the approved Declarative UI Runtime Render layer as passive abstract render command and immutable render command snapshot infrastructure. It consumes Scene/Layout identity and logical geometry values and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI Render Runtime command snapshot vocabulary.

WP-122 starts the Render Runtime layer after the Layout Runtime foundation by adding DDNet-independent abstract render command kinds, color/text policy values, render command records, and immutable render command snapshots.

## Scope

- Add stable render command ID value type.
- Add abstract render command kind vocabulary matching the approved initial command set.
- Add passive text alignment and text overflow policy vocabulary.
- Add logical color value type.
- Add immutable render command records keyed by scene element ID and logical layout bounds.
- Add immutable render command snapshots keyed by surface and scene ID.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No render command generation pass.
- No DDNet adapter translation.
- No graphics, text rendering, CUi, CUIRect, CRenderTools, texture, font, container, or cursor integration.
- No batching or caching.
- No image/font/resource lookup.
- No text measurement.
- No clip stack validation.
- No render diagnostics generation.
- No layout solving or measurement.
- No input, focus, capture, navigation, activation, hosting, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Render Runtime types live only under `sirius::ui::render`.
- Render command snapshots own immutable value records and expose them read-only.
- Render records may refer to `sirius::ui::scene` IDs and `sirius::ui::layout` logical bounds by value.
- Render snapshots are not renderers, generators, translators, adapter caches, services, managers, or lookup APIs.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- generates render commands from scenes or layouts;
- calls or includes DDNet rendering/UI/text/cursor APIs;
- measures text or content;
- resolves image, sprite, font, typography, theme, or localization resources;
- validates clip stacks or command support;
- performs batching or caching;
- integrates with Platform, Module Runtime, DDNet, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Render command IDs are stable string value types with read-only accessors and equality.
- Render command kind vocabulary represents push clip, pop clip, rectangle, gradient rectangle, outline, text, icon text, image/sprite reference, cursor request, and debug bounds.
- Text alignment and overflow policy vocabularies are passive values only.
- Color values are DDNet-independent immutable RGBA values.
- Render command records preserve command ID, optional element ID, kind, logical bounds, primary/secondary colors, stable text/resource payload, text alignment, overflow policy, required flag, and stable order index.
- Render command snapshots preserve surface ID, scene ID, deterministic command order, and read-only accessors.
- No generation pass, DDNet adapter translation, graphics/text/CUi/CUIRect/CRenderTools integration, batching/caching, resource lookup, text measurement, clip validation, diagnostics generation, Platform composition, Module Runtime change, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add render command snapshot baseline`
