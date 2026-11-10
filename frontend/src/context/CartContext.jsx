import { createContext, useCallback, useContext, useEffect, useState } from 'react'
import * as cartApi from '../api/cart'
import { useAuth } from './AuthContext'

const CartContext = createContext(null)

const EMPTY_CART = { items: [], subtotal: 0, itemCount: 0 }

export function CartProvider({ children }) {
  const { user } = useAuth()
  const [cart, setCart] = useState(EMPTY_CART)

  const refresh = useCallback(async () => {
    if (!user) {
      setCart(EMPTY_CART)
      return
    }
    const data = await cartApi.getCart()
    setCart(data)
  }, [user])

  useEffect(() => {
    refresh()
  }, [refresh])

  const addItem = useCallback(
    async (payload) => {
      const data = await cartApi.addCartItem(payload)
      setCart(data)
    },
    [],
  )

  const updateItem = useCallback(async (cartItemId, patch) => {
    const data = await cartApi.updateCartItem(cartItemId, patch)
    setCart(data)
  }, [])

  const removeItem = useCallback(async (cartItemId) => {
    const data = await cartApi.removeCartItem(cartItemId)
    setCart(data)
  }, [])

  const clear = useCallback(async () => {
    await cartApi.clearCart()
    setCart(EMPTY_CART)
  }, [])

  return (
    <CartContext.Provider value={{ cart, refresh, addItem, updateItem, removeItem, clear }}>
      {children}
    </CartContext.Provider>
  )
}

export function useCart() {
  const ctx = useContext(CartContext)
  if (!ctx) throw new Error('useCart must be used within CartProvider')
  return ctx
}
