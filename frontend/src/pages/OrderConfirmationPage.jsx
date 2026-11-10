import { useEffect, useState } from 'react'
import { Link, useParams } from 'react-router-dom'
import * as ordersApi from '../api/orders'

export default function OrderConfirmationPage() {
  const { orderId } = useParams()
  const [order, setOrder] = useState(null)
  const [error, setError] = useState(null)

  useEffect(() => {
    ordersApi
      .getOrder(orderId)
      .then((data) => setOrder(data.order))
      .catch((err) => setError(err.message))
  }, [orderId])

  if (error) return <p className="p-8 text-center text-red-500">{error}</p>
  if (!order) return <p className="p-8 text-center text-brand-navy/60">Loading…</p>

  return (
    <div className="p-8 max-w-md mx-auto text-center">
      <div className="text-5xl mb-4">✅</div>
      <h1 className="text-2xl font-bold text-brand-navy mb-2">Order placed!</h1>
      <p className="text-brand-navy/70 mb-6">
        Order #{order.id.slice(0, 8)} — total RM {order.total.toFixed(2)}
      </p>
      <Link to="/" className="text-brand-accent font-medium">
        Back to menu
      </Link>
    </div>
  )
}
