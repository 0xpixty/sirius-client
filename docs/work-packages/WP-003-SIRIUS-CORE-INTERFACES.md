# WP-003 — Sirius Core Interfaces

Status: Planned

Owner: Sirius Platform

Priority: High

Estimated Size: Small

---

# Summary

Introduce the foundational interfaces shared by all future Sirius infrastructure.

These interfaces define the common lifecycle and service concepts used throughout the Sirius platform.

This package intentionally contains no concrete implementations.

---

# Motivation

WP-002 introduced the Core Runtime.

Future systems such as Logger, Configuration, Scheduler, Event Bus and Module Manager require a common contract for lifecycle management and service ownership.

Defining these contracts now avoids duplicated APIs and keeps future work packages consistent.

---

# Goals

Introduce a minimal Core Interfaces layer.

Provide common lifecycle abstraction.

Provide a base service abstraction.

Remain completely engine-agnostic.

---

# Non Goals

This work package does NOT implement:

- Service Registry
- Logger
- Configuration
- Scheduler
- Event Bus
- Module System
- Plugin loading
- DDNet integration
- UI
- Rendering
- Networking

---

# Directory Layout

src/sirius/core/interfaces/

    runtime_component.h

    service.h

---

# Runtime Component

Introduce a lightweight runtime lifecycle interface.

Responsibilities:

- Initialize()
- Shutdown()

The interface should only describe lifecycle.

No ownership.

No dependencies.

---

# Service

Introduce a lightweight service marker/base interface.

This interface exists so future runtime services share a common base type.

No functionality is required today.

---

# Requirements

Interfaces must be minimal.

No implementation code.

No global state.

No singleton pattern.

No macros.

No engine dependencies.

No DDNet headers.

---

# Future Usage

Examples of future implementations:

Logger

Configuration

Scheduler

Event Bus

Resource Manager

Module Manager

All of these are expected to implement the interfaces introduced here.

---

# Acceptance Criteria

- Core Interfaces directory added.
- Runtime component interface introduced.
- Service interface introduced.
- Sirius Core remains DDNet-independent.
- No behavior changes.
- Project builds successfully.