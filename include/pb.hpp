template <class T>
class pb {
public:
    pb(T item, int steps) : _item(item), _steps{steps} {};

    class iterator {
    public:
        iterator(typename T::iterator iterator) : _iterator(iterator) {};
        typename T::iterator& operator*() { return _iterator; }
        iterator& operator++ () { 
            _iterator++; 
        }
        bool operator!= (const iterator& other) { return _iterator != other._iterator; }
    private:
        typename T::iterator _iterator;
    };

    iterator begin() { return iterator(_item.begin()); }
    iterator end() { return iterator(_item.end()); }
    iterator rbegin() { return iterator(_item.rbegin()); }
    iterator rend() { return iterator(_item.rend()); }

private:
    T _item;
    int _steps;
};