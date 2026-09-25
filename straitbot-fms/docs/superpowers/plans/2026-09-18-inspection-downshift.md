# Inspection Downshift Implementation Plan

> **For agentic workers:** Use executing-plans to implement tasks in this session, with verification after each deliverable.

**Goal:** Implement persisted inspection plans and waypoint/point binding in FMS.
**Architecture:** Reuse PointBinding and the archive publication lock. Store plans and execution claims in SQLite, keep configuration separate from device dispatch, and share the existing robot selector.
**Tech Stack:** FastAPI, SQLAlchemy/SQLite, Python 3.11, React/TypeScript, Semi UI.
**Spec:** `docs/INSPECTION-DOWNSHIFT.md`.

## Global Constraints
- Preserve legacy consumers, current local styling changes and existing data.
- No source-platform writes or live-device commands during verification.
- Robot PK and external robot ID remain distinct; point IDs remain strings.

## Task 1 — Live waypoint binding
Files: `backend/app/point_archive/relations.py`, `backend/app/routers/point_archive.py`, `frontend/src/api/pointArchive.ts`, `frontend/src/views/sink/WaypointBinding.tsx`, `backend/tests/test_point_archive_relations.py`.
- [x] Add scoped query arguments `robot_pk`, `waypoint_pk` and optional paginated binding results; preserve old call signatures.
- [x] Add `POST /bindings/batch` with explicit robot/waypoint/action and unique point IDs; validate every row before a single commit. Duplicate and invalid batches return errors without writes.
- [x] Replace static page with selected-robot waypoint search/pagination, bound-point list and searchable active-point picker. Reuse existing single deletion endpoint.
- [x] Verify pytest scenarios: two robots cannot mix, disabled point rolls back batch, duplicates rejected, point IDs retain zeroes, page switching ignores stale requests.

## Task 2 — Plan storage and schedule
Files: new `backend/app/models/inspection_plan.py`, `backend/app/services/inspection_plans.py`, `backend/app/routers/inspection_plans.py`, existing model exports, main/router registration and archive reference protection; new `backend/tests/test_inspection_plans.py`.
- [x] Define InspectionPlan and execution-claim models, explicit version for optimistic edits, point references, schedule shape and next occurrence calculations.
- [x] Implement CRUD, enable/disable, date-range occurrences and history with robot scope and engineer mutations.
- [x] Test recurrence boundaries, invalid dates/weekdays, duplicate names, stale edits, robot mismatch, reference deletion and restart persistence.

## Task 3 — Dispatch and scheduling
Files: plan service, existing poller and inspection reporting, new protocol adapter and tests.
- [x] Trace legacy cmd=100 payload to a concrete existing serializer; preserve external waypoint/action IDs in compiled content.
- [x] Claim execution durably before network I/O; snapshot points/targets; reject inactive/missing/cross-robot bindings; guard overlap and retries.
- [x] Poll due local schedules with durable uniqueness; explicit missed-run and uncertain-result behavior. Map reports to correct robot and execution.
- [x] Verify mock dispatch payload, duplicate clicks/ticks, failure and uncertain network outcome, restart and report correlation.

## Task 4 — Plan interface and delivery
Files: `frontend/src/views/sink/InspectionPlan.tsx`, new API client and focused styles, validation report.
- [x] Implement robot-scoped real list, edit form, schedule selector, point selection, calendar, history and explicit execution confirmation; remove all static controls and numbers.
- [x] Run relevant backend suite and production frontend build. Exercise complete CRUD/binding/plan flow on isolated deployment with two robots and mocked dispatch.
- [x] Backup and deploy to .88, verify real empty/data states and robot selection without creating active production schedules, record rollback and limitations.
