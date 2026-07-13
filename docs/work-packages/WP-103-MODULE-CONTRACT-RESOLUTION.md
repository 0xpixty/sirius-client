# WP-103 — Module Contract Import/Export Resolution

## Status

APPROVED by Sirius Lead fallback after repository inspection.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by resolving typed contract declarations into immutable binding records at the registration-plan/descriptor level.

It follows the accepted sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts

## Goal

Resolve module contract imports against module contract exports without exposing lookup APIs to modules or changing runtime behavior.

## Scope

- Add immutable `CModuleContractBinding` records.
- Add immutable `CModuleContractResolution` records.
- Add `ResolveModuleContractImports(const CModuleRegistrationPlan &)`.
- Resolve imports from module descriptors in deterministic registration-plan order.
- Bind required imports to exactly one matching export with the same contract ID and version.
- Reject missing required imports.
- Allow missing optional imports without producing a binding.
- Reject duplicate exports for the same contract ID and version.
- Reject empty contract IDs in imports or exports.
- Add focused source-level tests for successful binding, missing required imports, missing optional imports, and duplicate exports.

## Non-goals

- No module-facing contract lookup API.
- No service locator.
- No runtime binding injection.
- No module manager.
- No scanner or dynamic discovery.
- No runtime unloading.
- No routers, observers, event streams, or generalized dispatch.
- No lifecycle changes.
- No Platform startup behavior change.
- No UI, HUD, console command, Theme System, Plugin SDK, replay tools, gameplay modules, or DDNet adapter work.

## Acceptance criteria

1. Contract resolution exists as a passive value-level operation.
2. Required imports bind to exactly one matching export.
3. Missing required imports fail resolution.
4. Missing optional imports do not fail resolution.
5. Duplicate exports for the same contract ID/version fail resolution.
6. Empty import/export contract IDs fail resolution.
7. No module-facing lookup, service locator, manager, scanner, dynamic discovery, routing, or runtime unloading is introduced.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "ResolveModuleContractImports|CModuleContractBinding|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-103-MODULE-CONTRACT-RESOLUTION.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added and wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: resolution becomes service-location. Mitigation: resolution returns passive binding records only and does not expose module lookup or contract object access.
- Main risk: ambiguity policy is deferred too long. Mitigation: duplicate same-version providers are rejected immediately.
- Main risk: Platform behavior changes prematurely. Mitigation: this WP does not integrate resolution into Platform startup.

## Suggested commit message

`feat(modules): resolve module contract imports`
