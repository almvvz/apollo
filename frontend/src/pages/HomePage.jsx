import { useEffect, useState } from 'react'
import * as menuApi from '../api/menu'
import MenuItemCard from '../components/MenuItemCard'
import CustomizationModal from '../components/CustomizationModal'
import { useAuth } from '../context/AuthContext'
import { useCart } from '../context/CartContext'
import { useNavigate } from 'react-router-dom'

export default function HomePage() {
  const [categories, setCategories] = useState([])
  const [items, setItems] = useState([])
  const [activeCategoryId, setActiveCategoryId] = useState(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)
  const [selectedItem, setSelectedItem] = useState(null)

  const { user } = useAuth()
  const { addItem } = useCart()
  const navigate = useNavigate()

  useEffect(() => {
    async function load() {
      try {
        const [cats, menuItems] = await Promise.all([
          menuApi.getCategories(),
          menuApi.getItems(),
        ])
        setCategories(cats)
        setItems(menuItems)
      } catch (err) {
        setError(err.message)
      } finally {
        setLoading(false)
      }
    }
    load()
  }, [])

  const visibleItems = activeCategoryId
    ? items.filter((i) => i.categoryId === activeCategoryId)
    : items

  function handleSelect(item) {
    if (!user) {
      navigate('/login')
      return
    }
    setSelectedItem(item)
  }

  if (loading) return <p className="p-8 text-center text-brand-navy/60">Loading menu…</p>
  if (error) return <p className="p-8 text-center text-red-500">Couldn't load the menu: {error}</p>

  return (
    <div className="p-6 max-w-5xl mx-auto">
      <section className="rounded-card bg-gradient-to-br from-brand-navy to-brand-navy-light text-brand-white px-8 py-10 mb-8 shadow-md">
        <p className="text-sm uppercase tracking-[0.2em] text-brand-white/70 mb-2">Freshly brewed</p>
        <h1 className="text-3xl sm:text-4xl font-bold mb-2">
          {user ? `Hi ${user.displayName}, what's your pick today?` : 'Your daily cup, your way.'}
        </h1>
        <p className="text-brand-white/80 max-w-md">
          Pick a drink, tweak the size and add-ons, and we'll have it ready for you.
        </p>
      </section>

      <h2 className="text-xl font-bold text-brand-navy mb-4">Menu</h2>

      <div className="flex gap-2 mb-6 overflow-x-auto pb-1">
        <button
          onClick={() => setActiveCategoryId(null)}
          className={`px-4 py-1.5 rounded-full text-sm font-medium whitespace-nowrap ${
            activeCategoryId === null
              ? 'bg-brand-navy text-brand-white'
              : 'bg-white text-brand-navy border border-brand-mist'
          }`}
        >
          All
        </button>
        {categories.map((c) => (
          <button
            key={c.id}
            onClick={() => setActiveCategoryId(c.id)}
            className={`px-4 py-1.5 rounded-full text-sm font-medium whitespace-nowrap ${
              activeCategoryId === c.id
                ? 'bg-brand-navy text-brand-white'
                : 'bg-white text-brand-navy border border-brand-mist'
            }`}
          >
            {c.name}
          </button>
        ))}
      </div>

      {visibleItems.length === 0 ? (
        <p className="text-brand-navy/60">No items in this category.</p>
      ) : (
        <div className="grid grid-cols-2 sm:grid-cols-3 lg:grid-cols-4 gap-4">
          {visibleItems.map((item) => (
            <MenuItemCard key={item.id} item={item} onSelect={handleSelect} />
          ))}
        </div>
      )}

      {selectedItem && (
        <CustomizationModal
          item={selectedItem}
          onClose={() => setSelectedItem(null)}
          onConfirm={addItem}
        />
      )}
    </div>
  )
}
