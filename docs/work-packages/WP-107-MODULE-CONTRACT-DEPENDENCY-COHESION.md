# WP-107 - Contract Dependency / Lifecycle Cohesion

## Status

Approved and implemented.

## Goal

Ensure Module Runtime contract bindings cannot bypass the explicit module dependency and lifecycle model.

Every resolved contract binding must be backed by an explicit direct dependency edge from the importing module to the exporting module. This keeps contract resolution, dependency ordering, and lifecycle ordering coherent without inferring hidden dependencies.

## Scope

- Validate resolved contract bindings inside the existing Module Runtime composition boundary.
- Reject required contract imports that resolve to an exporter without an explicit importer-to-exporter dependency.
- Reject optional contract imports that resolve to an exporter without an explicit importer-to-exporter dependency.
- Preserve missing optional imports as unbound and valid.
- Preserve existing dependency graph, lifecycle graph, and contract resolution ownership.
- Add focused tests for required, optional-resolved, optional-missing, and dependency-backed cases.

## Non-goals

- No manager.
- No scanner.
- No service locator.
- No dynamic discovery.
- No runtime unloading.
- No UI or product work.
- No hidden inferred dependencies.
- No module-facing mutation APIs.
- No generalized lookup APIs.

## Acceptance criteria

- A required import and matching export without an explicit dependency fails composition.
- An optional import and matching export without an explicit dependency fails composition.
- A missing optional import remains unbound and composition succeeds.
- An import and export with an explicit dependency still succeeds.
- Dependency-backed lifecycle ordering remains dependency before consumer.
- `game-client` builds in Debug and RelWithDebInfo.
- `git diff --check` has no blocking whitespace errors.

## Commit message

`feat(modules): require contract dependency cohesion`
