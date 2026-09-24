# Inspection Workflow Implementation Plan

> **For agentic workers:** Execute this plan task by task in the current authorized workspace, preserving existing changes.

**Goal:** Complete archive → waypoint/action bindings → multi-map inspection plan workflow and improve dialogs, buttons and sidebar.
**Architecture:** Reuse the portable archive, SQLite PointBinding, existing plan compiler and HTTP robot adapter. Add scoped navigation and configuration previews; no duplicate binding store or device controls.
**Tech Stack:** FastAPI, SQLAlchemy, React, TypeScript, Semi UI.
**Spec:** User goal in this task; business-downshift.md. Legacy reference: new-hxzh-admin/src/views/confManager/module/BindCeDialog.vue and file_configuar APIs. Legacy Java/Vue remains untouched.

## Design contract
Industrial operations workspace; restrained navy #14283e, ink #243e58, blue #285ad6, pale blue #eef4fc, line #dfe7ef, white #ffffff. Segoe UI/Microsoft YaHei for headings and body; Consolas for IDs. Sidebar groups runtime, inspection workflow and engineering tools; archive → binding → plan order reflects the actual process. No decorative hero or extra summary cards. Dialogs keep 24px inner spacing, 16px viewport margin, scrollable body and separated footer. Active, hover, disabled and focus states remain distinct.

## Global constraints
- Preserve IDs, snapshots, compatibility APIs and existing user data. No schema migration.
- Scope robot/map/floor filtering on server and client. Clear stale selections when context changes.
- No configuration operation sends a robot command. Device verification uses isolated Demo interception.
- Keep root directory selection, arbitrary depth and fuzzy directory search. Do not copy legacy production databases.

## Task 1: scoped data and route preview
- [x] Extend binding-options(robot_pk,map_pk,floor,waypoint_pk) with counts, inherited floor and ID search; enrich binding rows with robot/map names and affected plan names.
- [x] Add catalog query `q` matching name/code/id without changing legacy `name` semantics.
- [x] Add GET /inspection-plans/{id}/preview using compile_route(..., 'preview', ...); return stage waypoint/action counts and selected point mappings, no writes/IO.
- [x] Add behavioral tests for scoping, atomic batch rollback, preview after bind/unbind, permissions and immutable execution snapshots. Run `python -m pytest tests -q --disable-warnings`.

## Task 2: connected workspaces
- [x] Extract DirectorySelect from PointArchive and reuse in binding/route pickers.
- [x] Rebuild WaypointBinding with map/floor/waypoint list, bindings, searchable directory selection, cross-page selection and actionable empty states.
- [x] Archive details link with point_id; bindings link with robot/map/floor into a plan draft. No auto-save/execute.
- [x] Scope embedded archive binding view to current robot. Plan editor offers directory filter, source binding links and read-only route preview.
- [x] Preserve async robot-switch guards and readable loading/errors. Verify build with `npm run build` in Docker.

## Task 3: shell and dialogs
- [x] Group every existing authorized route, preserve access filters, collapsed/expanded/mobile navigation and active indication.
- [x] Apply shared dialog and footer spacing to three workflow pages plus consistent buttons; narrow screens stay inside viewport.
- [x] Inspect browser screenshots at desktop and mobile; keyboard focus and scrolling must reach all actions.

## Task 4: acceptance and rollout
- [x] On isolated 8912 create archive point, bind to an action, navigate into a draft, save, preview and simulate execute; verify task snapshot matches point/action and no physical IO.
- [x] Verify disabled/unbound points cannot enter executable plans, cross-robot navigation resets and duplicate binding is rejected.
- [x] Build/test backend and frontend, deploy authorized 6.88 services preserving data/config and prior images.
- [x] Record results and rollback in docs/INSPECTION-WORKFLOW.md. Audit every item before marking goal complete.

Acceptance evidence, deployment identifiers and rollback are recorded in `docs/INSPECTION-WORKFLOW.md`.
