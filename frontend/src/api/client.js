const TOKEN_KEY = 'brewgo_auth_token'

export class ApiError extends Error {
  constructor(status, message) {
    super(message)
    this.status = status
  }
}

export function getToken() {
  try {
    return localStorage.getItem(TOKEN_KEY)
  } catch {
    return null
  }
}

export function setToken(token) {
  try {
    if (token) localStorage.setItem(TOKEN_KEY, token)
    else localStorage.removeItem(TOKEN_KEY)
  } catch {
    // ignore storage errors (private mode, etc.)
  }
}

export async function apiFetch(path, options = {}) {
  const token = getToken()
  const headers = {
    'Content-Type': 'application/json',
    ...(token ? { Authorization: `Bearer ${token}` } : {}),
    ...(options.headers || {}),
  }

  const res = await fetch(`/api${path}`, { ...options, headers })

  if (res.status === 204) return null

  let body = null
  const text = await res.text()
  if (text) {
    try {
      body = JSON.parse(text)
    } catch {
      body = null
    }
  }

  if (!res.ok) {
    throw new ApiError(res.status, body?.error || `Request failed (${res.status})`)
  }

  return body
}
