# WP-092 - Status Input Binding Composition

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Ownership decision: keep input binding defaults in Platform composition for this WP; do not move input types into the Status module contract without a future architecture decision.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.

Implementation evidence:

- Added private `CPlatform::ConfigureStatusInputBindings()`.
- `CPlatform::ConfigureInputBindings()` now configures the technical binding and then calls `ConfigureStatusInputBindings()`.
- All four existing Status binding IDs, input keys, activation IDs, and pressed-trigger behavior are preserved exactly.
- Platform remains the owner of input binding composition.
- No Status module input dependency, manager, router, scanner, observer, event system, service locator, generalized registry, UI, console, rendering, config, gameplay, network, or protocol change was introduced.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed.
- RelWithDebInfo `game-client`: passed.

## Goal

Separate Sirius Status input binding composition into a dedicated Platform-local helper while preserving exact behavior and Platform ownership of input wiring.

## Exact Scope

1. Add a private `CPlatform::ConfigureStatusInputBindings()` helper.
2. Move the four existing Sirius Status `ConfigureBindings(...)` calls from `ConfigureInputBindings()` into that helper:
   - status activation
   - status open command activation
   - status close command activation
   - status toggle command activation
3. Keep `ConfigureInputBindings()` responsible for technical binding setup and then call `ConfigureStatusInputBindings()`.
4. Preserve all binding IDs, input keys, activation IDs, and trigger behavior exactly.

## Non-Goals

- No Status module input binding contract.
- No new input binding IDs or keys.
- No UI, console, rendering, config, gameplay, network, or protocol changes.
- No manager, router, observer, event system, service locator, scanner, generalized registry, or dynamic binding discovery.
- No changes to feature activation, command activation, Status snapshot query, or module registry behavior.

## Acceptance Criteria

1. `CPlatform::ConfigureStatusInputBindings()` exists and is private.
2. `ConfigureInputBindings()` calls `ConfigureStatusInputBindings()`.
3. All four existing Status bindings are preserved exactly.
4. Platform remains the owner of input binding composition.
5. No forbidden architecture mechanisms are introduced.
6. `git diff --check` passes.
7. Debug `game-client` builds.
8. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "ConfigureStatusInputBindings|binding.sirius.status|input.sirius.status" src/sirius/platform
rg -n "router|scanner|scan|CommandManager|ServiceLocator|observer|event system|EventBus|MessageBus|global service|query registry|contract registry" src/sirius/platform
git diff --check
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

## Suggested Commit Message

`refactor(platform): separate status input binding composition`
