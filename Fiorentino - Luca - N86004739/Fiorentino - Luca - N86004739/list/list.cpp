#include "list.hpp"

namespace lasd {

/* ************************************************************************** */

// ...

/* ***********************************Node*********************************** */

template <typename Data>
inline List<Data>::Node::Node(const Data& dat) : key(dat), next(nullptr) {}

template <typename Data>
inline List<Data>::Node::Node(Data&& other) noexcept : key(std::move(other)), next(nullptr) {}

template <typename Data>
inline List<Data>::Node::Node(Node&& other)
  noexcept {
    std::swap(key, other.key);
    std::swap(next, other.next);
}

template <typename Data>
inline List<Data>::Node::~Node()
{
  next = nullptr;
}

template <typename Data>
inline bool List<Data>::Node::operator==(const Node& other)
  const noexcept {
  return (key == other.key && next == other.next);
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node& other)
  const noexcept {
  return !(*this == other);
}

template <typename Data>
inline void List<Data>::Node::Flush()
  noexcept {
    Node* current = this->next;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
}

/* ***********************************List*********************************** */

template <typename Data>
List<Data>::List()
  : head(nullptr), tail(nullptr) {
  size = 0;
}

template <typename Data>
List<Data>::List(const TraversableContainer<Data>& box)
  : List() {
  box.Traverse(
    [this](const Data& dat) {
      InsertAtBack(dat);
    }
  );
}

template <typename Data>
List<Data>::List(MappableContainer<Data>&& box)
  : List() {
  box.Map(
    [this](Data& dat) {
      InsertAtBack(std::move(dat));
    }
  );
}

template <typename Data>
List<Data>::List(const List<Data>& other)
{
  (*this) = other;
}

template <typename Data>
List<Data>::List(List<Data>&& other)
  noexcept : List() {
    (*this) = std::move(other);
}

template <typename Data>
List<Data>::~List()
{
  Clear();
}

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& other)
{

  if (this == &other) return *this;

  Clear();
  if (!other.Empty()) {
    head = other.Clone(tail);
  }
  size = other.size;
  return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& other)
  noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  return *this;
}

template<typename Data>
inline bool List<Data>::operator==(const List<Data>& other)
  const noexcept {

    if (size != other.size)
              return false;

    const Node* cur = other.head;
    bool diffAbsence = true;
    PreOrderTraverse(
      [this, &cur, &diffAbsence](const Data& dat) {
        if (cur->key != dat)
          diffAbsence = false;
        cur = cur->next;
      }
    );
    return diffAbsence;
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& other)
  const noexcept {
    return !(*this == other);
}

template <typename Data>
void List<Data>::InsertAtFront(const Data& dat)
{
  Node* newNode = new Node(dat);
  if (Empty()) {
    head = newNode;
    tail = newNode;
  } else {
    newNode->next = head;
    head = newNode;
  }
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dat)
{
  Node* newNode = new Node(std::move(dat));
  if (Empty()) {
    head = newNode;
    tail = newNode;
  } else {
    newNode->next = head;
    head = newNode;
  }
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront()
{
  if (Empty()) {
    throw std::length_error("List is empty");
  }
  Node* x = head;
  head = head->next;
  delete x;
  size--;
  if (Empty()) {
    tail = nullptr;
  }
}

template <typename Data>
Data List<Data>::FrontNRemove()
{
  if (Empty()) {
    throw std::length_error("List is empty");
  }
  Data frontData = Front();
  RemoveFromFront();
  return frontData;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& dat)
{
  Node* newNode = new Node(dat);
  if (Empty()) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& dat)
{
  Node* newNode = new Node(std::move(dat));
  if (Empty()) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

template <typename Data>
void List<Data>::RemoveFromBack()
{
  if (Empty()) {
    throw std::length_error("List is empty");
  }
  if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    Node* current = head;
    while (current->next != tail) {
      current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
  }
  size--;
}

template <typename Data>
Data List<Data>::BackNRemove()
{
  if (Empty()) {
    throw std::length_error("List is empty");
  }
  Data backData = Back();
  RemoveFromBack();
  return backData;
}

template <typename Data>
inline Data& List<Data>::operator[](ulong idx)
{
  if (idx >= size) {
    throw std::out_of_range("Index bigger than last element's index");
  }
  Node* current = head;
  for (ulong i = 0; i < idx; ++i) {
    current = current->next;
  }
  return const_cast<Data&>(current->key);
}

template <typename Data>
inline Data& List<Data>::Front()
{
  return const_cast<Data&>(static_cast<List<Data> const *>(this)->Front());
}

template <typename Data>
Data& List<Data>::Back()
{
  return const_cast<Data&>(static_cast<List<Data> const *>(this)->Back());
}

template <typename Data>
inline const Data& List<Data>::operator[](ulong idx)
  const {
    if (idx >= size) {
      throw std::out_of_range("Index bigger than last element's index");
    }
    Node* current = head;
    for (ulong i = 0; i < idx; ++i) {
      current = current->next;
    }
  return current->key;
}

template <typename Data>
inline const Data& List<Data>::Front() 
  const {
    if (Empty()) 
      throw std::length_error("List is empty");
  return head->key;
}

template <typename Data>
const Data& List<Data>::Back() 
  const {
    if (Empty()) 
      throw std::length_error("List is empty");
  return tail->key;
}

template <typename Data>
void List<Data>::Map(MapFun fun) 
  {
    Node* current = head;
    while (current != nullptr) {
      fun(current->key);
      current = current->next;
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun) 
  {
    Map(fun); // Pre-order mapping is the same as normal mapping for a list
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun) 
  {
    Node* current = head;
    while (current != nullptr) {
      fun(current->key);
      current = current->next;
    }
}

template <typename Data>
inline void List<Data>::Traverse(TraverseFun fun) 
  const {
    PreOrderTraverse(fun);
}

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) 
  const {
    Node* current = head;
    while (current != nullptr) {
      fun(current->key);
      current = current->next;
    }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) 
  const {
    postorderrecursion(head, fun);
}


template <typename Data>
typename List<Data>::Node* List<Data>::Clone(Node*& otherTail)
const {
  if (Empty()) 
    return nullptr;
  return head->recClone(otherTail);
}

template <typename Data>
typename List<Data>::Node* List<Data>::Node::recClone(Node*& otherTail) const {
  
  Node* newNode = new Node(key);
  if (next == nullptr){
    otherTail = newNode;
    return newNode;
  }
  newNode->next = next->recClone(otherTail);
  
  return newNode;
}


template <typename Data>
void List<Data>::postorderrecursion(Node* node, TraverseFun fun) 
  const {
    if (node == nullptr) return;
    postorderrecursion(node->next, fun);
    fun(node->key);
}

template <typename Data>
inline void List<Data>::Clear() 
  noexcept {
    /* 
    #TODO:
    if (Empty()) return;
    ->
    if (!Empty()) {
      head->Flush();
      delete head;
    }
    */
    if (!Empty()) {
      head->Flush();
      delete head;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */
}
