import { useEffect, useState } from 'react'
import { Link } from 'react-router-dom'
import { useAuth } from '../context/AuthContext'
import * as ordersApi from '../api/orders'

export default function ProfilePage() {
  const { user } = useAuth()
  const [orders, setOrders] = useState([])
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)

  useEffect(() => {
    ordersApi
      .getOrders()
      .then((data) => setOrders(data.orders))
      .catch((err) => setError(err.message))
      .finally(() => setLoading(false))
  }, [])

  return (
    <div className="p-6 max-w-2xl mx-auto">
      <h1 className="text-2xl font-bold text-brand-navy mb-1">{user.displayName}</h1>
      <p className="text-brand-navy/60 mb-6">{user.email}</p>

      <h2 className="font-semibold text-brand-navy mb-3">Order history</h2>
      {loading && <p className="text-brand-navy/60">Loading…</p>}
      {error && <p className="text-red-500">{error}</p>}
      {!loading && orders.length === 0 && (
        <p className="text-brand-navy/60">No orders yet.</p>
      )}
      <div className="flex flex-col gap-2">
        {orders.map((order) => (
          <Link
            key={order.id}
            to={`/profile/orders/${order.id}`}
            className="bg-white rounded-card p-4 flex justify-between items-center border border-brand-mist"
          >
            <div>
              <p className="font-medium text-brand-navy">Order #{order.id.slice(0, 8)}</p>
              <p className="text-sm text-brand-navy/60">
                {new Date(order.placedAt).toLocaleString()}
              </p>
            </div>
            <span className="font-semibold text-brand-accent">RM {order.total.toFixed(2)}</span>
          </Link>
        ))}
      </div>
    </div>
  )
}
