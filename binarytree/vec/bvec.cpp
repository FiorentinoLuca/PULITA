
namespace lasd {

  // {
  //     if (idx >= box.Size())
  //                return idx;
  //     if (calcRightIdx(idx) < box.Size())
  //     {
  //       idx = calcRightIdx(idx);
  //       while (calcLeftIdx(idx) < box.Size())
  //                     idx = calcLeftIdx(idx);
  //     }
  //     else
  //     {
  //       while (calcLeftIdx(calcParentIdx(idx)) != idx)
  //                             idx = calcParentIdx(idx);

  //       idx = calcParentIdx(idx); //calcLeft(calcParent(idx)) == idx
  //     }
      
  //     return idx;
  // }

  template <typename Data>
  inline BVecTInOrderIt<Data>::BVecTInOrderIt(BVecT<Data>& root)
  : root(root), current(&root) { 
    current = &LeftMostNode(); 
  }

  template <typename Data>
  bool BVecTInOrderIt<Data>::IsTerminated() const noexcept
  {
    return current->Size()==0;
  }

  template <typename Data>
  BTree<Data>& BVecTInOrderIt<Data>::LeftMostNode()
  {
    if (root.Empty())
      throw std::length_error("Empty tree");
    BTree<Data>* cur = current;
    while (cur->HasLeft())
          cur = &cur->L();
    return *cur;
  }

  template <typename Data>
  inline BVecT<Data>::BvecTRoot::BVecTRoot(dim)
  : Vector<Data>(dim) {}

  template <typename Data>
  inline BVecT<Data>::BvecTRoot::~BVecTRoot()
  {
    
  }

  template <typename Data>
  inline const Data& BVecT<Data>::operator[](ulong idx)
    const {
      return Vector<Data>::operator[](idx);
  }

  template <typename Data>
  inline Data& BVecT<Data>::operator[](ulong idx)
  {
    return const_cast<Data&>(static_cast<const BVecT<Data>*>(this)->operator[](idx));
  }

  template <typename Data>
  bool BVecT<Data>::HasLeft() const noexcept
  {
    return false;
  }
  
  template <typename Data>
  bool BVecT<Data>::HasRight() const noexcept
  {
    return false;
  }

  template <typename Data>
  const Data &BVecT<Data>::Element() const &
  {
    if (Empty())
      throw std::length_error("Empty tree");
    return nodes[idx];
  }

  template <typename Data>
  Data& BVecT<Data>::Element() &
  {
    return const_cast<Data &>(static_cast<const BVecT<Data>*>(this)->Element());
  }

  template <typename Data>
  Data&& BVecT<Data>::Element() &&
  {
    return std::move(static_cast<BVecT<Data>&>(*this).Element());
  }

  template <typename Data>
  inline const BTree<Data> BVecT<Data>::L()
    const {
      return BVecT<Data>();
  }

  template <typename Data>
  inline const BTree<Data>& BVecT<Data>::R()
    const {
      return BVecT<Data>();
  }

  template <typename Data>
  inline std::unique_ptr<BTree<Data>> BVecT<Data>::L() && {
    
    BVecT<Data> tmp = {
      .ghostNodes = this->ghostNodes,
      .areAlive = this->areAlive,
      .lastLeaf = this->lastLeaf,
      .rootIdx = calcLeftIdx(this->rootIdx)
    };
    
    return std::make_unique<BVecT<Data>>(std::move(tmp));
  }

  template <typename Data>
  inline BTree<Data>& BVecT<Data>::R()
  {
    return const_cast<BTree<Data>&>(static_cast<const BVecT<Data>*>(this)->R());
  }
  
  template <typename Data>
  BVecT<Data>::BVecT(const LinearContainer<Data>& box)
  : nodes(new ) {
    int i = 0;
    InOrderMappingThrough(
      tmp,
      [&i, &box](Data& dat)
      {
        dat = box[i++];
      }
    );
    this->Vector<Data>::operator=(std::move(tmp));
  }

  template <typename Data>
  BVecT<Data>::BVecT(MutableLinearContainer<Data>&& box)
  {
    int i = 0;
    Vector<Data>&& tmp = Vector<Data>(box.Size());
    InOrderMappingThrough(
      tmp,
      [&i, &box](Data& dat)
      {
        dat = std::move(box[i++]);
      }
    );
    this->Vector<Data>::operator=(std::move(tmp));
  }

  template <typename Data>
  BVecT<Data>::BVecT(const BVecT<Data> &)
  {
  }

  template <typename Data>
  BVecT<Data>::BVecT(BVecT<Data> &&)
  {
  }
  
  

} // namespace lasd