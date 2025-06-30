#include "setvec.hpp"

namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
const ulong SetVec<Data>::initialSize = 10;

template <typename Data>
SetVec<Data>::SetVec()
  : Vector<Data>(initialSize), head(0), numElements(0) {}

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& box)
  : Vector<Data>(box.Size()), head(0), numElements(0) {
  InsertAll(box);
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& box)
  : Vector<Data>(box.Size()), head(0), numElements(0) {
  InsertAll(box);
}

template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) 
  : Vector<Data>(other), head(0), numElements(other.numElements) {}

template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other)
  noexcept : SetVec<Data>() {
    *this = std::move(other);
}

template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other)
{

  if (this == &other) return *this;

  SetVec<Data>&& tmp = SetVec(other);
  std::swap(tmp, *this);

  return *this;
}

template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other)
  noexcept {
    this->Vector<Data>::operator= (std::move(other));
    std::swap(other.numElements, numElements);
    std::swap(other.head, head);
  return *this;
}

template <typename Data>
inline bool SetVec<Data>::operator==(const SetVec<Data>& other)
  const noexcept {
    if (numElements != other.numElements)
      return false;
    bool diffAbsence = true;
    for (ulong i = 0; diffAbsence && i < numElements; i++)
    {
      diffAbsence = (other[i] == operator[](i))?(diffAbsence):(false);
    }
  return diffAbsence;
}

template <typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

template <typename Data>
inline const Data& SetVec<Data>::Min()
  const {
    if (Empty()) throw std::length_error("Set is empty");
  return (*this)[0];
}

template <typename Data>
inline Data SetVec<Data>::MinNRemove() {
  if (Empty()) throw std::length_error("Set is empty"); // #TODO corrected: -> if(Empty()) throw std::length_error("SetVec is empty");
  Data& ret = (*this)[0];
  RemoveMin();
  return ret; // std::move(ret);
}

template <typename Data>
inline void SetVec<Data>::RemoveMin() {
  if (Empty()) {
    throw std::length_error("SetVec is empty");
  }
  Shift(0,-1);
  EnsureCapacity(numElements);
}

template <typename Data>
inline const Data& SetVec<Data>::Max()
  const {
    if (Empty()) throw std::length_error("Set is empty");
    return (*this)[numElements - 1];
}

template <typename Data>
inline Data SetVec<Data>::MaxNRemove() 
{
  if (Empty()) throw std::length_error("Set is empty"); // #TODO corrected: -> if(Empty()) throw std::length_error("SetVec is empty");
  Data ret = (*this)[numElements - 1];
  RemoveMax();
  return std::move(ret); //pesimizing
}

template <typename Data>
inline void SetVec<Data>::RemoveMax()
{
  if (numElements == 0) {
    throw std::length_error("Vector is empty");
  }
  Shift(numElements-1,-1);
  EnsureCapacity(numElements);
}

template <typename Data>
inline ulong SetVec<Data>::FindPred(const Data& dat)
{
  int idx = BSearch(dat);
  if (idx == -1 || (*this)[idx] == dat)
                                idx--;
  if (idx < 0)
    throw std::length_error("No predecessor found");

  return idx;
}

template <typename Data>
inline const Data& SetVec<Data>::Predecessor(const Data& dat) const {

  return (*this)[const_cast<SetVec<Data>*>(this)->FindPred(dat)];
}

template <typename Data>
inline Data SetVec<Data>::PredecessorNRemove(const Data& dat) {
  
  ulong idx = FindPred(dat);

  Data pred = std::move((*this)[idx]);
  Shift(idx, -1);
  EnsureCapacity(numElements);

  return pred; // std::move(pred);
}

template <typename Data>
inline void SetVec<Data>::RemovePredecessor(const Data& dat) {
  Shift(FindPred(dat), -1);
  EnsureCapacity(numElements);
}

template <typename Data>
inline ulong SetVec<Data>::FindSucc(const Data& dat)
{
  int idx = BSearch(dat);
  idx++;
  if (idx >= static_cast<int>(numElements))
    throw std::length_error("No successor found");

  return idx;
}

template <typename Data>
inline const Data& SetVec<Data>::Successor(const Data& dat)
  const {
    return (*this)[const_cast<SetVec<Data>*>(this)->FindSucc(dat)];
}

template <typename Data>
inline Data SetVec<Data>::SuccessorNRemove(const Data& dat) {
  
  ulong idx = FindSucc(dat);

  Data ret = std::move((*this)[idx]);
  Shift(idx, -1);
  EnsureCapacity(numElements);

  return ret; // std::move(ret);
}

