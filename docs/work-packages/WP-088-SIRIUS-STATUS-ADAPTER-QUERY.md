# WP-088 - Sirius Status Adapter Query

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- User architecture decision: Adapter/query surface.
- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Reviewer consultant: `CHANGES_REQUIRED` for WP numbering only; architecture of adapter query was accepted as bounded.
- Devil's Advocate consultant: `NO_BLOCKING_OBJECTION`.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer implementation check: `APPROVED`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: satisfied by explicit current request.

Implementation evidence:

- Added `CPlatform::SiriusStatusSnapshot() const noexcept`.
- Added `CPlatformBootstrap::SiriusStatusSnapshot() const noexcept`.
- Added `CDdnetPlatformHost::SiriusStatusSnapshot() const noexcept`.
- The query returns `std::optional<features::CSiriusStatusSnapshot>`.
- Missing bootstrap/platform/module/feature state returns an empty optional.
- The query reads `CSiriusStatusFeature::Snapshot()` and does not mutate Status feature state.
- No UI, console, rendering, config, gameplay, network/protocol, global service, manager, router, observer, event system, command, activation, or input binding was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- The unrelated dirty Status command-activation-pair draft in `src/sirius/platform/modules/status/sirius_status_module.*` was not staged for this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.

Numbering reconciliation:

- WP-087 is already committed as `c61e7bb0434c70632382cf6d689dd325db7d373e` (`refactor(platform): localize status module contract check`).
- The adapter/query work is therefore WP-088.
- A stale untracked WP-088 command-activation-contract draft was superseded by the user's explicit Adapter/query architecture decision.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-084-WP-086.md`
- `docs/work-packages/WP-086-SIRIUS-STATUS-SNAPSHOT.md`
- `docs/work-packages/WP-087-SIRIUS-STATUS-MODULE-CONTRACT-CHECK.md`
- `src/sirius/platform/features/status/sirius_status_snapshot.*`
- `src/sirius/platform/features/status/sirius_status_feature.*`
- `src/sirius/platform/modules/status/sirius_status_module.*`
- `src/sirius/platform/platform.*`
- `src/sirius/platform/platform_bootstrap.*`
- `src/sirius/adapters/ddnet/ddnet_platform_host.*`

## Goal

Expose a narrow, read-only Sirius Status query path through the existing Platform and DDNet adapter composition.

The query must consume and return the existing immutable `CSiriusStatusSnapshot`. It is a foundation for future UI, console, and other consumers, but this WP does not add those consumers.

## Exact Scope

1. Add a read-only Status snapshot query to `CPlatform`.
2. The Platform query must:
   - return an empty result when the Status module/feature is unavailable;
   - read the existing `CSiriusStatusFeature`;
   - return `CSiriusStatusFeature::Snapshot()`;
   - not mutate Status feature state.
3. Add a forwarding read-only query to `CPlatformBootstrap`.
4. Add a forwarding read-only query to `CDdnetPlatformHost`.
5. Use `std::optional<features::CSiriusStatusSnapshot>` optional value semantics for absence.
6. Use the existing Status-local module completeness check as a read-only guard where appropriate.
7. Update this WP status/evidence after validation.

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
- No new command, activation, or input binding.
- No public mutable module access.
- No service locator or generalized query registry.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The Status feature owns Status state and already exposes an immutable value snapshot. Platform owns module composition, so it is the narrow place that can find the Status feature and return its snapshot without exposing module internals.

The DDNet adapter remains adapter-only and should not know module registries, commands, activation mappings, or mutable feature implementation details. It only forwards an optional immutable value:

```text
DDNet-side consumer
  -> CDdnetPlatformHost::SiriusStatusSnapshot()
  -> CPlatformBootstrap::SiriusStatusSnapshot()
  -> CPlatform::SiriusStatusSnapshot()
  -> CSiriusStatusFeature::Snapshot()
```

This is intentionally a query, not routing, observation, eventing, or rendering.

## Acceptance Criteria

1. `CPlatform` exposes a read-only optional Status snapshot query.
2. `CPlatformBootstrap` forwards the query and returns empty when not started.
3. `CDdnetPlatformHost` forwards the query and remains adapter-only.
4. The query returns the existing immutable `CSiriusStatusSnapshot` value.
5. The query does not mutate Status feature, command, activation, input, or lifecycle state.
6. No UI/console/rendering/config/gameplay/network/protocol integration is introduced.
7. No manager/router/observer/event system/service locator/global service/generalized query registry is introduced.
8. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged unless a separately approved WP covers them.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "SiriusStatusSnapshot|CSiriusStatusSnapshot|IsSiriusStatusModuleComplete" src/sirius/platform src/sirius/adapters/ddnet
rg -n "router|scanner|scan|CommandManager|ServiceLocator|observer|event system|EventBus|MessageBus|global service|query registry" src/sirius/platform src/sirius/adapters/ddnet
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`feat(adapters): expose sirius status snapshot query`
