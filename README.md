# Apollo

A ZUS Coffee-style ordering web app, built as a learning project. Menu browsing with
size/add-on customization, cart, checkout, and simple user accounts — React + Tailwind
frontend, C++ (Drogon) backend, **no database**.

The app is branded "Apollo" (not ZUS) but intentionally mirrors ZUS Coffee's visual
style — navy blue/white palette, rounded cards — and uses product photos supplied by the
project owner that include ZUS's own logo/wordmark. This is a private, local learning
project, not published or distributed, and does not claim any affiliation with ZUS
Coffee.

## Architecture

- **Frontend** (`frontend/`): React (Vite) + Tailwind CSS v4 SPA. Talks to the backend
  over `/api/*`, proxied to `http://localhost:8080` in dev (see `vite.config.js`).
- **Backend** (`backend/`): C++ REST API built on [Drogon](https://github.com/drogonframework/drogon).
  All state — users, sessions, carts, orders — lives **entirely in RAM** and is lost on
  restart. The only file involved is `backend/seed/menu_seed.json`, which is read once at
  startup to populate the menu catalog; nothing is ever written back to it. This is a
  deliberate "no database" constraint, not an oversight.

Auth uses a Bearer token (not cookies): signup/login return a token, stored in
`localStorage` on the frontend and sent as `Authorization: Bearer <token>`. Passwords are
hashed with PBKDF2-HMAC-SHA256 — adequate for a demo, **not** production-grade
(bcrypt/argon2 would be the real choice).

## Running locally

Two terminals:

```bash
# Backend (http://localhost:8080)
cd backend
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j
./backend

# Frontend (http://localhost:5173)
cd frontend
npm install
npm run dev
```

Requires [Drogon](https://github.com/drogonframework/drogon) installed (`brew install drogon`
on macOS) and Node.js.

Because there's no database, **restarting the backend wipes all accounts, carts, and
orders** — this is expected. Sign up again after any backend restart.

## API

All backend routes are under `/api`. See `backend/controllers/` for the full set:
health, menu (categories/items), auth (signup/login/logout/me), cart (CRUD), and
orders (place/list/detail).
