# WP-086 - Sirius Status Snapshot

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
- User decision: not required.

Implementation evidence:

- Added `CSiriusStatusSnapshot`.
- Added `CSiriusStatusFeature::Snapshot() const noexcept`.
- Snapshot carries initialized/open/open-count/close-count state by value.
- Existing Status open/close/toggle behavior and individual getters remain unchanged.
- No UI, DDNet, adapter, config, networking, gameplay, command, activation, input, dispatcher, handler, router, scanner, manager, service locator, generalized registry, or event-bus change was added.
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
- `docs/architecture/AUDIT-WP-082-WP-083.md`
- `docs/work-packages/WP-085-SIRIUS-STATUS-TOGGLE-COMMAND.md`
- `src/sirius/platform/features/status/sirius_status_feature.*`

## Goal

Add a small immutable read model for the Sirius Status feature.

The Status feature now owns open, close, and toggle behavior. Before any future consumer is introduced, the feature should expose its state through a feature-owned value snapshot instead of requiring consumers to know individual counters and flags.

## Exact Scope

1. Add `CSiriusStatusSnapshot` under `src/sirius/platform/features/status/`.
2. The snapshot must be a small value type exposing:
   - initialized state;
   - open state;
   - open count;
   - close count.
3. Add `CSiriusStatusFeature::Snapshot() const noexcept`.
4. `Snapshot()` must not mutate feature state.
5. Update `src/sirius/CMakeLists.txt`.
6. Update this WP status/evidence after validation.

## Non-Goals

- No UI, DDNet, adapter, config, networking, gameplay, or rendering integration.
- No new command.
- No new activation or input binding.
- No new dispatcher, handler, router, scanner, manager, service locator, generalized registry, or event bus.
- No public `CPlatform` API.
- No changes to existing Status open/close/toggle behavior.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The read model belongs to the feature because the feature owns the state. Consumers should not need to reconstruct Status state from independent getters or counters when a stable feature-owned value can express the current state.

This remains inside the Status feature slice:

```text
CSiriusStatusFeature
  -> owns mutable state
  -> returns CSiriusStatusSnapshot value
```

No routing, external integration, lifecycle changes, or cross-module lookup are introduced.

## Acceptance Criteria

1. `CSiriusStatusSnapshot` is a value type local to Status feature code.
2. Snapshot exposes initialized, open, open count, and close count.
3. `CSiriusStatusFeature::Snapshot()` returns current feature state without mutation.
4. Existing individual getters continue to work unchanged.
5. Open/close/toggle behavior remains unchanged.
6. No router/scanner/manager/service locator/global registry is introduced.
7. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CSiriusStatusSnapshot|Snapshot\\(" src/sirius/platform/features/status
rg -n "router|scanner|scan|CommandManager|ServiceLocator|global command|event bus" src/sirius/platform/features/status
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`feat(features): add sirius status snapshot`
