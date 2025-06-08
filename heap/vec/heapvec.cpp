
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& box) 
  : Vector<Data>(box), SortableVector<Data>(box) {
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& box) 
  : Vector<Data>(box), SortableVector<Data>(std::move(box)) {
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec& other) 
  : Vector<Data>(other), SortableVector<Data>(other) {}

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec&& other) noexcept 
  : Vector<Data>(std::move(other)), SortableVector<Data>(std::move(other)) {}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  SortableVector<Data>::operator=(other);
  return *this;
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
  SortableVector<Data>::operator=(std::move(other));
  return *this;
}

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
  return SortableVector<Data>::operator==(other);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
  return SortableVector<Data>::operator!=(other);
}

template <typename Data>
inline bool HeapVec<Data>::IsHeap() const noexcept {
  if (Size() == 0) return true;
  ulong max;
  for (ulong i = 0; i < static_cast<ulong>(parent(Size()-1)); ++i) {
        max = GetMax(i, Size()-1);
    if (max != i) {
      return false;
    }
  }
  return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() noexcept {
  if (Size() == 0) return;
  for (long i = parent(Size() - 1); i >= 0; --i) {
    HeapifyDown(i, Size() - 1);
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong root, ulong heapEnd) noexcept {
  ulong max = GetMax(root, heapEnd);
  if (max != root) {
    std::swap((*this)[root], (*this)[max]);
    HeapifyDown(max, heapEnd);
  }
}

template <typename Data>
inline ulong HeapVec<Data>::GetMax(ulong root, ulong heapEnd) const noexcept {
  ulong max = root;
  if (left(root) <= heapEnd && (*this)[left(root)] > (*this)[max])
                                                 max = left(root);
  if (right(root) <= heapEnd && (*this)[right(root)] > (*this)[max])
                                                  max = right(root);
  return max;
}

template <typename Data>
inline int HeapVec<Data>::parent(ulong i) noexcept {
  return ((i+1)>>1) - 1;
}

template <typename Data>
inline ulong HeapVec<Data>::left(ulong i) noexcept {
  return 2 * (i + 1) - 1;
}

template <typename Data>
inline ulong HeapVec<Data>::right(ulong i) noexcept {
  return 2 * (i + 1);
}

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
  if (Size() <= 1) return;
  HeapSort();
}

template <typename Data>
void HeapVec<Data>::HeapSort() noexcept {
  if (Size() <= 1) return;
  Heapify();
  for (ulong i = Size()-1; i > 0; --i) {
    std::swap((*this)[0], (*this)[i]);
    HeapifyDown(0, i-1);
  }
}

template <typename Data>
void HeapVec<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = 0; i < Size(); ++i)
    {
        f((*this)[i]);
    }
}

template <typename Data>
void HeapVec<Data>::PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = 0; i < Size(); ++i)
    {
        f((*this)[i]);
    }
}

template <typename Data>
void HeapVec<Data>::PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = Size(); i > 0; --i)
    {
        f((*this)[i-1]);
    }
}


/* ************************************************************************** */

}
