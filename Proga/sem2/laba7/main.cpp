#include <bits/stdc++.h>

using namespace std;

template <typename T>
class circular_buffer
{
public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;
    public:

        iterator() : ptr(nullptr) {}

        iterator(T *ptr) : ptr(ptr) {}

        iterator(const iterator &itr) : ptr(itr.ptr) {}

        iterator& operator+=(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) {
            ptr += diff;
            return *this;
        }

        iterator& operator-=(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) {
            ptr -= diff;
            return *this;
        }

        T& operator*() const { return *ptr; }

        T* operator->() const { return ptr; }

        T& operator[](typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) const {
            return ptr[diff];
        }

        iterator& operator++() {
            ptr++;
            return *this;
        }

        iterator& operator--() {
            ptr--;
            return *this;
        }

        iterator operator++(T) {
            iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        iterator operator--(T) {
            iterator tmp(*this);
            --ptr;
            return tmp;
        }

        bool operator==(const iterator &itr) const {
            return ptr == itr.ptr;
        }

        bool operator!=(const iterator &itr) const {
            return ptr != itr.ptr;
        }

        bool operator>(const iterator &itr) const {
            return ptr > itr.ptr;
        }

        bool operator<(const iterator &itr) const {
            return ptr < itr.ptr;
        }

        bool operator>=(const iterator &itr) const {
            return ptr >= itr.ptr;
        }

        bool operator<=(const iterator &itr) const {
            return ptr <= itr.ptr;
        }

        iterator operator+(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) const {
            return iterator(ptr + diff);
        }

        iterator operator-(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) const {
            return iterator(ptr - diff);
        }

        typename std::iterator<std::random_access_iterator_tag, T>::difference_type operator-(const iterator &itr) const {
            return ptr - itr.ptr;
        }
    };

private:

    size_t buf_size = 0;
    size_t first, last;
    bool cycle = false;
    T* arr;

public:

    circular_buffer(size_t size_) {
        buf_size = size_;
        arr = new T[buf_size];
        first = 0;
        last = 0;
        cycle = false;
        for (size_t i = 0; i < buf_size; i++) {
            arr[i] = 0;
        }
    }

    circular_buffer(size_t size_, T value) {
        buf_size = size_;
        arr = new T[buf_size];
        last = 0;
        first = 0;
        cycle = false;
        for (size_t i = 0; i < buf_size; i++) {
            arr[i] = value;
        }
    }

    ~circular_buffer() {
        delete[] arr;
    }

    int size() {
        return buf_size;
    }

    void push_back(T v) {
        if (last == first && cycle) {
            throw out_of_range("Buffer is full. Not enough memory.\n");
        }
        arr[last] = v;
        last++;
        if (last == buf_size) {
            last = 0;
        }
        if (last == first) {
            cycle = true;
        }
    }

    T pop_back() {
        if (last == first && !cycle) {
            throw out_of_range("Buffer is clear. Nothing to pop\n");
        }
        if (last == first) {
            cycle = false;
        }
        last--;
        if (last == -1) {
            last = buf_size - 1;
        }
        T temp = arr[last];
        arr[last] = 0;
        return temp;
    }

    void push_front(T v) {
        if (first == last && cycle) {
            throw out_of_range("Buffer is full. Not enough memory.\n");
        }
        first--;
        if (first == -1) {
            first = buf_size - 1;
        }
        arr[first] = v;
        if (first == last) {
            cycle = true;
        }
    }

    void push_at(const iterator it, T value) {
        if (first == last && cycle) {
            throw out_of_range("Buffer is full. Not enough memory.\n");
        }
        iterator x;
        for (x = arr + first; x != it && x < arr + last; x++) {
            if (x == end()) {
                x = begin();
            }
        }
        if (x != it) {
            throw out_of_range("Iterator is not in buffer's range.\n");
        }
        auto temp = value;
        for (; x < arr + last; x++) {
            if (x == end()) {
                x = begin();
                if (x == arr + last) {
                    break;
                }
            }
            swap(*x, temp);
        }
        *x = temp;
        last++;
        if (last == buf_size) {
            last = 0;
        }
        if (last == first) {
            cycle = true;
        }
    }

    T pop_at(const iterator it) {
        if (first == last && !cycle) {
            throw out_of_range("Buffer is empty. Nothing to delete.\n");
        }
        if (first == last) {
            cycle = false;
        }
        iterator x;
        for (x = arr + first; x != it && x < arr + last; x++) {
            if (x == end()) {
                x = begin();
            }
        }
        if (x != it) {
            throw out_of_range("iterator is not in buffer's range.\n");
        }

        auto temp = arr[last];
        last--;
        if (last == -1) {
            last = buf_size - 1;
        }
        for (x = arr + last; x != it; x--) {
            swap(temp, *x);
            if (x == begin()) {
                x = end();
            }
        }
        swap(temp, *it);
        return temp;
    }

    T pop_front() {
        if (last == first && !cycle) {
            throw out_of_range("Buffer is empty. Nothing to delete.\n");
        }
        if (first == last) {
            cycle = false;
        }
        auto temp = arr[first];
        first++;
        if (first == buf_size) {
            first = 0;
        }
    }

    T get_first() {
        return arr[first];
    }

    T get_last() {
        return arr[last];
    }

    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(&(arr[buf_size]));
    }

    T operator [](size_t N) {
        if (N >= buf_size) {
            throw invalid_argument("Ring_buffer out of range");
        } else {
            return arr[N];
        }
    }

    void print() {
        bool cool = cycle;
        for (iterator cur = arr + first; cur != arr + last || cool; cur++) {
            if (cur == end()) {
                cur = begin();
                if (cur == arr + first) {
                    break;
                }
            }
            cout << *cur << " ";
            cool = false;
        }
        cout << endl;
    }

    void resize(int n) {
        delete []arr;
        arr = new T[n];
        for (size_t i = 0; i < buf_size; i++) {
            arr[i] = 0;
        }
    }
};

int main() {
    srand(time(NULL));
    circular_buffer <int> my_buffer(8);
    for (int i = 0; i < 8; i++)
    {
        my_buffer.push_back(rand() % 100);
    }
    my_buffer.print();
    for (int i = 0; i < 3; i++) {
        my_buffer.pop_back();
    }
    my_buffer.print();
    for (int i = 0; i < 3; i++) {
        my_buffer.pop_front();
    }
    my_buffer.print();
    my_buffer.push_back(3);
    my_buffer.push_front(2);
    my_buffer.print();
    sort(my_buffer.begin(), my_buffer.end());
    my_buffer.print();
}