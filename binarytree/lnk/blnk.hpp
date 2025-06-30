
#ifndef BVEC_HPP
#define BVEC_HPP

/* ************************************************************************** */

#include "../btree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BLnkT: virtual public BTree<Data> {

private:

protected:

  BLnkT<Data>* leftTreePtr;
  BLnkT<Data>* rightTreePtr;

public:
 
  // Default constructor
  BLnkT() = default;

  // Specific constructor
  BLnkT(const LinearContainer<Data>&);
  BLnkT(MutableLinearContainer<Data>&&);
  BLnkT(const BLnkT<Data>&); // cpy ctor
  BLnkT(BLnkT<Data>&&); // mov ctor
  BLnkT(const Data& dat); // node ctor
  BLnkT(Data&& dat); // node ctor
  
  // Destructor
  virtual
  ~BLnkT() = default;

  /* ************************************************************************ */

  // Copy assignment
  BLnkT<Data>& operator=(const BTree<Data>&);
  // Move assignment
  BLnkT<Data>& operator=(BTree<Data>&&);

  /* ************************************************************************ */
  
  const std::unique_ptr<const BTree<Data>> L() const override;
  const std::unique_ptr<const BTree<Data>> R() const override;

  const std::unique_ptr<BTree<Data>> L() override;
  const std::unique_ptr<BTree<Data>> R() override;

  bool HasLeft() const noexcept override;
  bool HasRight() const noexcept override;

  const Data& Element() const& override;
  Data& Element() & override;
  Data&& Element() && override;

  const Data& operator[](ulong) const override; // (non-mutable version; must throw std::out_of_range when out of range)
  Data& operator[](ulong) override; // (mutable version; must throw std::out

  /* ************************************************************************ */

protected:

  // Specific member functions

  
};



} // namespace lasd

#include "blnk.cpp"

#endif // BVEC_HPP