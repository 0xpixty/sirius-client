# WP-124 — UI Localization Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-124 directly implements the approved Declarative UI Runtime Localization layer as passive locale, localized text reference, formatting policy, plural metadata, and immutable localization snapshot infrastructure. It does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI Localization Runtime snapshot vocabulary.

WP-124 starts the Localization Runtime layer after the Theme Runtime foundation by adding stable locale and localized text identity values, formatting/plural policy vocabulary, immutable localized text records, fallback locale chains, and immutable localization snapshots.

## Scope

- Add stable locale ID and localized text key value types.
- Add localization snapshot version value type.
- Add passive formatting policy vocabulary.
- Add passive plural category vocabulary.
- Add immutable localized text snapshots with namespace/module identity, key, default text, resolved text, formatting policy, plural category, and stable order.
- Add immutable localization snapshots with active locale, version, text records, and fallback locale chain.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No translation lookup.
- No DDNet language lookup.
- No fallback resolution.
- No string formatting.
- No plural/select evaluation.
- No text measurement.
- No diagnostics generation.
- No invalidation propagation.
- No persistence, editor, hot reload, undo/redo, animation, theme, render, layout, or HUD behavior.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global current language, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Localization Runtime types live only under `sirius::ui::localization`.
- Localization snapshots own immutable value records and expose them read-only.
- Namespace/module identity is represented as stable strings until Module Runtime integration is introduced by a bounded Work Package.
- Localization snapshots are not translators, formatters, resolvers, services, managers, registries, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Scene, Layout, Render, Theme, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- resolves localized strings or fallback chains;
- formats strings or evaluates plural/select metadata;
- reads DDNet language state;
- measures text;
- mutates property/scene/layout/render snapshots;
- generates diagnostics or invalidations;
- integrates with Platform, Module Runtime, DDNet, Scene, Layout, Render, Theme, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, global current language, or global mutable state.

## Acceptance criteria

- Locale IDs and localized text keys are stable string value types with read-only accessors and equality.
- Localization version values are immutable after construction and expose read-only accessors.
- Formatting policy vocabulary represents none, number, date, time, date-time, and custom policies.
- Plural category vocabulary represents none, zero, one, two, few, many, and other categories.
- Localized text snapshots preserve namespace/module identity, key, default text, resolved text, formatting policy, plural category, and stable order index.
- Localization snapshots preserve active locale, version, deterministic text record order, fallback locale chain order, and read-only accessors.
- No translation lookup, DDNet language lookup, fallback resolution, formatting, plural/select evaluation, text measurement, diagnostics generation, invalidation propagation, Platform composition, Module Runtime change, DDNet adapter integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global current language, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add localization snapshot baseline`
