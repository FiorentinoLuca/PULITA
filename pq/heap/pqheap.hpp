
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, virtual protected HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  using Container::size;
  ulong heapSize = 0;
  static const ulong initialSize;

  // ...

public:

  // Default constructor
  PQHeap();

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data>&&); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap&);

  // Move constructor
  PQHeap(PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual
  ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap& operator=(const PQHeap&);

  // Move assignment
  PQHeap& operator=(PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data&) override; // Override PQ member (Copy of the value)
  void Insert(Data&&) override; // Override PQ member (Move of the value)

  void Change(ulong, const Data&) override; // Override PQ member (Copy of the value)
  void Change(ulong, Data&&) override; // Override PQ member (Move of the value)

  bool operator==(const PQHeap<Data>&) const noexcept;
  bool operator!=(const PQHeap<Data>&) const noexcept;

  void Clear() noexcept override; // Override ClearableContainer member

  ulong Size() const noexcept override;

  using LinearContainer<Data>::Front;
  using HeapVec<Data>::HeapifyDown;
  using HeapVec<Data>::Traverse;
  using HeapVec<Data>::PreOrderTraverse;
  using HeapVec<Data>::PostOrderTraverse;
  using HeapVec<Data>::Empty;

protected:

  // Auxiliary functions, if necessary!

  void HeapifyUp(ulong) noexcept;
  void Resize(ulong) override;
  void EnsureCapacity(ulong) override;

  using HeapVec<Data>::GetMax;
  using HeapVec<Data>::parent;
  using HeapVec<Data>::left;
  using HeapVec<Data>::right;

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
