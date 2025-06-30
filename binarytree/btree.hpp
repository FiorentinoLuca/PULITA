
#ifndef BTREE_HPP
#define BTREE_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"
#include "../zmytest/test.hpp"
#include "../iterator/iterator.hpp"
#include "../list/list.hpp"
#include <memory>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */


template <typename Data>
class BTree;

template <typename Data>
class BTree : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {

private:

  // ...

protected:

  class Iterator: virtual public lasd::Iterator<Data> {

  private:

  protected:

    ulong count;
    const BTree<Data>& root;
    Iterator(BTree<Data>&);

  public:

    virtual
    ~Iterator() = default;

  protected:

    virtual
    std::unique_ptr<BTree<Data>>& Current() = 0;
    virtual
    void LeftMostNodeDevelop() = 0;
    virtual
    void LeftMostLeafDevelop() = 0;

  };

public:

  class InOrderIt: virtual public Iterator<Data> {

  private:

  protected:

    std::unique_ptr<BTree<Data>> cursor;

    List<std::unique_ptr<BTree<Data>>> stack;
    auto Push = [&stack](decltype(stack)&& node) -> void
    {
      if (cursor.get()!=nullptr)
        stack.InsertAtFront(std::move(cursor));
      cursor = std::move(node);
    }
    auto Top = [&stack](void) -> decltype(stack)&
    {
      if (stack.Empty() && cursor.get()==nullptr)
          throw std::length_error("Empty Stack");
      return cursor;
    }
    auto Pop = [&stack](void) -> void
    {
      if (stack.Empty() && cursor.get()!=nullptr)
      {
        cursor = nullptr;
      }
      cursor = stack.FrontNRemove();
    }

  public:

    InOrderIt(BTree<Data>&); // template<template<typename> class It, Data> { for (Iterator<Data>&& it = It<Data>(tree); !it.IsTerminated(); ++i); }

    virtual
    ~InOrderIt() = default;

    bool IsTerminated() const noexcept override;

    Data& operator*() override;

    Iterator<Data>& operator++() override;

    Iterator<Data>& operator+(int idx) override;

    int operator-(Iterator<Data>& other) override;

    void Reset() override;

  protected:

    void LeftMostNodeDevelop() override;

  };

  // Destructor
  virtual
  ~BTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTree<Data>& operator=(const Set<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BTree<Data>& operator=(Set<Data>&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  virtual
  const std::unique_ptr<const BTree<Data>> Root() const& = 0;
  virtual
  const std::unique_ptr<const BTree<Data>> L() const& = 0;
  virtual
  const std::unique_ptr<const BTree<Data>> R() const& = 0;

  virtual
  const std::unique_ptr<BTree<Data>> Root() & = 0;
  virtual
  const std::unique_ptr<BTree<Data>> L() & = 0;
  virtual
  const std::unique_ptr<BTree<Data>> R() & = 0;
  
  virtual
  std::unique_ptr<BTree<Data>> Root() && = 0;
  virtual
  std::unique_ptr<BTree<Data>> L() && = 0;
  virtual
  std::unique_ptr<BTree<Data>> R() && = 0;

  virtual
  bool HasLeft() const noexcept = 0;
  virtual
  bool HasRight() const noexcept = 0;

  virtual
  const Data& Element() const& = 0;
  virtual
  Data& Element() & = 0;
  virtual
  Data&& Element() && = 0;

  void Clear() noexcept override = 0; // deletion wont be clearing
  void Clear() const noexcept = 0; // early nulling for deallocation in const objects
  ulong Size() const noexcept override = 0;

protected:

  static ulong calcLeftIdx(ulong);
  static ulong calcRightIdx(ulong);
  static ulong calcParentIdx(ulong);

  using MapFun = MappableContainer<Data>::MapFun;
  using TraverseFun = TraversableContainer<Data>::TraverseFun;

  static void InOrderMappingThrough(MutableLinearContainer<Data>&, MapFun);
  static void InOrderTraversingThrough(LinearContainer<Data> &box, TraverseFun f);

  friend void ::mytest();

};

} // namespace lasd

#include "btree.cpp"

#endif // BTREE_HPP