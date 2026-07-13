# WP-104 — Module Contract Binding Integration

## Status

APPROVED by Sirius Lead fallback after repository inspection.

## Milestone fit

This Work Package directly advances Foundation V2 / Sirius Module Runtime by integrating passive contract import/export resolution into Platform composition state without exposing service-location or module-facing lookup.

It follows the accepted sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts

## Goal

Have Platform resolve and retain immutable module contract bindings during explicit module composition, and expose only aggregate diagnostics about those bindings.

## Scope

- Resolve module contract imports from the explicit registration plan during `CPlatform::ConfigureModules()`.
- Store the immutable `CModuleContractResolution` in `CPlatform`.
- Fail Platform construction if contract resolution fails.
- Extend Module Runtime diagnostics snapshot with aggregate contract binding count.
- Keep module-facing APIs unchanged.
- Keep runtime lifecycle, activation, commands, features, bindings, Status behavior, DDNet adapter behavior, and module ownership unchanged.

## Non-goals

- No module-facing contract lookup API.
- No service locator.
- No runtime injection into modules.
- No dynamic discovery.
- No scanner.
- No module manager.
- No runtime unloading.
- No routers, observers, event streams, or generalized dispatch.
- No UI, HUD, console command, Theme System, Plugin SDK, replay tools, gameplay modules, or DDNet adapter work.
- No new product module contract declarations.

## Acceptance criteria

1. `CPlatform` resolves contract imports from the explicit module registration plan.
2. `CPlatform` stores the immutable resolution result.
3. Resolution failure prevents Platform composition from succeeding.
4. Diagnostics reports the stored contract binding count.
5. Current modules remain contract-free and produce zero bindings.
6. No module-facing lookup, service locator, manager, scanner, dynamic discovery, routing, or runtime unloading is introduced.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "ResolveModuleContractImports|CModuleContractResolution|ContractBindingCount|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-104-MODULE-CONTRACT-BINDING-INTEGRATION.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests remain source-wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Risk review

- Main risk: stored bindings become a service locator. Mitigation: Platform stores the passive resolution result but exposes no module-facing lookup or contract object access.
- Main risk: Platform policy grows. Mitigation: this WP only adds composition-time validation/storage from the explicit plan, matching existing dependency/lifecycle graph composition.
- Main risk: diagnostics overexposes internals. Mitigation: diagnostics reports only aggregate binding count in this WP.

## Suggested commit message

`feat(platform): integrate module contract binding state`
