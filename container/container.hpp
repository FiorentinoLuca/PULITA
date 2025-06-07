
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <cmath>

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  // ...
  ulong size;

  /* ************************************************************************ */

  // Default constructor
  Container()
    : size(0) {}

public:

  // Destructor
  virtual 
    ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container& other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container& operator=(Container&& other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators /* Dovrebbero non essere generati dal compilatore */
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  inline bool Empty()
    const noexcept {
      bool isEmpty = false;
      if (Size() == 0)
        isEmpty = true;
      return isEmpty;
  } // (concrete function should not throw exceptions)

  virtual
  inline ulong Size()
    const noexcept {
      return size;
  } // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual 
    ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  void Clear() noexcept = 0;

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual 
  ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer& operator=(ResizableContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  void Resize(ulong) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() 
    noexcept override {
      Resize(0);
  } // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif
