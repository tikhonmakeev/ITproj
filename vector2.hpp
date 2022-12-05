#ifndef SFML_VECTOR2_HPP
#define SFML_VECTOR2_HPP
namespace sf
{
template <typename T>
class Vector2{
   public:
   Vector2();
   Vector2(T X, T Y);
   template <typename U>
   explicit Vector2(const Vector2<U>& vector);
   T x; 
   T y; 
};
template <typename T>
Vector2<T> operator -(const Vector2<T>& right);
template <typename T>
Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);
template <typename T>
Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);
template <typename T>
Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);
template <typename T>
Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);
template <typename T>
Vector2<T> operator *(const Vector2<T>& left, T right);
template <typename T>
Vector2<T> operator *(T left, const Vector2<T>& right);
template <typename T>
Vector2<T>& operator *=(Vector2<T>& left, T right);
template <typename T>
Vector2<T> operator /(const Vector2<T>& left, T right);
template <typename T>
Vector2<T>& operator /=(Vector2<T>& left, T right);
template <typename T>
bool operator ==(const Vector2<T>& left, const Vector2<T>& right);
template <typename T>
bool operator !=(const Vector2<T>& left, const Vector2<T>& right);
#include <SFML/System/Vector2.inl>
typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;
}
#endif // SFML_VECTOR2_HPP