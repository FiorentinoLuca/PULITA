
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
SetLst<Data>::SetLst()
  : List<Data>() {}

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> &box)
{
  box.Traverse(
    [this](const Data &dat)
    {
        Insert(dat);
    }
  );
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> &&box)
{
  box.Map(
    [this](Data &dat)
    {
        Insert(std::move(dat));
    }
  );
}

template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data> &other)
{
  (*this) = other;
}

template <typename Data>
SetLst<Data>::SetLst(SetLst<Data> &&other) noexcept
{
  (*this) = std::move(other);
}

template <typename Data>
SetLst<Data> &SetLst<Data>::operator=(const SetLst<Data>& other)
{
  if (other.Empty())
  {
    Clear();
    return *this;
  }
  head = other.Clone(tail);

  return *this;
}

template <typename Data>
SetLst<Data> &SetLst<Data>::operator=(SetLst<Data> &&other) noexcept
{
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->size, other.size);
  return *this;
}

template <typename Data>
inline bool SetLst<Data>::operator==(const SetLst<Data> &other) const noexcept
{
  return List<Data>::operator==(other);
}

template <typename Data>
inline bool SetLst<Data>::operator!=(const SetLst<Data> &other) const noexcept
{
  return List<Data>::operator!=(other);
}

template <typename Data>
inline const Data& SetLst<Data>::Min()
  const {
    return List<Data>::Front();
}

template <typename Data>
inline Data SetLst<Data>::MinNRemove() {
  return List<Data>::FrontNRemove();
}

template <typename Data>
inline void SetLst<Data>::RemoveMin() {
  List<Data>::RemoveFromFront();
}

template <typename Data>
inline const Data& SetLst<Data>::Max()
  const {
    return List<Data>::Back();
}

template <typename Data>
inline Data SetLst<Data>::MaxNRemove() {
  return List<Data>::BackNRemove();
}

template <typename Data>
inline void SetLst<Data>::RemoveMax() {
  List<Data>::RemoveFromBack();
}

template <typename Data>
typename List<Data>::Node** SetLst<Data>::FindPred(const Data &dat)
{
  Node** ret;
  Set<Data>::template BSearch<SetLst<Data>, Node**>(dat, nullptr, &head, size, ret);

  if (ret == nullptr)
    throw std::length_error("No predecessor found");

  return ret;
}

template <typename Data>
inline const Data& SetLst<Data>::Predecessor(const Data& dat) const {

  return (*const_cast<SetLst<Data>*>(this)->FindPred(dat))->key;
}

template <typename Data>
inline Data SetLst<Data>::PredecessorNRemove(const Data& dat) {
  
  Node** pPred2Nxt = FindPred(dat);
  Data ret = std::move((*pPred2Nxt)->key);

  Node *x = (*pPred2Nxt)->next;
  if (x == head)
  {
    List<Data>::RemoveFromFront();
    return ret;
  }
  else if (x == tail) {
    List<Data>::RemoveFromBack();
    return ret;
  }

  (*pPred2Nxt)->next = (*pPred2Nxt)->next->next;
  size--;
  delete x;

  return ret;
}

template <typename Data>
inline void SetLst<Data>::RemovePredecessor(const Data& dat) {
  PredecessorNRemove(dat);
}

template <typename Data>
typename List<Data>::Node** SetLst<Data>::FindSucc(const Data &dat)
{
  Node** ret = BSearch(dat);

  if (Empty() || (ret != nullptr && *ret == tail))
    throw std::length_error("No successor found");

  return ret;
}

template <typename Data>
inline const Data& SetLst<Data>::Successor(const Data& dat)
  const {
    Node** pSucc2Nxt = const_cast<SetLst<Data>*>(this)->FindSucc(dat);
    if (pSucc2Nxt == nullptr)
      pSucc2Nxt = &const_cast<SetLst<Data>*>(this)->head;
  return (*pSucc2Nxt)->key;
}

template <typename Data>
inline Data SetLst<Data>::SuccessorNRemove(const Data& dat) {
  
  Node** pSucc2Nxt = FindSucc(dat);
  if (pSucc2Nxt == nullptr)
         pSucc2Nxt = &head;

  Data ret = std::move((*pSucc2Nxt)->key);

  Node *x = *pSucc2Nxt;
  if (x == head)
  {
    List<Data>::RemoveFromFront();
    return ret;
  }
  else if (x == tail) {
    List<Data>::RemoveFromBack();
    return ret;
  }
  (*pSucc2Nxt)->next = (*pSucc2Nxt)->next->next;
  delete x;
  size--;
  
  return ret;
}

