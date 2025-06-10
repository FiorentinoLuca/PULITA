
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
const ulong PQHeap<Data>::initialSize = 10;

template <typename Data>
PQHeap<Data>::PQHeap()
: Vector<Data>(initialSize), heapSize(0) {}

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& box)
: Vector<Data>(box), HeapVec<Data>(box), heapSize(box.Size()) {}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& box)
: Vector<Data>(std::move(box)), HeapVec<Data>(std::move(box)), heapSize(box.Size()) {}

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap& other)
: Vector<Data>(other), heapSize(other.heapSize) {}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap&& other) noexcept
: Vector<Data>(std::move(other))
{
  std::swap(heapSize, other.heapSize);
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
  HeapVec<Data>::operator=(other);
  heapSize = other.heapSize;
  return *this;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
  HeapVec<Data>::operator=(std::move(other));
  std::swap(heapSize, other.heapSize);
  return *this;
}

template <typename Data>
bool PQHeap<Data>::operator==(const PQHeap<Data>& other) const noexcept {
  HeapVec<Data> sx = *this;
  HeapVec<Data> dx = other;
  sx.Sort();
  dx.Sort();
  return sx.SortableVector<Data>::operator==(dx);
}

template <typename Data>
bool PQHeap<Data>::operator!=(const PQHeap<Data>& other) const noexcept {
  return !(*this == other);
}

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
  if (heapSize == 0) {
    throw std::length_error("Heap is empty");
  }
  return Front();
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
  
  if (heapSize == 0) {
    throw std::length_error("Heap is empty");
  }

  if (heapSize == 1) {
    Clear();
    return;
  }

  std::swap((*this)[0], (*this)[heapSize - 1]);
  HeapifyDown(0, heapSize - 2);
  
  --heapSize;
  EnsureCapacity(heapSize);
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  Data tip = Tip();
  RemoveTip();
  return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  EnsureCapacity(heapSize + 1);
  ++heapSize;
  (*this)[heapSize-1] = value;
  HeapifyUp(heapSize - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
  EnsureCapacity(heapSize + 1);
  ++heapSize;
  (*this)[heapSize-1] = std::move(value);
  HeapifyUp(heapSize - 1);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
  
  Data oldValue = (*this)[index];
  (*this)[index] = value;

  if (value > oldValue) {
    HeapifyUp(index);
  } else if (value < oldValue) {
    HeapifyDown(index, heapSize - 1);
  }
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
  
  Data oldValue = (*this)[index];
  (*this)[index] = std::move(value);

  if (value > oldValue) {
    HeapifyUp(index);
  } else if (value < oldValue) {
    HeapifyDown(index, heapSize - 1);
  }
}

template <typename Data>
void PQHeap<Data>::HeapifyUp(ulong child) noexcept {
  
  if (child == 0) return;

  ulong parentIdx, max;
  do {
    parentIdx = parent(child);
    max = GetMax(parentIdx, child);
    if (max == child) {
      std::swap((*this)[parentIdx], (*this)[child]);
      child = parentIdx;
    } 
  } while (child > 0 && max != parentIdx);
}

template <typename Data>
void PQHeap<Data>::EnsureCapacity(ulong dim)
{
  float resizingFactor = 1.5;
  
  if (size < dim) { // | | | | | -> | | | | | | | 
    if (Empty()) {
      Resize(initialSize);
      return;
    }
    Resize(static_cast<ulong>(std::ceil(resizingFactor*size))); // #TODO corrected: resizingFactor*size -> std::ceil(resizingFactor*size)
    return;
  }

  if (heapSize < std::ceil(resizingFactor))
                                    return;

  // |x|x|x|x| | | | | | -> |x|x|x|x| | |
  if (size > static_cast<ulong>(heapSize*resizingFactor*resizingFactor))          
                    Resize(static_cast<ulong>(heapSize*resizingFactor));
}

template <typename Data>
void PQHeap<Data>::Resize(ulong newSize)
{
  if (newSize == 0) {
    this->Vector<Data>::Clear();
  }

  PQHeap<Data> oldPQ(std::move(*this));
  this->buffer = new Data[newSize];
  this->size = newSize;
  heapSize = oldPQ.heapSize;

  oldPQ.Transfer(*this, 0, oldPQ.heapSize, 0);
}

template <typename Data>
void PQHeap<Data>::Clear() noexcept {
  heapSize = 0;
  EnsureCapacity(heapSize);
  return;
}

template <typename Data>
ulong PQHeap<Data>::Size() const noexcept {
  return heapSize;
}

/* ************************************************************************** */

}
