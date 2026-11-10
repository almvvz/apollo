import { apiFetch } from './client'

export function getCart() {
  return apiFetch('/cart')
}

export function addCartItem({ menuItemId, quantity, selectedSizeId, selectedAddOnIds }) {
  return apiFetch('/cart/items', {
    method: 'POST',
    body: JSON.stringify({ menuItemId, quantity, selectedSizeId, selectedAddOnIds }),
  })
}

export function updateCartItem(cartItemId, patch) {
  return apiFetch(`/cart/items/${encodeURIComponent(cartItemId)}`, {
    method: 'PATCH',
    body: JSON.stringify(patch),
  })
}

export function removeCartItem(cartItemId) {
  return apiFetch(`/cart/items/${encodeURIComponent(cartItemId)}`, { method: 'DELETE' })
}

export function clearCart() {
  return apiFetch('/cart', { method: 'DELETE' })
}
