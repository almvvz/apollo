import { useState } from 'react'
import { Link, useLocation, useNavigate } from 'react-router-dom'
import { useAuth } from '../context/AuthContext'

export default function LoginPage() {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [error, setError] = useState(null)
  const [submitting, setSubmitting] = useState(false)

  const { login } = useAuth()
  const navigate = useNavigate()
  const location = useLocation()

  async function handleSubmit(e) {
    e.preventDefault()
    setError(null)
    setSubmitting(true)
    try {
      await login({ email, password })
      navigate(location.state?.from?.pathname ?? '/')
    } catch (err) {
      setError(err.message)
    } finally {
      setSubmitting(false)
    }
  }

  return (
    <div className="max-w-sm mx-auto p-8">
      <h1 className="text-2xl font-bold text-brand-navy mb-6">Log in</h1>
      <form onSubmit={handleSubmit} className="flex flex-col gap-3">
        <input
          type="email"
          required
          placeholder="Email"
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          className="border border-brand-mist rounded-lg px-3 py-2"
        />
        <input
          type="password"
          required
          placeholder="Password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          className="border border-brand-mist rounded-lg px-3 py-2"
        />
        {error && <p className="text-red-500 text-sm">{error}</p>}
        <button
          type="submit"
          disabled={submitting}
          className="bg-brand-navy text-brand-white rounded-full py-2.5 font-semibold disabled:opacity-60"
        >
          {submitting ? 'Logging in…' : 'Log in'}
        </button>
      </form>
      <p className="text-sm text-brand-navy/70 mt-4">
        No account?{' '}
        <Link to="/signup" className="text-brand-accent font-medium">
          Sign up
        </Link>
      </p>
    </div>
  )
}
