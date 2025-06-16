#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <typeinfo>

/* ************************************************************************** */

#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../set/vec/setvec.hpp"
#include "../list/list.hpp"
#include "../set/lst/setlst.hpp"
#include "../heap/vec/heapvec.hpp"      // <-- HeapVec
#include "../pq/heap/pqheap.hpp"        // <-- PQHeap

/* ************************************************************************** */

using namespace std;

namespace myT
{

  #define NUM_OF_CONTAINER 7
  #define NUM_OF_CLEARABLE 7
  #define NUM_OF_RESIZABLE 2
  #define NUM_OF_TESTABLE 7
  #define NUM_OF_TRAVERSABLE 7
  #define NUM_OF_MAPPABLE 3
  #define NUM_OF_DICTIONARY 2
  #define NUM_OF_ORDERED_DICTIONARY 2
  #define NUM_OF_LINEAR 7
  #define NUM_OF_MUTABLE_LINEAR 4
  #define NUM_OF_SORTABLE_LINEAR 2
  #define NUM_OF_VECTOR 2
  #define NUM_OF_SORTABLE_VECTOR 1
  #define NUM_OF_LIST 1
  #define NUM_OF_SET 2
  #define NUM_OF_SET_VEC 1
  #define NUM_OF_SET_LST 1
  #define NUM_OF_HEAP 1
  #define NUM_OF_PQ 1

  void ContainersTest(lasd::Container &box)
  {
    std::cout << "----------------------------------------ContainersTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "box.Size() ==  " << box.Size() << std::endl;
    std::cout << "box.Empty() ==  " << std::string(box.Empty() ? "true" : "false") << std::endl;
  }

  template <typename Data>
  void TestablesTest(lasd::TestableContainer<Data> &box,const Data &dat)
  {
    std::cout << "----------------------------------------TestablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "box.Exists(" << dat << ") ==  " << std::string(box.Exists(dat) ? "true" : "false") << std::endl;
  }

  void ResizablesTest(lasd::ResizableContainer &box, ulong size)
  {
    std::cout << "----------------------------------------ResizablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Before resizing: box.Size() ==  " << box.Size() << std::endl;
    ulong newSize = size;
    box.Resize(newSize);
    std::cout << "After resizing to ";
    std::cout << newSize;
    std::cout << ": box.Size() ==  " << box.Size() << std::endl;
  }

  void ClearablesTest(lasd::ClearableContainer &box)
  {
    std::cout << "----------------------------------------ClearablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Before clearing: box.Size() ==  " << box.Size() << std::endl;
    box.Clear();
    std::cout << "After clearing";
    std::cout << ": box.Size() ==  " << box.Size() << std::endl;
  }

  template <typename Data>
  void DictionariesTest(lasd::DictionaryContainer<Data>& box, const Data& dat, const lasd::TraversableContainer<Data>& toInsert)
  {
    std::cout << "----------------------------------------DictionariesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    // Insert (copy)
    std::cout << "box.Insert(" << dat << ") == " << (box.Insert(dat) ? "true" : "false") << std::endl;
    // Insert (move)
    std::cout << "box.Insert(move(" << dat << ")) == " << (box.Insert(Data(dat)) ? "true" : "false") << std::endl;

    // Remove
    std::cout << "box.Remove(" << dat << ") == " << (box.Remove(dat) ? "true" : "false") << std::endl;

    // InsertAll (Traversable)
    std::cout << "box.InsertAll(toInsert) == " << (box.InsertAll(toInsert) ? "true" : "false") << std::endl;
    // InsertAll (Mappable, move)
    std::cout << "box.InsertAll(move(Vector)) == " << (box.InsertAll(lasd::Vector<Data>(toInsert)) ? "true" : "false") << std::endl;

    // RemoveAll
    std::cout << "box.RemoveAll(toInsert) == " << (box.RemoveAll(toInsert) ? "true" : "false") << std::endl;

    // InsertSome (Traversable)
    std::cout << "box.InsertSome(toInsert) == " << (box.InsertSome(toInsert) ? "true" : "false") << std::endl;
    // InsertSome (Mappable, move)
    std::cout << "box.InsertSome(move(Vector)) == " << (box.InsertSome(lasd::Vector<Data>(toInsert)) ? "true" : "false") << std::endl;

    // RemoveSome
    std::cout << "box.RemoveSome(toInsert) == " << (box.RemoveSome(toInsert) ? "true" : "false") << std::endl;
  }

  template <typename Data, typename Accumulator>
  void TraversablesTest(lasd::TraversableContainer<Data> &box,
    std::function<void(const Data &)> visitfun,
    std::function<Accumulator(const Data &, const Accumulator &)> foldfun,
    const Accumulator& init) {
      
      std::cout << "----------------------------------------TraversablesTest: ";
      std::cout << typeid(box).name();
      std::cout << "----------------------------------------" << std::endl;

      std::cout << "Begin traversing through the box: " << std::endl;
      box.Traverse(visitfun);
      std::cout << "End traversing through the box" << std::endl;

      std::cout << "Fold of the box begining with: " << init << std::endl;
      std::cout << box.Fold(foldfun, init) << std::endl;
  }
  
  template <typename Data>
  void OrderedDictionariesTest(lasd::OrderedDictionaryContainer<Data>& box, const Data& dat)
  {
    std::cout << "----------------------------------------OrderedDictionariesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    try { std::cout << "box.Min() == " << box.Min() << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.Min() exception: " << e.what() << std::endl; }

