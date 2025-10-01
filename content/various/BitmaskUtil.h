#pragma once
uint64_t two(int b) {
    return 1ULL << b;
}
uint64_t flip_bit(uint64_t mask, int b) {
    return mask ^ two(b);
}
int get_bit(uint64_t mask, int b) {
    return (mask >> b) & 1ULL;
}
uint64_t set_bit(uint64_t mask, int b, int new_val) {
    return mask + (new_val - get_bit(mask, b)) * two(b);
}
int popcount(uint64_t mask) {
    return __builtin_popcountll(mask);
}
int ctz(uint64_t mask) {
    return __builtin_ctzll(mask);
}
template<typename F>
void for_each_submask(uint64_t mask, F f) {
    for(uint64_t smk = mask; smk > 0; smk = (smk - 1) & mask) {
        f(smk);
    }
}