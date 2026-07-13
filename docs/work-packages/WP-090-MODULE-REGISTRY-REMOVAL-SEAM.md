# WP-090 - Module Registry Removal Seam

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECTURE_APPROVED`.
- Lead reconciliation: accepted because the Architect result arrived before Lead fallback implementation began.
- Reviewer consultant: `REVIEWER_UNAVAILABLE` after one silent instance and one silent retry.
- Devil's Advocate consultant: `DEVIL_UNAVAILABLE` after one silent instance and one silent retry.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- Latest architecture audit: `AUDITOR_FALLBACK_APPROVED` in `docs/architecture/AUDIT-WP-087-WP-089.md`.

Implementation evidence:

- Added `CModuleRegistry::Remove(const CModuleId &Id)`.
- Removal returns `false` while the registry is sealed.
- Removal returns `false` when the ID is absent.
- Removal erases the corresponding registration-order pointer before erasing the owned module from the map.
- Remaining registration order is preserved by single-vector-element erase.
- No production caller was introduced.
- No module unloading, lifecycle integration, dynamic module system, router, manager, observer, event system, service locator, scanning, UI, console, rendering, gameplay, network, or protocol change was introduced.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed.
- RelWithDebInfo `game-client`: passed.
- Focused tests: no `tests` directory/focused `CModuleRegistry` test infrastructure is present in this checkout; source inspection plus required builds were used as allowed by this WP.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-087-WP-089.md`
- `src/sirius/platform/modules/module_registry.*`
- Other local registry removal patterns:
  - `src/sirius/platform/features/feature_activation_registry.*`
  - `src/sirius/platform/commands/activation/command_activation_resolver.*`

## Goal

Add and validate a narrow `CModuleRegistry::Remove(const CModuleId &Id)` API so module registry ownership has the same local removal capability already present in other platform registries.

This is a bounded registry seam only. It does not add module unloading, lifecycle integration, dynamic modules, or a production caller.

## Exact Scope

1. Add `bool CModuleRegistry::Remove(const CModuleId &Id);`.
2. The method must:
   - return `false` when the registry is sealed;
   - return `false` when the module ID is absent;
   - remove the module from the owning map when present;
   - remove the corresponding raw pointer from registration-order storage;
   - preserve registration order for all remaining modules;
   - return `true` only when a module was actually removed.
3. Preserve existing `Register`, `Has`, `Get`, `ModulesInRegistrationOrder`, `Count`, `Clear`, `Seal`, and `Unseal` semantics.
4. Do not add any caller unless repository evidence shows an already-approved use.
5. Update this WP status/evidence after validation.

## Non-Goals

- No module unloading workflow.
- No lifecycle shutdown integration.
- No dynamic module system.
- No public `CPlatform::Modules()` restoration.
- No UI.
- No console commands.
- No rendering.
- No config changes.
- No gameplay behavior.
- No networking or protocol changes.
- No manager.
- No router.
- No service locator.
- No observer or event system.
- No generalized module discovery, scanning, or routing.
- No changes to Status feature, commands, adapter query, or activation behavior.

## Architecture Rationale

`CModuleRegistry` already owns modules and registration order. A local `Remove()` seam is consistent with other small registries that support explicit removal by ID, provided it remains only a registry mutation primitive and does not imply runtime module unloading.

The seam is acceptable because it is:

- local to the registry;
- sealed-state aware;
- explicit by concrete `CModuleId`;
- not exposed through `CPlatform`;
- not paired with scanning, routing, dynamic discovery, or lifecycle policy.

## Acceptance Criteria

1. `CModuleRegistry::Remove()` exists in `module_registry.h/.cpp`.
2. Removal is blocked while sealed.
3. Missing IDs return `false`.
4. Present IDs return `true` and remove ownership from the map.
5. Registration-order pointer storage no longer contains the removed module.
6. Remaining registration order is preserved.
7. No new production caller is introduced.
8. No forbidden architecture mechanisms are introduced.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "bool CModuleRegistry::Remove|\\.Remove\\(" src/sirius/platform src/sirius/adapters/ddnet tests
rg -n "router|scanner|scan|CommandManager|ServiceLocator|observer|event system|EventBus|MessageBus|global service|query registry" src/sirius/platform src/sirius/adapters/ddnet
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

If focused local tests for `CModuleRegistry` already exist, update/run them. If no focused test infrastructure exists for this registry, source inspection plus required builds is acceptable for this narrow seam.

## Suggested Commit Message

`refactor(platform): add module registry removal seam`