    try { std::cout << "box.MinNRemove() == " << box.MinNRemove() << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.MinNRemove() exception: " << e.what() << std::endl; }

    try { box.RemoveMin(); std::cout << "box.RemoveMin() OK" << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.RemoveMin() exception: " << e.what() << std::endl; }

    try { std::cout << "box.Max() == " << box.Max() << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.Max() exception: " << e.what() << std::endl; }

    try { std::cout << "box.MaxNRemove() == " << box.MaxNRemove() << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.MaxNRemove() exception: " << e.what() << std::endl; }

    try { box.RemoveMax(); std::cout << "box.RemoveMax() OK" << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.RemoveMax() exception: " << e.what() << std::endl; }

    try { std::cout << "box.Predecessor(" << dat << ") == " << box.Predecessor(dat) << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.Predecessor() exception: " << e.what() << std::endl; }

    try { std::cout << "box.PredecessorNRemove(" << dat << ") == " << box.PredecessorNRemove(dat) << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.PredecessorNRemove() exception: " << e.what() << std::endl; }

    try { box.RemovePredecessor(dat); std::cout << "box.RemovePredecessor() OK" << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.RemovePredecessor() exception: " << e.what() << std::endl; }

    try { std::cout << "box.Successor(" << dat << ") == " << box.Successor(dat) << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.Successor() exception: " << e.what() << std::endl; }

    try { std::cout << "box.SuccessorNRemove(" << dat << ") == " << box.SuccessorNRemove(dat) << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.SuccessorNRemove() exception: " << e.what() << std::endl; }

    try { box.RemoveSuccessor(dat); std::cout << "box.RemoveSuccessor() OK" << std::endl; }
    catch (const std::length_error& e) { std::cout << "box.RemoveSuccessor() exception: " << e.what() << std::endl; }
  }

  template <typename Data>
  void MappablesTest(lasd::MappableContainer<Data>& box, std::function<void(Data&)> mapfun)
  {
    std::cout << "----------------------------------------MappablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Before Map:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    box.Map(mapfun);

    std::cout << "After Map:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data, typename Accumulator>
  void PreOrderTraversablesTest(
    lasd::PreOrderTraversableContainer<Data> &box,
    std::function<void(const Data &)> visitfun,
    std::function<Accumulator(const Data &, const Accumulator &)> foldfun,
    const Accumulator& init) {
      std::cout << "----------------------------------------PreOrderTraversablesTest: ";
      std::cout << typeid(box).name();
      std::cout << "----------------------------------------" << std::endl;

      std::cout << "Begin traversing through the box: " << std::endl;
      box.Traverse(visitfun);

      std::cout << "Begin traversing(PREORDER) through the box: " << std::endl;
      box.PreOrderTraverse(visitfun);
      std::cout << "End traversing through the box" << std::endl;

      std::cout << "Fold of the box begining with: " << init << std::endl;
      std::cout << box.Fold(foldfun, init) << std::endl;
  }
  
  template <typename Data, typename Accumulator>
  void PostOrderTraversablesTest(
    lasd::PostOrderTraversableContainer<Data> &box,
    std::function<void(const Data &)> visitfun,
    std::function<Accumulator(const Data &, const Accumulator &)> foldfun,
    const Accumulator& init) {

      std::cout << "----------------------------------------PostOrderTraversablesTest: ";
      std::cout << typeid(box).name();
      std::cout << "----------------------------------------" << std::endl;

      std::cout << "Begin traversing through the box: " << std::endl;
      box.Traverse(visitfun);

      std::cout << "Begin traversing(POSTORDER) through the box: " << std::endl;
      box.PostOrderTraverse(visitfun);
      std::cout << "End traversing through the box" << std::endl;

      std::cout << "Fold of the box begining with: " << init << std::endl;
      std::cout << box.Fold(foldfun, init) << std::endl;
  }

  template <typename Data>
  void PreOrderMappablesTest(lasd::PreOrderMappableContainer<Data>& box, std::function<void(Data&)> mapfun)
  {
    std::cout << "----------------------------------------PreOrderMappablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Before PreOrderMap:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    box.PreOrderMap(mapfun);

    std::cout << "After PreOrderMap:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data>
  void PostOrderMappablesTest(lasd::PostOrderMappableContainer<Data>& box, std::function<void(Data&)> mapfun)
  {
    std::cout << "----------------------------------------PostOrderMappablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Before PostOrderMap:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    box.PostOrderMap(mapfun);

    std::cout << "After PostOrderMap:" << std::endl;
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data>
  void LinearsTest(lasd::LinearContainer<Data>& box, lasd::LinearContainer<Data>& other, ulong idx)
  {
    std::cout << "----------------------------------------LinearsTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Contents of box: ";
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    std::cout << "Contents of other: ";
    other.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    try { std::cout << "Front: " << box.Front() << std::endl; }
    catch (const std::length_error& e) { std::cout << "Front() exception: " << e.what() << std::endl; }

    try { std::cout << "Back: " << box.Back() << std::endl; }
    catch (const std::length_error& e) { std::cout << "Back() exception: " << e.what() << std::endl; }

    try { std::cout << "operator[](" << idx << ") == " << box[idx] << std::endl; }
    catch (const std::out_of_range& e) { std::cout << "operator[] exception: " << e.what() << std::endl; }

    std::cout << "operator== (other): " << ((box == other) ? "true" : "false") << std::endl;
    std::cout << "operator!= (other): " << ((box != other) ? "true" : "false") << std::endl;
  }

  template <typename Data>
  void MutableLinearsTest(lasd::MutableLinearContainer<Data>& box, const Data& f, const Data& b, ulong idx, const Data& dat)
  {
    std::cout << "----------------------------------------MutableLinearsTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Before: ";
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    try { std::cout << "Front() = " << (box.Front()=f) << std::endl; }
    catch (const std::length_error& e) { std::cout << "Front() exception: " << e.what() << std::endl; }

    try { std::cout << "Back() = " << (box.Back()=b) << std::endl; }
    catch (const std::length_error& e) { std::cout << "Back() exception: " << e.what() << std::endl; }

    try { std::cout << "operator[](" << idx << ") = " << (box[idx]=dat) << std::endl; }
    catch (const std::out_of_range& e) { std::cout << "operator[] exception: " << e.what() << std::endl; }

    std::cout << "After: ";
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

  }

  template <typename Data>
  void SortableLinearsTest(lasd::SortableLinearContainer<Data>& box)
  {
    std::cout << "----------------------------------------SortableLinearsTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Before Sort: ";
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    box.Sort();

    std::cout << "After Sort: ";
    box.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

  }

  template <typename Data>
  void ListsTest(lasd::List<Data>& list)
  {
    std::cout << "----------------------------------------ListTest: ";
    std::cout << typeid(list).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Contents: ";
    list.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    try {
      list.InsertAtFront(Data("front_data"));
      std::cout << "InsertAtFront: OK" << std::endl;
    } catch (std::length_error& e) { std::cout << "InsertAtFront exception:" << e.what() << std::endl; }

    try {
      list.InsertAtBack(Data("back_data"));
      std::cout << "InsertAtBack: OK" << std::endl;
    } catch (std::length_error& e) { std::cout << "InsertAtFront exception:" << e.what() << std::endl; }

    std::cout << "After InsertAtFront/Back: ";
    list.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    try {
      list.RemoveFromFront();
      std::cout << "RemoveFromFront: OK" << std::endl;
    } catch (const std::length_error& e) { std::cout << "RemoveFromFront exception: " << e.what() << std::endl; }

    try {
      list.RemoveFromBack();
      std::cout << "RemoveFromBack: OK" << std::endl;
    } catch (const std::length_error& e) { std::cout << "RemoveFromBack exception: " << e.what() << std::endl; }

    std::cout << "After RemoveFromFront/Back: ";
    list.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    try {
      std::cout << "FrontNRemove: " << list.FrontNRemove() << std::endl;
    } catch (const std::length_error& e) { std::cout << "FrontNRemove exception: " << e.what() << std::endl; }

    try {
      std::cout << "BackNRemove: " << list.BackNRemove() << std::endl;
    } catch (const std::length_error& e) { std::cout << "BackNRemove exception: " << e.what() << std::endl; }

    std::cout << "After FrontNRemove/BackNRemove: ";
    list.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data>
  void HeapsTest(lasd::Heap<Data>& heap)
  {
    std::cout << "----------------------------------------HeapTest: ";
    std::cout << typeid(heap).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Contents: ";
    heap.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    std::cout << "IsHeap(): " << (heap.IsHeap() ? "true" : "false") << std::endl;

    std::cout << "Calling Heapify()..." << std::endl;
    heap.Heapify();

    std::cout << "After Heapify, IsHeap(): " << (heap.IsHeap() ? "true" : "false") << std::endl;

    std::cout << "After Heapify, contents: ";
    heap.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data>
  void PQsTest(lasd::PQ<Data>& pq, const Data& dat, ulong idx)
  {
    std::cout << "----------------------------------------PQsTest: ";
    std::cout << typeid(pq).name();
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Contents: ";
    pq.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    // Tip
    try { std::cout << "Tip: " << pq.Tip() << std::endl; }
    catch (const std::length_error& e) { std::cout << "Tip() exception: " << e.what() << std::endl; }

    // RemoveTip
    try { pq.RemoveTip(); std::cout << "RemoveTip: OK" << std::endl; }
    catch (const std::length_error& e) { std::cout << "RemoveTip() exception: " << e.what() << std::endl; }

    // TipNRemove
    try { std::cout << "TipNRemove: " << pq.TipNRemove() << std::endl; }
    catch (const std::length_error& e) { std::cout << "TipNRemove() exception: " << e.what() << std::endl; }

    // Insert (copy)
    pq.Insert(dat);
    std::cout << "After Insert (copy): ";
    pq.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    // Insert (move)
    pq.Insert(Data(dat));
    std::cout << "After Insert (move): ";
    pq.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;

    // Change (copy)
    try { pq.Change(idx, dat); std::cout << "Change(" << idx << ", copy): OK" << std::endl; }
    catch (const std::out_of_range& e) { std::cout << "Change() exception: " << e.what() << std::endl; }

    // Change (move)
    try { pq.Change(idx, Data(dat)); std::cout << "Change(" << idx << ", move): OK" << std::endl; }
    catch (const std::out_of_range& e) { std::cout << "Change() exception: " << e.what() << std::endl; }

    std::cout << "After Change: ";
    pq.Traverse([](const Data& dat) { std::cout << dat << ", "; });
    std::cout << std::endl;
  }

  template <typename Data>
  class BoxRandomTester;

  template <typename Data>
  lasd::Vector<Data> getRandomTraversableContainer(const lasd::Set<Data> &Alphabet, ulong min, ulong max)
  {
    ulong size = min + (rand() % (std::max(0, static_cast<int>(max - min + 1))));
    lasd::Vector<Data> travCont(size);

    travCont.Map(
      [&Alphabet](Data &dat)
      {
        dat = Alphabet[rand() % Alphabet.Size()];
      }
    );

    return std::move(travCont);
  }

  template <typename Data>
  lasd::Vector<Data> getRandomUniqueTraversableContainer(const lasd::Set<Data> &Alphabet, ulong min, ulong max)
  {
    lasd::SetVec<Data> uniquesAlphabet(Alphabet);
    max = std::min(max, uniquesAlphabet.Size());
    ulong size = min + (rand() % (std::max(0, static_cast<int>(max - min + 1))));
  
    std::vector<ulong> indices(uniquesAlphabet.Size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937(BoxRandomTester<Data>::seed));

    lasd::Vector<Data> travCont(size);
    for (ulong i = 0; i < size; ++i) {
      travCont[i] = Alphabet[indices[i]];
    }

    return std::move(travCont);
  }

  template <typename Data>
  BoxRandomTester<Data> EmptyBoxes()
  {
    return BoxRandomTester<Data>();
  }

  template <typename Data>
  BoxRandomTester<Data> MonoBoxes(const lasd::Set<Data> &Alphabet) {
    BoxRandomTester<Data> testBox(
      
      // --- Container ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // vectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // listContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // sortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // pqHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // heapVecContainer

      // --- Testable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // testableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // testableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // testableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // testableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // testableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // testablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // testableHeapVecContainer

      // --- Clearable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // clearableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // clearableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // clearableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // clearableSetLstContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // clearablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // clearableHeapVecContainer

      // --- Resizable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // resizableVectorContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // resizableSortVecContainer

      // --- Dictionary ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // dictionarySetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // dictionarySetLstContainer

      // --- Traversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // traversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // traversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // traversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // traversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // traversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // traversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // traversableHeapVecContainer

      // --- OrderedDictionary ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // orderedDictionarySetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // orderedDictionarySetLstContainer

      // --- Mappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // mappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // mappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // mappableSortVecContainer

      // --- PreOrderTraversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // preOrderTraversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // preOrderTraversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // preOrderTraversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // preOrderTraversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // preOrderTraversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // preOrderTraversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // preOrderTraversableHeapVecContainer

      // --- PostOrderTraversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // postOrderTraversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // postOrderTraversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // postOrderTraversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // postOrderTraversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // postOrderTraversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // postOrderTraversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // postOrderTraversableHeapVecContainer

      // --- PreOrderMappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // preOrderMappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // preOrderMappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // preOrderMappableSortVecContainer

      // --- PostOrderMappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // postOrderMappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // postOrderMappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // postOrderMappableSortVecContainer

      // --- Linear ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // linearVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // linearListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // linearSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // linearSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // linearSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // linearPQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // linearHeapVecContainer

      // --- MutableLinear ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // mutableLinearVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // mutableLinearListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // mutableLinearSortVecContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // mutableLinearHeapVecContainer

      // --- SortableLinear ---
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // sortableLinearSortVecContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // sortableLinearHeapVecContainer

      // --- Set ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),       // setVec
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),       // setLst

      // --- Heap ---
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // heap1
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // heap2

      // --- PQ ---
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // pq1
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // pq2

      // --- Concrete ---
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // list1
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),           // list2
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // vector1
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // vector2
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setLst1
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setLst2
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setVec1
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),   // setVec2
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // sortableVector1
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)), // sortableVector2
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // heapVec1
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),        // heapVec2
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),         // pqHeap1
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1))          // pqHeap2
    );

    return std::move(testBox);
  }
    
  template <typename Data>
  BoxRandomTester<Data> MultiBoxes(const lasd::Set<Data> &Alphabet, ulong maxsize) {
    BoxRandomTester<Data> testBox(
      
      // --- Container ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // vectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // listContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // sortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // pqHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // heapVecContainer

      // --- Testable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // testableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // testableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // testableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // testableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // testableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // testablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // testableHeapVecContainer

      // --- Clearable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // clearableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // clearableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // clearableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // clearableSetLstContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // clearablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // clearableHeapVecContainer

      // --- Resizable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // resizableVectorContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // resizableSortVecContainer

      // --- Dictionary ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // dictionarySetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // dictionarySetLstContainer

      // --- Traversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // traversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // traversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // traversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // traversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // traversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // traversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // traversableHeapVecContainer

      // --- OrderedDictionary ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // orderedDictionarySetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // orderedDictionarySetLstContainer

      // --- Mappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // mappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // mappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // mappableSortVecContainer

      // --- PreOrderTraversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // preOrderTraversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // preOrderTraversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // preOrderTraversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // preOrderTraversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // preOrderTraversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // preOrderTraversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // preOrderTraversableHeapVecContainer

      // --- PostOrderTraversable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // postOrderTraversableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // postOrderTraversableListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // postOrderTraversableSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // postOrderTraversableSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // postOrderTraversableSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // postOrderTraversablePQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // postOrderTraversableHeapVecContainer

      // --- PreOrderMappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // preOrderMappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // preOrderMappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // preOrderMappableSortVecContainer

      // --- PostOrderMappable ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // postOrderMappableVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // postOrderMappableListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // postOrderMappableSortVecContainer

      // --- Linear ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // linearVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // linearListContainer
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // linearSetVecContainer
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // linearSetLstContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // linearSortVecContainer
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // linearPQHeapContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // linearHeapVecContainer

      // --- MutableLinear ---
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // mutableLinearVectorContainer
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // mutableLinearListContainer
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // mutableLinearSortVecContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // mutableLinearHeapVecContainer

      // --- SortableLinear ---
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // sortableLinearSortVecContainer
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // sortableLinearHeapVecContainer

      // --- Set ---
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setVec
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setLst

      // --- Heap ---
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // heap1
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // heap2

      // --- PQ ---
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // pq1
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // pq2

      // --- Concrete ---
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // list1
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),           // list2
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // vector1
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // vector2
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setLst1
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setLst2
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setVec1
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),   // setVec2
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // sortableVector1
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)), // sortableVector2
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // heapVec1
      lasd::HeapVec<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),        // heapVec2
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),         // pqHeap1
      lasd::PQHeap<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize))          // pqHeap2
    );

    return std::move(testBox);
  }

  template <typename Data>
  class BoxRandomTester
  {
  public:

    static const time_t seed;

    /* ************************************************************************** */
    // Container interfaces
    /* ************************************************************************** */
    lasd::Container &vectorContainer;
    lasd::Container &listContainer;
    lasd::Container &setVecContainer;
    lasd::Container &setLstContainer;
    lasd::Container &sortVecContainer;
    lasd::Container &pqHeapContainer;           // PQHeap as Container
    lasd::Container &heapVecContainer;          // HeapVec as Container

    /* ************************************************************************** */
    // TestableContainer interfaces
    /* ************************************************************************** */
    lasd::TestableContainer<Data> &testableVectorContainer;
    lasd::TestableContainer<Data> &testableListContainer;
    lasd::TestableContainer<Data> &testableSetVecContainer;
    lasd::TestableContainer<Data> &testableSetLstContainer;
    lasd::TestableContainer<Data> &testableSortVecContainer;
    lasd::TestableContainer<Data> &testablePQHeapContainer;      // PQHeap as TestableContainer
    lasd::TestableContainer<Data> &testableHeapVecContainer;     // HeapVec as TestableContainer

    /* ************************************************************************** */
    // ClearableContainer interfaces
    /* ************************************************************************** */
    lasd::ClearableContainer &clearableVectorContainer;
    lasd::ClearableContainer &clearableListContainer;
    lasd::ClearableContainer &clearableSetVecContainer;
    lasd::ClearableContainer &clearableSetLstContainer;
    lasd::ClearableContainer &clearablePQHeapContainer;          // PQHeap as ClearableContainer
    lasd::ClearableContainer &clearableHeapVecContainer;         // HeapVec as ClearableContainer

    /* ************************************************************************** */
    // ResizableContainer interfaces
    /* ************************************************************************** */
    lasd::ResizableContainer &resizableVectorContainer;
    lasd::ResizableContainer &resizableSortVecContainer;

    /* ************************************************************************** */
    // DictionaryContainer interfaces
    /* ************************************************************************** */
    lasd::DictionaryContainer<Data> &dictionarySetVecContainer;
    lasd::DictionaryContainer<Data> &dictionarySetLstContainer;

    /* ************************************************************************** */
    // TraversableContainer interfaces
    /* ************************************************************************** */
    lasd::TraversableContainer<Data> &traversableVectorContainer;
    lasd::TraversableContainer<Data> &traversableListContainer;
    lasd::TraversableContainer<Data> &traversableSetVecContainer;
    lasd::TraversableContainer<Data> &traversableSetLstContainer;
    lasd::TraversableContainer<Data> &traversableSortVecContainer;
    lasd::TraversableContainer<Data> &traversablePQHeapContainer;    // PQHeap as TraversableContainer
    lasd::TraversableContainer<Data> &traversableHeapVecContainer;   // HeapVec as TraversableContainer

    /* ************************************************************************** */
    // OrderedDictionaryContainer interfaces
    /* ************************************************************************** */
    lasd::OrderedDictionaryContainer<Data> &orderedDictionarySetVecContainer;
    lasd::OrderedDictionaryContainer<Data> &orderedDictionarySetLstContainer;

    /* ************************************************************************** */
    // MappableContainer interfaces
    /* ************************************************************************** */
    lasd::MappableContainer<Data> &mappableVectorContainer;
    lasd::MappableContainer<Data> &mappableListContainer;
    lasd::MappableContainer<Data> &mappableSortVecContainer;

    /* ************************************************************************** */
    // PreOrderTraversableContainer interfaces
    /* ************************************************************************** */
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableVectorContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableListContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSetVecContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSetLstContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSortVecContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversablePQHeapContainer;    // PQHeap as PreOrderTraversableContainer
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableHeapVecContainer;   // HeapVec as PreOrderTraversableContainer

    /* ************************************************************************** */
    // PostOrderTraversableContainer interfaces
    /* ************************************************************************** */
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableVectorContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableListContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSetVecContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSetLstContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSortVecContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversablePQHeapContainer;    // PQHeap as PostOrderTraversableContainer
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableHeapVecContainer;   // HeapVec as PostOrderTraversableContainer

    /* ************************************************************************** */
    // PreOrderMappableContainer interfaces
    /* ************************************************************************** */
    lasd::PreOrderMappableContainer<Data> &preOrderMappableVectorContainer;
    lasd::PreOrderMappableContainer<Data> &preOrderMappableListContainer;
    lasd::PreOrderMappableContainer<Data> &preOrderMappableSortVecContainer;

    /* ************************************************************************** */
    // PostOrderMappableContainer interfaces
    /* ************************************************************************** */
    lasd::PostOrderMappableContainer<Data> &postOrderMappableVectorContainer;
    lasd::PostOrderMappableContainer<Data> &postOrderMappableListContainer;
    lasd::PostOrderMappableContainer<Data> &postOrderMappableSortVecContainer;

    /* ************************************************************************** */
    // LinearContainer interfaces
    /* ************************************************************************** */
    lasd::LinearContainer<Data> &linearVectorContainer;
    lasd::LinearContainer<Data> &linearListContainer;
    lasd::LinearContainer<Data> &linearSetVecContainer;
    lasd::LinearContainer<Data> &linearSetLstContainer;
    lasd::LinearContainer<Data> &linearSortVecContainer;
    lasd::LinearContainer<Data> &linearPQHeapContainer;      // PQHeap as LinearContainer
    lasd::LinearContainer<Data> &linearHeapVecContainer;     // HeapVec as LinearContainer

    /* ************************************************************************** */
    // MutableLinearContainer interfaces
    /* ************************************************************************** */
    lasd::MutableLinearContainer<Data> &mutableLinearVectorContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearListContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearSortVecContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearHeapVecContainer; // HeapVec as MutableLinearContainer

    /* ************************************************************************** */
    // SortableLinearContainer interfaces
    /* ************************************************************************** */
    lasd::SortableLinearContainer<Data> &sortableLinearSortVecContainer;
    lasd::SortableLinearContainer<Data> &sortableLinearHeapVecContainer; // HeapVec as SortableLinearContainer

    /* ************************************************************************** */
    // Set interfaces
    /* ************************************************************************** */
    lasd::Set<Data> &setVec;
    lasd::Set<Data> &setLst;

    /* ************************************************************************** */
    // Heap interfaces
    /* ************************************************************************** */
    lasd::Heap<Data> &heap1; // HeapVec as Heap
    lasd::Heap<Data> &heap2; // HeapVec as Heap

    /* ************************************************************************** */
    // PQ interfaces
    /* ************************************************************************** */
    lasd::PQ<Data> &pq1; // PQHeap as PQ
    lasd::PQ<Data> &pq2; // PQHeap as PQ

    /* ************************************************************************** */
    // Concrete data structures
    /* ************************************************************************** */
    lasd::List<Data> &list1;
    lasd::List<Data> &list2;
    lasd::Vector<Data> &vector1;
    lasd::Vector<Data> &vector2;
    lasd::SetLst<Data> &setLst1;
    lasd::SetLst<Data> &setLst2;
    lasd::SetVec<Data> &setVec1;
    lasd::SetVec<Data> &setVec2;
    lasd::SortableVector<Data> &sortableVector1;
    lasd::SortableVector<Data> &sortableVector2;
    lasd::HeapVec<Data> &heapVec1; // Concrete HeapVec instance
    lasd::HeapVec<Data> &heapVec2; // Concrete HeapVec instance
    lasd::PQHeap<Data> &pqHeap1; // Concrete PQHeap instance
    lasd::PQHeap<Data> &pqHeap2; // Concrete PQHeap instance

    BoxRandomTester(const BoxRandomTester<Data> &) = delete;
    BoxRandomTester<Data> &operator=(const BoxRandomTester<Data> &) = delete;

    BoxRandomTester &operator=(BoxRandomTester<Data> &&other)
    {
      // --- Container ---
      *dynamic_cast<lasd::Vector<Data>*>(&vectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&listContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.listContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&pqHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.pqHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&heapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.heapVecContainer));

      // --- Testable ---
      *dynamic_cast<lasd::Vector<Data>*>(&testableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.testableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&testableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.testableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&testableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.testableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&testableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.testableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&testableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.testableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&testablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.testablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&testableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.testableHeapVecContainer));

      // --- Clearable ---
      *dynamic_cast<lasd::Vector<Data>*>(&clearableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.clearableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&clearableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.clearableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&clearableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.clearableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&clearableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.clearableSetLstContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&clearablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.clearablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&clearableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.clearableHeapVecContainer));

      // --- Resizable ---
      *dynamic_cast<lasd::Vector<Data>*>(&resizableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.resizableVectorContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&resizableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.resizableSortVecContainer));

      // --- Dictionary ---
      *dynamic_cast<lasd::SetVec<Data>*>(&dictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.dictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&dictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.dictionarySetLstContainer));

      // --- Traversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&traversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.traversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&traversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.traversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&traversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.traversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&traversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.traversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&traversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.traversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&traversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.traversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&traversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.traversableHeapVecContainer));

      // --- OrderedDictionary ---
      *dynamic_cast<lasd::SetVec<Data>*>(&orderedDictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.orderedDictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&orderedDictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.orderedDictionarySetLstContainer));

      // --- Mappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&mappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.mappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&mappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.mappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&mappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.mappableSortVecContainer));

      // --- PreOrderTraversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&preOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.preOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&preOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.preOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&preOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.preOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&preOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.preOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&preOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.preOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&preOrderTraversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.preOrderTraversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&preOrderTraversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.preOrderTraversableHeapVecContainer));

      // --- PostOrderTraversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&postOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.postOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&postOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.postOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&postOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.postOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&postOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.postOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&postOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.postOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&postOrderTraversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.postOrderTraversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&postOrderTraversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.postOrderTraversableHeapVecContainer));

      // --- PreOrderMappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&preOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.preOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&preOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.preOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&preOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.preOrderMappableSortVecContainer));

      // --- PostOrderMappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&postOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.postOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&postOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.postOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&postOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.postOrderMappableSortVecContainer));

      // --- Linear ---
      *dynamic_cast<lasd::Vector<Data>*>(&linearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.linearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&linearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.linearListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&linearSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.linearSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&linearSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.linearSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&linearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.linearSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&linearPQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.linearPQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&linearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.linearHeapVecContainer));

      // --- MutableLinear ---
      *dynamic_cast<lasd::Vector<Data>*>(&mutableLinearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.mutableLinearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&mutableLinearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.mutableLinearListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&mutableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.mutableLinearSortVecContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&mutableLinearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.mutableLinearHeapVecContainer));

      // --- SortableLinear ---
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableLinearSortVecContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&sortableLinearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.sortableLinearHeapVecContainer));

      // --- Set ---
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec) = std::move(dynamic_cast<lasd::Set<Data>&>(other.setVec));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst) = std::move(dynamic_cast<lasd::Set<Data>&>(other.setLst));

      // --- Heap ---
      *dynamic_cast<lasd::HeapVec<Data>*>(&heap1) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.heap1));
      *dynamic_cast<lasd::HeapVec<Data>*>(&heap2) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.heap2));

      // --- PQ ---
      *dynamic_cast<lasd::PQHeap<Data>*>(&pq1) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.pq1));
      *dynamic_cast<lasd::PQHeap<Data>*>(&pq2) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.pq2));

      // --- Concrete ---
      *dynamic_cast<lasd::List<Data>*>(&list1) = std::move(dynamic_cast<lasd::List<Data>&>(other.list1));
      *dynamic_cast<lasd::List<Data>*>(&list2) = std::move(dynamic_cast<lasd::List<Data>&>(other.list2));
      *dynamic_cast<lasd::Vector<Data>*>(&vector1) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vector1));
      *dynamic_cast<lasd::Vector<Data>*>(&vector2) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vector2));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst1) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLst1));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst2) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLst2));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec1) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVec1));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec2) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVec2));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableVector1) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableVector1));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableVector2) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableVector2));
      *dynamic_cast<lasd::HeapVec<Data>*>(&heapVec1) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.heapVec1));
      *dynamic_cast<lasd::HeapVec<Data>*>(&heapVec2) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(other.heapVec2));
      *dynamic_cast<lasd::PQHeap<Data>*>(&pqHeap1) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.pqHeap1));
      *dynamic_cast<lasd::PQHeap<Data>*>(&pqHeap2) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(other.pqHeap2));

      return *this;
    }

    BoxRandomTester(BoxRandomTester<Data> &&other)
      noexcept : BoxRandomTester<Data>() {
        (*this) = std::move(other);
    }

    BoxRandomTester()

      // --- Container ---
      : vectorContainer(*new lasd::Vector<Data>())
      , listContainer(*new lasd::List<Data>())
      , setVecContainer(*new lasd::SetVec<Data>())
      , setLstContainer(*new lasd::SetLst<Data>())
      , sortVecContainer(*new lasd::SortableVector<Data>())
      , pqHeapContainer(*new lasd::PQHeap<Data>())
      , heapVecContainer(*new lasd::HeapVec<Data>())

      // --- Testable ---
      , testableVectorContainer(*new lasd::Vector<Data>())
      , testableListContainer(*new lasd::List<Data>())
      , testableSetVecContainer(*new lasd::SetVec<Data>())
      , testableSetLstContainer(*new lasd::SetLst<Data>())
      , testableSortVecContainer(*new lasd::SortableVector<Data>())
      , testablePQHeapContainer(*new lasd::PQHeap<Data>())
      , testableHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- Clearable ---
      , clearableVectorContainer(*new lasd::Vector<Data>())
      , clearableListContainer(*new lasd::List<Data>())
      , clearableSetVecContainer(*new lasd::SetVec<Data>())
      , clearableSetLstContainer(*new lasd::SetLst<Data>())
      , clearablePQHeapContainer(*new lasd::PQHeap<Data>())
      , clearableHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- Resizable ---
      , resizableVectorContainer(*new lasd::Vector<Data>())
      , resizableSortVecContainer(*new lasd::SortableVector<Data>())

      // --- Dictionary ---
      , dictionarySetVecContainer(*new lasd::SetVec<Data>())
      , dictionarySetLstContainer(*new lasd::SetLst<Data>())

      // --- Traversable ---
      , traversableVectorContainer(*new lasd::Vector<Data>())
      , traversableListContainer(*new lasd::List<Data>())
      , traversableSetVecContainer(*new lasd::SetVec<Data>())
      , traversableSetLstContainer(*new lasd::SetLst<Data>())
      , traversableSortVecContainer(*new lasd::SortableVector<Data>())
      , traversablePQHeapContainer(*new lasd::PQHeap<Data>())
      , traversableHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- OrderedDictionary ---
      , orderedDictionarySetVecContainer(*new lasd::SetVec<Data>())
      , orderedDictionarySetLstContainer(*new lasd::SetLst<Data>())

      // --- Mappable ---
      , mappableVectorContainer(*new lasd::Vector<Data>())
      , mappableListContainer(*new lasd::List<Data>())
      , mappableSortVecContainer(*new lasd::SortableVector<Data>())

      // --- PreOrderTraversable ---
      , preOrderTraversableVectorContainer(*new lasd::Vector<Data>())
      , preOrderTraversableListContainer(*new lasd::List<Data>())
      , preOrderTraversableSetVecContainer(*new lasd::SetVec<Data>())
      , preOrderTraversableSetLstContainer(*new lasd::SetLst<Data>())
      , preOrderTraversableSortVecContainer(*new lasd::SortableVector<Data>())
      , preOrderTraversablePQHeapContainer(*new lasd::PQHeap<Data>())
      , preOrderTraversableHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- PostOrderTraversable ---
      , postOrderTraversableVectorContainer(*new lasd::Vector<Data>())
      , postOrderTraversableListContainer(*new lasd::List<Data>())
      , postOrderTraversableSetVecContainer(*new lasd::SetVec<Data>())
      , postOrderTraversableSetLstContainer(*new lasd::SetLst<Data>())
      , postOrderTraversableSortVecContainer(*new lasd::SortableVector<Data>())
      , postOrderTraversablePQHeapContainer(*new lasd::PQHeap<Data>())
      , postOrderTraversableHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- PreOrderMappable ---
      , preOrderMappableVectorContainer(*new lasd::Vector<Data>())
      , preOrderMappableListContainer(*new lasd::List<Data>())
      , preOrderMappableSortVecContainer(*new lasd::SortableVector<Data>())

      // --- PostOrderMappable ---
      , postOrderMappableVectorContainer(*new lasd::Vector<Data>())
      , postOrderMappableListContainer(*new lasd::List<Data>())
      , postOrderMappableSortVecContainer(*new lasd::SortableVector<Data>())

      // --- Linear ---
      , linearVectorContainer(*new lasd::Vector<Data>())
      , linearListContainer(*new lasd::List<Data>())
      , linearSetVecContainer(*new lasd::SetVec<Data>())
      , linearSetLstContainer(*new lasd::SetLst<Data>())
      , linearSortVecContainer(*new lasd::SortableVector<Data>())
      , linearPQHeapContainer(*new lasd::PQHeap<Data>())
      , linearHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- MutableLinear ---
      , mutableLinearVectorContainer(*new lasd::Vector<Data>())
      , mutableLinearListContainer(*new lasd::List<Data>())
      , mutableLinearSortVecContainer(*new lasd::SortableVector<Data>())
      , mutableLinearHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- SortableLinear ---
      , sortableLinearSortVecContainer(*new lasd::SortableVector<Data>())
      , sortableLinearHeapVecContainer(*new lasd::HeapVec<Data>())

      // --- Set ---
      , setVec(*new lasd::SetVec<Data>())
      , setLst(*new lasd::SetLst<Data>())

      // --- Heap ---
      , heap1(*new lasd::HeapVec<Data>())
      , heap2(*new lasd::HeapVec<Data>())

      // --- PQ ---
      , pq1(*new lasd::PQHeap<Data>())
      , pq2(*new lasd::PQHeap<Data>())

      // --- Concrete ---
      , list1(*new lasd::List<Data>())
      , list2(*new lasd::List<Data>())
      , vector1(*new lasd::Vector<Data>())
      , vector2(*new lasd::Vector<Data>())
      , setLst1(*new lasd::SetLst<Data>())
      , setLst2(*new lasd::SetLst<Data>())
      , setVec1(*new lasd::SetVec<Data>())
      , setVec2(*new lasd::SetVec<Data>())
      , sortableVector1(*new lasd::SortableVector<Data>())
      , sortableVector2(*new lasd::SortableVector<Data>())
      , heapVec1(*new lasd::HeapVec<Data>())
      , heapVec2(*new lasd::HeapVec<Data>())
      , pqHeap1(*new lasd::PQHeap<Data>())
      , pqHeap2(*new lasd::PQHeap<Data>())
    {}

    BoxRandomTester(

      // --- Container ---
      lasd::Container &&vectorContainer,
      lasd::Container &&listContainer,
      lasd::Container &&setVecContainer,
      lasd::Container &&setLstContainer,
      lasd::Container &&sortVecContainer,
      lasd::Container &&pqHeapContainer,
      lasd::Container &&heapVecContainer,

      // --- Testable ---
      lasd::TestableContainer<Data> &&testableVectorContainer,
      lasd::TestableContainer<Data> &&testableListContainer,
      lasd::TestableContainer<Data> &&testableSetVecContainer,
      lasd::TestableContainer<Data> &&testableSetLstContainer,
      lasd::TestableContainer<Data> &&testableSortVecContainer,
      lasd::TestableContainer<Data> &&testablePQHeapContainer,
      lasd::TestableContainer<Data> &&testableHeapVecContainer,

      // --- Clearable ---
      lasd::ClearableContainer &&clearableVectorContainer,
      lasd::ClearableContainer &&clearableListContainer,
      lasd::ClearableContainer &&clearableSetVecContainer,
      lasd::ClearableContainer &&clearableSetLstContainer,
      lasd::ClearableContainer &&clearablePQHeapContainer,
      lasd::ClearableContainer &&clearableHeapVecContainer,

      // --- Resizable ---
      lasd::ResizableContainer &&resizableVectorContainer,
      lasd::ResizableContainer &&resizableSortVecContainer,

      // --- Dictionary ---
      lasd::DictionaryContainer<Data> &&dictionarySetVecContainer,
      lasd::DictionaryContainer<Data> &&dictionarySetLstContainer,

      // --- Traversable ---
      lasd::TraversableContainer<Data> &&traversableVectorContainer,
      lasd::TraversableContainer<Data> &&traversableListContainer,
      lasd::TraversableContainer<Data> &&traversableSetVecContainer,
      lasd::TraversableContainer<Data> &&traversableSetLstContainer,
      lasd::TraversableContainer<Data> &&traversableSortVecContainer,
      lasd::TraversableContainer<Data> &&traversablePQHeapContainer,
      lasd::TraversableContainer<Data> &&traversableHeapVecContainer,

      // --- OrderedDictionary ---
      lasd::OrderedDictionaryContainer<Data> &&orderedDictionarySetVecContainer,
      lasd::OrderedDictionaryContainer<Data> &&orderedDictionarySetLstContainer,

      // --- Mappable ---
      lasd::MappableContainer<Data> &&mappableVectorContainer,
      lasd::MappableContainer<Data> &&mappableListContainer,
      lasd::MappableContainer<Data> &&mappableSortVecContainer,

      // --- PreOrderTraversable ---
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableVectorContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableListContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSetVecContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSetLstContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSortVecContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversablePQHeapContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableHeapVecContainer,

      // --- PostOrderTraversable ---
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableVectorContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableListContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSetVecContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSetLstContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSortVecContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversablePQHeapContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableHeapVecContainer,

      // --- PreOrderMappable ---
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableVectorContainer,
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableListContainer,
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableSortVecContainer,

      // --- PostOrderMappable ---
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableVectorContainer,
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableListContainer,
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableSortVecContainer,

      // --- Linear ---
      lasd::LinearContainer<Data> &&linearVectorContainer,
      lasd::LinearContainer<Data> &&linearListContainer,
      lasd::LinearContainer<Data> &&linearSetVecContainer,
      lasd::LinearContainer<Data> &&linearSetLstContainer,
      lasd::LinearContainer<Data> &&linearSortVecContainer,
      lasd::LinearContainer<Data> &&linearPQHeapContainer,
      lasd::LinearContainer<Data> &&linearHeapVecContainer,

      // --- MutableLinear ---
      lasd::MutableLinearContainer<Data> &&mutableLinearVectorContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearListContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearSortVecContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearHeapVecContainer,

      // --- SortableLinear ---
      lasd::SortableLinearContainer<Data> &&sortableLinearSortVecContainer,
      lasd::SortableLinearContainer<Data> &&sortableLinearHeapVecContainer,

      // --- Set ---
      lasd::Set<Data> &&setVec,
      lasd::Set<Data> &&setLst,

      // --- Heap ---
      lasd::Heap<Data> &&heap1,
      lasd::Heap<Data> &&heap2,

      // --- PQ ---
      lasd::PQ<Data> &&pq1,
      lasd::PQ<Data> &&pq2,

      // --- Concrete ---
      lasd::List<Data> &&list1,
      lasd::List<Data> &&list2,
      lasd::Vector<Data> &&vector1,
      lasd::Vector<Data> &&vector2,
      lasd::SetLst<Data> &&setLst1,
      lasd::SetLst<Data> &&setLst2,
      lasd::SetVec<Data> &&setVec1,
      lasd::SetVec<Data> &&setVec2,
      lasd::SortableVector<Data> &&sortableVector1,
      lasd::SortableVector<Data> &&sortableVector2,
      lasd::HeapVec<Data> &&heapVec1,
      lasd::HeapVec<Data> &&heapVec2,
      lasd::PQHeap<Data> &&pqHeap1,
      lasd::PQHeap<Data> &&pqHeap2
    )
    : BoxRandomTester<Data>()
    {
      // --- Container ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->vectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(vectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->listContainer) = std::move(dynamic_cast<lasd::List<Data>&>(listContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->pqHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(pqHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->heapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(heapVecContainer));

      // --- Testable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->testableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(testableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->testableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(testableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->testableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(testableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->testableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(testableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->testableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(testableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->testablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(testablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->testableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(testableHeapVecContainer));

      // --- Clearable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->clearableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(clearableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->clearableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(clearableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->clearableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(clearableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->clearableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(clearableSetLstContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->clearablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(clearablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->clearableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(clearableHeapVecContainer));

      // --- Resizable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->resizableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(resizableVectorContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->resizableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(resizableSortVecContainer));

      // --- Dictionary ---
      *dynamic_cast<lasd::SetVec<Data>*>(&this->dictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(dictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->dictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(dictionarySetLstContainer));

      // --- Traversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->traversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(traversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->traversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(traversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->traversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(traversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->traversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(traversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->traversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(traversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->traversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(traversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->traversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(traversableHeapVecContainer));

      // --- OrderedDictionary ---
      *dynamic_cast<lasd::SetVec<Data>*>(&this->orderedDictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(orderedDictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->orderedDictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(orderedDictionarySetLstContainer));

      // --- Mappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->mappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(mappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->mappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(mappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->mappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(mappableSortVecContainer));

      // --- PreOrderTraversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->preOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(preOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->preOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(preOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->preOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(preOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->preOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(preOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->preOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(preOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->preOrderTraversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(preOrderTraversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->preOrderTraversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(preOrderTraversableHeapVecContainer));

      // --- PostOrderTraversable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->postOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(postOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->postOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(postOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->postOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(postOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->postOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(postOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->postOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(postOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->postOrderTraversablePQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(postOrderTraversablePQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->postOrderTraversableHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(postOrderTraversableHeapVecContainer));

      // --- PreOrderMappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->preOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(preOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->preOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(preOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->preOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(preOrderMappableSortVecContainer));

      // --- PostOrderMappable ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->postOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(postOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->postOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(postOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->postOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(postOrderMappableSortVecContainer));

      // --- Linear ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->linearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(linearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->linearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(linearListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->linearSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(linearSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->linearSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(linearSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->linearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(linearSortVecContainer));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->linearPQHeapContainer) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(linearPQHeapContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->linearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(linearHeapVecContainer));

      // --- MutableLinear ---
      *dynamic_cast<lasd::Vector<Data>*>(&this->mutableLinearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(mutableLinearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->mutableLinearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(mutableLinearListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->mutableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(mutableLinearSortVecContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->mutableLinearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(mutableLinearHeapVecContainer));

      // --- SortableLinear ---
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableLinearSortVecContainer));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->sortableLinearHeapVecContainer) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(sortableLinearHeapVecContainer));

      // --- Set ---
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec) = std::move(dynamic_cast<lasd::Set<Data>&>(setVec));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst) = std::move(dynamic_cast<lasd::Set<Data>&>(setLst));

      // --- Heap ---
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->heap1) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(heap1));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->heap2) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(heap2));

      // --- PQ ---
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->pq1) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(pq1));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->pq2) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(pq2));

      // --- Concrete ---
      *dynamic_cast<lasd::List<Data>*>(&this->list1) = std::move(dynamic_cast<lasd::List<Data>&>(list1));
      *dynamic_cast<lasd::List<Data>*>(&this->list2) = std::move(dynamic_cast<lasd::List<Data>&>(list2));
      *dynamic_cast<lasd::Vector<Data>*>(&this->vector1) = std::move(dynamic_cast<lasd::Vector<Data>&>(vector1));
      *dynamic_cast<lasd::Vector<Data>*>(&this->vector2) = std::move(dynamic_cast<lasd::Vector<Data>&>(vector2));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst1) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLst1));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst2) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLst2));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec1) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVec1));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec2) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVec2));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableVector1) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableVector1));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableVector2) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableVector2));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->heapVec1) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(heapVec1));
      *dynamic_cast<lasd::HeapVec<Data>*>(&this->heapVec2) = std::move(dynamic_cast<lasd::HeapVec<Data>&>(heapVec2));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->pqHeap1) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(pqHeap1));
      *dynamic_cast<lasd::PQHeap<Data>*>(&this->pqHeap2) = std::move(dynamic_cast<lasd::PQHeap<Data>&>(pqHeap2));
    }

    ~BoxRandomTester()
    {
      // --- Container ---
      delete &vectorContainer;
      delete &listContainer;
      delete &setVecContainer;
      delete &setLstContainer;
      delete &sortVecContainer;
      delete &pqHeapContainer;
      delete &heapVecContainer;

      // --- Testable ---
      delete &testableVectorContainer;
      delete &testableListContainer;
      delete &testableSetVecContainer;
      delete &testableSetLstContainer;
      delete &testableSortVecContainer;
      delete &testablePQHeapContainer;
      delete &testableHeapVecContainer;

      // --- Clearable ---
      delete &clearableVectorContainer;
      delete &clearableListContainer;
      delete &clearableSetVecContainer;
      delete &clearableSetLstContainer;
      delete &clearablePQHeapContainer;
      delete &clearableHeapVecContainer;

      // --- Resizable ---
      delete &resizableVectorContainer;
      delete &resizableSortVecContainer;

      // --- Dictionary ---
      delete &dictionarySetVecContainer;
      delete &dictionarySetLstContainer;

      // --- Traversable ---
      delete &traversableVectorContainer;
      delete &traversableListContainer;
      delete &traversableSetVecContainer;
      delete &traversableSetLstContainer;
      delete &traversableSortVecContainer;
      delete &traversablePQHeapContainer;
      delete &traversableHeapVecContainer;

      // --- OrderedDictionary ---
      delete &orderedDictionarySetVecContainer;
      delete &orderedDictionarySetLstContainer;

      // --- Mappable ---
      delete &mappableVectorContainer;
      delete &mappableListContainer;
      delete &mappableSortVecContainer;

      // --- PreOrderTraversable ---
      delete &preOrderTraversableVectorContainer;
      delete &preOrderTraversableListContainer;
      delete &preOrderTraversableSetVecContainer;
      delete &preOrderTraversableSetLstContainer;
      delete &preOrderTraversableSortVecContainer;
      delete &preOrderTraversablePQHeapContainer;
      delete &preOrderTraversableHeapVecContainer;

      // --- PostOrderTraversable ---
      delete &postOrderTraversableVectorContainer;
      delete &postOrderTraversableListContainer;
      delete &postOrderTraversableSetVecContainer;
      delete &postOrderTraversableSetLstContainer;
      delete &postOrderTraversableSortVecContainer;
      delete &postOrderTraversablePQHeapContainer;
      delete &postOrderTraversableHeapVecContainer;

      // --- PreOrderMappable ---
      delete &preOrderMappableVectorContainer;
      delete &preOrderMappableListContainer;
      delete &preOrderMappableSortVecContainer;

      // --- PostOrderMappable ---
      delete &postOrderMappableVectorContainer;
      delete &postOrderMappableListContainer;
      delete &postOrderMappableSortVecContainer;

      // --- Linear ---
      delete &linearVectorContainer;
      delete &linearListContainer;
      delete &linearSetVecContainer;
      delete &linearSetLstContainer;
      delete &linearSortVecContainer;
      delete &linearPQHeapContainer;
      delete &linearHeapVecContainer;

      // --- MutableLinear ---
      delete &mutableLinearVectorContainer;
      delete &mutableLinearListContainer;
      delete &mutableLinearSortVecContainer;
      delete &mutableLinearHeapVecContainer;

      // --- SortableLinear ---
      delete &sortableLinearSortVecContainer;
      delete &sortableLinearHeapVecContainer;

      // --- Set ---
      delete &setVec;
      delete &setLst;

      // --- Heap ---
      delete &heap1;
      delete &heap2;

      // --- PQ ---
      delete &pq1;
      delete &pq2;

      // --- Concrete ---
      delete &list1;
      delete &list2;
      delete &vector1;
      delete &vector2;
      delete &setLst1;
      delete &setLst2;
      delete &setVec1;
      delete &setVec2;
      delete &sortableVector1;
      delete &sortableVector2;
      delete &heapVec1;
      delete &heapVec2;
      delete &pqHeap1;
      delete &pqHeap2;
    }

  };

  template <typename Data>
  std::ostream& operator<<(std::ostream& os, const BoxRandomTester<Data>& box) {
    auto printOrBottom = [&os](const lasd::TraversableContainer<Data>& cont) {
      if (cont.Empty())
        os << "⊥";
      else
        cont.Traverse([&os](const Data& dat){ os << dat << ", "; });
      os << std::endl;
    };

    // Container interfaces
    os << "\tvectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.vectorContainer));
    os << "\tlistContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.listContainer));
    os << "\tsetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.setVecContainer));
    os << "\tsetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.setLstContainer));
    os << "\tsortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.sortVecContainer));
    os << "\tpqHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.pqHeapContainer));
    os << "\theapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.heapVecContainer));

    // TestableContainer interfaces
    os << "\ttestableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.testableVectorContainer));
    os << "\ttestableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.testableListContainer));
    os << "\ttestableSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.testableSetVecContainer));
    os << "\ttestableSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.testableSetLstContainer));
    os << "\ttestableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.testableSortVecContainer));
    os << "\ttestablePQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.testablePQHeapContainer));
    os << "\ttestableHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.testableHeapVecContainer));

    // ClearableContainer interfaces
    os << "\tclearableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.clearableVectorContainer));
    os << "\tclearableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.clearableListContainer));
    os << "\tclearableSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.clearableSetVecContainer));
    os << "\tclearableSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.clearableSetLstContainer));
    os << "\tclearablePQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.clearablePQHeapContainer));
    os << "\tclearableHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.clearableHeapVecContainer));

    // ResizableContainer interfaces
    os << "\tresizableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.resizableVectorContainer));
    os << "\tresizableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.resizableSortVecContainer));

    // DictionaryContainer interfaces
    os << "\tdictionarySetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.dictionarySetVecContainer));
    os << "\tdictionarySetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.dictionarySetLstContainer));

    // TraversableContainer interfaces
    os << "\ttraversableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.traversableVectorContainer));
    os << "\ttraversableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.traversableListContainer));
    os << "\ttraversableSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.traversableSetVecContainer));
    os << "\ttraversableSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.traversableSetLstContainer));
    os << "\ttraversableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.traversableSortVecContainer));
    os << "\ttraversablePQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.traversablePQHeapContainer));
    os << "\ttraversableHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.traversableHeapVecContainer));

    // OrderedDictionaryContainer interfaces
    os << "\torderedDictionarySetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.orderedDictionarySetVecContainer));
    os << "\torderedDictionarySetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.orderedDictionarySetLstContainer));

    // MappableContainer interfaces
    os << "\tmappableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.mappableVectorContainer));
    os << "\tmappableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.mappableListContainer));
    os << "\tmappableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.mappableSortVecContainer));

    // PreOrderTraversableContainer interfaces
    os << "\tpreOrderTraversableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.preOrderTraversableVectorContainer));
    os << "\tpreOrderTraversableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.preOrderTraversableListContainer));
    os << "\tpreOrderTraversableSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.preOrderTraversableSetVecContainer));
    os << "\tpreOrderTraversableSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.preOrderTraversableSetLstContainer));
    os << "\tpreOrderTraversableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.preOrderTraversableSortVecContainer));
    os << "\tpreOrderTraversablePQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.preOrderTraversablePQHeapContainer));
    os << "\tpreOrderTraversableHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.preOrderTraversableHeapVecContainer));

    // PostOrderTraversableContainer interfaces
    os << "\tpostOrderTraversableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.postOrderTraversableVectorContainer));
    os << "\tpostOrderTraversableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.postOrderTraversableListContainer));
    os << "\tpostOrderTraversableSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.postOrderTraversableSetVecContainer));
    os << "\tpostOrderTraversableSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.postOrderTraversableSetLstContainer));
    os << "\tpostOrderTraversableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.postOrderTraversableSortVecContainer));
    os << "\tpostOrderTraversablePQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.postOrderTraversablePQHeapContainer));
    os << "\tpostOrderTraversableHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.postOrderTraversableHeapVecContainer));

    // PreOrderMappableContainer interfaces
    os << "\tpreOrderMappableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.preOrderMappableVectorContainer));
    os << "\tpreOrderMappableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.preOrderMappableListContainer));
    os << "\tpreOrderMappableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.preOrderMappableSortVecContainer));

    // PostOrderMappableContainer interfaces
    os << "\tpostOrderMappableVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.postOrderMappableVectorContainer));
    os << "\tpostOrderMappableListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.postOrderMappableListContainer));
    os << "\tpostOrderMappableSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.postOrderMappableSortVecContainer));

    // LinearContainer interfaces
    os << "\tlinearVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.linearVectorContainer));
    os << "\tlinearListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.linearListContainer));
    os << "\tlinearSetVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.linearSetVecContainer));
    os << "\tlinearSetLstContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.linearSetLstContainer));
    os << "\tlinearSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.linearSortVecContainer));
    os << "\tlinearPQHeapContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.linearPQHeapContainer));
    os << "\tlinearHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.linearHeapVecContainer));

    // MutableLinearContainer interfaces
    os << "\tmutableLinearVectorContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.mutableLinearVectorContainer));
    os << "\tmutableLinearListContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.mutableLinearListContainer));
    os << "\tmutableLinearSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.mutableLinearSortVecContainer));
    os << "\tmutableLinearHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.mutableLinearHeapVecContainer));

    // SortableLinearContainer interfaces
    os << "\tsortableLinearSortVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.sortableLinearSortVecContainer));
    os << "\tsortableLinearHeapVecContainer: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.sortableLinearHeapVecContainer));

    // Set interfaces
    os << "\tsetVec: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.setVec));
    os << "\tsetLst: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.setLst));

    // Heap interfaces
    os << "\theap1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.heap1));
    os << "\theap2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.heap2));

    // PQ interfaces
    os << "\tpq1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.pq1));
    os << "\tpq2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.pq2));

    // Concrete data structures
    os << "\tlist1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.list1));
    os << "\tlist2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::List<Data>&>(box.list2));
    os << "\tvector1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.vector1));
    os << "\tvector2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::Vector<Data>&>(box.vector2));
    os << "\tsetLst1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.setLst1));
    os << "\tsetLst2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetLst<Data>&>(box.setLst2));
    os << "\tsetVec1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.setVec1));
    os << "\tsetVec2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SetVec<Data>&>(box.setVec2));
    os << "\tsortableVector1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.sortableVector1));
    os << "\tsortableVector2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::SortableVector<Data>&>(box.sortableVector2));
    os << "\theapVec1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.heapVec1));
    os << "\theapVec2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::HeapVec<Data>&>(box.heapVec2));
    os << "\tpqHeap1: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.pqHeap1));
    os << "\tpqHeap2: " << std::endl;
    printOrBottom(dynamic_cast<const lasd::PQHeap<Data>&>(box.pqHeap2));

    return os;
  }

  class MyType
  {

  public:
    string buffer;
    int id;
    static int count;

    MyType()
        : buffer()
    {
      id = count++;
      // std::cout << "Costruendo(): ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }
    MyType(const char *buff)
        : buffer(buff)
    {
      id = count++;
      // std::cout << "Costruendo(buff): ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }
    MyType(string &&dat)
        : buffer(std::move(dat))
    {
      id = count++;
      // std::cout << "Costruendo(dat): ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }
    MyType(const MyType &other)
        : buffer(other.buffer)
    {
      id = count++;
      // std::cout << "CpyCtor(other): ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }
    MyType(MyType &&other)
        : buffer(std::move(other.buffer))
    {
      id = count++;
      // std::cout << "MovCtor(other): ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }
    MyType &operator=(const MyType &other)
    {
      MyType &&tmp = MyType(other);
      std::swap(tmp, *this);
      // std::cout << "CpyAss(other): ";
      // std::cout << typeid(MyType).name() << std::endl;
      return *this;
    }
    MyType &operator=(MyType &&other)
    {
      buffer = std::move(other.buffer);
      // std::cout << "MovAss(other): ";
      // std::cout << typeid(MyType).name() << std::endl;
      return *this;
    }
    ~MyType()
    {
      // delete &buffer;
      // std::cout << "Distruggendo: ";
      // std::cout << "ConstructionID: " + to_string(id) + "; ";
      // std::cout << typeid(MyType).name() << std::endl;
    }

    const char *c_str()
        const noexcept
    {
      return buffer.c_str();
    }

    bool operator==(const MyType &other)
        const
    {
      return buffer == other.buffer;
    }

    bool operator!=(const MyType &other) const
    {
      return buffer != other.buffer;
    }

    bool operator<(const MyType &other) const
    {
      return buffer < other.buffer;
    }
    
    bool operator<=(const MyType &other) const
    {
      return buffer <= other.buffer;
    }
    
    bool operator>(const MyType &other) const
    {
      return buffer > other.buffer;
    }
    
    bool operator>=(const MyType &other) const
    {
      return buffer >= other.buffer;
    }
    
    friend std::ostream &operator<<(std::ostream &prefix, const MyType &data);
  };
  
  int MyType::count = 0;

  std::ostream &operator<<(std::ostream &prefix, const MyType &data)
  {
    return prefix << data.buffer;
  }
  
  using DataT = MyType;
  
  template <typename Data>
  const time_t BoxRandomTester<Data>::seed = time(nullptr);
  
  // template <typename Data>
  // const time_t BoxRandomTester<Data>::seed = 1750093403;

  std::string randomInRange(const std::string& min, const std::string& max) {

    static std::mt19937 gen(BoxRandomTester<DataT>::seed);
    // Trova il primo carattere che differisce
    size_t i = 0;
    while (i < min.size() && i < max.size() && min[i] == max[i]) ++i;

    std::string result = min.substr(0, i);

    // Se min == max o min > max, ritorna min
    if (min > max) throw std::invalid_argument("min must be less or equal than max");
    if (min == max) return min;

    // Se uno dei due è finito, aggiungi un carattere random tra '\0' e max[i]-1 oppure min[i]+1 e 255
    if (i == min.size() && i < max.size()) {
        std::uniform_int_distribution<int> dist(0, static_cast<unsigned char>(max[i]) - 1);
        result += static_cast<char>(dist(gen));
    } else if (i == max.size() && i < min.size()) {
        std::uniform_int_distribution<int> dist(static_cast<unsigned char>(min[i]) + 1, 255);
        result += static_cast<char>(dist(gen));
    } else if (i < min.size() && i < max.size()) {
        // Scegli un carattere tra min[i]+1 e max[i]-1 se possibile
        unsigned char minc = static_cast<unsigned char>(min[i]);
        unsigned char maxc = static_cast<unsigned char>(max[i]);
        if (maxc > minc + 1) {
            std::uniform_int_distribution<int> dist(minc + 1, maxc - 1);
            result += static_cast<char>(dist(gen));
        } else {
            // Non c'è spazio, quindi scegli min o max e aggiungi caratteri random
            result += min[i];
            // Aggiungi caratteri random per rendere la stringa > min e < max
            std::uniform_int_distribution<int> dist('a', 'z');
            for (size_t j = i + 1; j < std::max(min.size(), max.size()); ++j) {
                result += static_cast<char>(dist(gen));
            }
        }
    }
    return result;
  }

  MyType randomInRange(const MyType& min, const MyType& max) {
    return MyType(randomInRange(min.buffer, max.buffer));
  }

  int randomInRange(int min, int max) {
    if (min > max) throw std::invalid_argument("min must be less or equal than max");
    static std::mt19937 gen(BoxRandomTester<DataT>::seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
  }

  float randomInRange(float min, float max) {
    if (min > max) throw std::invalid_argument("min must be less or equal than max");
    static std::mt19937 gen(BoxRandomTester<DataT>::seed);
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
  }

  std::string randomOutRange(std::string min, std::string max) {
    if (min == max) { std::string tmp = min; 
      min.back() = tmp.back()-1;
      max.back() = tmp.back()+1;
    } else {
      min.back() = min.back() - 1;
      max.back() = max.back() + 1;
    }
    return randomInRange(min, max); 
  }

  MyType randomOutRange(const MyType& min, const MyType& max) {
    return MyType(randomOutRange(min.buffer, max.buffer));
  }

  int randomOutRange(int min, int max) {
    if (min == max) {
      int tmp = min;
      min = tmp - 1;
      max = tmp + 1;
    } else {
      min += 1;
      max -= 1;
    }
    return randomInRange(min - 1, max + 1);
  }

  float randomOutRange(float min, float max) {
    if (min == max) {
      float tmp = min;
      min = tmp - 1.25f;
      max = tmp + 1.25f;
    } else {
      min += 1.25f;
      max -= 1.25f;
    }
    return randomInRange(min - 1, max + 1);
  }

  template <typename Data>
  typename lasd::TraversableContainer<Data>::TraverseFun travF;

  template <typename Data, typename Accumulator>
  typename lasd::TraversableContainer<Data>::FoldFun<Accumulator> foldF;

  template <typename Data>
  typename lasd::MappableContainer<Data>::MapFun mapF;

  template <typename Data>
  void Gentest1(const lasd::Set<Data> &Alphabet){

    {
      std::cout << "Testing All Interfaces on EmptyBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::EmptyBoxes<Data>();

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      std::cout << "Random seed: " << BoxRandomTester<DataT>::seed << std::endl;

      // 1. ContainersTest
      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);

      // 2. TestablesTest
      TestablesTest(testBox.testableVectorContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableListContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSortVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));

      // 3. ResizablesTest
      ResizablesTest(testBox.resizableVectorContainer, 10);
      ResizablesTest(testBox.resizableSortVecContainer, 10);

      // 4. ClearablesTest
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);

      // 5. DictionariesTest
      DictionariesTest(testBox.dictionarySetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);
      DictionariesTest(testBox.dictionarySetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);

      // 6. TraversablesTest
      lasd::TraversableContainer<Data>* localTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::TraversableContainer<Data>*> tmp = {
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer,
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localTraversables[i] = std::move(tmp[i]);
        }
      }
      TraversablesTest<Data, int>(
        *localTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 7. OrderedDictionariesTest
      try { OrderedDictionariesTest(testBox.orderedDictionarySetVecContainer, randomOutRange(testBox.orderedDictionarySetVecContainer.Min(), testBox.orderedDictionarySetVecContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      try { OrderedDictionariesTest(testBox.orderedDictionarySetLstContainer, randomOutRange(testBox.orderedDictionarySetLstContainer.Min(), testBox.orderedDictionarySetLstContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      
      // 8. MappablesTest
      lasd::MappableContainer<Data>* localMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::MappableContainer<Data>*> tmp = {
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer,
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localMappables[i] = std::move(tmp[i]);
        }
      }
      MappablesTest(*localMappables[0], mapF<Data>);

      // 9. PreOrderTraversablesTest
      lasd::PreOrderTraversableContainer<Data>* localPreOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PreOrderTraversableContainer<Data>*> tmp = {
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer,
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer
        };

        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPreOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PreOrderTraversablesTest(
        *localPreOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 10. PostOrderTraversablesTest
      lasd::PostOrderTraversableContainer<Data>* localPostOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PostOrderTraversableContainer<Data>*> tmp = {
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer,
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPostOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PostOrderTraversablesTest(
        *localPostOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 11. PreOrderMappablesTest
      lasd::PreOrderMappableContainer<Data>* localPreOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PreOrderMappableContainer<Data>*> tmp = {
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer,
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPreOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PreOrderMappablesTest(
        *localPreOrderMappables[0], 
        // [](Data& dat){ dat = Data("pre_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("pre_" + dat.buffer); })
        mapF<Data>
      );

      // 12. PostOrderMappablesTest
      lasd::PostOrderMappableContainer<Data>* localPostOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PostOrderMappableContainer<Data>*> tmp = {
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer,
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPostOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PostOrderMappablesTest(
        *localPostOrderMappables[0], 
        // [](Data& dat){ dat = Data("post_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("post_" + dat.buffer); })
        mapF<Data>
      );

      // 13. LinearsTest
      lasd::LinearContainer<Data>* localLinears[NUM_OF_LINEAR];
      {
        std::vector<lasd::LinearContainer<Data>*> tmp = {
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer,
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_LINEAR; ++i) {
          localLinears[i] = std::move(tmp[i]);
        }
      }
      LinearsTest(*localLinears[0], *localLinears[NUM_OF_LINEAR-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))));

      // 14. MutableLinearsTest
      lasd::MutableLinearContainer<Data>* localMutableLinears[NUM_OF_MUTABLE_LINEAR];
      {
        std::vector<lasd::MutableLinearContainer<Data>*> tmp = {
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer,
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MUTABLE_LINEAR; ++i) {
          localMutableLinears[i] = std::move(tmp[i]);
        }
      }
      MutableLinearsTest(*localMutableLinears[0], Alphabet[0], Alphabet[Alphabet.Size()-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))), Alphabet[randomInRange(0, Alphabet.Size()-1)]);

      // 15. SortableLinearsTest
      lasd::SortableLinearContainer<Data>* localSortableLinears[NUM_OF_SORTABLE_LINEAR];
      {
        std::vector<lasd::SortableLinearContainer<Data>*> tmp = {
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer,
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(std::random_device{}()));
        for (ulong i = 0; i < NUM_OF_SORTABLE_LINEAR; ++i) {
          localSortableLinears[i] = std::move(tmp[i]);
        }
      }
      SortableLinearsTest(*localSortableLinears[0]);

      // 16. ListsTest
      ListsTest(testBox.list1);

      // 17. HeapsTest
      HeapsTest(testBox.heap1);

      // 18. PQsTest
      try { PQsTest(testBox.pq1, randomOutRange(Alphabet.Min(), testBox.pq1.Tip()), randomOutRange(0, testBox.pq1.Size()-1)); }
      catch(std::exception &e) { std::cout << "PQsTest exception: " << e.what() << std::endl; }

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    }

    {
      std::cout << "Testing All Interfaces on MonoBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::MonoBoxes<Data>(Alphabet);

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      std::cout << "Random seed: " << BoxRandomTester<Data>::seed << std::endl;

      // 1. ContainersTest
      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);

      // 2. TestablesTest
      TestablesTest(testBox.testableVectorContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableListContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSortVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));

      // 3. ResizablesTest
      ResizablesTest(testBox.resizableVectorContainer, 10);
      ResizablesTest(testBox.resizableSortVecContainer, 10);

      // 4. ClearablesTest
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);

      // 5. DictionariesTest
      DictionariesTest(testBox.dictionarySetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);
      DictionariesTest(testBox.dictionarySetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);

      // 6. TraversablesTest
      lasd::TraversableContainer<Data>* localTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::TraversableContainer<Data>*> tmp = {
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer,
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localTraversables[i] = std::move(tmp[i]);
        }
      }
      TraversablesTest<Data, int>(
        *localTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 7. OrderedDictionariesTest
      try { OrderedDictionariesTest(testBox.orderedDictionarySetVecContainer, randomOutRange(testBox.orderedDictionarySetVecContainer.Min(), testBox.orderedDictionarySetVecContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      try { OrderedDictionariesTest(testBox.orderedDictionarySetLstContainer, randomOutRange(testBox.orderedDictionarySetLstContainer.Min(), testBox.orderedDictionarySetLstContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      
      // 8. MappablesTest
      lasd::MappableContainer<Data>* localMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::MappableContainer<Data>*> tmp = {
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer,
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localMappables[i] = std::move(tmp[i]);
        }
      }
      MappablesTest(*localMappables[0], mapF<Data>);

      // 9. PreOrderTraversablesTest
      lasd::PreOrderTraversableContainer<Data>* localPreOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PreOrderTraversableContainer<Data>*> tmp = {
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer,
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer
        };

        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPreOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PreOrderTraversablesTest(
        *localPreOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 10. PostOrderTraversablesTest
      lasd::PostOrderTraversableContainer<Data>* localPostOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PostOrderTraversableContainer<Data>*> tmp = {
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer,
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPostOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PostOrderTraversablesTest(
        *localPostOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 11. PreOrderMappablesTest
      lasd::PreOrderMappableContainer<Data>* localPreOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PreOrderMappableContainer<Data>*> tmp = {
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer,
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPreOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PreOrderMappablesTest(
        *localPreOrderMappables[0], 
        // [](Data& dat){ dat = Data("pre_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("pre_" + dat.buffer); })
        mapF<Data>
      );

      // 12. PostOrderMappablesTest
      lasd::PostOrderMappableContainer<Data>* localPostOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PostOrderMappableContainer<Data>*> tmp = {
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer,
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPostOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PostOrderMappablesTest(
        *localPostOrderMappables[0], 
        // [](Data& dat){ dat = Data("post_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("post_" + dat.buffer); })
        mapF<Data>
      );

      // 13. LinearsTest
      lasd::LinearContainer<Data>* localLinears[NUM_OF_LINEAR];
      {
        std::vector<lasd::LinearContainer<Data>*> tmp = {
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer,
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_LINEAR; ++i) {
          localLinears[i] = std::move(tmp[i]);
        }
      }
      LinearsTest(*localLinears[0], *localLinears[NUM_OF_LINEAR-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))));

      // 14. MutableLinearsTest
      lasd::MutableLinearContainer<Data>* localMutableLinears[NUM_OF_MUTABLE_LINEAR];
      {
        std::vector<lasd::MutableLinearContainer<Data>*> tmp = {
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer,
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MUTABLE_LINEAR; ++i) {
          localMutableLinears[i] = std::move(tmp[i]);
        }
      }
      MutableLinearsTest(*localMutableLinears[0], Alphabet[0], Alphabet[Alphabet.Size()-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))), Alphabet[randomInRange(0, Alphabet.Size()-1)]);

      // 15. SortableLinearsTest
      lasd::SortableLinearContainer<Data>* localSortableLinears[NUM_OF_SORTABLE_LINEAR];
      {
        std::vector<lasd::SortableLinearContainer<Data>*> tmp = {
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer,
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_SORTABLE_LINEAR; ++i) {
          localSortableLinears[i] = std::move(tmp[i]);
        }
      }
      SortableLinearsTest(*localSortableLinears[0]);

      // 16. ListsTest
      ListsTest(testBox.list1);

      // 17. HeapsTest
      HeapsTest(testBox.heap1);

      // 18. PQsTest
      try { PQsTest(testBox.pq1, randomOutRange(Alphabet.Min(), testBox.pq1.Tip()), randomOutRange(0, testBox.pq1.Size()-1)); }
      catch(std::exception &e) { std::cout << "PQsTest exception: " << e.what() << std::endl; }

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    }

      
    {
      std::cout << "Testing All Interfaces on MultiBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::MultiBoxes<Data>(Alphabet, 20);

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      std::cout << "Random seed: " << BoxRandomTester<DataT>::seed << std::endl;

      // 1. ContainersTest
      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);

      // 2. TestablesTest
      TestablesTest(testBox.testableVectorContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableListContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));
      TestablesTest(testBox.testableSortVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()));

      // 3. ResizablesTest
      ResizablesTest(testBox.resizableVectorContainer, 10);
      ResizablesTest(testBox.resizableSortVecContainer, 10);

      // 4. ClearablesTest
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);

      // 5. DictionariesTest
      DictionariesTest(testBox.dictionarySetVecContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);
      DictionariesTest(testBox.dictionarySetLstContainer, randomOutRange(Alphabet.Min(), Alphabet.Max()), testBox.traversableVectorContainer);

      // 6. TraversablesTest
      lasd::TraversableContainer<Data>* localTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::TraversableContainer<Data>*> tmp = {
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer,
          &testBox.traversableVectorContainer,
          &testBox.traversableListContainer,
          &testBox.traversableSetVecContainer,
          &testBox.traversableSetLstContainer,
          &testBox.traversableSortVecContainer,
          &testBox.traversablePQHeapContainer,
          &testBox.traversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localTraversables[i] = std::move(tmp[i]);
        }
      }
      TraversablesTest<Data, int>(
        *localTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 7. OrderedDictionariesTest
      try { OrderedDictionariesTest(testBox.orderedDictionarySetVecContainer, randomOutRange(testBox.orderedDictionarySetVecContainer.Min(), testBox.orderedDictionarySetVecContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      try { OrderedDictionariesTest(testBox.orderedDictionarySetLstContainer, randomOutRange(testBox.orderedDictionarySetLstContainer.Min(), testBox.orderedDictionarySetLstContainer.Max())); }
      catch(std::exception &e) { std::cout << "OrderedDictionariesTest exception: " << e.what() << std::endl; }
      
      // 8. MappablesTest
      lasd::MappableContainer<Data>* localMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::MappableContainer<Data>*> tmp = {
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer,
          &testBox.mappableVectorContainer,
          &testBox.mappableListContainer,
          &testBox.mappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localMappables[i] = std::move(tmp[i]);
        }
      }
      MappablesTest(*localMappables[0], mapF<Data>);

      // 9. PreOrderTraversablesTest
      lasd::PreOrderTraversableContainer<Data>* localPreOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PreOrderTraversableContainer<Data>*> tmp = {
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer,
          &testBox.preOrderTraversableVectorContainer,
          &testBox.preOrderTraversableListContainer,
          &testBox.preOrderTraversableSetVecContainer,
          &testBox.preOrderTraversableSetLstContainer,
          &testBox.preOrderTraversableSortVecContainer,
          &testBox.preOrderTraversablePQHeapContainer,
          &testBox.preOrderTraversableHeapVecContainer
        };

        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPreOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PreOrderTraversablesTest(
        *localPreOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 10. PostOrderTraversablesTest
      lasd::PostOrderTraversableContainer<Data>* localPostOrderTraversables[NUM_OF_TRAVERSABLE];
      {
        std::vector<lasd::PostOrderTraversableContainer<Data>*> tmp = {
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer,
          &testBox.postOrderTraversableVectorContainer,
          &testBox.postOrderTraversableListContainer,
          &testBox.postOrderTraversableSetVecContainer,
          &testBox.postOrderTraversableSetLstContainer,
          &testBox.postOrderTraversableSortVecContainer,
          &testBox.postOrderTraversablePQHeapContainer,
          &testBox.postOrderTraversableHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_TRAVERSABLE; ++i) {
          localPostOrderTraversables[i] = std::move(tmp[i]);
        }
      }
      PostOrderTraversablesTest(
        *localPostOrderTraversables[0],
        // [](const Data& dat){ std::cout << dat << " "; },
        // [](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); },
        // std::function<void(const Data&)>([](const Data& dat){ std::cout << dat << " "; }),
        // std::function<Data(const Data&, const Data&)>([](const Data& dat, const Data& acc){ return DataT(acc.buffer + dat.buffer); }),
        travF<Data>,
        foldF<Data, int>,
        0
      );

      // 11. PreOrderMappablesTest
      lasd::PreOrderMappableContainer<Data>* localPreOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PreOrderMappableContainer<Data>*> tmp = {
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer,
          &testBox.preOrderMappableVectorContainer,
          &testBox.preOrderMappableListContainer,
          &testBox.preOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPreOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PreOrderMappablesTest(
        *localPreOrderMappables[0], 
        // [](Data& dat){ dat = Data("pre_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("pre_" + dat.buffer); })
        mapF<Data>
      );

      // 12. PostOrderMappablesTest
      lasd::PostOrderMappableContainer<Data>* localPostOrderMappables[NUM_OF_MAPPABLE];
      {
        std::vector<lasd::PostOrderMappableContainer<Data>*> tmp = {
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer,
          &testBox.postOrderMappableVectorContainer,
          &testBox.postOrderMappableListContainer,
          &testBox.postOrderMappableSortVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MAPPABLE; ++i) {
          localPostOrderMappables[i] = std::move(tmp[i]);
        }
      }
      PostOrderMappablesTest(
        *localPostOrderMappables[0], 
        // [](Data& dat){ dat = Data("post_" + dat.buffer); }
        // std::function<void(Data&)>([](Data& dat){ dat = Data("post_" + dat.buffer); })
        mapF<Data>
      );

      // 13. LinearsTest
      lasd::LinearContainer<Data>* localLinears[NUM_OF_LINEAR];
      {
        std::vector<lasd::LinearContainer<Data>*> tmp = {
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer,
          &testBox.linearVectorContainer,
          &testBox.linearListContainer,
          &testBox.linearSetVecContainer,
          &testBox.linearSetLstContainer,
          &testBox.linearSortVecContainer,
          &testBox.linearPQHeapContainer,
          &testBox.linearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_LINEAR; ++i) {
          localLinears[i] = std::move(tmp[i]);
        }
      }
      LinearsTest(*localLinears[0], *localLinears[NUM_OF_LINEAR-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))));

      // 14. MutableLinearsTest
      lasd::MutableLinearContainer<Data>* localMutableLinears[NUM_OF_MUTABLE_LINEAR];
      {
        std::vector<lasd::MutableLinearContainer<Data>*> tmp = {
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer,
          &testBox.mutableLinearVectorContainer,
          &testBox.mutableLinearListContainer,
          &testBox.mutableLinearSortVecContainer,
          &testBox.mutableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_MUTABLE_LINEAR; ++i) {
          localMutableLinears[i] = std::move(tmp[i]);
        }
      }
      MutableLinearsTest(*localMutableLinears[0], Alphabet[0], Alphabet[Alphabet.Size()-1], randomOutRange(0, std::max(0, static_cast<int>(std::min((*localLinears[0]).Size()-1, (*localLinears[NUM_OF_LINEAR-1]).Size()-1)))), Alphabet[randomInRange(0, Alphabet.Size()-1)]);

      // 15. SortableLinearsTest
      lasd::SortableLinearContainer<Data>* localSortableLinears[NUM_OF_SORTABLE_LINEAR];
      {
        std::vector<lasd::SortableLinearContainer<Data>*> tmp = {
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer,
          &testBox.sortableLinearSortVecContainer,
          &testBox.sortableLinearHeapVecContainer
        };
        std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
        for (ulong i = 0; i < NUM_OF_SORTABLE_LINEAR; ++i) {
          localSortableLinears[i] = std::move(tmp[i]);
        }
      }
      SortableLinearsTest(*localSortableLinears[0]);

      // 16. ListsTest
      ListsTest(testBox.list1);

      // 17. HeapsTest
      HeapsTest(testBox.heap1);

      // 18. PQsTest
      try { PQsTest(testBox.pq1, randomOutRange(Alphabet.Min(), testBox.pq1.Tip()), randomOutRange(0, testBox.pq1.Size()-1)); }
      catch(std::exception &e) { std::cout << "PQsTest exception: " << e.what() << std::endl; }

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      {
        std::string ans;
        std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
        if (ans == "1") {
          std::cout << testBox;
          std::cout << "Press Enter to continue..." << std::endl;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    }

 
  }

  template <typename Box>
  std::function<void(Box**)> Empty;
  template <typename Box>
  std::function<void(Box**)> Singletonize;
  template <typename Box>
  std::function<void(Box**)> Multiply;

  template <typename Data>
  void Gentest2(const lasd::Set<Data> &Alphabet){
    enum class Algebra {
      VEC, // Modification by explicit resizing
      LST, // Modification by appending and stacking
      SET, // Modification by insertion and removal
      PQ // Modification by priority queue operations
    };
    BoxRandomTester<Data> testBox;

    lasd::Vector<Data>* localVecs[NUM_OF_VECTOR];
    {
      std::vector<lasd::Vector<Data>*> tmp = {
        &testBox.vector1,
        &testBox.vector2,
        &testBox.sortableVector1,
        &testBox.sortableVector2,
        &testBox.vector1,
        &testBox.vector2,
        &testBox.sortableVector1,
        &testBox.sortableVector2
      };
      std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
      for (ulong i = 0; i < NUM_OF_VECTOR; ++i) {
        localVecs[i] = std::move(tmp[i]);
      }
    }
    lasd::List<Data>* localLists[2*NUM_OF_LIST];
    {
      std::vector<lasd::List<Data>*> tmp = {
        &testBox.list1,
        &testBox.list2,
        &testBox.list1,
        &testBox.list2
      };
      std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
      for (ulong i = 0; i < 2*NUM_OF_LIST; ++i) {
        localLists[i] = std::move(tmp[i]);
      }
    }
    lasd::Set<Data>* localSets[NUM_OF_SET];
    {
      std::vector<lasd::Set<Data>*> tmp = {
        &testBox.setVec1,
        &testBox.setVec2,
        &testBox.setLst1,
        &testBox.setLst2,
        &testBox.setVec1,
        &testBox.setVec2,
        &testBox.setLst1,
        &testBox.setLst2
      };
      std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        localSets[i] = std::move(tmp[i]);
      }
    }
    lasd::PQHeap<Data>* localPQs[2*NUM_OF_PQ];
    {
      std::vector<lasd::PQHeap<Data>*> tmp = {
        &testBox.pqHeap1,
        &testBox.pqHeap2,
        &testBox.pqHeap1,
        &testBox.pqHeap2
      };
      std::shuffle(tmp.begin(), tmp.end(), std::mt19937(BoxRandomTester<Data>::seed));
      for (ulong i = 0; i < 2*NUM_OF_PQ; ++i) {
        localPQs[i] = std::move(tmp[i]);
      }
    }

    Empty<lasd::Vector<Data>> = [&](lasd::Vector<Data>* localVecs[NUM_OF_VECTOR])
    {
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < NUM_OF_VECTOR; ++i) {
        do {
          localVecs[i]->Resize(std::max(0, static_cast<int>(localVecs[i]->Size()-1)));
        } while (localVecs[i]->Size() > 1);
      }
      for (ulong i = 0; i < NUM_OF_VECTOR; ++i) {
        do {
          localVecs[i]->Resize(std::max(0, static_cast<int>(localVecs[i]->Size()-1)));
        } while (localVecs[i]->Size() > 1);
      }
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Vector<Data> localCopies[NUM_OF_VECTOR] = { *localVecs[0], *localVecs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0].Clear();
      for (ulong i = 1; i < NUM_OF_VECTOR; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      for (ulong i = 0; i < NUM_OF_VECTOR; ++i) {
        localCopies[i].Clear();
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Singletonize<lasd::Vector<Data>> = [&](lasd::Vector<Data>* localVecs[NUM_OF_VECTOR])
    {
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);
      localVecs[0]->Resize(1);
      localVecs[0]->operator[](0) = randomInRange(Alphabet.Min(), Alphabet.Max());
      for (ulong i = 1; i < NUM_OF_VECTOR; ++i) {
        *localVecs[i] = *localVecs[i-1];
      }
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Vector<Data> localCopies[NUM_OF_VECTOR] = { *localVecs[0], *localVecs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0].Resize(1);
      localCopies[0][0] = randomInRange(Alphabet.Min(), Alphabet.Max());
      for (ulong i = 1; i < NUM_OF_VECTOR; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Multiply<lasd::Vector<Data>> = [&](lasd::Vector<Data>* localVecs[NUM_OF_VECTOR])
    {
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);
      localVecs[0]->operator=(getRandomTraversableContainer(Alphabet,2,20));
      for (ulong i = 1; i < NUM_OF_VECTOR; ++i) {
        *localVecs[i] = *localVecs[i-1];
      }
      TraversablesTest<Data, int>(*localVecs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localVecs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Vector<Data> localCopies[NUM_OF_VECTOR] = { *localVecs[0], *localVecs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0] = getRandomTraversableContainer(Alphabet,2,20);
      for (ulong i = 1; i < NUM_OF_VECTOR; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Empty<lasd::List<Data>> = [&](lasd::List<Data>* localLists[2*NUM_OF_LIST])
    {
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < 2*NUM_OF_LIST; ++i) {
        do {
          for (ulong j = 0; j < 2; j++)
            switch (randomInRange(0, 1)) {
              case 0: try{ localLists[i]->RemoveFromBack(); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromBack: " << e.what() << std::endl; }
                      break;
              case 1: try{ localLists[i]->RemoveFromFront(); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromFront: " << e.what() << std::endl; }
                      break;
            }
        } while (localLists[i]->Size() > 0 && !(localLists[i]->Empty()));
      }
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);

      lasd::List<Data> localCopies[2*NUM_OF_LIST] = { *localLists[0], *localLists[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0].Clear();
      for (ulong i = 1; i < 2*NUM_OF_LIST; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      for (ulong i = 0; i < 2*NUM_OF_LIST; ++i) {
        localCopies[i].Clear();
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Singletonize<lasd::List<Data>> = [&](lasd::List<Data>* localLists[2*NUM_OF_LIST])
    {
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < 2*NUM_OF_LIST; ++i) {
        while( localLists[i]->Size() > 2) {
          for (ulong j = 0; j < 2; j++)
            switch (randomInRange(0, 1)) {
              case 0: try{ localLists[i]->RemoveFromBack(); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromBack: " << e.what() << std::endl; }
                      break;
              case 1: try{ localLists[i]->RemoveFromFront(); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromFront: " << e.what() << std::endl; }
                      break;
            }
        }
      }
      if (localLists[0]->Size() == 2)
        localLists[0]->RemoveFromBack();
      if (localLists[0]->Empty()) {
        Data dat = randomOutRange(Alphabet.Min(), Alphabet.Max());
        switch (randomInRange(0, 1)) {
          case 0: try{ localLists[0]->InsertAtBack(dat); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromBack: " << e.what() << std::endl; }
                  break;
          case 1: try{ localLists[0]->InsertAtFront(dat); } catch (std::length_error &e) { std::cout << "Exception in RemoveFromFront: " << e.what() << std::endl; }
                  break;
        }
      }
      for (ulong i = 1; i < 2*NUM_OF_LIST; ++i) {
        *localLists[i] = *localLists[i-1];
      }
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);

      lasd::List<Data> localCopies[2*NUM_OF_LIST] = { *localLists[0], *localLists[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0][0] = randomInRange(Alphabet.Min(), Alphabet.Max());
      for (ulong i = 1; i < 2*NUM_OF_LIST; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Multiply<lasd::List<Data>> = [&](lasd::List<Data>* localLists[2*NUM_OF_LIST])
    {
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);
      const lasd::LinearContainer<Data>& localLinear = getRandomTraversableContainer(Alphabet,2,20);
      do {
        for (ulong j = 0; j < 2; j++)
          switch (randomInRange(0, 1)) {
            case 0: localLists[0]->InsertAtBack(localLinear[randomInRange(0, localLinear.Size() - 1)]); // size protected
                  break;
            case 1: localLists[0]->InsertAtFront(localLinear[randomInRange(0, localLinear.Size() - 1)]);
                  break;
          }
      } while (localLists[0]->Size() < localLinear.Size());
      for (ulong i = 1; i < 2*NUM_OF_LIST; ++i) {
        *localLists[i] = *localLists[i-1];
      }
      TraversablesTest<Data, int>(*localLists[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localLists[1], travF<Data>, foldF<Data, int>, 0);

      lasd::List<Data> localCopies[2*NUM_OF_LIST] = { *localLists[0], *localLists[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      ulong maxSize = randomInRange(2, 20);
      do {
        for (ulong j = 0; j < 2; j++)
          switch (randomInRange(0, 1)) {
            case 0: localCopies[0].InsertAtBack(randomOutRange(Alphabet.Min(), Alphabet.Max()));
                  break;
            case 1: localCopies[0].InsertAtFront(randomOutRange(Alphabet.Min(), Alphabet.Max()));
                  break;
          }
      } while (localCopies[0].Size() < maxSize);
      for (ulong i = 1; i < 2*NUM_OF_LIST; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Empty<lasd::Set<Data>> = [&](lasd::Set<Data>* localSets[NUM_OF_SET])
    {
      lasd::SetVec<Data> vecCopies[NUM_OF_SET];
      lasd::SetLst<Data> lstCopies[NUM_OF_SET];
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        localSets[i]->Clear();
      }
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Set<Data>* localCopies[NUM_OF_SET] {};
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        if (typeid(*localSets[i]) == typeid(lasd::SetVec<Data>)) {
          vecCopies[i] = lasd::SetVec<Data>(*dynamic_cast<lasd::SetVec<Data>*>(localSets[i]));
          localCopies[i] = &vecCopies[i];
        } else if (typeid(*localSets[i]) == typeid(lasd::SetLst<Data>)) {
          lstCopies[i] = lasd::SetLst<Data>(*dynamic_cast<lasd::SetLst<Data>*>(localSets[i]));
          localCopies[i] = &lstCopies[i];
        }
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0]->Clear();
      for (ulong i = 1; i < NUM_OF_SET; ++i) {
        localCopies[i]->RemoveAll(*localCopies[i]);
        localCopies[i]->InsertAll(std::move(*localCopies[i-1])); // Traversable && ~ const Traversable&
      }
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        localCopies[i]->Clear();
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Singletonize<lasd::Set<Data>> = [&](lasd::Set<Data>* localSets[NUM_OF_SET])
    {
      lasd::SetVec<Data> vecCopies[NUM_OF_SET];
      lasd::SetLst<Data> lstCopies[NUM_OF_SET];
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        while( localSets[i]->Size() > 1) {
          switch (randomInRange(0, 4)) {
            case 0: try{ localSets[i]->Remove(randomOutRange(Alphabet.Min(), Alphabet.Max())); } catch (std::length_error &e) { std::cout << "Exception in Remove: " << e.what() << std::endl; }
                    break;
            case 1: try{ localSets[i]->RemovePredecessor(randomOutRange(Alphabet.Min(), Alphabet.Max())); } catch (std::length_error &e) { std::cout << "Exception in RemovePredescesor: " << e.what() << std::endl; }
                    break;
            case 2: try{ localSets[i]->RemoveSuccessor(randomOutRange(Alphabet.Min(), Alphabet.Max())); } catch (std::length_error &e) { std::cout << "Exception in RemoveSuccessor: " << e.what() << std::endl; }
                    break;
            case 3: try{ localSets[i]->RemoveMin(); } catch (std::length_error &e) { std::cout << "Exception in RemoveMin: " << e.what() << std::endl; }
                    break;
            case 4: try{ localSets[i]->RemoveMax(); } catch (std::length_error &e) { std::cout << "Exception in RemoveMax: " << e.what() << std::endl; }
                    break;
          }
        }
      }
      lasd::Vector datas(getRandomUniqueTraversableContainer(Alphabet, 1, 1));
      for (ulong i = 0; i < NUM_OF_SET/2; ++i) { 
        if (localSets[i]->Empty()) {

          switch (randomInRange(0, 3)) {
            case 0: try{ localSets[i]->Insert(datas[randomInRange(0, datas.Size()-1)]); } catch (std::length_error &e) { std::cout << "Exception in Insert(cpy): " << e.what() << std::endl; }
                    break;
            case 1: try{ localSets[i]->InsertAll(datas); } catch (std::length_error &e) { std::cout << "Exception in InsertAll(cpy): " << e.what() << std::endl; }
                    break;
            case 2: try{ localSets[i]->Insert(randomOutRange(Alphabet.Min(), Alphabet.Max())); } catch (std::length_error &e) { std::cout << "Exception in Insert(move): " << e.what() << std::endl; }
                    break;
            case 3: try{ localSets[i]->InsertSome(getRandomTraversableContainer(Alphabet, 1, 1)); } catch (std::length_error &e) { std::cout << "Exception in InsertSome(move): " << e.what() << std::endl; }
          }
        }
      }
      for (ulong i = NUM_OF_SET/2; i < NUM_OF_SET; ++i) {
        localSets[i]->RemoveSome(*localSets[i]);
        localSets[i]->InsertSome(*localSets[i-1]);
      }
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Set<Data>* localCopies[NUM_OF_SET] {};
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        if (typeid(*localSets[i]) == typeid(lasd::SetVec<Data>)) {
          vecCopies[i] = lasd::SetVec<Data>(*dynamic_cast<lasd::SetVec<Data>*>(localSets[i]));
          localCopies[i] = &vecCopies[i];
        } else if (typeid(*localSets[i]) == typeid(lasd::SetLst<Data>)) {
          lstCopies[i] = lasd::SetLst<Data>(*dynamic_cast<lasd::SetLst<Data>*>(localSets[i]));
          localCopies[i] = &lstCopies[i];
        }
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
      if (!(localCopies[0] == &vecCopies[0])^(localCopies[1]==&vecCopies[1])) {
        if (localCopies[1] == &vecCopies[1]) {
            *dynamic_cast<lasd::SetVec<Data>*>(localCopies[1]) = std::move(*dynamic_cast<lasd::SetVec<Data>*>(localCopies[0]));
        } else {
            *dynamic_cast<lasd::SetLst<Data>*>(localCopies[1]) = std::move(*dynamic_cast<lasd::SetLst<Data>*>(localCopies[0]));
        }      
      }else
      {
        localCopies[1]->RemoveSome(*localCopies[1]);
        localCopies[1]->InsertSome(*localCopies[0]);
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Multiply<lasd::Set<Data>> = [&](lasd::Set<Data>* localSets[NUM_OF_SET])
    {
      lasd::SetVec<Data> vecCopies[NUM_OF_SET];
      lasd::SetLst<Data> lstCopies[NUM_OF_SET];
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);
      const lasd::LinearContainer<Data>& localLinear = getRandomUniqueTraversableContainer(Alphabet,2,20);
      do {
        for (ulong j = 0; j < 2; j++)
          switch (randomInRange(0, 1)) {
            case 0: localSets[0]->Insert(localLinear[randomInRange(0, localLinear.Size() - 1)]); // size protected
                  break;
            case 1: try {localSets[0]->Insert(randomOutRange(localSets[0]->Min(), localSets[0]->Max())); } catch (std::length_error &e) {};
                  break;
          }
      } while (localSets[0]->Size() < localLinear.Size());
      for (ulong i = NUM_OF_SET/2; i < NUM_OF_SET; ++i) {
        localSets[i]->InsertAll(*localSets[i-1]);
      }
      TraversablesTest<Data, int>(*localSets[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localSets[1], travF<Data>, foldF<Data, int>, 0);

      lasd::Set<Data>* localCopies[NUM_OF_SET] {};
      for (ulong i = 0; i < NUM_OF_SET; ++i) {
        if (typeid(*localSets[i]) == typeid(lasd::SetVec<Data>)) {
          vecCopies[i] = lasd::SetVec<Data>(*dynamic_cast<lasd::SetVec<Data>*>(localSets[i]));
          localCopies[i] = &vecCopies[i];
        } else if (typeid(*localSets[i]) == typeid(lasd::SetLst<Data>)) {
          lstCopies[i] = lasd::SetLst<Data>(*dynamic_cast<lasd::SetLst<Data>*>(localSets[i]));
          localCopies[i] = &lstCopies[i];
        }
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
      if (!(localCopies[0] == &vecCopies[0])^(localCopies[1]==&vecCopies[1])) {
        if (localCopies[1] == &vecCopies[1]) {
            *dynamic_cast<lasd::SetVec<Data>*>(localCopies[1]) = std::move(*dynamic_cast<lasd::SetVec<Data>*>(localCopies[0]));
        } else {
            *dynamic_cast<lasd::SetLst<Data>*>(localCopies[1]) = std::move(*dynamic_cast<lasd::SetLst<Data>*>(localCopies[0]));
        }      
      }
      else
      {
        localCopies[1]->RemoveSome(*localCopies[1]);
        localCopies[1]->InsertSome(*localCopies[0]);
      }
      TraversablesTest<Data, int>(*localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Empty<lasd::PQHeap<Data>> = [&](lasd::PQHeap<Data>* localPQs[NUM_OF_PQ])
    {
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < 2*NUM_OF_PQ; ++i) {
        while (localPQs[i]->Size() > 0) {
          try { localPQs[i]->RemoveTip(); } catch (std::length_error &e) { std::cout << "Exception in RemoveMin: " << e.what() << std::endl; }
        }
      }
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::PQHeap<Data> localCopies[2*NUM_OF_PQ] = { *localPQs[0], *localPQs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0].Clear();
      for (ulong i = 1; i < 2*NUM_OF_PQ; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      for (ulong i = 0; i < 2*NUM_OF_PQ; ++i) {
        localCopies[i].Clear();
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Singletonize<lasd::PQHeap<Data>> = [&](lasd::PQHeap<Data>* localPQs[NUM_OF_PQ])
    {
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);
      for (ulong i = 0; i < 2*NUM_OF_PQ; ++i) {
        while (localPQs[i]->Size() > 1) {
          try { localPQs[i]->RemoveTip(); } catch (std::length_error &e) { std::cout << "Exception in RemoveMin: " << e.what() << std::endl; }
        }
      }
      if (localPQs[0]->Size() == 1)
        localPQs[0]->RemoveTip();
      if (localPQs[0]->Empty()) {
        Data dat = randomInRange(Alphabet.Min(), Alphabet.Max());
        try { localPQs[0]->Insert(dat); } catch (std::length_error &e) { std::cout << "Exception in Insert(cpy): " << e.what() << std::endl; }
      }
      for (ulong i = 1; i < 2*NUM_OF_PQ; ++i) {
        *localPQs[i] = *localPQs[i-1];
      }
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::PQHeap<Data> localCopies[2*NUM_OF_PQ] = { *localPQs[0], *localPQs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      localCopies[0].Change(0, randomInRange(Alphabet.Min(), Alphabet.Max()));
      for (ulong i = 1; i < 2*NUM_OF_PQ; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    Multiply<lasd::PQHeap<Data>> = [&](lasd::PQHeap<Data>* localPQs[NUM_OF_PQ])
    {
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);
      const lasd::LinearContainer<Data>& localLinear = getRandomTraversableContainer(Alphabet,2,20);
      do {
        for (ulong j = 0; j < 2; j++)
          switch (randomInRange(0, 1)) {
            case 0: localPQs[0]->Insert(localLinear[randomInRange(0, localLinear.Size() - 1)]); // size protected
                  break;
            case 1: localPQs[0]->Insert(randomOutRange(Alphabet.Min(), Alphabet.Max()));
                  break;
          }
      } while (localPQs[0]->Size() < localLinear.Size());
      for (ulong i = 1; i < NUM_OF_PQ; ++i) {
        *localPQs[i] = *localPQs[i-1];
      }
      TraversablesTest<Data, int>(*localPQs[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(*localPQs[1], travF<Data>, foldF<Data, int>, 0);

      lasd::PQHeap<Data> localCopies[2*NUM_OF_PQ] = { *localPQs[0], *localPQs[1] };
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
      ulong maxSize = randomInRange(2, 20);
      do {
        for (ulong j = 0; j < 2; j++)
          switch (randomInRange(0, 1)) {
            case 0: localCopies[0].Insert(randomOutRange(Alphabet.Min(), Alphabet.Max()));
                  break;
            case 1: localCopies[0].Insert(randomOutRange(Alphabet.Min(), Alphabet.Max()));
                  break;
          }
      } while (localCopies[0].Size() < maxSize);
      for (ulong i = 1; i < NUM_OF_PQ; ++i) {
        localCopies[i] = std::move(localCopies[i-1]);
      }
      TraversablesTest<Data, int>(localCopies[0], travF<Data>, foldF<Data, int>, 0);
      TraversablesTest<Data, int>(localCopies[1], travF<Data>, foldF<Data, int>, 0);
    };

    bool executed[4]{};
    while (!executed[0] || !executed[1] || !executed[2] || !executed[3]) {
      switch(randomInRange(static_cast<int>(Algebra::VEC), static_cast<int>(Algebra::PQ)))
      {
        case static_cast<int>(Algebra::VEC):
          if (executed[0]) break;
          std::cout << "Testing a Vector" << std::endl;
          std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
          {
            std::string ans;
            std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
            if (ans == "1") {
              std::cout << testBox;
              std::cout << "Press Enter to continue..." << std::endl;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
          }
          std::cout << "Random seed: " << BoxRandomTester<Data>::seed << std::endl; 
          {
            static bool done[6]{};
            if (!done[0]) { Empty<lasd::Vector<Data>>(localVecs); done[0] = true; break; }
            if (!done[1]) { Singletonize<lasd::Vector<Data>>(localVecs); done[1] = true; break; }
            if (!done[2]) { Empty<lasd::Vector<Data>>(localVecs); done[2] = true; break; }          
            if (!done[3]) { Multiply<lasd::Vector<Data>>(localVecs); done[3] = true; break; }
            if (!done[4]) { Singletonize<lasd::Vector<Data>>(localVecs); done[4] = true; break; }
            if (!done[5]) { Empty<lasd::Vector<Data>>(localVecs); done[5] = true; }
          }
          executed[0] = true;
          break;
        case static_cast<int>(Algebra::LST): {
          if (executed[1]) break;
          std::cout << "Testing a List" << std::endl;
          std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
          {
            std::string ans;
            std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
            if (ans == "1") {
              std::cout << testBox;
              std::cout << "Press Enter to continue..." << std::endl;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
          }
          std::cout << "Random seed: " << BoxRandomTester<Data>::seed << std::endl;           
          {
            static bool done[6]{};
            if (!done[0]) { Empty<lasd::List<Data>>(localLists); done[0] = true; break; }
            if (!done[1]) { Singletonize<lasd::List<Data>>(localLists); done[1] = true; break; }
            if (!done[2]) { Empty<lasd::List<Data>>(localLists); done[2] = true; break; }          
            if (!done[3]) { Multiply<lasd::List<Data>>(localLists); done[3] = true; break; }
            if (!done[4]) { Singletonize<lasd::List<Data>>(localLists); done[4] = true; break; }
            if (!done[5]) { Empty<lasd::List<Data>>(localLists); done[5] = true; }
          }
          executed[1] = true;
          break;
        }
        case static_cast<int>(Algebra::SET): {
          if (executed[2]) break;
          std::cout << "Testing a Set" << std::endl;
          std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
          {
            std::string ans;
            std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
            if (ans == "1") {
              std::cout << testBox;
              std::cout << "Press Enter to continue..." << std::endl;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
          }
          std::cout << "Random seed: " << BoxRandomTester<Data>::seed << std::endl;           
          {
            static bool done[6]{};
            if (!done[0]) { Empty<lasd::Set<Data>>(localSets); done[0] = true; break; }
            if (!done[1]) { Singletonize<lasd::Set<Data>>(localSets); done[1] = true; break; }
            if (!done[2]) { Empty<lasd::Set<Data>>(localSets); done[2] = true; break; }          
            if (!done[3]) { Multiply<lasd::Set<Data>>(localSets); done[3] = true; break; }
            if (!done[4]) { Singletonize<lasd::Set<Data>>(localSets); done[4] = true; break; }
            if (!done[5]) { Empty<lasd::Set<Data>>(localSets); done[5] = true; }
          }
          executed[2] = true;
          break;
        }
        case static_cast<int>(Algebra::PQ): {
          if (executed[3]) break;
          std::cout << "Testing a Priority Queue" << std::endl;
          std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
          {
            std::string ans;
            std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
            if (ans == "1") {
              std::cout << testBox;
              std::cout << "Press Enter to continue..." << std::endl;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
          }
          std::cout << "Random seed: " << BoxRandomTester<Data>::seed << std::endl;           
          {
            static bool done[6]{};
            if (!done[0]) { Empty<lasd::PQHeap<Data>>(localPQs); done[0] = true; break; }
            if (!done[1]) { Singletonize<lasd::PQHeap<Data>>(localPQs); done[1] = true; break; }
            if (!done[2]) { Empty<lasd::PQHeap<Data>>(localPQs); done[2] = true; break; }          
            if (!done[3]) { Multiply<lasd::PQHeap<Data>>(localPQs); done[3] = true; break; }
            if (!done[4]) { Singletonize<lasd::PQHeap<Data>>(localPQs); done[4] = true; break; }
            if (!done[5]) { Empty<lasd::PQHeap<Data>>(localPQs); done[5] = true; }
          }
          executed[3] = true;
          break;
        }
      }
    }
  }

} // namespace myT

using namespace myT;

template <typename Box>
Box *globalBox;

void mytest()
{
  // ...
  
  srand(BoxRandomTester<DataT>::seed);

  std::cout << "Random seed: " << BoxRandomTester<DataT>::seed << std::endl;
  
  BoxRandomTester<DataT> boxTester;
  std::vector<DataT> alphabetData = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
  boxTester.vector1 = lasd::Vector<DataT>(alphabetData.size());
  {
    int i = 0;
    boxTester.vector1.Map(
      [&i, &alphabetData](DataT &dat)
      {
        dat = alphabetData[i++];
      }
    );
  }
  boxTester.setVec2 = lasd::SetVec<DataT>(boxTester.vector1);
  mapF<DataT> = [](DataT &dat)
  {
    dat = DataT("mapped_" + dat.buffer);
  };
  travF<DataT> = [](const DataT &dat)
  {
    std::cout << dat << ", ";
  };
  foldF<DataT, int> = [&](const DataT &dat, const int &acc)
  {
    return acc + (boxTester.setVec2.Exists(dat) ? 1 : 0);
  };

  std::cout << "Gentest1:" << std::endl;
  Gentest1<DataT>(boxTester.setVec2);
  std::cout << "Gentest2:" << std::endl;
  Gentest2<DataT>(boxTester.setVec2);

  std::cout << "\nvector1 contents: ";
  boxTester.vector1.Map(
    [](DataT &dat)
    {
      std::cout << dat << " ";
    }
  );
  std::cout << std::endl;

  /* Prova */ {

    using Box = lasd::SetVec<DataT>;
    globalBox<Box> = &boxTester.setVec1;

    std::cout << globalBox<Box>->Size() << std::endl;
    std::cout << (globalBox<Box>->Empty() ? "true" : "false") << std::endl;

    // ClearableContainer
    globalBox<Box>->Clear();

    // // ResizableContainer
    // globalBox<Box>->Resize(20);

    // TestableContainer
    std::cout<< (globalBox<Box>->Exists(alphabetData[0])? "true":"false") << std::endl;
    
    // OrderedDictionaryContainer
    globalBox<Box>->Insert(alphabetData[0]);
    globalBox<Box>->Insert(myT::MyType("new_data"));
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    globalBox<Box>->Remove(alphabetData[0]);
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    globalBox<Box>->InsertAll(boxTester.vector1);
    globalBox<Box>->InsertAll(lasd::Vector(boxTester.vector1));
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    globalBox<Box>->RemoveAll(boxTester.vector1);
    globalBox<Box>->RemoveSome(boxTester.vector1);
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    globalBox<Box>->InsertSome(boxTester.vector1);
    globalBox<Box>->InsertSome(lasd::Vector(boxTester.vector1));
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { std::cout << globalBox<Box>->Min() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    try { std::cout << globalBox<Box>->MinNRemove() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { globalBox<Box>->RemoveMin();
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { std::cout << globalBox<Box>->Max() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    try { std::cout << globalBox<Box>->MaxNRemove() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { globalBox<Box>->RemoveMax();
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { std::cout << globalBox<Box>->Predecessor(alphabetData[0]) << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    try { std::cout << globalBox<Box>->PredecessorNRemove(alphabetData[0]) << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { globalBox<Box>->RemovePredecessor(alphabetData[0]);
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { std::cout << globalBox<Box>->Successor(alphabetData[0]) << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    try { std::cout << globalBox<Box>->SuccessorNRemove(alphabetData[0]) << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    try { globalBox<Box>->RemoveSuccessor(alphabetData[0]);
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }

    // // MutableLinear
    // globalBox<Box>->Map([](DataT &dat) { dat = DataT("mapped_" + dat.buffer); });
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // globalBox<Box>->PostOrderMap([](DataT &dat) { dat = DataT("mapped_" + dat.buffer); }); std::cout << std::endl;
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // globalBox<Box>->PreOrderMap([](DataT &dat) { dat = DataT("mapped_" + dat.buffer); }); std::cout << std::endl;
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // try {
    //   std::cout << (globalBox<Box>->operator[](globalBox<Box>->Size()>>1) = DataT("modified")) << std::endl;
    // } catch (const std::out_of_range &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // try {
    //   std::cout << (globalBox<Box>->Front() = DataT("modified") ) << std::endl;
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // try {
    //   std::cout << (globalBox<Box>->Back() = DataT("modified") ) << std::endl;
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }

    // LinearContainer
    globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    std::cout << globalBox<Box>->Fold<DataT>([](const DataT &dat, const DataT &acc) { return DataT(acc.buffer + dat.buffer + ". "); }, DataT()) << std::endl;
    globalBox<Box>->PostOrderTraverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    std::cout << globalBox<Box>->PostOrderFold<DataT>([](const DataT &dat, const DataT &acc) { return DataT(acc.buffer + dat.buffer + ". "); }, DataT()) << std::endl;
    globalBox<Box>->PreOrderTraverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    std::cout << globalBox<Box>->PreOrderFold<DataT>([](const DataT &dat, const DataT &acc) { return DataT(acc.buffer + dat.buffer + ". "); }, DataT()) << std::endl;
    std::cout << (((*globalBox<Box>) == (*globalBox<Box>)) ? "true" : "false") << std::endl;
    std::cout << (((*globalBox<Box>) != (*globalBox<Box>)) ? "true" : "false") << std::endl;
    try {
      std::cout << static_cast<const Box*>(globalBox<Box>)->operator[](globalBox<Box>->Size()>>1) << std::endl;
    } catch (const std::out_of_range &e) {
      std::cout << e.what() << std::endl;
    }
    try {
      std::cout << static_cast<const Box*>(globalBox<Box>)->Front() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }
    try {
      std::cout << static_cast<const Box*>(globalBox<Box>)->Back() << std::endl;
    } catch (const std::length_error &e) {
      std::cout << e.what() << std::endl;
    }

    // // SortableLinear
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;    globalBox<Box>->Sort();
    // globalBox<Box>->Sort();
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // globalBox<Box>->operator[](globalBox<Box>->Size()>>1)= DataT("A");
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // globalBox<Box>->Sort();
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;

    // // List
    // globalBox<Box>->InsertAtBack(myT::MyType("new_data1"));
    // globalBox<Box>->InsertAtFront(alphabetData[0]);
    // globalBox<Box>->InsertAtFront(myT::MyType("new_data"));
    // globalBox<Box>->InsertAtBack(alphabetData[1]);
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // try {
    //   globalBox<Box>->RemoveFromBack();
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // try {
    //   globalBox<Box>->RemoveFromFront();
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // try {
    //   std::cout << globalBox<Box>->BackNRemove() << std::endl;
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;
    // try {
    //   std::cout << globalBox<Box>->FrontNRemove() << std::endl;
    // } catch (const std::length_error &e) {
    //   std::cout << e.what() << std::endl;
    // }
    // globalBox<Box>->Traverse([](const DataT &dat){std::cout << dat << ", ";}); std::cout << std::endl;

  }

  std::cout << "Random seed: " << BoxRandomTester<DataT>::seed << std::endl;
  std::cin.get();
}
