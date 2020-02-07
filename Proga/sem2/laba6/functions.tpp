template <typename container>
bool allOf(const container& c, bool (&f)(int)) {
    for (auto& x : c) {
        if (!f(x)) {
            return false;
        }
    }
    return true;
}

template <typename container>
bool anyOf(const container& c, bool (&f)(int)) {
    for (auto& x : c) {
        if (f(x)) {
            return true;
        }
    }
    return false;
}

template <typename container>
bool noneOf(const container& c, bool (&f)(int)) {
    for (auto& x : c) {
        if (f(x)) {
            return false;
        }
    }
    return true;
}

template <typename container>
bool oneOf(const container& c, bool (&f)(int)) {
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

template <typename container>
bool isSorted(const container& c, bool (&f)(int)) {
    bool was = false;
    for (auto& x : c) {
        if (f(x)) {
            was = true;
        } else if (was) {
            return false;
        }
    }
    return true;
}

template <typename container>
bool isPartitioned(const container& c, bool (&f)(int)) {
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
object findNot(const InputIterator begin, const InputIterator end, object value) {
    for (auto it = begin; it != end; it = next(it)) {
        if (*it != value) {
            return *it;
        }
    }
    return object();
}

template <class InputIterator, class object>
object findBackward(InputIterator begin, InputIterator end, object value) {
    for (auto it = prev(end); it != begin; it = prev(it)) {
        if (*it == value) {
            return *it;
        }
    }
    return object();
}

template <typename container>
bool isPalindrom(const container& c, bool (&f)(int)) {
    for (auto it1 = c.begin(), it2 = prev(c.end()); it1 != c.end(); it1 = next(it1), it2 = prev(it2)) {
        if (f(*it1) ^ f(*it2)) {
            return false;
        }
    }
    return true;
}