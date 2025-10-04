#pragma once
template<class T>
struct compression {
    vector<T> values;
    compression() {
        values.clear();
    }
    void push(const T& x) {
        values.push_back(x);
    }
    void build() { /// Nen So
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
    }

    int get(const T& v, bool index_from_one = false) const { /// Lay ID
        return (lower_bound(all(values), v) - values.begin()) + index_from_one;
    }

    T get_value(const int& v) const { /// Lay gia tri cua so nen, dam bao v thuoc doan [0, values.size())
        assert(0 <= v && v < (int) values.size());
        return values[v];
    }

    int size() const {
        return (int) values.size();
    }
};
