import { useEffect, useState } from 'react'
import { Link, useParams } from 'react-router-dom'
import * as ordersApi from '../api/orders'

export default function OrderDetailPage() {
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
    <div className="p-6 max-w-2xl mx-auto">
      <Link to="/profile" className="text-sm text-brand-accent">
        ← Back to profile
      </Link>
      <h1 className="text-2xl font-bold text-brand-navy mt-2 mb-1">
        Order #{order.id.slice(0, 8)}
      </h1>
      <p className="text-brand-navy/60 mb-6">{new Date(order.placedAt).toLocaleString()}</p>

      <div className="bg-white rounded-card p-4">
        {order.items.map((item, idx) => (
          <div key={idx} className="flex justify-between py-1 text-sm">
            <span>
              {item.quantity}× {item.nameSnapshot}
              {item.selectedSizeLabel ? ` (${item.selectedSizeLabel})` : ''}
            </span>
            <span>RM {item.lineTotal.toFixed(2)}</span>
          </div>
        ))}
        <div className="flex justify-between text-sm pt-2 mt-2 border-t border-brand-mist">
          <span>Subtotal</span>
          <span>RM {order.subtotal.toFixed(2)}</span>
        </div>
        <div className="flex justify-between text-sm">
          <span>Tax</span>
          <span>RM {order.tax.toFixed(2)}</span>
        </div>
        <div className="flex justify-between font-bold text-brand-navy">
          <span>Total</span>
          <span>RM {order.total.toFixed(2)}</span>
        </div>
      </div>
    </div>
  )
}
