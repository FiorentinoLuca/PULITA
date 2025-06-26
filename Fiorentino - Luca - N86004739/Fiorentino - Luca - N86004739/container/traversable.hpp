
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual
  ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer<Data>& operator=(const TraversableContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TraversableContainer<Data>& operator=(TraversableContainer<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual
  void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data&, const Accumulator&)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual
  ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */
  
  // Copy assignment
  PreOrderTraversableContainer<Data>&
  operator=(const PreOrderTraversableContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderTraversableContainer<Data>&
  operator=(PreOrderTraversableContainer<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual
  void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;


  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual
  ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer<Data>& 
  operator=(const PostOrderTraversableContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderTraversableContainer<Data>& 
  operator=(PostOrderTraversableContainer<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual
  void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  void Traverse(TraverseFun) const override; // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
