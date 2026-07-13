# WP-079 - Platform Modules Test Seam Cleanup

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- User architecture decision: complete remaining platform composition cleanup first.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Removed public mutable and const `CPlatform::Modules()` declarations and implementations.
- Replaced the focused platform lifecycle test's technical-command observation with the existing private `CPlatformActivationLifecycleTestPeer`.
- Replaced the focused failed-start test's module clearing with the existing private test peer.
- No `CPlatform::Modules()` declaration/implementation or `Platform.Modules()` call remains in source/tests.
- Production behavior is unchanged.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: source-updated but not executed because local GTest remains unavailable in the configured build.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/architecture/AUDIT-WP-073-WP-076.md`
- `docs/work-packages/WP-078-TECHNICAL-ACTIVATION-PROOF-IDS.md`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`
- `src/test/sirius_platform_activation_lifecycle_test.cpp`

## Goal

Remove the public mutable `CPlatform::Modules()` composition seam and replace the current focused test usage with the existing private test peer.

`CPlatform` owns module composition. Exposing `Modules()` publicly gives external callers mutable access to the module registry and makes Platform look like a module service locator. The only current callers are focused lifecycle tests.

## Exact Scope

1. Remove public `CPlatform::Modules()` mutable and const declarations.
2. Remove both `CPlatform::Modules()` implementations.
3. Extend `CPlatformActivationLifecycleTestPeer` in `src/test/sirius_platform_activation_lifecycle_test.cpp` only.
4. The peer may:
   - return the technical command for observation;
   - clear platform modules to preserve the existing failed-start test case.
5. Update helper/test code to use the peer instead of public `Modules()`.

## Non-Goals

- No production public replacement accessor.
- No product-facing test hook.
- No module manager, service locator, router, scanner, registration framework, or generalized composition API.
- No behavior changes to Start, Stop, activation fan-out, shutdown reconciliation, technical proof wiring, or module lifecycle.
- No changes to module registry implementation.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.
- No first real feature/command in this WP.

## Architecture Rationale

Platform remains the composition root. Module registry mutation should stay internal to Platform composition, not exposed as a public runtime API. The current focused tests still need to inspect the technical command and simulate missing module composition; the already private `CPlatformActivationLifecycleTestPeer` is the narrowest existing seam for that purpose.

This is intentionally not a new abstraction. It is a reduction of public API surface.

## Acceptance Criteria

1. No `CPlatform::Modules()` declaration or implementation remains.
2. No `Platform.Modules()` call remains.
3. The platform lifecycle test still observes the technical command through the private test peer.
4. The failed-start test still clears modules through the private test peer.
5. Production behavior is unchanged.
6. No protected dirty files are changed or staged.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CPlatform::Modules|Platform\\.Modules\\(|Modules\\(\\)" src/sirius src/test docs/architecture .codex/docs/CURRENT_STATE.md
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are source-updated, but execution remains limited by current local GTest availability unless a test-enabled build is already available.

## Suggested Commit Message

`refactor(platform): remove public modules composition seam`
