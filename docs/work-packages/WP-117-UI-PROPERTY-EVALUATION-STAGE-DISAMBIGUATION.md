# WP-117 — UI Property Evaluation Stage Disambiguation

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-117 corrects a concrete lower-layer implementation defect discovered while preparing the aggregate property snapshot layer: `property_metadata_snapshot.h` and `property_evaluation.h` both declared `EPropertyEvaluationStage` in `sirius::ui::property`. That prevented the approved lower Property Runtime headers from being composed together.

This is not an architecture change. It preserves the approved Property Runtime evaluation responsibilities and renames only the passive WP-116 evaluation-order vocabulary so it no longer collides with metadata-owned evaluation-stage metadata.

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

Make the existing metadata and evaluation headers safely composable before introducing aggregate property snapshots.

## Scope

- Rename WP-116 `EPropertyEvaluationStage` to `EPropertyEvaluationOrderStage`.
- Update passive evaluation order and result records to use the disambiguated vocabulary.
- Preserve all existing passive evaluation semantics.

## Non-goals

- No new property runtime behavior.
- No expression execution.
- No dependency graph construction, traversal, sorting, validation, or evaluation.
- No source lookup, binding resolution, theme resolution, localization resolution, animation resolution, or profile lookup.
- No property mutation, storage mutation, operation application, generation mutation, invalidation propagation, or diagnostic generation.
- No aggregate property snapshot yet.
- No scene, layout, render, theme, localization, editor, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Acceptance criteria

- `property_metadata_snapshot.h` and `property_evaluation.h` can be included together.
- Evaluation order records continue to carry passive evaluation order stage plus stable order index.
- Evaluation records continue to carry property ID, passive evaluation order stage, status, optional effective stored value, and generation stamp.
- No behavior, mutation, lookup, evaluation engine, dependency traversal, diagnostics generation, Platform/Module/DDNet integration, manager, scanner, service locator, router, callback/event behavior, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Focused include-composition compile through Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`fix(ui): disambiguate property evaluation stages`
