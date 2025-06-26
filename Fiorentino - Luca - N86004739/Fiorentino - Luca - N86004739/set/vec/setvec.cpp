#include "setvec.hpp"

namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
const ulong SetVec<Data>::initialSize = 10;

template <typename Data>
SetVec<Data>::SetVec()
  : Vector<Data>(initialSize), numElements(0) {}

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& box)
  : Vector<Data>(box.Size()) {

  box.Traverse(
    [this](const Data &dat)
    {
      Insert(dat);
    }
  );
  
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& box)
  : Vector<Data>(box.Size()) {

  box.Map(
    [this](Data& dat)
    {
      Insert(std::move(dat));
    }
  );
}

template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) 
  : Vector<Data>(other), numElements(other.numElements) {}

template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other)
  noexcept {
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
  return ret;
}

template <typename Data>
inline void SetVec<Data>::RemoveMin() {
  if (numElements == 0) {
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
  return std::move(ret);
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

  return pred;
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

  return ret;
}

template <typename Data>
inline void SetVec<Data>::RemoveSuccessor(const Data& dat) {
  Shift(FindSucc(dat), -1);
  EnsureCapacity(numElements);
}

template <typename Data>
bool SetVec<Data>::Insert(const Data& dat) {
  /*
  int foundIndex = BSearch(dat);

  if (foundIndex != -1 && (*this)[foundIndex] == dat)
                                        return false;

  EnsureCapacity(numElements + 1);

  Shift(foundIndex, 1);
  foundIndex = foundIndex+1;

  (*this)[foundIndex] = dat;

  return true;
  */
 
  return AttachWithIn(dat, numElements + 1);
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
bool SetVec<Data>::Insert(Data&& dat) {
  /*
    int foundIndex = BSearch(dat);

    if (foundIndex != -1 && (*this)[foundIndex] == dat) 
                                          return false;

    EnsureCapacity(numElements + 1);

    Shift(foundIndex, 1);
    foundIndex = foundIndex+1;

    (*this)[foundIndex] = std::move(dat);

  return true;
  */
  return AttachWithIn(std::move(dat), numElements + 1);
}

template <typename Data>
bool SetVec<Data>::InsertAll(const TraversableContainer<Data>& box) {
  bool check = true;
  box.Traverse(
    [this, &box, &check](const Data&dat)
    {
      check = (AttachWithIn(dat, box.Size()) && check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertAll(MappableContainer<Data>&& box) {
  bool check = true;
  box.Map(
    [this, &box, &check](Data& dat)
    {
      check = (AttachWithIn(std::move(dat), box.Size()) && check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertSome(const TraversableContainer<Data>& box) {
  bool check = false;
  box.Traverse(
    [this, &box, &check](const Data& dat)
    {
      check = (AttachWithIn(dat, box.Size()) || check);
    }
  );
  return check;
}

template <typename Data>
bool SetVec<Data>::InsertSome(MappableContainer<Data>&& box) {
  bool check = false;
  box.Map(
    [this, &box, &check](Data& dat)
    {
      check = (AttachWithIn(std::move(dat), box.Size()) || check);
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
    }
    Resize( std::max(dim, static_cast<ulong>(std::ceil(resizingFactor*size))) ); // #TODO corrected: resizingFactor*size ->  std::max(dim, static_cast<ulong>(std::ceil(resizingFactor*size)))
    return;
  }

  if (numElements < std::ceil(resizingFactor))
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
void SetVec<Data>::Transfer(SetVec<Data> &receiver, ulong srcStart, int grouping, ulong dstStart)
{

  // if (std::abs(grouping) > std::min(numElements, receiver.numElements))
  //                    throw std::invalid_argument("non valid grouping");

  // if (Set<Data>::card(dstStart, dstStart + std::abs(grouping)-1)<=receiver.size 
  //   && Set<Data>::card(srcStart, srcStart + std::abs(grouping)-1)<=size) {
    
  //   int sign = (grouping < 0) ? -1 : 1;

  //   ulong srcIndex, dstIndex;
  //   for (int i = grouping; std::abs(i) > 0; i=sign*(std::abs(i)-1)) {

  //     srcIndex=mod(srcStart+i-sign, numElements);
  //     dstIndex=mod(dstStart+i-sign, receiver.numElements);

  //     receiver.buffer[mod(dstIndex+receiver.head, receiver.size)] = std::move((*this).buffer[mod(srcIndex+head, size)]);
  //   }

  // } else {
  //   throw std::length_error("Index bigger than last element's index");
  // }

  this->Vector<Data>::Transfer(receiver, srcStart, grouping, dstStart);
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
void SetVec<Data>::ShiftLeft(int idx, int dim)
{
  ulong leftMargin = std::min(idx+1, static_cast<int>(numElements));
  if (dim>=0)
  {
    numElements = numElements+dim; // la transfer usa Size()
    head = mod(head-dim, size);


    // Traverse set: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, fine
    // Shift(3,2)           {     lem     }
    // Traverse set: 0 , 1 , 2 , 3 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , fine
    //                              { dim }

    // Traverse set: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, fine
    // Shift(1,3)                   {lem}
    // Traverse set:  0 , 1 , 0 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , fine
    //                       {   dim   }

                            // {                        oldNumElements+dim                        }
                            //                                     {        } lefMarg <
                            //                   {override|                 } lefMarg >
    ulong oldIdx = idx+dim; //  0,            ...         idx+1,  ... oldIdx, ... oldIdx+1+rightMargin-1
                            //                            {       dim       }
                            //                   {        } <
                            //  {xxxxxxxx<lefMarg>xxxxxxxx} >    Per questo si fa dal esterno al interno
    Transfer(*this, oldIdx-(leftMargin-1), leftMargin, idx-(leftMargin-1)); 
  }
  else
  {
    // |leftMargin, -dim-1|;
    //   |-dim, leftMargin|;
    ulong leftReminder = std::max(0, dim + static_cast<int>(leftMargin));
    ulong rightReminder = std::max(0, -dim - static_cast<int>(leftMargin)); // overflowing formula

                                                 //                      |||||||||   : leftMargin
    //                                                                       |||||   : -dim
    //                                                                               : rightReminder

                                               //                            |||||   : leftMargin
    //                                                                    ||||||||   : -dim
    //                                                                    |||        : rightReminder    

    Transfer(*this, idx+dim/*idx+dim-(leftReminder-1)*/, -leftReminder/*leftReminder*/, idx/*idx-(leftReminder-1)*/);
    numElements = numElements+dim+rightReminder;
    head = mod(head-dim-rightReminder, size);
    ShiftRight(Empty()?0:mod(-rightReminder, numElements), -rightReminder);

                                                                                  // Regola d' oro: 
                                            //    per il grouping della transfer sempre dal estremo 
                                            // vicino a la zona senza, a quella con, binding logico

                                            // un po come l'igiene intima...

    /*
    
      Sequenza per capire = idx-(m+(m-1)),... idx-(m-(m-m)),  idx-(m-1), ... idx-(m-m)
                            idx-(2m + 1) ,... idx-(m)      ,  idx-(m+1), ... idx-(0)

                              (idx+dim, -card(0,idx+dim), idx)
    Transfer(*this, idx+dim-(card(0,idx+dim)-1), card(0,idx+dim), idx-(card(0,idx+dim)-1)); 
    numElements = numElements+dim+rightReminder; // numElements+dim+reminder
    head = mod(head-dim-rightReminder, size); // head-dim+reminder
    ShiftRight(mod(-rightReminder, numElements), -rightReminder);

    */
    
  }
}

template <typename Data>
void SetVec<Data>::ShiftRight(int idx, int dim)
{
  ulong rightMargin = card(idx+1, numElements-1);

  if (dim>=0)
  {

    // la transfer usa Size()
    numElements = numElements+dim;                                             
    Transfer(*this, idx+1+(rightMargin-1), -rightMargin, idx+1+dim+(rightMargin-1)); 
                                                                                    //{                        dim                       }
                                                    // idx+1, ... idx+1+rightMargin-1, idx+1+rightMargin-1+1, ... idx+1+rightMargin-1+dim, ... idx+1+2*rightMargin+dim-1
                                                    // idx+1, ... oldNumElements-1          // sotto lo sketch della dimostrazione
                                                    // {   (idx+1+rm-1-(idx+1))+1   }       // che il grouping e corretto per arrivare con lo estremo al ultimo elemento
                                                    // {           rm-1+1           }

    /*
    
  if (dim>=0)
  {
    idx = idx+1;
    numElements = numElements+dim;
    Transfer(*this, idx, card(idx, numElements-1-dim), idx+dim);
  }
    
    */
  }
  else
  {
    rightMargin = card(idx, numElements-1);

    ulong rightReminder = std::max(0, dim + static_cast<int>(rightMargin)); 
    ulong leftReminder = std::max(0, -dim - static_cast<int>(rightMargin)); //overflowing formula
                                                                                                  
    Transfer(*this, numElements-1-(rightReminder-1), rightReminder, idx); // (idx+dim, -card(0,idx+dim), idx)
    numElements = numElements+dim+leftReminder;
    ShiftLeft(std::max(0, static_cast<int>(leftReminder)-1), -leftReminder);
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
    ShiftLeft(idx, dim);
    return;
  }
  ShiftRight(idx, dim);

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

    // {
    //   ulong delta = card(lIdx, rIdx);
    //   if (delta == 0) return;
    //   int mid = lIdx + std::ceil(float(delta)/2)-1;
    //   if (mid > lIdx)
    //     recursiveInOrder(box, f, lIdx, mid-1);
    //   f(box[mid]);
    //   if (mid < rIdx)
    //     recursiveInOrder(box, f, mid+1, rIdx);
    //   return;
    // };

/* ************************************************************************** */

}
