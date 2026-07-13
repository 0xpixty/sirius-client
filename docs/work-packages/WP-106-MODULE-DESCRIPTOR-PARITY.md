# WP-106 — Definition / Constructed Descriptor Parity

## Status

APPROVED by Sirius Lead following the Module Runtime Milestone Readiness Checkpoint.

## Goal

Prove that the descriptor used for Module Runtime composition matches the descriptor of the actual constructed module before registration.

## Scope

- Add a narrow descriptor parity check between `CModuleDefinition::Descriptor()` and the constructed `IModule::Descriptor()`.
- Compare module ID, feature IDs, command IDs, module-service IDs, dependency IDs, contract imports, and contract exports.
- Require parity in `CPlatform::ConfigureModules()` before registry insertion.
- Add focused source-level tests for matching descriptors and dependency/contract mismatches.

## Non-goals

- No manager.
- No scanner.
- No service locator.
- No dynamic discovery.
- No runtime unloading.
- No UI or product work.
- No hidden inferred dependencies.
- No module-facing mutation or generalized lookup APIs.

## Acceptance criteria

1. A constructed module cannot be registered if its descriptor differs from the definition descriptor used for runtime composition.
2. Existing technical and Status modules still compose successfully.
3. Descriptor parity includes ownership declarations, dependency declarations, and contract declarations.
4. `git diff --check` passes.
5. Debug `game-client` builds.
6. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "AreModuleDescriptorsEquivalent|ServiceLocator|scanner|router|observer|manager|dynamic discovery|runtime unloading" src/sirius src/test docs/work-packages/WP-106-MODULE-DESCRIPTOR-PARITY.md
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client --config Debug
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client --config RelWithDebInfo
```

Focused C++ tests are added and wired, but the current configured local build trees do not expose the GTest runner targets used by these source-level tests.

## Suggested commit message

`feat(modules): validate definition descriptor parity`
