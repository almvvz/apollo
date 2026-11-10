import { Link } from 'react-router-dom'

export default function NotFoundPage() {
  return (
    <div className="p-8 text-center">
      <h1 className="text-2xl font-bold text-brand-navy mb-2">Page not found</h1>
      <Link to="/" className="text-brand-accent font-medium">
        Back to menu
      </Link>
    </div>
  )
}
