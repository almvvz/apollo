import { Link, useNavigate } from 'react-router-dom'
import { useAuth } from '../context/AuthContext'
import { useCart } from '../context/CartContext'

export default function Navbar() {
  const { user, logout } = useAuth()
  const { cart } = useCart()
  const navigate = useNavigate()

  async function handleLogout() {
    await logout()
    navigate('/')
  }

  return (
    <nav className="sticky top-0 z-40 bg-brand-navy/95 backdrop-blur text-brand-white px-6 py-4 flex items-center justify-between shadow-md">
      <Link to="/" className="text-xl font-bold tracking-[0.2em]">
        APOLLO
      </Link>
      <div className="flex items-center gap-5 text-sm font-medium">
        <Link to="/cart" className="relative hover:text-brand-accent transition-colors">
          Cart
          {cart.itemCount > 0 && (
            <span className="absolute -top-2 -right-3 bg-brand-accent text-brand-white text-xs rounded-full w-5 h-5 flex items-center justify-center">
              {cart.itemCount}
            </span>
          )}
        </Link>
        {user ? (
          <>
            <Link to="/profile" className="hover:text-brand-accent transition-colors">
              {user.displayName}
            </Link>
            <button onClick={handleLogout} className="hover:text-brand-accent transition-colors">
              Log out
            </button>
          </>
        ) : (
          <>
            <Link to="/login" className="hover:text-brand-accent transition-colors">
              Log in
            </Link>
            <Link
              to="/signup"
              className="bg-brand-accent text-brand-white px-3 py-1.5 rounded-full hover:opacity-90 transition-opacity"
            >
              Sign up
            </Link>
          </>
        )}
      </div>
    </nav>
  )
}
