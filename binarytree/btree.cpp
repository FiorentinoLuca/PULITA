#include "btree.hpp"

namespace lasd {

  template <typename Data>
  BTree<Data>::Iterator::Iterator(BTree<Data>& root)
  : root(root), count(0) {}

  template <typename Data>
  void BTree<Data>::Iterator::LeftMostNodeDevelop()
  {
    if (root.Empty())
      throw std::length_error("Empty tree");
    BTree<Data>* cur = Current();
    while (cur->HasLeft())
          cur = &cur->L();
  }

  template <typename Data>
  void BTree<Data>::Iterator::LeftMostLeafDevelop()
  {
    BTree<Data>* cur = &LeftMostNodeDevelop(root);

    while (cur->HasRight())
    {
      cur = &cur->R();
      cur = &LeftMostNodeDevelop(*cur);
    }

  }

  template <typename Data>
  inline void BTree<Data>::InOrderIt::LeftMostNodeDevelop()
  {
    while (Top()->HasLeft())
    {
      Push(Top()->L()) // *cursor gets owned only by one node in the stack
      count++;
    }
  }

  template <typename Data>
  inline BTree<Data>::InOrderIt::InOrderIt(const BTree<Data>& root)
  : BTIterator<Data>(root), cursor(nullptr) {
    if (root.Empty()) 
              return; // Current() == nullptr  <->  IsTerminated()
    Push(unique_ptr<BTree>(&root));
    count++;
    LeftMostNodeDevelop();
  }

  template <typename Data>
  bool BTree<Data>::InOrderIt::IsTerminated() const noexcept
  {
    return Top().get()==nullptr;
  }

  template <typename Data>
  Data& BTree<Data>::InOrderIt::operator*()
  {
    return Top()->Element();
  }

  template <typename Data>
  Iterator<Data>& BTree<Data>::InOrderIt::operator++()
  {

    if (IsTerminated())
      throw std::out_of_range("Iterator is terminated")

    count++;
    if (Top()->HasRight()) {
      Top() = Top()->R();
      LeftMostNodeDevelop();
    }
    else {
      Pop();
    }

    return *this;
  }

  template <typename Data>
  Iterator<Data>& BTree<Data>::InOrderIt::operator+(int dist)
  {
    int delta = count + dist;
    if (delta < 0 )
      throw std::out_of_range("Non valid distance for iterating");

    this->Reset();
    while(count < static_cast<ulong>(delta))
    {
      ++(*this);
    }

    return *this;
  }

  template <typename Data>
  int BTree<Data>::InOrderIt::operator-(Iterator<Data> &other)
  {

    if (root != other.root)
      throw std::invalid_argument("Iterators on different trees");

    return count - other.count;
  }

  template <typename Data>
  void BTree<Data>::InOrderIt::Reset()
  {
    while (Top().get()!=nullptr)
                          Pop();
    count=1;
    Push(unique_ptr<Btree<Data>>(&root));
  }

// calcLeft(a+1) = calcRight(a) + 1
// 2*(a+1)+1 = 2*(a)+2 + 1

  template <typename Data>
  inline ulong BTree<Data>::calcLeftIdx(ulong idx)
  {
    return 2*(idx+1)-1; // 0->1
  }

  template <typename Data>
  inline ulong BTree<Data>::calcRightIdx(ulong idx)
  {
    return 2*(idx+1); // 0->2
  }
  
// per ogni ulong a -> 1 <= b ; f(2*a+1) = f(2*(a+1)) = a <-> f = [](b)->ulong { (b-1)/2 }

  template <typename Data>
  inline ulong BTree<Data>::calcParentIdx(ulong idx)
  {
    return (idx-1)>>1;
  }

  template <typename Data>
  void BTree<Data>::InOrderMappingThrough(MutableLinearContainer<Data>& box, MapFun f)
  {
    const std::function<ulong(ulong)> InOrderSuccessor = [&](ulong idx)
    {
      if (idx >= box.Size())
                 return idx;
      if (calcRightIdx(idx) < box.Size())
      {
        idx = calcRightIdx(idx);
        while (calcLeftIdx(idx) < box.Size())
                      idx = calcLeftIdx(idx);
      }
      else
      {
        while (calcLeftIdx(calcParentIdx(idx)) != idx)
                              idx = calcParentIdx(idx);

        idx = calcParentIdx(idx); //calcLeft(calcParent(idx)) == idx
      }
      
      return idx;
    };

    ulong cur = 0;
    while (calcLeftIdx(cur) < box.Size())
                  cur = calcLeftIdx(cur);

    while (cur < box.Size()) {
      f(box[cur]);
      cur = InOrderSuccessor(cur);
    }
  }

