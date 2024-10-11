/**
 * Author: ngthanhtrung23
 * Description:	MergeAdjSeg is true = merge 2 consecutive segments,
 * e.g. [1, 10] and [11, 20] = [1, 20]
 */
template<typename T, bool MergeAdjSeg = true>
struct RangeSet {
    T n_elements() const { return sz; }
    T n_ranges() const { return ranges.size(); }

    bool contains(T x) const {
        auto it = ranges.upper_bound(x);
        return it != ranges.begin() && x <= prev(it)->second;
    }

    // Find range containing x, i.e. l <= x <= r
    auto find_range(T x) const {
        auto it = ranges.upper_bound(x);
        return it != ranges.begin() && x <= prev(it)->second ? prev(it) : ranges.end();
    }

    T insert(T l, T r) {	// Insert [l, r]
        assert(l <= r);
        auto it = ranges.upper_bound(l);
        if (it != ranges.begin() && is_mergeable(prev(it)->second, l)) {
            it = prev(it);
            l = min(l, it->first);
        }
        T inserted = 0;
        for (; it != ranges.end() && is_mergeable(r, it->first); it = ranges.erase(it)) {
            auto [cl, cr] = *it;
            r = max(r, cr);
            inserted -= cr - cl + 1;
        }

        inserted += r - l + 1;
        ranges[l] = r;
        sz += inserted;
        return inserted;
    }

    T erase(T l, T r) {		// Erase [l, r]
        assert(l <= r);
        T tl = l, tr = r;
        auto it = ranges.upper_bound(l);
        if (it != ranges.begin() && l <= prev(it)->second) {
            it = prev(it);
            tl = it->first;
        }

        T erased = 0;
        for (; it != ranges.end() && it->first <= r; it = ranges.erase(it)) {
            auto [cl, cr] = *it;
            tr = cr;
            erased += cr - cl + 1;
        }
        if (tl < l) {
            ranges[tl] = l-1;
            erased -= l - tl;
        }
        if (r < tr) {
            ranges[r + 1] = tr;
            erased -= tr - r;
        }
        sz -= erased;
        return erased;
    }

    // Find min x: x >= lower && x NOT in this set
    T minimum_excluded(T lower) const {
        static_assert(MergeAdjSeg);
        auto it = find_range(lower);
        return it == ranges.end() ? lower : it->second + 1;
    }

    // Find max x: x <= upper && x NOT in this set
    T maximum_excluded(T upper) const {
        static_assert(MergeAdjSeg);
        auto it = find_range(upper);
        return it == ranges.end() ? upper : it->first - 1;
    }

    T sz = 0;
    map<T, T> ranges;
	
    bool is_mergeable(T cur_r, T next_l) {
        return next_l <= cur_r + MergeAdjSeg;
    }
};