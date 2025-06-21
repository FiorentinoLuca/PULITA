
#ifndef BTREE_HPP
#define BTREE_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BTree : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {

private:

  // ...

protected:

  // ...

public:

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
  void InsertBefore(const Data&, ulong) = 0;
  virtual
  void InsertBefore(Data&&, ulong) = 0;

  virtual
  void InsertAfter(const Data&, ulong) = 0;
  virtual
  void InsertAfter(Data&&, ulong) = 0;

  virtual
  const BTree& L() const = 0;
  virtual
  const BTree& R() const = 0;

  virtual
  BTree& L() = 0;
  virtual
  BTree& R() = 0;

protected:

  using MapFun = MappableContainer<Data>::MapFun;

  static void InOrderMappingThrough(MutableLinearContainer<Data>& box, MappableContainer<Data>::MapFun f)
  {
    auto recursiveInOrder = [&](MutableLinearContainer<Data>& box, MapFun f, ulong lIdx, ulong rIdx)
    {
      ulong delta = std::max(0, static_cast<int>(rIdx-lIdx+1));
      if (delta == 0) throw std::length_error("lIdx deve essere minore o uguale a rIdx");
      if (delta == 1) {
        f(box[lIdx]);
        return;
      }
      ulong mid = lIdx + std::max(0, ((static_cast<int>(delta))>>1)-1) // lIdx + card(1, ((rIdx+1)>>1)-1 )
      recursiveInOrder(box, f, lIdx, mid);
      f(box[mid]);
      recursiveInOrder(box, f, mid+1, rIdx);
    };

    recursiveInOrder(box, f, 0, box.Size()-1);
  }

};

} // namespace lasd

#endif // BTREE_HPP