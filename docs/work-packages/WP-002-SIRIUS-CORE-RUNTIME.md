# WP-002 - Introduce Sirius Core Runtime

## Status

Proposed

## Goal

Introduce the first internal runtime owned entirely by the Sirius Platform.

WP-002 must turn `CPlatform` from an empty platform object into the owner of a minimal Sirius Core Runtime.

The runtime introduced in this work package is lifecycle infrastructure only.

It must not provide visible functionality or introduce future subsystems prematurely.

## Background

WP-001 established the following ownership chain:

```text
CClient
    ->
CDdnetPlatformHost
    ->
CPlatformBootstrap
    ->
CPlatform
```

`CPlatform` currently stores only `CPlatformConfiguration`.

Future Sirius systems must not be placed directly inside DDNet integration code and must not accumulate directly inside `CPlatform`.

WP-002 introduces a dedicated internal runtime boundary:

```text
CClient
    ->
CDdnetPlatformHost
    ->
CPlatformBootstrap
    ->
CPlatform
    ->
CCoreRuntime
```

The runtime will become the future composition boundary for Sirius systems, but WP-002 must not implement those systems.

## Architectural decision

Create the runtime under:

```text
src/sirius/core/runtime/
```

The directory structure introduced by WP-002 must be:

```text
src/sirius/
|-- adapters/
|   `-- ddnet/
|-- core/
|   `-- runtime/
`-- platform/
```

Do not create empty speculative directories for scheduler, services, modules, UI, rendering, input, foundation, or other future systems.

Directories must be created only when a work package introduces real code for them.

## Required files

Create:

```text
src/sirius/core/runtime/core_runtime.h
src/sirius/core/runtime/core_runtime.cpp
src/sirius/core/runtime/core_runtime_configuration.h
src/sirius/core/runtime/core_runtime_state.h
```

Modify only where required:

```text
src/sirius/CMakeLists.txt
src/sirius/platform/platform.h
src/sirius/platform/platform.cpp
```

Do not modify DDNet lifecycle integration unless a concrete build issue proves it is necessary.

## Core Runtime responsibilities

`CCoreRuntime` is responsible only for its own lifecycle state.

It must expose:

```cpp
void Start();
void Stop() noexcept;
bool IsRunning() const noexcept;
```

Do not add `Tick()` in WP-002.

There is currently no actual DDNet frame integration and no consumer for a runtime tick. Adding an unused frame method would be speculative API design.

A future frame-pipeline work package will introduce frame execution deliberately.

## Runtime state

Introduce a strongly typed state:

```cpp
enum class ECoreRuntimeState
{
	Stopped,
	Running,
};
```

The runtime must start in `Stopped`.

`Start()` must be idempotent:

- calling `Start()` while stopped changes the state to running;
- calling `Start()` while already running performs no work.

`Stop()` must be idempotent:

- calling `Stop()` while running changes the state to stopped;
- calling `Stop()` while already stopped performs no work.

No additional lifecycle states are required.

Do not introduce:

- Starting;
- Stopping;
- Failed;
- Suspended;
- Initialized;
- error codes;
- exceptions used as lifecycle states.

## Runtime configuration

Introduce `CCoreRuntimeConfiguration`.

It may remain empty in WP-002.

It exists as an explicit construction boundary for future runtime configuration.

Use value semantics.

Do not add DDNet types, pointers, callbacks, service references, settings, or placeholders.

## Ownership

`CPlatform` must own the runtime using explicit RAII ownership:

```cpp
std::unique_ptr<CCoreRuntime>
```

Expected ownership:

```text
CPlatform
    owns
        std::unique_ptr<CCoreRuntime>
```

`CPlatform` must remain non-copyable and non-movable.

`CCoreRuntime` must also be non-copyable and non-movable.

No global objects, singleton, service locator, static-owned runtime, or hidden ownership is allowed.

## Platform lifecycle

`CPlatform` must construct and start the runtime during platform construction.

Expected construction flow:

```text
CPlatform construction
    ->
