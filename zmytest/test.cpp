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

/* ************************************************************************** */

using namespace std;

namespace myT
{

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
  void TraversablesTest(lasd::TraversableContainer<Data> &box, Data init)
  {
    std::cout << "----------------------------------------TraversablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Begin traversing through the box: " << std::endl;
    box.Traverse(
        [](const Data &dat)
        {
          std::cout << dat << ", " << std::endl;
        });
    std::cout << "End traversing through the box" << std::endl;

    std::cout << "Fold of the box begining with: " << init << std::endl;
    std::cout << box.Fold(
                     [](const Data &dat, const Data &acc)
                     {
                       return acc + dat;
                     },
                     init)
              << std::endl;
  }

  template <typename Data>
  void PreOrderTraversablesTest(lasd::PreOrderTraversableContainer<Data> &box, Data init)
  {
    std::cout << "----------------------------------------PreOrderTraversablesTest: ";
    std::cout << typeid(box).name();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Begin traversing through the box: " << std::endl;
    box.Traverse(
        [](const Data &dat)
        {
          std::cout << dat << ", " << std::endl;
        });

    std::cout << "Begin traversing(PREORDER) through the box: " << std::endl;
    box.PreOrderTraverse(
        [](const Data &dat)
        {
          std::cout << dat << ", " << std::endl;
        });
    std::cout << "End traversing through the box" << std::endl;
    std::cout << "Fold of the box begining with: " << init << std::endl;
    std::cout << box.Fold(
      [](const Data &dat, const Data &acc)
      {
        return acc + dat;
      },
      init)
    << std::endl;
  }

  template <typename Data>
  class BoxRandomTester;

  template <typename Data>
  BoxRandomTester<Data> EmptyBoxes()
  {
    return BoxRandomTester<Data>();
  }

  template <typename Data>
  lasd::Vector<Data> getRandomTraversableContainer(const lasd::Vector<Data> &Alphabet, ulong min, ulong max)
  {
    ulong size = min + (rand() % (std::max(0, static_cast<int>(max - min + 1))));
    lasd::Vector<Data> travCont(size);

    travCont.Map(
      [Alphabet](Data &dat)
      {
        dat = Alphabet[rand() % Alphabet.Size()];
      }
    );

    return std::move(travCont);
  }

  template <typename Data>
  lasd::Vector<Data> getRandomUniqueTraversableContainer(const lasd::Vector<Data> &Alphabet, ulong min, ulong max)
  {
    lasd::SetVec<Data> uniquesAlphabet(Alphabet);
    max = std::min(max, uniquesAlphabet.Size());
    ulong size = min + (rand() % (std::max(0, static_cast<int>(max - min + 1))));
  
    std::vector<ulong> indices(uniquesAlphabet.Size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device{}()));

    lasd::Vector<Data> travCont(size);
    for (ulong i = 0; i < size; ++i) {
      travCont[i] = Alphabet[indices[i]];
    }

