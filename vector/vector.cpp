
namespace lasd {

/* ************************************************************************** */

// ...

/* ********************************Vector*************************** */

template <typename Data>
Vector<Data>::Vector()
  : Vector(0) {}

template <typename Data>
Vector<Data>::Vector(ulong dim)
{
  size = dim;
  if (size > 0)
      buffer = new Data[size]{};
  else
    buffer = nullptr;
}

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& box)
  : Vector(box.Size()) {
  int i = 0;
  box.Traverse(
    [this, &i](const Data& dat)
    {
      buffer[i] = dat;
      i++;
    }
  );
}

template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& box)
  : Vector(box.Size()) {
  int i = 0;
  box.Map(
    [this, &i](Data& dat)
    {
      buffer[i] = std::move(dat);
      i++;
    }
  );
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& other)
  : Vector(0) {
  *this = other;
}

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& other)
  noexcept : Vector(0) {
    *this = std::move(other);
}

template <typename Data>
Vector<Data>::~Vector()
{
  Clear();
}

template <typename Data>
inline Vector<Data>& Vector<Data>::operator=(const Vector<Data>& other)
{
  if (this == &other) return *this;

  EnsureCapacity(other.size);
  int i = 0;
  other.Traverse(
    [this, &i](const Data& dat)
    {
      buffer[i] = dat;
      i++;
    }
  );
  return *this;
}

template<typename Data>
inline Vector<Data>& Vector<Data>::operator=(Vector<Data>&& other)
  noexcept {
    std::swap(size, other.size);
    std::swap(buffer, other.buffer);
    return *this;
}

template<typename Data>
inline bool Vector<Data>::operator==(const Vector<Data>& other)
  const noexcept {
    return LinearContainer<Data>::operator==(other);
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& other)
  const noexcept {
    return LinearContainer<Data>::operator!=(other);
}

template <typename Data>
inline Data& Vector<Data>::operator[](ulong idx)
{
  if (idx >= size)
    throw std::out_of_range("Index bigger than last element's index");
  return (*this).buffer[idx];
}

template <typename Data>
inline Data& Vector<Data>::Front()
{
  if (Empty())
    throw std::length_error("Invalid access to empty vector");
  return (*this).MutableLinearContainer<Data>::Front();
}

template <typename Data>
inline Data& Vector<Data>::Back()
{
  if (Empty())
    throw std::length_error("Invalid access to empty vector");
  return (*this).MutableLinearContainer<Data>::Back();
}

template <typename Data>
inline const Data& Vector<Data>::operator[](ulong idx)
  const {
    if (idx >= size)
      throw std::out_of_range("Index bigger than last element's index");
  return this->buffer[idx];
}

template <typename Data>
inline const Data& Vector<Data>::Front()
  const {
    if (Empty())
      throw std::length_error("Invalid access to empty vector");
    return (*this).MutableLinearContainer<Data>::Front();
}

template <typename Data>
inline const Data& Vector<Data>::Back()
  const {
    if (Empty())
      throw std::length_error("Invalid access to empty vector");
    return (*this).MutableLinearContainer<Data>::Back();
}

template <typename Data>
inline void Vector<Data>::Resize(ulong newSize)
{
  if (0 == newSize)
           Clear();
  else {
    Vector<Data> newVector(newSize);
    this->Transfer(newVector, 0, std::min(size, newVector.size), 0);
    *this = std::move(newVector);
  }
}

template <typename Data>
void Vector<Data>::Clear()
  noexcept {
    delete[] buffer;
    buffer = nullptr;
    size = 0;
}

template <typename Data>
inline void Vector<Data>::EnsureCapacity(ulong dim)
{
  if (size != dim)
    *this = Vector(dim);
}

template <typename Data>
inline ulong Vector<Data>::mod(int x, int m) {
  return static_cast<ulong>(((x%m) + m)%m);
}

template <typename Data>
inline void Vector<Data>::Transfer(Vector<Data> &receiver, ulong srcStart, int grouping, ulong dstStart)
{
  if (std::abs(grouping) > std::min(Size(), receiver.Size()))
    throw std::invalid_argument("non valid grouping");
    
  int sign = (grouping < 0) ? -1 : 1;

  ulong srcIndex, dstIndex;
  for (int i = grouping; std::abs(i) > 0; i=sign*(std::abs(i)-1)) {

    srcIndex=mod(srcStart+i-sign, Size());
    dstIndex=mod(dstStart+i-sign, receiver.Size());

    receiver[dstIndex] = std::move((*this)[srcIndex]);
  }

}

/* ***************************SortableVector********************************* */

template <typename Data>
SortableVector<Data>::SortableVector(ulong dim)
  : Vector<Data>(dim) {}

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data>& box)
  : Vector<Data>(box) {}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data>&& box)
  : Vector<Data>(std::move(box)) {}

template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data>& other)
  : Vector<Data>(other) {}

template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data>&& other)
  noexcept : Vector<Data>(std::move(other)) {}

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& other)
{
  Vector<Data>::operator=(other);
  return *this;
}

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& other)
  noexcept {
    Vector<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

}