create CCoreRuntime
    ->
CCoreRuntime::Start()
```

`CPlatform` must stop the runtime before destroying it.

Expected destruction flow:

```text
CPlatform destruction
    ->
CCoreRuntime::Stop()
    ->
runtime destruction
    ->
platform destruction
```

Destructor cleanup must remain safe if `Stop()` has already been called internally.

Do not expose the runtime through a public getter in WP-002.

The runtime remains a private implementation detail of `CPlatform`.

## Dependency rules

Code under:

```text
src/sirius/core/
```

must not include headers from:

```text
engine/
game/
src/game/
src/engine/
sirius/adapters/
```

Core Runtime may depend only on:

- the C++ standard library;
- other lower-level Sirius core types introduced by this WP.

`CPlatform` may depend on Core Runtime.

Core Runtime must not depend on `CPlatform`.

The allowed dependency direction is:

```text
platform -> core/runtime
```

The forbidden direction is:

```text
core/runtime -> platform
```

DDNet integration remains isolated under:

```text
src/sirius/adapters/ddnet/
```

## CMake integration

Add all WP-002 source and header files to `SIRIUS_CLIENT`.

Follow the existing Sirius CMake organization and alphabetical source-list formatting.

Do not introduce a new library target in WP-002.

Do not modify unrelated DDNet CMake source lists.

## Observable behavior

The client must remain behaviorally identical.

WP-002 must not introduce:

- lifecycle logs;
- console output;
- UI;
- renderer integration;
- input integration;
- settings;
- configuration loading;
- networking behavior;
- gameplay behavior;
- new commands;
- visible branding;
- frame callbacks.

## Explicit non-goals

Do not implement or scaffold:

- Module Runtime;
- Module Manager;
- Module Graph;
- Service Registry;
- Dependency Injection;
- Contracts;
- Scheduler;
- Event Bus;
- Frame Pipeline;
- Tick Loop;
- UI Runtime;
- View system;
- Elements;
- Render Objects;
- Renderer;
- Input Routing;
- Layout;
- Invalidation;
- Theme system;
- Animation system;
- Settings integration;
- Persistence;
- Logging;
- Diagnostics;
- Threading;
- async execution;
- reflection;
- plugin loading.

Do not create interfaces or placeholder classes for these systems.

## Scope discipline

WP-002 must remain small.

Expected changes are limited to:

- four new Core Runtime files;
- Sirius CMake registration;
- minimal `CPlatform` ownership and lifecycle changes;
- the WP document;
- optionally a dedicated Codex task record if repository policy requires it and it remains git-ignored.

If implementation appears to require changes outside this scope, stop and report the architectural issue instead of expanding the task.

## Acceptance criteria

WP-002 is accepted only when all of the following are true:

- `CCoreRuntime` exists under `src/sirius/core/runtime/`;
- the runtime has explicit stopped/running state;
- lifecycle operations are idempotent;
- `CPlatform` exclusively owns the runtime;
- runtime construction and destruction are RAII-safe;
- no DDNet headers enter Sirius Core Runtime;
- no public runtime getter is introduced;
- no unused `Tick()` API is introduced;
- no visible client behavior changes;
- no lifecycle logs are added;
- no unrelated files are modified;
- Debug build succeeds;
- RelWithDebInfo build succeeds;
- launch/close smoke test succeeds;
- `git diff --check` succeeds for scoped files.

## Deliverables

After implementation, provide:

1. Short implementation summary.
2. Exact files created and modified.
3. Ownership explanation.
4. Lifecycle explanation.
5. Dependency-boundary explanation.
6. Debug build result.
7. RelWithDebInfo build result.
8. Launch/close smoke-test result.
9. `git diff --check` result.
10. Complete WP-002 diff.
11. Any deviations from this work package.
12. Suggested commit message.

Suggested commit message:

```text
feat(runtime): introduce Sirius Core Runtime
```

Do not commit until Architecture Review approves the implementation.
