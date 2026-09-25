# Repository Guidelines

## Architecture and Business Migration
Straitbot FMS is the new architecture for upcoming business capability migration (业务下沉). The existing integration platform remains actively maintained: `../../hxzh-dev-3/backend/` is Java/Spring Boot and `../../hxzh-dev-3/new-hxzh-admin/` is Vue 2. FMS uses Python/FastAPI and React/TypeScript; migration does not imply retiring the legacy platform.

In the shared workspace, read `../../hxzh-dev-3/rules/business-downshift.md`. For standalone checkouts, retain these requirements: trace the original business flow, define capability ownership, map identifiers and API semantics, preserve existing consumers, and document validation and rollback. Record cross-architecture designs in `docs/`; reuse existing capabilities before adding duplicate screens or services.

## Project Structure
- `backend/app/`: FastAPI application, routers, services, device protocols, state machines, and simulation.
- `backend/tests/`: pytest and unittest tests; `backend/data/` contains persistent data and bundled defaults—distinguish fixtures from runtime data.
- `frontend/src/`: React views, components, and API clients.
- `docs/`, `ARCHITECTURE.md`, and `README.md`: design and operational context; verify older descriptions against current code.

## Development Commands
Use Python 3.11, matching the backend Docker image, and an isolated environment.
- In `backend/`, run `python -m pip install -r requirements.txt`, then `python -m uvicorn app.main:app --reload` with local test configuration.
- Install pytest separately (`python -m pip install pytest`); run `python -m pytest tests` from `backend/`.
- `python -m unittest tests.test_simulation -v` runs the simulation unittest suite from `backend/`.
- In `frontend/`, install dependencies, then use `npm run dev` or `npm run build`; the build runs TypeScript checking followed by Vite.

## Style and Verification
Use four-space Python indentation, snake_case functions, and PascalCase classes. Follow surrounding TypeScript formatting, normally two spaces, with PascalCase React components. No frontend lint/test script or shared coverage threshold is currently configured.

Name Python tests `test_*.py`; cover changed behavior, protocol errors, retries, and state transitions as applicable. Use simulation and isolated data before device integration. Regress legacy consumers when shared contracts change.

## Commits and Reviews
Prefer `feat(scope): description`, `fix(scope): description`, or `docs(scope): description`. PRs should describe migration scope, link issues/companion changes, show UI screenshots, and record validation, data compatibility, and rollout/rollback requirements. Preserve local work; exclude secrets and runtime artifacts. Device control and deployment must remain within the task's authorized scope.
