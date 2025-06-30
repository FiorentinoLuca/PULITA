
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>,
  virtual public ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::size; // si riesce a fare il lookup nella prima fase grazie a che lo eredita da Resizable no template
  Data *buffer;

  // ...

public:

  // Default constructor
  Vector();

  /* ************************************************************************ */

  // Specific constructors
  Vector(ulong); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual
  ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data>&);

  // Move assignment
  Vector<Data>& operator=(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  using MutableLinearContainer<Data>:: operator[];
  using MutableLinearContainer<Data>:: Front;
  using MutableLinearContainer<Data>:: Back;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member
 
  void Traverse(typename TraversableContainer<Data>::TraverseFun f) const override;

protected:

  // Auxiliary functions, if necessary!

  virtual
  void EnsureCapacity(ulong dim);
  static ulong mod(int, int);  
  virtual
  void Transfer(Vector<Data>&, ulong, int, ulong);

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
  virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(ulong); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector&);

  // Move constructor
  SortableVector(SortableVector&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual
  ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector<Data>& operator=(const SortableVector<Data>&);

  // Move assignment
  SortableVector<Data>& operator=(SortableVector<Data>&&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
