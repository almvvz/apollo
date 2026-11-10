export default function MenuItemCard({ item, onSelect }) {
  return (
    <button
      onClick={() => onSelect(item)}
      className="bg-white rounded-card shadow-sm hover:shadow-md transition-shadow text-left p-4 flex flex-col gap-2 border border-brand-mist"
    >
      <div className="w-full h-32 rounded-lg bg-brand-mist overflow-hidden flex items-center justify-center">
        {item.imageUrl ? (
          <img
            src={item.imageUrl}
            alt={item.name}
            className="w-full h-full object-cover"
          />
        ) : (
          <span className="text-3xl">☕</span>
        )}
      </div>
      <h3 className="font-semibold text-brand-navy">{item.name}</h3>
      <p className="text-sm text-brand-navy/70 line-clamp-2">{item.description}</p>
      <span className="mt-auto font-medium text-brand-accent">
        RM {item.basePrice.toFixed(2)}
      </span>
    </button>
  )
}
