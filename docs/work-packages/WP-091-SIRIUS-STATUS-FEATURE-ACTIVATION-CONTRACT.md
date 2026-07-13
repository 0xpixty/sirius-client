# WP-091 - Sirius Status Feature Activation Contract

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Reviewer consultant: `REVIEWER_UNAVAILABLE` after one silent instance and one silent retry.
- Devil's Advocate consultant: `DEVIL_UNAVAILABLE` after one silent instance and one silent retry.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- Latest architecture audit: `AUDITOR_FALLBACK_APPROVED` in `docs/architecture/AUDIT-WP-087-WP-089.md`.

Implementation evidence:

- Added `modules::status::CSiriusStatusFeatureActivation`.
- Added `modules::status::SiriusStatusFeatureActivation()`.
- The Status-local mapping remains `activation.sirius.status` -> `feature.sirius.status`.
- `CPlatform::ConfigureStatusModule()` now consumes the Status-local feature activation contract when registering the resolver mapping and inactive feature activation record.
- Existing failure semantics are preserved for failed resolver and activation-record registration.
- No manager, router, scanner, observer, event system, service locator, generalized registry, new activation behavior, input binding, UI, console, rendering, gameplay, network, or protocol change was introduced.
- Remaining direct Status ID references in Platform are outside this WP's feature activation mapping scope: input binding IDs and read-only snapshot lookup.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed.
- RelWithDebInfo `game-client`: passed.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-087-WP-089.md`
- `docs/work-packages/WP-089-SIRIUS-STATUS-COMMAND-ACTIVATION-CONTRACT.md`
- `docs/work-packages/WP-090-MODULE-REGISTRY-REMOVAL-SEAM.md`
- `src/sirius/platform/modules/status/sirius_status_module.*`
- `src/sirius/platform/platform.*`

## Goal

Move the Sirius Status feature activation mapping contract into the Status module contract and have Platform consume that explicit Status-owned mapping.

This continues the same ownership cleanup as WP-087 and WP-089 without changing runtime behavior or introducing generalized registration machinery.

## Exact Scope

1. Add a small immutable value type under `sirius::platform::modules::status` that pairs:
   - `activation::CActivationId`
   - `features::CFeatureId`
2. Add a Status-local function returning the current Sirius Status feature activation mapping:
   - `activation.sirius.status` -> `feature.sirius.status`
3. Update `CPlatform::ConfigureStatusModule()` to consume the Status-local feature activation contract when registering:
   - `m_FeatureActivationResolver`
   - `m_FeatureActivations`
4. Preserve existing explicit registration path and failure semantics.
5. Update this WP status/evidence after validation.

## Non-Goals

- No UI.
- No console commands.
- No rendering.
- No config changes.
- No gameplay behavior.
- No network/protocol changes.
- No global services.
- No managers.
- No routers.
- No observers.
- No event systems.
- No generalized command, feature, activation, or module scanning.
- No service locator or generalized contract registry.
- No new activation behavior.
- No new input bindings.
- No changes to command activation mapping behavior.
- No changes to `CModuleRegistry::Remove()`.

## Architecture Rationale

The Status module owns the Status feature ID and Status activation ID. Platform remains the explicit composition root, but it should consume the Status-owned feature activation contract rather than assembling the Status activation-to-feature pair inline.

This keeps the relationship local and explicit:

```text
CPlatform::ConfigureStatusModule()
  -> modules::status::SiriusStatusFeatureActivation()
  -> m_FeatureActivationResolver.Register(...)
  -> m_FeatureActivations.Register(...)
```

This is not discovery, routing, scanning, or service location. It is a single fixed Status-local contract consumed by explicit Platform wiring.

## Acceptance Criteria

1. Status feature activation contract definition lives in `src/sirius/platform/modules/status/sirius_status_module.*`.
2. Platform no longer creates separate local `SiriusStatusActivationId()` and `SiriusStatusFeatureId()` variables for the feature activation mapping.
3. Platform still explicitly registers the Status activation resolver mapping and inactive feature activation record.
4. The mapping remains exactly `activation.sirius.status` -> `feature.sirius.status`.
5. Existing failure semantics are preserved when registration fails.
6. No manager/router/scanner/observer/event system/service locator/generalized registry is introduced.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "SiriusStatusFeatureActivation|CSiriusStatusFeatureActivation|SiriusStatusActivationId|SiriusStatusFeatureId" src/sirius/platform
rg -n "router|scanner|scan|CommandManager|ServiceLocator|observer|event system|EventBus|MessageBus|global service|query registry|contract registry" src/sirius/platform
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`refactor(platform): localize status feature activation contract`
