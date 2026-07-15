# WP-102 — Module Contract Identity Baseline

## Status

APPROVED by Sirius Lead fallback after repository inspection.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by adding the typed contract vocabulary required before import/export resolution can exist.

It follows the accepted sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts

## Goal

Introduce immutable typed module contract identity declarations for module-owned imports and exports without resolving, binding, routing, or exposing contracts to consumers.

## Scope

- Add `CModuleContractId`.
- Add `CModuleContractVersion`.
- Add `EModuleContractImportRequirement`.
- Add `CModuleContractImport`.
- Add `CModuleContractExport`.
- Extend `CModuleDescriptor` to carry immutable contract imports and exports.
- Preserve all existing descriptor constructors as contract-free.
- Add descriptor helpers for checking whether a contract is imported or exported.
- Add focused source-level tests for value identity and descriptor declarations.

## Non-goals

- No contract resolution.
- No import/export binding.
- No provider selection.
- No service locator.
- No module manager.
- No scanner or dynamic discovery.
- No runtime unloading.
- No routers, observers, event streams, or generalized dispatch.
- No UI, HUD, console commands, Theme System, Plugin SDK, replay tools, or gameplay modules.
- No change to module startup, shutdown, activation, commands, bindings, diagnostics, Status behavior, DDNet adapter behavior, or Platform composition behavior.

## Acceptance criteria

1. Contract IDs are explicit value objects.
2. Contract versions are explicit value objects.
3. Module contract imports carry ID, version, and required/optional requirement.
4. Module contract exports carry ID and version.
5. Module descriptors can declare imports and exports immutably.
6. Existing modules remain contract-free unless explicitly updated later.
7. Existing descriptor constructors and current module construction continue to work.
8. No forbidden architecture mechanism is introduced.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CModuleContractId|CModuleContractImport|CModuleContractExport|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-102-MODULE-CONTRACT-IDENTITY-BASELINE.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added and wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: contracts become service-location. Mitigation: this WP adds only immutable declaration values and no lookup or binding API.
- Main risk: contract model overreaches. Mitigation: only ID, version, import requirement, and export declaration are introduced.
- Main risk: descriptor constructor churn breaks current modules. Mitigation: existing constructors remain and default to empty contract declarations.

## Suggested commit message

`feat(modules): add module contract identity baseline`