  template <typename Data>
  void BTree<Data>::InOrderTraversingThrough(LinearContainer<Data>& box, TraverseFun f)
  {
    // learning stuff
    {

  //   // std::function<void(LinearContainer<Data>&, TraverseFun, ulong, ulong)> recursiveInOrder;
  //   // recursiveInOrder = [&](LinearContainer<Data>& box, TraverseFun f, ulong lIdx, ulong rIdx)
  //   // {
  //   //   ulong delta = card(lIdx, rIdx);
  //   //   if (delta == 0) return;
  //   //   int mid = lIdx + std::ceil(float(delta)/2)-1;
  //   //   if (mid > lIdx)
  //   //     recursiveInOrder(box, f, lIdx, mid-1);
  //   //   f(box[mid]);
  //   //   if (mid < rIdx)
  //   //     recursiveInOrder(box, f, mid+1, rIdx);
  //   //   return;
  //   // };

  //   ulong card(int, int);
  //   auto LeftMostNode = [&](ulong idx)
  //   {
  //     if (box.Empty())
  //       throw std::length_error("Empty tree");
  //     ulong cur = 0;
  //     while (HasLeft(box))
  //                   cur = calcLeftIdx(cur);
  //     return cur;
  //   };

  //   auto CompleteCard = [&](int h) -> ulong
  //   {
  //     return (1<<(h+1)) - 1;
  //   };

  // // height( CompleteCard( height(t)-1 )+1 ) = height(t) = height(CompleteCard(height(t)))
  // // CompleteCard( height(t)-1 )+1 = 2^height(t); CompleteCard(height(t)) = 2^(height(t)+1)-1
  // // height(t) = log_2(CompleteCard(height(t))+1)-1 = floor(log_2(t==0?(1/2):card(t)))

  //   auto Height = [&](ulong size) -> int
  //   {
  //     return (size==0 ? -1 : std::floor(std::log(size)/std::log(2)));
  //   };

  //   auto MaxNumNodes = [&](ulong size) -> ulong
  //   {
  //     return CompleteCard(Height(size));
  //   };

  //   auto LastLevelReminder = [&](ulong size) -> ulong
  //   {
  //     int h = Height(size);
  //     return (h<=0 ? 0 : (size % CompleteCard(h-1)));
  //   };

  // // card(t) = CompleteCard(height(t)-1)+LastLevelReminder(card(t))
  // // NumberOfReminderParents = ceil(LastLevelReminder(card(t))/2)

  //   ulong root;

  //   auto TraverseFromRootUntilReminderParents = [&]() -> void
  //   {
  //     ulong postamble = (LastLevelReminder()+std::ceil(float(LastLevelReminder())/2));

  //     for (int i = 0; i < box.Size()-postamble; i++);
  //   };

    }

    const std::function<ulong(ulong)> InOrderSuccessor = [&](ulong idx)
    {
      if (idx >= box.Size())
                   return idx;
      if (calcRightIdx(idx) < box.Size())
      {
        idx = calcRightIdx(idx);
        while (calcLeftIdx(idx) < box.Size())
                      idx = calcLeftIdx(idx);
      }
      else
      {
        while (calcLeftIdx(calcParentIdx(idx)) != idx)
                              idx = calcParentIdx(idx);

        idx = calcParentIdx(idx); //calcLeft(calcParent(idx)) == idx
      }
      
      return idx;
    };

    ulong cur = 0;
    while (calcLeftIdx(cur) < box.Size())
                  cur = calcLeftIdx(cur);

    while (cur < box.Size()) {
      f(box[cur]);
      cur = InOrderSuccessor(cur);
    }

  }

  // ulong card(int a, int b)  
  // {
  //   return std::max(0, b-a+1);
  // }

} // namespace lasd