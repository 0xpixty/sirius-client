# WP-076 - Remove Unused Platform Deactivation API

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Removed public `CPlatform::DeactivateActivation()` declaration and implementation.
- No `DeactivateActivation` references remain in `src/`.
- Private lifecycle-gated `Activate()` and `Deactivate()` remain in place for binding activation adapter use.
- Binding activation, feature activation, and command activation files were not changed.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: not applicable; this WP removes an unused public wrapper and does not change runtime activation behavior.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/architecture/AUDIT-WP-069-WP-072.md`
- `docs/work-packages/WP-073-FEATURE-ACTIVATION-SHUTDOWN-RESTART-CONSISTENCY.md`
- `docs/work-packages/WP-074-BINDING-ACTIVATION-RESOLVER-CLEANUP.md`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`

## Goal

Remove the unused public `CPlatform::DeactivateActivation()` method.

WP-073 made activation and deactivation fan-out lifecycle-gated through the private `activation::IActivationHandler` implementation. The remaining public `DeactivateActivation()` method is not used anywhere in the repository and exposes manual activation-state mutation without a concrete current consumer.

## Exact Scope

1. Remove the public `CPlatform::DeactivateActivation(const activation::CActivationId &)` declaration.
2. Remove its implementation from `platform.cpp`.
3. Preserve private `CPlatform::Activate()` and `CPlatform::Deactivate()` because they are required by the binding activation adapter through `activation::IActivationHandler`.
4. Verify no repository call sites remain.

## Non-Goals

- No changes to private activation/deactivation fan-out behavior.
- No changes to lifecycle gating, shutdown reconciliation, feature activation controller semantics, or command activation behavior.
- No changes to binding adapter, dispatcher, registry, matcher, or input source behavior.
- No changes to public `Modules()` in this WP.
- No DDNet integration, product feature, module scanning, router, manager, service, event bus, or generalized activation API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

`CPlatform` should remain the composition root, not a broad product-control surface. Since there is no current consumer for manual public deactivation, keeping `DeactivateActivation()` increases public API area without demonstrated pressure. The binding path already reaches the private lifecycle-gated handler through explicit composition.

Removing the unused method reduces Platform policy surface while preserving the existing source-neutral activation boundary.

## Acceptance Criteria

1. `CPlatform::DeactivateActivation()` is removed from the public header.
2. Its implementation is removed.
3. Private `Activate()` and `Deactivate()` remain unchanged except for surrounding whitespace if mechanically necessary.
4. No call sites or declarations of `DeactivateActivation` remain.
5. Activation binding, feature activation, and command activation files are unchanged.
6. Protected dirty `module_registry.*` files remain untouched and unstaged.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "DeactivateActivation" src docs .codex/docs
git diff --check
git diff -- src/sirius/platform/platform.h src/sirius/platform/platform.cpp
git diff -- src/sirius/platform/input src/sirius/platform/features src/sirius/platform/commands
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are not newly required because this Work Package removes an unused public wrapper and does not change runtime activation behavior.

## Suggested Commit Message

`refactor(platform): remove unused deactivation api`