template <typename Data>
inline void SetVec<Data>::RemoveSuccessor(const Data& dat) {
  Shift(FindSucc(dat), -1);
  EnsureCapacity(numElements);
}

template <typename Data>
bool SetVec<Data>::AttachWithIn(const Data& dat, ulong dim)
{
  int foundIndex = BSearch(dat);

  if (foundIndex != -1 && (*this)[foundIndex] == dat)
                                        return false;

  EnsureCapacity(dim);

  Shift(foundIndex, 1);
  foundIndex = foundIndex+1;

  (*this)[foundIndex] = dat;

  return true;
}

template <typename Data>
bool SetVec<Data>::AttachWithIn(Data&& dat, ulong dim)
{
  int foundIndex = BSearch(dat);

  if (foundIndex != -1 && (*this)[foundIndex] == dat)
                                        return false;

  EnsureCapacity(dim);

  Shift(foundIndex, 1);
  foundIndex = foundIndex+1;

  (*this)[foundIndex] = std::move(dat);

  return true;
}

template <typename Data>
bool SetVec<Data>::Insert(const Data& dat) {
  return AttachWithIn(dat, numElements + 1);
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& dat) {
  return AttachWithIn(std::move(dat), numElements + 1);
}

template <typename Data>
bool SetVec<Data>::InsertAll(const TraversableContainer<Data>& box) {
  bool check = true;
  ulong oldCard = numElements;
  box.Traverse(
    [this, &box, &check, oldCard](const Data&dat)
    {
      check = (AttachWithIn(dat, box.Size()+oldCard) && check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertAll(MappableContainer<Data>&& box) {
  bool check = true;
  ulong oldCard = numElements;
  box.Map(
    [this, &box, &check, oldCard](Data& dat)
    {
      check = (AttachWithIn(std::move(dat), box.Size()+oldCard) && check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertSome(const TraversableContainer<Data>& box) {
  bool check = false;
  ulong oldCard = numElements;
  box.Traverse(
    [this, &box, &check, oldCard](const Data& dat)
    {
      check = (AttachWithIn(dat, box.Size()+oldCard) || check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertSome(MappableContainer<Data>&& box) {
  bool check = false;
  ulong oldCard = numElements;
  box.Map(
    [this, &box, &check, oldCard](Data& dat)
    {
      check = (AttachWithIn(std::move(dat), box.Size()+oldCard) || check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& data) {

  int foundIndex = BSearch(data);

  if (foundIndex == -1 || (*this)[foundIndex] != data)
                                         return false;

  Shift(foundIndex, -1);
  EnsureCapacity(numElements);

  return true;

}

template <typename Data>
const Data& SetVec<Data>::operator[](ulong idx)
  const {
    
    if (idx >= numElements) 
      throw std::out_of_range("Index out of range");
    
  return buffer[mod(idx + head, size)];
}

template <typename Data>
inline bool SetVec<Data>::Exists(const Data& data) const noexcept{
  bool itExists = false;
  int foundIndex = BSearch(data);
  if (foundIndex != -1 && (*this)[foundIndex] == data)
                                      itExists = true;
  return itExists;
}

template <typename Data>
void SetVec<Data>::Clear() 
  noexcept {

    if (size==0)
         return;
    
    numElements = 1;
    RemoveMin();
}

template <typename Data>
inline bool SetVec<Data>::Empty() const noexcept {
  return (numElements == 0);
}

template <typename Data>
ulong SetVec<Data>::Size()
  const noexcept {
    return numElements;
}

template <typename Data>
void SetVec<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = 0; i < numElements; ++i)
    {
        f((*this)[i]);
    }
}

template <typename Data>
void SetVec<Data>::PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = 0; i < numElements; ++i)
    {
        f((*this)[i]);
    }
}

template <typename Data>
void SetVec<Data>::PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun f)
  const {
    for (ulong i = numElements; i > 0; --i)
    {
        f((*this)[i-1]);
    }
}

template <typename Data>
Data& SetVec<Data>::operator[](ulong idx)
{
  return const_cast<Data&>(static_cast<const SetVec<Data>*>(this)->operator[](idx));
}

template <typename Data>
inline const Data& SetVec<Data>::Front() const {
  if (numElements == 0) throw std::length_error("Set is empty");
  return (*this)[0];
}

template <typename Data>
inline const Data& SetVec<Data>::Back() const {
  if (numElements == 0) throw std::length_error("Set is empty");
  return (*this)[numElements - 1];
}

template <typename Data>
void SetVec<Data>::EnsureCapacity(ulong dim)
{
  float resizingFactor = 1.5;
  
  if (size < dim) { // | | | | | -> | | | | | | | 
    
    if (Empty()) {
      Resize(initialSize);
      return;
    }
    Resize( std::max(dim, static_cast<ulong>(std::ceil(resizingFactor*size))) ); // #TODO corrected: resizingFactor*size ->  std::max(dim, static_cast<ulong>(std::ceil(resizingFactor*size)))
    return;
  }

  if (dim>0 || numElements < std::ceil(resizingFactor))
                                       return;

  // |x|x|x|x| | | | | | -> |x|x|x|x| | |
  if (size > static_cast<ulong>(numElements*resizingFactor*resizingFactor))          
                    Resize(static_cast<ulong>(numElements*resizingFactor));
}

template <typename Data>
void SetVec<Data>::Resize(ulong newSize)
{

  if (newSize == 0) {
    this->Vector<Data>::Clear();
  }

  SetVec<Data> oldSet(std::move(*this));
  this->buffer = new Data[newSize];
  this->size = newSize;
  numElements = oldSet.numElements;
  head = 0;

  oldSet.Transfer(*this, 0, oldSet.numElements, 0);
}

template <typename Data>
inline bool SetVec<Data>::isLefter(int idx, int dim)
{
  if (idx >= static_cast<int>(numElements))
    throw std::out_of_range("Index bigger than last element's index");
  if (dim >= 0)
    return (card(0,idx) < card(idx+1,numElements-1));
  return (card(0,idx) < card(idx,numElements-1));
}

template <typename Data>
void SetVec<Data>::LeftShift(int idx, int dim)
{
  ulong leftMargin = std::min(idx+1, static_cast<int>(numElements));
  if (dim>=0)
  {
    numElements = numElements+dim; // la transfer usa Size()
    head = mod(head-dim, size);

    ulong oldIdx = idx+dim;
    Transfer(*this, oldIdx-(leftMargin-1), leftMargin, idx-(leftMargin-1)); 
  }
  else
  {
    ulong leftReminder = std::max(0, dim + static_cast<int>(leftMargin));
    ulong rightReminder = std::max(0, -dim - static_cast<int>(leftMargin)); // overflowing formula

    Transfer(*this, idx+dim/*idx+dim-(leftReminder-1)*/, -leftReminder/*leftReminder*/, idx/*idx-(leftReminder-1)*/);
    numElements = numElements+dim+rightReminder;
    head = mod(head-dim-rightReminder, size);
    RightShift(Empty()?0:mod(-rightReminder, numElements), -rightReminder);
    
  }
}

template <typename Data>
void SetVec<Data>::RightShift(int idx, int dim)
{
  ulong rightMargin = card(idx+1, numElements-1);

  if (dim>=0)
  {
    // la transfer usa Size()
    numElements = numElements+dim;                                             
    Transfer(*this, idx+1+(rightMargin-1), -rightMargin, idx+1+dim+(rightMargin-1)); 
  }
  else
  {
    rightMargin = card(idx, numElements-1);

    ulong rightReminder = std::max(0, dim + static_cast<int>(rightMargin)); 
    ulong leftReminder = std::max(0, -dim - static_cast<int>(rightMargin)); //overflowing formula
                                                                                                  
    Transfer(*this, numElements-1-(rightReminder-1), rightReminder, idx);
    numElements = numElements+dim+leftReminder;
    LeftShift(std::max(0, static_cast<int>(leftReminder)-1), -leftReminder);
  }
}

template <typename Data>
void SetVec<Data>::Shift(int idx, int dim)
{
  if (dim > static_cast<int>(size-numElements) || dim < static_cast<int>(-numElements))
                              throw std::invalid_argument("Non valid shift dimension");

  if (idx < -1 || (idx < 0 && dim<0) || idx >= static_cast<int>(numElements))
                          throw std::length_error("Shift idx out of bounds");

  if (isLefter(idx,dim))
  {
    LeftShift(idx, dim);
    return;
  }
  RightShift(idx, dim);
  
  return;
}

template <typename Data>
inline const Data& SetVec<Data>::getData(const int& idx) 
  const {
    return (*this)[idx];
}

template <typename Data>
inline int SetVec<Data>::Reach(int cur, ulong mov, int &predCur) 
  const {
    cur = cur + mov;
    predCur = predCur + card(predCur, cur-2);
  return cur;
}

template <typename Data>
inline int SetVec<Data>::BSearch(const Data &dat)
  const {
    int tmp;
  return Set<Data>::template BSearch<SetVec<Data>, int>(dat, -1, 0, numElements, tmp);
}

/* ************************************************************************** */

}
