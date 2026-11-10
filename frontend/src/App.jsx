import { Route, Routes } from 'react-router-dom'
import Navbar from './components/Navbar'
import ProtectedRoute from './components/ProtectedRoute'
import HomePage from './pages/HomePage'
import LoginPage from './pages/LoginPage'
import SignupPage from './pages/SignupPage'
import CartPage from './pages/CartPage'
import CheckoutPage from './pages/CheckoutPage'
import OrderConfirmationPage from './pages/OrderConfirmationPage'
import ProfilePage from './pages/ProfilePage'
import OrderDetailPage from './pages/OrderDetailPage'
import NotFoundPage from './pages/NotFoundPage'

export default function App() {
  return (
    <div className="min-h-screen">
      <Navbar />
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/signup" element={<SignupPage />} />

        <Route element={<ProtectedRoute />}>
          <Route path="/cart" element={<CartPage />} />
          <Route path="/checkout" element={<CheckoutPage />} />
          <Route path="/orders/:orderId/confirmation" element={<OrderConfirmationPage />} />
          <Route path="/profile" element={<ProfilePage />} />
          <Route path="/profile/orders/:orderId" element={<OrderDetailPage />} />
        </Route>

        <Route path="*" element={<NotFoundPage />} />
      </Routes>
    </div>
  )
}
