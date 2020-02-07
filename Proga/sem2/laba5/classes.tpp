//
// Created by vadim on 7.02.20.
//

template <typename T>
Matrix<T>::Matrix() {
    n = m = 3;
    x.assign(n, vector<int>(m, 0));
}

template <typename T>
Matrix<T>::Matrix(int n_, int m_) {
    n = n_;
    m = m_;
    x.assign(n, vector<T>(m, 0));
}

template <typename T>
Matrix<T>::Matrix(Matrix& x_) {
    n = x_.n;
    m = x_.m;
    x = x_.x;
}

template <typename T>
Matrix<T>::Matrix(vector<vector<T>>& x_) {
    n = x_.size();
    if (n) {
        m = x_[0].size();
    } else {
        m = 0;
    }
    x = x_;
}

template <typename T>
pair<int, int> Matrix<T>::getSize() {
    return make_pair(n, m);
}

template <typename T>
T Matrix<T>::get(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) {
        throw OutOfRangeException();
    }
    return x[i][j];
}

template <typename T>
void Matrix<T>::editField(int i, int j, T a) {
    if (i < 0 || i >= n || j < 0 || j >= m) {
        throw OutOfRangeException();
    }
    x[i][j] = a;
}