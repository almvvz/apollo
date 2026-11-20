import { useMemo, useState } from 'react'

export default function CustomizationModal({ item, onClose, onConfirm }) {
  const [sizeId, setSizeId] = useState(item.sizes?.[0]?.id ?? null)
  const [addOnIds, setAddOnIds] = useState([])
  const [quantity, setQuantity] = useState(1)
  const [submitting, setSubmitting] = useState(false)

  const total = useMemo(() => {
    const sizeDelta = item.sizes?.find((s) => s.id === sizeId)?.priceDelta ?? 0
    const addOnDelta = item.addOns
      .filter((a) => addOnIds.includes(a.id))
      .reduce((sum, a) => sum + a.priceDelta, 0)
    return (item.basePrice + sizeDelta + addOnDelta) * quantity
  }, [item, sizeId, addOnIds, quantity])

  function toggleAddOn(id) {
    setAddOnIds((prev) => (prev.includes(id) ? prev.filter((x) => x !== id) : [...prev, id]))
  }

  async function handleConfirm() {
    setSubmitting(true)
    try {
      await onConfirm({
        menuItemId: item.id,
        quantity,
        selectedSizeId: sizeId,
        selectedAddOnIds: addOnIds,
      })
      onClose()
    } finally {
      setSubmitting(false)
    }
  }

  return (
    <div
      className="fixed inset-0 bg-brand-navy/40 backdrop-blur-sm flex items-center justify-center p-4 z-50"
      onClick={onClose}
    >
      <div
        className="animate-pop-in bg-white rounded-card shadow-2xl max-w-md w-full max-h-[90vh] overflow-y-auto flex flex-col gap-4"
        onClick={(e) => e.stopPropagation()}
      >
        {item.imageUrl && (
          <img
            src={item.imageUrl}
            alt={item.name}
            className="w-full h-48 object-cover rounded-t-card"
          />
        )}
        <div className="px-6 flex items-start justify-between">
          <div>
            <h2 className="text-lg font-bold text-brand-navy">{item.name}</h2>
            <p className="text-sm text-brand-navy/70">{item.description}</p>
          </div>
          <button onClick={onClose} className="text-brand-navy/50 hover:text-brand-navy">
            ✕
          </button>
        </div>

        <div className="px-6 pb-6 flex flex-col gap-4">
          {item.sizes?.length > 0 && (
            <fieldset>
              <legend className="text-sm font-semibold text-brand-navy mb-2">Size</legend>
              <div className="flex gap-2">
                {item.sizes.map((s) => (
                  <label
                    key={s.id}
                    className={`px-3 py-1.5 rounded-full border text-sm cursor-pointer ${
                      sizeId === s.id
                        ? 'bg-brand-navy text-brand-white border-brand-navy'
                        : 'border-brand-mist text-brand-navy'
                    }`}
                  >
                    <input
                      type="radio"
                      name="size"
                      value={s.id}
                      checked={sizeId === s.id}
                      onChange={() => setSizeId(s.id)}
                      className="hidden"
                    />
                    {s.label}
                    {s.priceDelta > 0 && ` +${s.priceDelta.toFixed(2)}`}
                  </label>
                ))}
              </div>
            </fieldset>
          )}

          {item.addOns?.length > 0 && (
            <fieldset>
              <legend className="text-sm font-semibold text-brand-navy mb-2">Add-ons</legend>
              <div className="flex flex-col gap-1.5">
                {item.addOns.map((a) => (
                  <label key={a.id} className="flex items-center gap-2 text-sm text-brand-navy">
                    <input
                      type="checkbox"
                      checked={addOnIds.includes(a.id)}
                      onChange={() => toggleAddOn(a.id)}
                    />
                    {a.label} <span className="text-brand-navy/60">+{a.priceDelta.toFixed(2)}</span>
                  </label>
                ))}
              </div>
            </fieldset>
          )}

          <div className="flex items-center gap-3">
            <span className="text-sm font-semibold text-brand-navy">Qty</span>
            <button
              onClick={() => setQuantity((q) => Math.max(1, q - 1))}
              className="w-8 h-8 rounded-full border border-brand-mist"
            >
              −
            </button>
            <span className="w-6 text-center">{quantity}</span>
            <button
              onClick={() => setQuantity((q) => q + 1)}
              className="w-8 h-8 rounded-full border border-brand-mist"
            >
              +
            </button>
          </div>

          <button
            onClick={handleConfirm}
            disabled={submitting}
            className="bg-brand-accent text-brand-white font-semibold rounded-full py-3 shadow-md hover:brightness-110 transition disabled:opacity-60"
          >
            {submitting ? 'Adding…' : `Add to cart — RM ${total.toFixed(2)}`}
          </button>
        </div>
      </div>
    </div>
  )
}
