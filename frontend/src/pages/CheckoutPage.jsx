import { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { useCart } from '../context/CartContext'
import * as ordersApi from '../api/orders'

export default function CheckoutPage() {
  const { cart, refresh } = useCart()
  const [submitting, setSubmitting] = useState(false)
  const [error, setError] = useState(null)
  const navigate = useNavigate()

  async function handlePlaceOrder() {
    setSubmitting(true)
    setError(null)
    try {
      const { order } = await ordersApi.placeOrder()
      await refresh()
      navigate(`/orders/${order.id}/confirmation`)
    } catch (err) {
      setError(err.message)
    } finally {
      setSubmitting(false)
    }
  }

  return (
    <div className="p-6 max-w-2xl mx-auto">
      <h1 className="text-2xl font-bold text-brand-navy mb-4">Checkout</h1>

      <div className="bg-white rounded-card p-4 mb-6">
        {cart.items.map((item) => (
          <div key={item.id} className="flex justify-between py-1 text-sm">
            <span>
              {item.quantity}× {item.nameSnapshot ?? item.name}
            </span>
            <span>RM {item.lineTotal.toFixed(2)}</span>
          </div>
        ))}
        <div className="flex justify-between font-bold text-brand-navy mt-2 pt-2 border-t border-brand-mist">
          <span>Subtotal</span>
          <span>RM {cart.subtotal.toFixed(2)}</span>
        </div>
      </div>

      {error && <p className="text-red-500 text-sm mb-3">{error}</p>}

      <button
        onClick={handlePlaceOrder}
        disabled={submitting || cart.items.length === 0}
        className="w-full bg-brand-navy text-brand-white font-semibold rounded-full py-3 disabled:opacity-60"
      >
        {submitting ? 'Placing order…' : 'Place order'}
      </button>
    </div>
  )
}
