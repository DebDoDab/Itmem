//
// Created by vadim on 7.02.20.
//
template <typename container, class object>
bool allOf(const container& c, bool (&f)(object)) {
    for (auto& x : c) {
        if (!f(x)) {
            return false;
        }
    }
    return true;
}

template <typename container, class object>
bool anyOf(const container& c, bool (&f)(object)) {
    for (auto& x : c) {
        if (f(x)) {
            return true;
        }
    }
    return false;
}

template <typename container, class object>
bool noneOf(const container& c, bool (&f)(object)) {
    for (auto& x : c) {
        if (f(x)) {
            return false;
        }
    }
    return true;
}

template <typename container, class object>
bool oneOf(const container& c, bool (&f)(object)) {
    bool was = false;
    for (auto& x : c) {
        if (f(x) && !was) {
            was = true;
        } else if (f(x)) {
            return false;
        }
    }
    return was;
}

template <class InputIterator, class object>
bool isSorted(const InputIterator& begin, const InputIterator& end, bool (&f)(object, object)) {
    if (begin == end) {
        return true;
    }

    for (auto it1 = begin, it2 = next(begin); it2 != end; it1 = next(it1), it2 = next(it2)) {
        if (!f(*it1, *it2)) {
            return false;
        }
    }
    return true;
}

template <typename container, class object>
bool isPartitioned(const container& c, bool (&f)(object)) {
    int was = -1;
    for (auto& x : c) {
        if (f(x) && was == -1) {
            was = 1;
        } else if (!f(x) && was == -1) {
            was = 0;
        } else if (f(x) && was == 0) {
            return false;
        } else if (!f(x) && was == 1) {
            return false;
        }
    }
    return true;
}

template <class InputIterator, class object>
object findNot(const InputIterator& begin, const InputIterator& end, object value) {
    for (auto it = begin; it != end; it = next(it)) {
        if (*it != value) {
            return *it;
        }
    }
    return object();
}

template <class InputIterator, class object>
object findBackward(const InputIterator& begin, const InputIterator& end, object value) {
    for (auto it = prev(end); it != end; it = prev(it)) {
        if (*it == value) {
            return *it;
        }
        if (it == begin) {
            break;
        }
    }
    return object();
}

template <typename container, class object>
bool isPalindrome(const container& c, bool (&f)(object)) {
    for (auto it1 = c.begin(), it2 = prev(c.end()); it1 != c.end(); it1 = next(it1), it2 = prev(it2)) {
        if (f(*it1) ^ f(*it2)) {
            return false;
        }
    }
    return true;
}