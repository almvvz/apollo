import { apiFetch } from './client'

export function getCategories() {
  return apiFetch('/menu/categories')
}

export function getItems(categoryId) {
  const qs = categoryId ? `?categoryId=${encodeURIComponent(categoryId)}` : ''
  return apiFetch(`/menu/items${qs}`)
}

export function getItem(itemId) {
  return apiFetch(`/menu/items/${encodeURIComponent(itemId)}`)
}