    return std::move(travCont);
  }

  template <typename Data>
  BoxRandomTester<Data> MonoBoxes(const lasd::Vector<Data> &Alphabet) {
    BoxRandomTester<Data> testBox(
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 1, 1))
    );

    return std::move(testBox);
  }

  template <typename Data>
  BoxRandomTester<Data> MultiBoxes(const lasd::Vector<Data> &Alphabet, ulong maxsize) {
    BoxRandomTester<Data> testBox(
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::List<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::Vector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetLst<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SetVec<Data>(getRandomUniqueTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize)),
      lasd::SortableVector<Data>(getRandomTraversableContainer<Data>(Alphabet, 2, maxsize))
    );

    return std::move(testBox);
  }
    
  template <typename Data>
  class BoxRandomTester
  {
  public:

    static const time_t seed;
    
    lasd::Container &vectorContainer;
    lasd::Container &listContainer;
    lasd::Container &setVecContainer;
    lasd::Container &setLstContainer;
    lasd::Container &sortVecContainer;
    lasd::TestableContainer<Data> &testableVectorContainer;
    lasd::TestableContainer<Data> &testableListContainer;
    lasd::TestableContainer<Data> &testableSetVecContainer;
    lasd::TestableContainer<Data> &testableSetLstContainer;
    lasd::TestableContainer<Data> &testableSortVecContainer;
    lasd::ClearableContainer &clearableVectorContainer;
    lasd::ClearableContainer &clearableListContainer;
    lasd::ClearableContainer &clearableSetVecContainer;
    lasd::ClearableContainer &clearableSetLstContainer;
    lasd::ResizableContainer &resizableVectorContainer;
    lasd::ResizableContainer &resizableSortVecContainer;
    lasd::DictionaryContainer<Data> &dictionarySetVecContainer;
    lasd::DictionaryContainer<Data> &dictionarySetLstContainer;
    lasd::TraversableContainer<Data> &traversableVectorContainer;
    lasd::TraversableContainer<Data> &traversableListContainer;
    lasd::TraversableContainer<Data> &traversableSetVecContainer;
    lasd::TraversableContainer<Data> &traversableSetLstContainer;
    lasd::TraversableContainer<Data> &traversableSortVecContainer;
    lasd::OrderedDictionaryContainer<Data> &orderedDictionarySetVecContainer;
    lasd::OrderedDictionaryContainer<Data> &orderedDictionarySetLstContainer;
    lasd::MappableContainer<Data> &mappableVectorContainer;
    lasd::MappableContainer<Data> &mappableListContainer;
    lasd::MappableContainer<Data> &mappableSortVecContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableVectorContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableListContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSetVecContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSetLstContainer;
    lasd::PreOrderTraversableContainer<Data> &preOrderTraversableSortVecContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableVectorContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableListContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSetVecContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSetLstContainer;
    lasd::PostOrderTraversableContainer<Data> &postOrderTraversableSortVecContainer;
    lasd::PreOrderMappableContainer<Data> &preOrderMappableVectorContainer;
    lasd::PreOrderMappableContainer<Data> &preOrderMappableListContainer;
    lasd::PreOrderMappableContainer<Data> &preOrderMappableSortVecContainer;
    lasd::PostOrderMappableContainer<Data> &postOrderMappableVectorContainer;
    lasd::PostOrderMappableContainer<Data> &postOrderMappableListContainer;
    lasd::PostOrderMappableContainer<Data> &postOrderMappableSortVecContainer;
    lasd::LinearContainer<Data> &linearVectorContainer;
    lasd::LinearContainer<Data> &linearListContainer;
    lasd::LinearContainer<Data> &linearSetVecContainer;
    lasd::LinearContainer<Data> &linearSetLstContainer;
    lasd::LinearContainer<Data> &linearSortVecContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearVectorContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearListContainer;
    lasd::MutableLinearContainer<Data> &mutableLinearSortVecContainer;
    lasd::SortableLinearContainer<Data> &sortableLinearSortVec1Container;
    lasd::SortableLinearContainer<Data> &sortableLinearSortVec2Container;
    lasd::List<Data> &list1;
    lasd::List<Data> &list2;
    lasd::Set<Data> &setVec;
    lasd::Set<Data> &setLst;
    lasd::Vector<Data> &vector1;
    lasd::Vector<Data> &vector2;
    lasd::SetLst<Data> &setLst1;
    lasd::SetLst<Data> &setLst2;
    lasd::SetVec<Data> &setVec1;
    lasd::SetVec<Data> &setVec2;
    lasd::SortableVector<Data> &sortableVector1;
    lasd::SortableVector<Data> &sortableVector2;

    BoxRandomTester(const BoxRandomTester<Data> &) = delete;
    BoxRandomTester<Data> &operator=(const BoxRandomTester<Data> &) = delete;

    BoxRandomTester &operator=(BoxRandomTester<Data> &&other)
    {
      *dynamic_cast<lasd::Vector<Data>*>(&vectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&listContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.listContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&testableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.testableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&testableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.testableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&testableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.testableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&testableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.testableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&testableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.testableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&clearableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.clearableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&clearableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.clearableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&clearableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.clearableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&clearableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.clearableSetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&resizableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.resizableVectorContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&resizableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.resizableSortVecContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&dictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.dictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&dictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.dictionarySetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&traversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.traversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&traversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.traversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&traversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.traversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&traversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.traversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&traversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.traversableSortVecContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&orderedDictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.orderedDictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&orderedDictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.orderedDictionarySetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&mappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.mappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&mappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.mappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&mappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.mappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&preOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.preOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&preOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.preOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&preOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.preOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&preOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.preOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&preOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.preOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&postOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.postOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&postOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.postOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&postOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.postOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&postOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.postOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&postOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.postOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&preOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.preOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&preOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.preOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&preOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.preOrderMappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&postOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.postOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&postOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.postOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&postOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.postOrderMappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&linearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.linearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&linearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.linearListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&linearSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.linearSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&linearSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.linearSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&linearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.linearSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&mutableLinearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.mutableLinearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&mutableLinearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(other.mutableLinearListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&mutableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.mutableLinearSortVecContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableLinearSortVec1Container) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableLinearSortVec1Container));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableLinearSortVec2Container) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableLinearSortVec2Container));
      *dynamic_cast<lasd::List<Data>*>(&list1) = std::move(dynamic_cast<lasd::List<Data>&>(other.list1));
      *dynamic_cast<lasd::List<Data>*>(&list2) = std::move(dynamic_cast<lasd::List<Data>&>(other.list2));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVec));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLst));
      *dynamic_cast<lasd::Vector<Data>*>(&vector1) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vector1));
      *dynamic_cast<lasd::Vector<Data>*>(&vector2) = std::move(dynamic_cast<lasd::Vector<Data>&>(other.vector2));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst1) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLst1));
      *dynamic_cast<lasd::SetLst<Data>*>(&setLst2) = std::move(dynamic_cast<lasd::SetLst<Data>&>(other.setLst2));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec1) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVec1));
      *dynamic_cast<lasd::SetVec<Data>*>(&setVec2) = std::move(dynamic_cast<lasd::SetVec<Data>&>(other.setVec2));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableVector1) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableVector1));
      *dynamic_cast<lasd::SortableVector<Data>*>(&sortableVector2) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(other.sortableVector2));


      return *this;
    }

    BoxRandomTester(BoxRandomTester<Data> &&other)
      noexcept : BoxRandomTester<Data>() {
        (*this) = std::move(other);
    }


    BoxRandomTester()
    : vectorContainer(*new lasd::Vector<Data>()),
    listContainer(*new lasd::List<Data>()),
    setVecContainer(*new lasd::SetVec<Data>()),
    setLstContainer(*new lasd::SetLst<Data>()),
    sortVecContainer(*new lasd::SortableVector<Data>()),
    testableVectorContainer(*new lasd::Vector<Data>()),
    testableListContainer(*new lasd::List<Data>()),
    testableSetVecContainer(*new lasd::SetVec<Data>()),
    testableSetLstContainer(*new lasd::SetLst<Data>()),
    testableSortVecContainer(*new lasd::SortableVector<Data>()),
    clearableVectorContainer(*new lasd::Vector<Data>()),
    clearableListContainer(*new lasd::List<Data>()),
    clearableSetVecContainer(*new lasd::SetVec<Data>()),
    clearableSetLstContainer(*new lasd::SetLst<Data>()),
    resizableVectorContainer(*new lasd::Vector<Data>()),
    resizableSortVecContainer(*new lasd::SortableVector<Data>()),
    dictionarySetVecContainer(*new lasd::SetVec<Data>()),
    dictionarySetLstContainer(*new lasd::SetLst<Data>()),
    traversableVectorContainer(*new lasd::Vector<Data>()),
    traversableListContainer(*new lasd::List<Data>()),
    traversableSetVecContainer(*new lasd::SetVec<Data>()),
    traversableSetLstContainer(*new lasd::SetLst<Data>()),
    traversableSortVecContainer(*new lasd::SortableVector<Data>()),
    orderedDictionarySetVecContainer(*new lasd::SetVec<Data>()),
    orderedDictionarySetLstContainer(*new lasd::SetLst<Data>()),
    mappableVectorContainer(*new lasd::Vector<Data>()),
    mappableListContainer(*new lasd::List<Data>()),
    mappableSortVecContainer(*new lasd::SortableVector<Data>()),
    preOrderTraversableVectorContainer(*new lasd::Vector<Data>()),
    preOrderTraversableListContainer(*new lasd::List<Data>()),
    preOrderTraversableSetVecContainer(*new lasd::SetVec<Data>()),
    preOrderTraversableSetLstContainer(*new lasd::SetLst<Data>()),
    preOrderTraversableSortVecContainer(*new lasd::SortableVector<Data>()),
    postOrderTraversableVectorContainer(*new lasd::Vector<Data>()),
    postOrderTraversableListContainer(*new lasd::List<Data>()),
    postOrderTraversableSetVecContainer(*new lasd::SetVec<Data>()),
    postOrderTraversableSetLstContainer(*new lasd::SetLst<Data>()),
    postOrderTraversableSortVecContainer(*new lasd::SortableVector<Data>()),
    preOrderMappableVectorContainer(*new lasd::Vector<Data>()),
    preOrderMappableListContainer(*new lasd::List<Data>()),
    preOrderMappableSortVecContainer(*new lasd::SortableVector<Data>()),
    postOrderMappableVectorContainer(*new lasd::Vector<Data>()),
    postOrderMappableListContainer(*new lasd::List<Data>()),
    postOrderMappableSortVecContainer(*new lasd::SortableVector<Data>()),
    linearVectorContainer(*new lasd::Vector<Data>()),
    linearListContainer(*new lasd::List<Data>()),
    linearSetVecContainer(*new lasd::SetVec<Data>()),
    linearSetLstContainer(*new lasd::SetLst<Data>()),
    linearSortVecContainer(*new lasd::SortableVector<Data>()),
    mutableLinearVectorContainer(*new lasd::Vector<Data>()),
    mutableLinearListContainer(*new lasd::List<Data>()),
    mutableLinearSortVecContainer(*new lasd::SortableVector<Data>()),
    sortableLinearSortVec1Container(*new lasd::SortableVector<Data>()),
    sortableLinearSortVec2Container(*new lasd::SortableVector<Data>()),
    list1(*new lasd::List<Data>()),
    list2(*new lasd::List<Data>()),
    setVec(*new lasd::SetVec<Data>()),
    setLst(*new lasd::SetLst<Data>()),
    vector1(*new lasd::Vector<Data>()),
    vector2(*new lasd::Vector<Data>()),
    setLst1(*new lasd::SetLst<Data>()),
    setLst2(*new lasd::SetLst<Data>()),
    setVec1(*new lasd::SetVec<Data>()),
    setVec2(*new lasd::SetVec<Data>()),
    sortableVector1(*new lasd::SortableVector<Data>()),
    sortableVector2(*new lasd::SortableVector<Data>())
    {}

    BoxRandomTester
    (
      lasd::Container &&vectorContainer,
      lasd::Container &&listContainer,
      lasd::Container &&setVecContainer,
      lasd::Container &&setLstContainer,
      lasd::Container &&sortVecContainer,
      lasd::TestableContainer<Data> &&testableVectorContainer,
      lasd::TestableContainer<Data> &&testableListContainer,
      lasd::TestableContainer<Data> &&testableSetVecContainer,
      lasd::TestableContainer<Data> &&testableSetLstContainer,
      lasd::TestableContainer<Data> &&testableSortVecContainer,
      lasd::ClearableContainer &&clearableVectorContainer,
      lasd::ClearableContainer &&clearableListContainer,
      lasd::ClearableContainer &&clearableSetVecContainer,
      lasd::ClearableContainer &&clearableSetLstContainer,
      lasd::ResizableContainer &&resizableVectorContainer,
      lasd::ResizableContainer &&resizableSortVecContainer,
      lasd::DictionaryContainer<Data> &&dictionarySetVecContainer,
      lasd::DictionaryContainer<Data> &&dictionarySetLstContainer,
      lasd::TraversableContainer<Data> &&traversableVectorContainer,
      lasd::TraversableContainer<Data> &&traversableListContainer,
      lasd::TraversableContainer<Data> &&traversableSetVecContainer,
      lasd::TraversableContainer<Data> &&traversableSetLstContainer,
      lasd::TraversableContainer<Data> &&traversableSortVecContainer,
      lasd::OrderedDictionaryContainer<Data> &&orderedDictionarySetVecContainer,
      lasd::OrderedDictionaryContainer<Data> &&orderedDictionarySetLstContainer,
      lasd::MappableContainer<Data> &&mappableVectorContainer,
      lasd::MappableContainer<Data> &&mappableListContainer,
      lasd::MappableContainer<Data> &&mappableSortVecContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableVectorContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableListContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSetVecContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSetLstContainer,
      lasd::PreOrderTraversableContainer<Data> &&preOrderTraversableSortVecContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableVectorContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableListContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSetVecContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSetLstContainer,
      lasd::PostOrderTraversableContainer<Data> &&postOrderTraversableSortVecContainer,
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableVectorContainer,
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableListContainer,
      lasd::PreOrderMappableContainer<Data> &&preOrderMappableSortVecContainer,
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableVectorContainer,
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableListContainer,
      lasd::PostOrderMappableContainer<Data> &&postOrderMappableSortVecContainer,
      lasd::LinearContainer<Data> &&linearVectorContainer,
      lasd::LinearContainer<Data> &&linearListContainer,
      lasd::LinearContainer<Data> &&linearSetVecContainer,
      lasd::LinearContainer<Data> &&linearSetLstContainer,
      lasd::LinearContainer<Data> &&linearSortVecContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearVectorContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearListContainer,
      lasd::MutableLinearContainer<Data> &&mutableLinearSortVecContainer,
      lasd::SortableLinearContainer<Data> &&sortableLinearSortVec1Container,
      lasd::SortableLinearContainer<Data> &&sortableLinearSortVec2Container,
      lasd::List<Data> &&list1,
      lasd::List<Data> &&list2,
      lasd::Set<Data> &&setVec,
      lasd::Set<Data> &&setLst,
      lasd::Vector<Data> &&vector1,
      lasd::Vector<Data> &&vector2,
      lasd::SetLst<Data> &&setLst1,
      lasd::SetLst<Data> &&setLst2,
      lasd::SetVec<Data> &&setVec1,
      lasd::SetVec<Data> &&setVec2,
      lasd::SortableVector<Data> &&sortableVector1,
      lasd::SortableVector<Data> &&sortableVector2
    )
    : BoxRandomTester<Data>()
    {
      *dynamic_cast<lasd::Vector<Data>*>(&this->vectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(vectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->listContainer) = std::move(dynamic_cast<lasd::List<Data>&>(listContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->testableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(testableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->testableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(testableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->testableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(testableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->testableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(testableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->testableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(testableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->clearableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(clearableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->clearableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(clearableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->clearableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(clearableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->clearableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(clearableSetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->resizableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(resizableVectorContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->resizableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(resizableSortVecContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->dictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(dictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->dictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(dictionarySetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->traversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(traversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->traversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(traversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->traversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(traversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->traversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(traversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->traversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(traversableSortVecContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->orderedDictionarySetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(orderedDictionarySetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->orderedDictionarySetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(orderedDictionarySetLstContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->mappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(mappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->mappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(mappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->mappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(mappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->preOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(preOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->preOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(preOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->preOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(preOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->preOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(preOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->preOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(preOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->postOrderTraversableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(postOrderTraversableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->postOrderTraversableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(postOrderTraversableListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->postOrderTraversableSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(postOrderTraversableSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->postOrderTraversableSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(postOrderTraversableSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->postOrderTraversableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(postOrderTraversableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->preOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(preOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->preOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(preOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->preOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(preOrderMappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->postOrderMappableVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(postOrderMappableVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->postOrderMappableListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(postOrderMappableListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->postOrderMappableSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(postOrderMappableSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->linearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(linearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->linearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(linearListContainer));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->linearSetVecContainer) = std::move(dynamic_cast<lasd::SetVec<Data>&>(linearSetVecContainer));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->linearSetLstContainer) = std::move(dynamic_cast<lasd::SetLst<Data>&>(linearSetLstContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->linearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(linearSortVecContainer));
      *dynamic_cast<lasd::Vector<Data>*>(&this->mutableLinearVectorContainer) = std::move(dynamic_cast<lasd::Vector<Data>&>(mutableLinearVectorContainer));
      *dynamic_cast<lasd::List<Data>*>(&this->mutableLinearListContainer) = std::move(dynamic_cast<lasd::List<Data>&>(mutableLinearListContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->mutableLinearSortVecContainer) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(mutableLinearSortVecContainer));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableLinearSortVec1Container) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableLinearSortVec1Container));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableLinearSortVec2Container) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableLinearSortVec2Container));
      *dynamic_cast<lasd::List<Data>*>(&this->list1) = std::move(dynamic_cast<lasd::List<Data>&>(list1));
      *dynamic_cast<lasd::List<Data>*>(&this->list2) = std::move(dynamic_cast<lasd::List<Data>&>(list2));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVec));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLst));
      *dynamic_cast<lasd::Vector<Data>*>(&this->vector1) = std::move(dynamic_cast<lasd::Vector<Data>&>(vector1));
      *dynamic_cast<lasd::Vector<Data>*>(&this->vector2) = std::move(dynamic_cast<lasd::Vector<Data>&>(vector2));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst1) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLst1));
      *dynamic_cast<lasd::SetLst<Data>*>(&this->setLst2) = std::move(dynamic_cast<lasd::SetLst<Data>&>(setLst2));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec1) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVec1));
      *dynamic_cast<lasd::SetVec<Data>*>(&this->setVec2) = std::move(dynamic_cast<lasd::SetVec<Data>&>(setVec2));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableVector1) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableVector1));
      *dynamic_cast<lasd::SortableVector<Data>*>(&this->sortableVector2) = std::move(dynamic_cast<lasd::SortableVector<Data>&>(sortableVector2));
    }

    ~BoxRandomTester()
    {
      delete &vectorContainer;
      delete &listContainer;
      delete &setVecContainer;
      delete &setLstContainer;
      delete &sortVecContainer;
      delete &testableVectorContainer;
      delete &testableListContainer;
      delete &testableSetVecContainer;
      delete &testableSetLstContainer;
      delete &testableSortVecContainer;
      delete &clearableVectorContainer;
      delete &clearableListContainer;
      delete &clearableSetVecContainer;
      delete &clearableSetLstContainer;
      delete &resizableVectorContainer;
      delete &resizableSortVecContainer;
      delete &dictionarySetVecContainer;
      delete &dictionarySetLstContainer;
      delete &traversableVectorContainer;
      delete &traversableListContainer;
      delete &traversableSetVecContainer;
      delete &traversableSetLstContainer;
      delete &traversableSortVecContainer;
      delete &orderedDictionarySetVecContainer;
      delete &orderedDictionarySetLstContainer;
      delete &mappableVectorContainer;
      delete &mappableListContainer;
      delete &mappableSortVecContainer;
      delete &preOrderTraversableVectorContainer;
      delete &preOrderTraversableListContainer;
      delete &preOrderTraversableSetVecContainer;
      delete &preOrderTraversableSetLstContainer;
      delete &preOrderTraversableSortVecContainer;
      delete &postOrderTraversableVectorContainer;
      delete &postOrderTraversableListContainer;
      delete &postOrderTraversableSetVecContainer;
      delete &postOrderTraversableSetLstContainer;
      delete &postOrderTraversableSortVecContainer;
      delete &preOrderMappableVectorContainer;
      delete &preOrderMappableListContainer;
      delete &preOrderMappableSortVecContainer;
      delete &postOrderMappableVectorContainer;
      delete &postOrderMappableListContainer;
      delete &postOrderMappableSortVecContainer;
      delete &linearVectorContainer;
      delete &linearListContainer;
      delete &linearSetVecContainer;
      delete &linearSetLstContainer;
      delete &linearSortVecContainer;
      delete &mutableLinearVectorContainer;
      delete &mutableLinearListContainer;
      delete &mutableLinearSortVecContainer;
      delete &sortableLinearSortVec1Container;
      delete &sortableLinearSortVec2Container;
      delete &list1;
      delete &list2;
      delete &setVec;
      delete &setLst;
      delete &vector1;
      delete &vector2;
      delete &setLst1;
      delete &setLst2;
      delete &setVec1;
      delete &setVec2;
      delete &sortableVector1;
      delete &sortableVector2;
    }
  };

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
  // const time_t BoxRandomTester<Data>::seed = 1749211491;
  
  template <typename Data>
  void Gentest1(const lasd::Vector<Data> &Alphabet){
    {
      std::cout << "Testing EmptyBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::EmptyBoxes<Data>();
      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);
      TestablesTest(testBox.testableVectorContainer, Alphabet[0]);
      TestablesTest(testBox.testableListContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetVecContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetLstContainer, Alphabet[0]);
      TestablesTest(testBox.testableSortVecContainer, Alphabet[0]);
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);
      ResizablesTest(testBox.resizableVectorContainer, 10);
      ResizablesTest(testBox.resizableSortVecContainer, 10);
    }
  
    {
      std::cout << "\n\nTesting MonoBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::MonoBoxes<Data>(Alphabet);

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      if (std::cin.get() == '1'){

        std::cin.get();
        std::cout << "\nMonoBoxes generated:" << std::endl;

        std::cout << "\tvectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.vectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tlistContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.listContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.setVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.setLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.sortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.testableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableListContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.testableListContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.testableSetVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.testableSetLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.testableSortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.clearableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableListContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.clearableListContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableSetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.clearableSetVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableSetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.clearableSetLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tresizableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.resizableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tresizableSortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.resizableSortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

      }

      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);
      TestablesTest(testBox.testableVectorContainer, Alphabet[0]);
      TestablesTest(testBox.testableListContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetVecContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetLstContainer, Alphabet[0]);
      TestablesTest(testBox.testableSortVecContainer, Alphabet[0]);
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);
      ResizablesTest(testBox.resizableVectorContainer, 10);
      ResizablesTest(testBox.resizableSortVecContainer, 10);
    }

    {
      std::cout << "\n\nTesting MultiBoxes:" << std::endl;
      BoxRandomTester<Data> testBox = myT::MultiBoxes<Data>(Alphabet, 10);

      std::cout << "Enter to continue, If print is desired press 1..." <<  std::endl;
      if (std::cin.get() == '1'){

        std::cin.get();
        std::cout << "\nMultiBoxes generated:" << std::endl;

        std::cout << "\tvectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.vectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tlistContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.listContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.setVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.setLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tsortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.sortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.testableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableListContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.testableListContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.testableSetVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.testableSetLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\ttestableSortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.testableSortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.clearableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableListContainer: " << std::endl;
        dynamic_cast<lasd::List<Data>&>(testBox.clearableListContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableSetVecContainer: " << std::endl;
        dynamic_cast<lasd::SetVec<Data>&>(testBox.clearableSetVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tclearableSetLstContainer: " << std::endl;
        dynamic_cast<lasd::SetLst<Data>&>(testBox.clearableSetLstContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tresizableVectorContainer: " << std::endl;
        dynamic_cast<lasd::Vector<Data>&>(testBox.resizableVectorContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

        std::cout << "\tresizableSortVecContainer: " << std::endl;
        dynamic_cast<lasd::SortableVector<Data>&>(testBox.resizableSortVecContainer).Traverse(
          [](const Data &dat)
          {
            std::cout << dat << " ";
          }
        ); std::cout << std::endl;

      }

      ContainersTest(testBox.vectorContainer);
      ContainersTest(testBox.listContainer);
      ContainersTest(testBox.sortVecContainer);
      ContainersTest(testBox.setVecContainer);
      ContainersTest(testBox.setLstContainer);
      TestablesTest(testBox.testableVectorContainer, Alphabet[0]);
      TestablesTest(testBox.testableListContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetVecContainer, Alphabet[0]);
      TestablesTest(testBox.testableSetLstContainer, Alphabet[0]);
      TestablesTest(testBox.testableSortVecContainer, Alphabet[0]);
      ClearablesTest(testBox.clearableVectorContainer);
      ClearablesTest(testBox.clearableListContainer);
      ClearablesTest(testBox.clearableSetVecContainer);
      ClearablesTest(testBox.clearableSetLstContainer);
      ResizablesTest(testBox.resizableVectorContainer, 5);
      ResizablesTest(testBox.resizableSortVecContainer, 5);
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
  Gentest1<DataT>(boxTester.vector1);

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
