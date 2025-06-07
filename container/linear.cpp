
namespace lasd {

/* ************************************************************************** */
// ...

/* ***************************LinearContainer********************************* */

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& other) 
  const noexcept {
    if (Size() != other.Size())
                             return false;
    bool diffAbsence = true;
    for (ulong i = 0; diffAbsence && i < size && i < other.size; i++)
    {
      diffAbsence = (other[i] == operator[](i))?(diffAbsence):(false);
    }
    return diffAbsence;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& other)
  const noexcept {
    return !(other == *this);
}

template <typename Data>
inline const Data &LinearContainer<Data>::Front()
  const {
    return operator[](0);
}

template <typename Data>
inline const Data &LinearContainer<Data>::Back()
  const {
    return operator[](size - 1);
}

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun f)
  const {
    enum mode {PRE_ORDER, POST_ORDER};
    switch (PRE_ORDER)
    {
    case PRE_ORDER:
      PreOrderTraverse(f);
      break;
    case POST_ORDER:
      PostOrderTraverse(f);
      break;
    } 
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun f)
  const {
    if (Container::Empty())
                    return;

    for (ulong i = 0; i < size; i++)
    {
      f(operator[](i));
    }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun f)
  const {
    if (Container::Empty())
                    return;

    for (ulong i = size; i != 0; i--){
      f((operator[])(i-1));
    }
}

/* ***************************MutableLinearContainer********************************* */

// Non Mutable

template <typename Data>
inline Data& MutableLinearContainer<Data>::operator[](ulong index)
{
  return const_cast<Data&>(static_cast<const MutableLinearContainer<Data>*>
                                                (this)->operator[](index));
}

template <typename Data>
inline const Data& MutableLinearContainer<Data>::Front()
  const {
    return (*static_cast<const MutableLinearContainer<Data>*>(this))
                                                     .operator[](0);
}

// Mutable

template <typename Data>
inline const Data& MutableLinearContainer<Data>::Back()
  const {
    return (*static_cast<const MutableLinearContainer<Data>*>(this))
                                                .operator[](size-1);
}

template <typename Data>
inline Data& MutableLinearContainer<Data>::Front()
{
  return (*this)[0];
}

template <typename Data>
inline Data& MutableLinearContainer<Data>::Back()
{
  return (*this).operator[](size-1);
}

template <typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun f)
{
  enum mode {PRE_ORDER, POST_ORDER};
  switch (PRE_ORDER)
  {
  case PRE_ORDER:
    PreOrderMap(f);
    break;
  case POST_ORDER:
    PostOrderMap(f);
    break;
  } 
}

template<typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun f)
{
  for (ulong i = 0; i < size; ++i)
  {
      f((*this)[i]);
  }
}

template<typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun f)
{
  for (ulong i = size; i != 0; i--){
    f((operator[])(i-1));
  }
}

/* ***************************SortableLinearContainer*********************** */

template<typename Data>
void SortableLinearContainer<Data>::Sort()
  noexcept {
    InsertionSort();
}

template<typename Data>
void SortableLinearContainer<Data>::InsertionSort()
  noexcept {
    Data x;
    ulong i;
    for (ulong j = 1; j < size; j++)
    {
        x = (*this)[j];
        i = j;
        while (i > 0 && (*this)[i-1] > x)
        {
            (*this)[i]=(*this)[i-1];
            i--;
        }
        (*this)[i] = x;
    }
}

/* ************************************************************************** */

}
