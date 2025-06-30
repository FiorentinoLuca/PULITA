namespace lasd {

  template <typename Data>
  class Iterator
  {
  private:

  protected:
    
  public:

    virtual
    ~Iterator() = default;

    // Specific member functions

    virtual
    bool IsTerminated() const noexcept = 0;

    virtual
    Data operator*() = 0;

    virtual
    Iterator& operator++() = 0;

    virtual
    Iterator& operator+(int idx) = 0;

    virtual
    int operator-(Iterator& other) = 0;

    virtual
    void Reset() = 0;

  };

  template <typename Data>
  Iterator<Data>& operator+(int idx, Iterator<Data>& it)
  {
    return it+idx;
  }



} // namespace lasd