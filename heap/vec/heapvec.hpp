
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>,
  virtual protected SortableVector<Data> {
  // Must extend Heap<Data>,
  // Could extend SortableVector<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&&); // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec&);

  // Move constructor
  HeapVec(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec&);

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec&) const noexcept;
  bool operator!=(const HeapVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override; // Override Heap member

  void Heapify() noexcept; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

  using Container::Size;

  void Traverse(typename TraversableContainer<Data>::TraverseFun) const override; // Override TraversableContainer member
  void PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override; // Override TraversableContainer member
  void PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override; // Override TraversableContainer member

protected:

  // Auxiliary functions, if necessary!
  
  void HeapSort() noexcept;
  void HeapifyDown(ulong, ulong) noexcept;
  ulong GetMax(ulong, ulong) const noexcept;
  static int parent(ulong) noexcept;
  static ulong left(ulong) noexcept;
  static ulong right(ulong) noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
