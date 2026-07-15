# WP-074 - Binding Activation Resolver Cleanup

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Sirius Architect: operationally unavailable from the prior WP-074 planning attempts.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Deleted `src/sirius/platform/input/bindings/activation/activation_resolver.h`.
- Removed the deleted header from `src/sirius/CMakeLists.txt`.
- No source references remain to `IActivationResolver` or the deleted binding-local header.
- Command and feature activation resolvers were not changed.
- Binding activation runtime files were not changed.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: not applicable; this WP removes an unused header and source-list entry without runtime behavior changes.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-069-WP-072.md`
- `docs/work-packages/WP-073-FEATURE-ACTIVATION-SHUTDOWN-RESTART-CONSISTENCY.md`
- `src/sirius/CMakeLists.txt`
- `src/sirius/platform/input/bindings/activation/activation_resolver.h`

## Goal

Remove the obsolete binding-local activation resolver interface that is no longer used by the binding activation pipeline.

The binding layer now emits source-neutral activation IDs through the binding activation adapter, registry, dispatcher, and handler interfaces. Command and feature activation resolution are owned by their dedicated Platform activation paths. The generic binding-local resolver header has no production include sites and should not remain as misleading architecture surface.

## Exact Scope

1. Delete `src/sirius/platform/input/bindings/activation/activation_resolver.h`.
2. Remove `platform/input/bindings/activation/activation_resolver.h` from `src/sirius/CMakeLists.txt`.
3. Verify no repository references remain to `IActivationResolver` or the deleted header.
4. Update current-state documentation after approval to remove the obsolete-resolver watch item and record the WP-074 commit baseline.

## Non-Goals

- No changes to `command_activation_resolver.*`.
- No changes to `feature_activation_resolver.*`.
- No changes to binding adapter, registry, dispatcher, matcher, or handler behavior.
- No activation behavior, lifecycle, command, feature, module, DDNet adapter, or Core changes.
- No public API replacement for the deleted unused interface.
- No module scanning, router, service, manager, or generalized activation abstraction.
- No cleanup of unrelated public Platform API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The deleted header is a generic interface in the binding activation directory:

```text
IActivationResolver<TId>
  Resolve(CBindingActivationId) -> TId*
```

It creates the impression that bindings should resolve directly into feature or command IDs. Current approved architecture says bindings must remain source-neutral and must not know Features or Commands. Removing the unused interface reduces accidental architecture surface without changing runtime behavior.

The dedicated command and feature activation resolvers remain valid Platform-owned consumers of neutral activation IDs and are not part of this cleanup.

## Acceptance Criteria

1. The obsolete binding-local `activation_resolver.h` file is removed.
2. `src/sirius/CMakeLists.txt` no longer lists the removed file.
3. No references remain to `IActivationResolver` or the removed binding-local header.
4. Command and feature activation resolver files are unchanged.
5. Binding activation runtime files are unchanged.
6. Protected dirty `module_registry.*` files remain untouched by this WP.
7. No production behavior changes are introduced.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
git status --short --branch
rg -n "IActivationResolver|platform/input/bindings/activation/activation_resolver.h|activation_resolver.h" src docs .codex/docs
git diff --check
git diff -- src/sirius/platform/commands/activation/command_activation_resolver.h src/sirius/platform/commands/activation/command_activation_resolver.cpp
git diff -- src/sirius/platform/features/activation/feature_activation_resolver.h src/sirius/platform/features/activation/feature_activation_resolver.cpp
git diff -- src/sirius/platform/input/bindings/activation
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

## Focused Self-Review

Confirm that this is only source-list and unused-header cleanup; the binding layer still emits neutral activation, command/feature resolvers remain Platform-owned, Core/DDNet boundaries are untouched, no replacement abstraction was invented, and unrelated dirty files remain excluded.

## Suggested Commit Message

`refactor(input): remove obsolete binding activation resolver`
