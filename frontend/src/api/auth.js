import { apiFetch } from './client'

export function signup({ email, password, displayName }) {
  return apiFetch('/auth/signup', {
    method: 'POST',
    body: JSON.stringify({ email, password, displayName }),
  })
}

export function login({ email, password }) {
  return apiFetch('/auth/login', {
    method: 'POST',
    body: JSON.stringify({ email, password }),
  })
}

export function logout() {
  return apiFetch('/auth/logout', { method: 'POST' })
}

export function me() {
  return apiFetch('/auth/me')
}
