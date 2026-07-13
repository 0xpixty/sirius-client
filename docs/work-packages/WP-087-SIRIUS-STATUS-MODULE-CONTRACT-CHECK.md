# WP-087 - Sirius Status Module Contract Check

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after silent consultant attempts.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Added `IsSiriusStatusModuleComplete()` in Status-local module composition code.
- The predicate verifies the concrete Status module ID, Status feature ID, and open/close/toggle command IDs.
- `CPlatform::Start()` now calls the Status-local predicate instead of spelling out Status command completeness directly.
- Platform still performs explicit module lookup, lifecycle startup, activation wiring, dispatch, and input binding.
- No behavior, UI, DDNet, adapter, config, networking, gameplay, command, activation, input, dispatcher, handler, router, scanner, manager, service locator, generalized registry, EventBus, or MessageBus change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-084-WP-086.md`
- `docs/work-packages/WP-086-SIRIUS-STATUS-SNAPSHOT.md`
- `src/sirius/platform/platform.*`
- `src/sirius/platform/modules/status/sirius_status_module.*`

## Goal

Reduce remaining Status-specific module contract knowledge in `CPlatform::Start()` without changing behavior or introducing generalized routing/composition machinery.

`CPlatform` should still be the explicit composition and wiring root, but Status-local code should own the concrete question, "does this module contain the Status feature and Status commands required by the current Status slice?"

## Exact Scope

1. Add a Status-local module contract predicate under `src/sirius/platform/modules/status/sirius_status_module.*`.
2. The predicate must verify the concrete `module.sirius.status` contract:
   - module ID;
   - Status feature ID;
   - open command ID;
   - close command ID;
   - toggle command ID.
3. Update `CPlatform::Start()` to call the Status-local predicate instead of spelling out Status command checks directly.
4. Preserve existing lifecycle, activation, command dispatch, input binding, and snapshot behavior.
5. Update this WP status/evidence after validation.

## Non-Goals

- No UI, DDNet, adapter, config, networking, gameplay, rendering, or console integration.
- No new feature state.
- No new command.
- No new activation ID or input binding.
- No command router.
- No module scanner.
- No manager, service locator, global registry, generalized factory registry, EventBus, or MessageBus.
- No new public `CPlatform` API.
- No changes to technical activation proof behavior.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The Status module already owns construction of the Status feature and Status commands. Platform still owns composition and lifecycle startup, but it should not need a growing checklist of Status-owned internals for startup readiness.

This WP keeps the boundary concrete and local:

```text
CPlatform::Start()
  -> gets module.sirius.status explicitly
  -> asks Status-local predicate whether the concrete Status contract is present
```

There is no module iteration, no cross-module lookup, no generalized routing, and no product-facing behavior change.

## Acceptance Criteria

1. A Status-local predicate verifies the current Status module contract.
2. `CPlatform::Start()` no longer directly lists Status open/close/toggle command checks.
3. Platform remains responsible for explicit module lookup, startup, lifecycle, activation, dispatchers, and binding wiring.
4. Status feature, commands, activation behavior, snapshot, and input behavior remain unchanged.
5. No router/scanner/manager/service locator/global registry is introduced.
6. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "IsSiriusStatusModuleComplete|SiriusStatusOpenCommandId|SiriusStatusCloseCommandId|SiriusStatusToggleCommandId" src/sirius/platform/modules/status src/sirius/platform/platform.cpp
rg -n "router|scanner|scan|CommandManager|ServiceLocator|global command|factory registry|EventBus|MessageBus" src/sirius/platform/modules/status src/sirius/platform/platform.cpp
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`refactor(platform): localize status module contract check`
