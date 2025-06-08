
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
const ulong PQHeap<Data>::initialSize = 10;

template <typename Data>
void PQHeap<Data>::EnsureCapacity(ulong dim)
{
  float resizingFactor = 1.5;
  
  if (size < dim) { // | | | | | -> | | | | | | | 
    Resize(static_cast<ulong>(resizingFactor*size));
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

  SetVec<Data> oldSet(std::move(*this));
  this->buffer = new Data[newSize];
  this->size = newSize;
  heapSize = oldSet.heapSize;
  head = 0;

  oldSet.Transfer(*this, 0, oldSet.heapSize, 0);
}

/* ************************************************************************** */

}
