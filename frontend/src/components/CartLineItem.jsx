export default function CartLineItem({ item, onUpdateQuantity, onRemove }) {
  return (
    <div className="flex items-center justify-between gap-4 py-4 border-b border-brand-mist">
      <div className="flex-1">
        <h3 className="font-semibold text-brand-navy">{item.nameSnapshot ?? item.name}</h3>
        {item.selectedSizeLabel && (
          <p className="text-sm text-brand-navy/60">Size: {item.selectedSizeLabel}</p>
        )}
        {item.selectedAddOnLabels?.length > 0 && (
          <p className="text-sm text-brand-navy/60">
            Add-ons: {item.selectedAddOnLabels.join(', ')}
          </p>
        )}
      </div>
      <div className="flex items-center gap-2">
        <button
          onClick={() => onUpdateQuantity(item.id, Math.max(1, item.quantity - 1))}
          className="w-7 h-7 rounded-full border border-brand-mist"
        >
          −
        </button>
        <span className="w-6 text-center">{item.quantity}</span>
        <button
          onClick={() => onUpdateQuantity(item.id, item.quantity + 1)}
          className="w-7 h-7 rounded-full border border-brand-mist"
        >
          +
        </button>
      </div>
      <span className="font-medium text-brand-accent w-20 text-right">
        RM {item.lineTotal.toFixed(2)}
      </span>
      <button onClick={() => onRemove(item.id)} className="text-brand-navy/40 hover:text-red-500">
        ✕
      </button>
    </div>
  )
}
