import { createContext, useCallback, useContext, useEffect, useState } from 'react'
import * as authApi from '../api/auth'
import { getToken, setToken, ApiError } from '../api/client'

const AuthContext = createContext(null)

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null)
  const [loading, setLoading] = useState(true)

  useEffect(() => {
    async function rehydrate() {
      if (!getToken()) {
        setLoading(false)
        return
      }
      try {
        const me = await authApi.me()
        setUser(me)
      } catch {
        setToken(null)
        setUser(null)
      } finally {
        setLoading(false)
      }
    }
    rehydrate()
  }, [])

  const signup = useCallback(async (payload) => {
    const { user, token } = await authApi.signup(payload)
    setToken(token)
    setUser(user)
    return user
  }, [])

  const login = useCallback(async (payload) => {
    const { user, token } = await authApi.login(payload)
    setToken(token)
    setUser(user)
    return user
  }, [])

  const logout = useCallback(async () => {
    try {
      await authApi.logout()
    } catch {
      // token may already be invalid server-side; clear local state regardless
    }
    setToken(null)
    setUser(null)
  }, [])

  return (
    <AuthContext.Provider value={{ user, loading, signup, login, logout }}>
      {children}
    </AuthContext.Provider>
  )
}

export function useAuth() {
  const ctx = useContext(AuthContext)
  if (!ctx) throw new Error('useAuth must be used within AuthProvider')
  return ctx
}

export { ApiError }
