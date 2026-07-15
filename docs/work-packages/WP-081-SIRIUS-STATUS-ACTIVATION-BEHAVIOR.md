# WP-081 - Sirius Status Activation Behavior

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

- Added `CSiriusStatusActivationBehavior : IFeatureActivationBehavior`.
- Behavior holds an explicit `CSiriusStatusFeature&` and calls `Open()`/`Close()`.
- Platform registers `activation.sirius.status`, `feature.sirius.status`, an activation record, and the behavior explicitly during status module composition.
- Registration failures are explicit.
- No input binding, command activation route, router, scanner, manager, service locator, UI, DDNet, or adapter change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: not added/executed because local GTest remains unavailable.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/work-packages/WP-070-FEATURE-ARCHITECTURE-PLANNING.md`
- `docs/work-packages/WP-080-SIRIUS-STATUS-MODULE-FEATURE.md`
- `src/sirius/platform/features/status/sirius_status_feature.h/.cpp`
- `src/sirius/platform/features/activation/feature_activation_behavior.h`
- `src/sirius/platform/platform.cpp`

## Goal

Add explicit activation behavior for the real Sirius Status feature.

The status feature already owns open/closed state. This WP adds a feature-specific activation behavior that holds `CSiriusStatusFeature&`, calls `Open()` on activation, and calls `Close()` on deactivation. Platform composition registers the activation mapping and behavior explicitly.

## Exact Scope

1. Add `CSiriusStatusActivationBehavior : IFeatureActivationBehavior`.
2. Register activation ID `activation.sirius.status` to feature ID `feature.sirius.status`.
3. Register a feature activation record for `feature.sirius.status`.
4. Register the status activation behavior using the composed `CSiriusStatusFeature&`.
5. Keep the status module-owned feature and commands from WP-080 unchanged.
6. Update Sirius source lists.

## Non-Goals

- No input binding for the status activation.
- No command activation routing for status commands.
- No command router, manager, service locator, scanner, generalized module registration, or module iteration.
- No UI/DDNet/adapter/config/networking changes.
- No change to technical activation proof behavior.
- No public `CPlatform` API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

WP-070 allows activation behavior to call into a feature when explicitly constructed with a feature reference by composition. This WP does exactly that:

```text
CActivationId("activation.sirius.status")
  -> feature.sirius.status
  -> CSiriusStatusActivationBehavior
  -> CSiriusStatusFeature::Open()/Close()
```

The behavior does not discover the feature. Platform wires it locally while composing the status module.

## Acceptance Criteria

1. Status activation behavior implements `IFeatureActivationBehavior`.
2. Behavior owns no feature state; it holds only an explicit non-owning `CSiriusStatusFeature&`.
3. `Activate()` calls `CSiriusStatusFeature::Open()`.
4. `Deactivate()` calls `CSiriusStatusFeature::Close()`.
5. Platform registers `activation.sirius.status`, `feature.sirius.status`, and the behavior explicitly.
6. No input binding or command activation route is added.
7. No manager/router/service locator/scanner/generalized registration is introduced.
8. Protected dirty files remain untouched and unstaged.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "activation\\.sirius\\.status|CSiriusStatusActivationBehavior|feature\\.sirius\\.status" src/sirius
rg -n "FeatureManager|CommandManager|ServiceLocator|router|scanner|scan" src/sirius/platform/features/status src/sirius/platform/platform.cpp
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are not added in this WP because local GTest remains unavailable; source inspection and required client builds are mandatory.

## Suggested Commit Message

`feat(features): activate sirius status feature`
