
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
  virtual public PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...
  using Container::size;

public:

  // Destructor
  virtual 
  ~LinearContainer() = default; // Default destructor

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator= (const LinearContainer&) = delete;
  // Move assignment
  LinearContainer& operator= (LinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.
  
  bool operator!=(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  const Data& operator[](ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  virtual
  const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual
  const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  using Container::Size;

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data>, virtual public LinearContainer<Data> {
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  // ...
  using Container::size; // Inherit size from LinearContainer

public:

  // Destructor
  virtual
  ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer<Data>& operator=(const MutableLinearContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer<Data>& operator=(MutableLinearContainer<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  const Data& operator[](ulong) const override = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  const Data& Front() const override; // (non-mutable version; concrete function must throw std::length_error when empty)

  const Data& Back() const override; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual
  Data& operator[](ulong); // (mutable version; concrete function must throw std::out_of_range when out of range)
  
  virtual
  Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)
  
  virtual
  Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  using LinearContainer<Data>::Traverse;

  using Container::Size;

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  // ...
  using Container::size; // Inherit size from MutableLinearContainer

public:

  // Destructor
  virtual
  ~SortableLinearContainer() = default;


  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.
  
  // Move assignment
  SortableLinearContainer& operator=( SortableLinearContainer&&) = delete; // Move assignment of abstract types is not be possible.
  
  /* ************************************************************************ */

  // Specific member function

  virtual
  void Sort() noexcept;

  using Container::Size;

protected:

  // Auxiliary member functions
 
  // ...
  void InsertionSort() noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
