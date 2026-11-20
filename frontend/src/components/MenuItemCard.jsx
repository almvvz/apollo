export default function MenuItemCard({ item, onSelect }) {
  return (
    <button
      onClick={() => onSelect(item)}
      className="group bg-white rounded-card shadow-sm hover:shadow-lg hover:-translate-y-1 transition-all duration-200 text-left p-3 flex flex-col gap-2 border border-brand-mist focus-visible:outline-2 focus-visible:outline-brand-accent"
    >
      <div className="w-full aspect-square rounded-xl bg-brand-mist overflow-hidden flex items-center justify-center">
        {item.imageUrl ? (
          <img
            src={item.imageUrl}
            alt={item.name}
            className="w-full h-full object-cover transition-transform duration-300 group-hover:scale-105"
          />
        ) : (
          <span className="text-sm text-brand-navy/40">No image</span>
        )}
      </div>
      <h3 className="font-semibold text-brand-navy">{item.name}</h3>
      <p className="text-sm text-brand-navy/70 line-clamp-2">{item.description}</p>
      <div className="mt-auto flex items-center justify-between">
        <span className="font-semibold text-brand-accent">RM {item.basePrice.toFixed(2)}</span>
        <span className="w-8 h-8 rounded-full bg-brand-navy text-brand-white flex items-center justify-center text-lg leading-none group-hover:bg-brand-accent transition-colors">
          +
        </span>
      </div>
    </button>
  )
}