template <typename Data>
inline void SetLst<Data>::RemoveSuccessor(const Data& dat) {
  SuccessorNRemove(dat);
}

template <typename Data>
bool SetLst<Data>::Insert(const Data &dat)
{
  typename List<Data>::Node** foundNode = BSearch(dat);
  if (foundNode != nullptr && (*foundNode)->key == dat)
                                          return false;

  if (foundNode == nullptr) {
    List<Data>::InsertAtFront(dat);
    return true;
  } else if ((*foundNode)->next == nullptr) { // foundNode == tail, anziche nullptr, inserendo un nuovo massimo perdo il prefisso
    List<Data>::InsertAtBack(dat);
    return true;
  }
  Node* newNode = new Node(dat);

  if (Empty()) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = (*foundNode)->next;
    (*foundNode)->next = newNode;
  }    
  size++;
  return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data &&dat)
{
  typename List<Data>::Node** foundNode = BSearch(dat);
  if (foundNode != nullptr && (*foundNode)->key == dat)
                                          return false;

  if (foundNode == nullptr) {
    List<Data>::InsertAtFront(std::move(dat));
    return true;
  } else if ((*foundNode)->next == nullptr) { // foundNode == tail, anziche nullptr, inserendo un nuovo massimo perdo il prefisso
    List<Data>::InsertAtBack(std::move(dat));
    return true;
  }
  Node* newNode = new Node(std::move(dat));

  if (Empty()) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = (*foundNode)->next;
    (*foundNode)->next = newNode;
  }    
  size++;
  return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& dat) {
  
  if (Empty()) {
    return false;
  }

  typename List<Data>::Node** pPred;
  typename List<Data>::Node** foundNode = const_cast<SetLst<Data>*>(this)->Set<Data>::template BSearch<SetLst<Data>, Node**>(dat, nullptr, &const_cast<SetLst<Data>*>(this)->head, size, pPred);

  if (foundNode == nullptr || (*foundNode)->key != dat)
                                           return false;

  Node *x = nullptr;

  if (head == tail) {
    x = head;
    head = nullptr;
    tail = nullptr;
  }
  else {
    if (pPred == nullptr) {
      x = head;
      head = head->next;
    }
    else {
      if (*pPred == tail) {
        List<Data>::RemoveFromBack();
        return true;
      }
      else if (*pPred == head) {
        List<Data>::RemoveFromFront();
        return true;
      }
      else {
        x = (*pPred)->next;
        (*pPred)->next = (*pPred)->next->next;
      }
    }
  }

  delete x;
  size--;
  
  return true;
}

template <typename Data>
inline const Data& SetLst<Data>::operator[](ulong idx)
  const {
    return List<Data>::operator[](idx);
}

template <typename Data>
inline bool SetLst<Data>::Exists(const Data &data) const noexcept
{
  if (Empty())
    return false;

  Node** foundNode = BSearch(data);
  return (foundNode != nullptr && *foundNode != nullptr && (*foundNode)->key == data);
}

template <typename Data>
inline void SetLst<Data>::Clear() noexcept
{
  List<Data>::Clear();
}

template <typename Data>
void SetLst<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun f)
    const
{
  Node *cur = List<Data>::head;
  for (ulong i = 0; i < size; ++i)
  {
    f(cur->key);
    cur = cur->next;
  }
}

template <typename Data>
inline const Data& SetLst<Data>::getData(typename List<Data>::Node** cur) 
  const {
    return (*cur)->key;
}

template <typename Data>
inline typename List<Data>::Node** SetLst<Data>::Reach(Node** cur, ulong mov, Node**& predCur) 
  const {
    for (ulong i = 0; i < mov; ++i) {
      predCur = cur;
      cur = &(*cur)->next;
    }

  return cur;
}

template <typename Data>
inline typename List<Data>::Node** SetLst<Data>::BSearch(const Data &dat)
  const {
    Node** tmp;
  return const_cast<SetLst<Data>*>(this)->Set<Data>::template BSearch<SetLst<Data>, Node**>(dat, nullptr, &const_cast<SetLst<Data>*>(this)->head, size, tmp);
}

/* ************************************************************************** */

}
