import { Link, useNavigate } from 'react-router-dom'
import { useCart } from '../context/CartContext'
import CartLineItem from '../components/CartLineItem'

export default function CartPage() {
  const { cart, updateItem, removeItem } = useCart()
  const navigate = useNavigate()

  if (cart.items.length === 0) {
    return (
      <div className="p-8 max-w-2xl mx-auto text-center">
        <h1 className="text-2xl font-bold text-brand-navy mb-2">Your cart is empty</h1>
        <Link to="/" className="text-brand-accent font-medium">
          Browse the menu
        </Link>
      </div>
    )
  }

  return (
    <div className="p-6 max-w-2xl mx-auto">
      <h1 className="text-2xl font-bold text-brand-navy mb-4">Your cart</h1>

      <div>
        {cart.items.map((item) => (
          <CartLineItem
            key={item.id}
            item={item}
            onUpdateQuantity={(id, quantity) => updateItem(id, { quantity })}
            onRemove={removeItem}
          />
        ))}
      </div>

      <div className="flex items-center justify-between mt-6 mb-4">
        <span className="font-semibold text-brand-navy">Subtotal</span>
        <span className="font-bold text-brand-accent">RM {cart.subtotal.toFixed(2)}</span>
      </div>

      <button
        onClick={() => navigate('/checkout')}
        className="w-full bg-brand-accent text-brand-white font-semibold rounded-full py-3"
      >
        Checkout
      </button>
    </div>
  )
}
