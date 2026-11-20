template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard, gnu::always_inline]] inline static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard, gnu::always_inline]] inline static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::integral T,
    SortOrder order,
    bool stable,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass),
    u32 capacity = 100'001>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;

    using Count = UintForValue<capacity>;
    inline static Count count[base];
    inline static UT temp[capacity];

    template <u8 pass_index>
    [[gnu::always_inline, gnu::hot]] static void
    do_pass(UT* data, UT* output, u32 n) noexcept
    {
        std::memset(count, 0, sizeof(count));
        constexpr UT shift = pass_index * bits_per_pass;
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking = std::is_signed_v<T>;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (num_passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (u32 i = 0; i != n; ++i)
        {
            auto& v = data[i];
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        if constexpr (order == SortOrder::Ascending)
        {
            if constexpr (stable)
            {
                for (u32 i = 1; i != base; ++i) count[i] += count[i - 1];

                for (u32 i = n; i--;)
                {
                    UT digit = (data[i] >> shift) & mask;
                    output[--count[digit]] = data[i] ^ post_sign_mask;
                }
            }
            else
            {
                Count sum = 0;
                for (u32 i = 0; i != base; ++i)
                {
                    Count frequency = count[i];
                    count[i] = sum;
                    sum += frequency;
                }

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = data[j];
                    output[count[(v >> shift) & mask]++] = v ^ post_sign_mask;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            Count sum = 0;
            for (u32 i = base; i--;)
            {
                Count frequency = count[i];
                count[i] = sum;
                sum += frequency;
            }

            for (u32 i = 0; i != n; ++i)
            {
                UT v = (data[i] >> shift) & mask;
                output[count[v]++] = data[i] ^ post_sign_mask;
            }
        }
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    [[gnu::always_inline, gnu::hot]] inline static void do_passes(
        UT* data,
        u32 n,
        std::integer_sequence<u8, pass_index...>) noexcept
    {
        (do_pass<pass_index>(
             pass_index % 2 ? temp : data,
             pass_index % 2 ? data : temp,
             n),
         ...);
        if constexpr (num_passes % 2) std::memcpy(data, temp, n * sizeof(UT));
    }

public:
    [[gnu::always_inline, gnu::hot]] inline static void sort(
        T* data,
        u32 n) noexcept
    {
        if (n) do_passes(reinterpret_cast<UT*>(data), n, pass_idx_seq);
    }

    [[gnu::always_inline, gnu::hot]] inline static void sort(
        std::span<T> arr) noexcept
    {
        sort(arr.data(), cast<u32>(arr.size()));
    }
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void radix_sort(T* data, u32 n) noexcept
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np, capacity>::sort(data, n);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void radix_sort(std::span<T> arr) noexcept
{
    radix_sort<bits_per_pass, num_passes, order, capacity>(
        arr.data(),
        cast<u32>(arr.size()));
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void stable_radix_sort(T* data, u32 n) noexcept
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np, capacity>::sort(data, n);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
[[gnu::always_inline]] inline void stable_radix_sort(std::span<T> arr) noexcept
{
    stable_radix_sort<bits_per_pass, num_passes, order, capacity>(
        arr.data(),
        cast<u32>(arr.size()));
}

#ifdef LC_LOCAL_BUILD
#define LC_SOLUTION_NAME(suffix) Solution_##suffix
#else
#define LC_SOLUTION_NAME(suffix) Solution
#endif

#ifndef LC_LOCAL_BUILD

inline auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class LC_SOLUTION_NAME(adaptive)
{
    static constexpr u32 kWords = (1'000'001 + 63) / 64;
    inline static u64 present[kWords];
    inline static u64 duplicate[kWords];

    static void clear_occurrences(u32 first, u32 last)
    {
        std::memset(present + first, 0, (last - first + 1) * 8);
        std::memset(duplicate + first, 0, (last - first + 1) * 8);
    }

    static void add_occurrence(u32 x)
    {
        u32 word = x >> 6;
        u64 mask = u64{1} << (x & 63);
        if (duplicate[word] & mask) return;
        duplicate[word] |= present[word] & mask;
        present[word] |= mask;
    }

    [[gnu::always_inline]] static u32 pop_highest(u64& word)
    {
        u32 bit = 63 - cast<u32>(__builtin_clzll(word));
        word ^= u64{1} << bit;
        return bit;
    }

    static void for_each_distinct_descending(u32 first, u32 last, auto&& visit)
    {
        for (u32 i = last + 1; i-- != first;)
        {
            u64 word = present[i];
            while (word)
            {
                u32 bit = pop_highest(word);
                visit((i << 6) | bit, (duplicate[i] & (u64{1} << bit)) != 0);
            }
        }
    }

    [[gnu::always_inline]] static u32 max(u32 a, u32 b)
    {
        return a > b ? a : b;
    }

    static u32 sorted(u32* data, u32 n)
    {
        u32 previous = 0, keep = 0, increment = 0, answer = 0;
        for (auto* p = data + n; p != data;)
        {
            u32 x = *--p;
            u32 d = previous - x;
            u32 next_keep =
                1 + (increment & -u32{d == 0}) + (keep & -u32{d == 1});
            u32 next_increment =
                d == 0 ? increment
                       : 1 + (increment & -u32{d == 1}) + (keep & -u32{d == 2});
            previous = x;
            keep = next_keep;
            increment = next_increment;
            answer = max(answer, max(keep, increment));
        }
        return answer;
    }

public:
    [[gnu::flatten, gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]]
    u32 maxSelectedElements(std::vector<int>& nums) noexcept
    {
        auto* data = reinterpret_cast<u32*>(nums.data());
        u32 n = cast<u32>(nums.size());
        if (n <= 128)
        {
            std::sort(data, data + n);
            return sorted(data, n);
        }

        u32 low = 1'000'000, high = 0;
        for (u32 i = 0; i != n; ++i)
        {
            u32 x = data[i];
            low = std::min(low, x);
            high = max(high, x);
        }
        if (low == high) return 2;

        u32 first = low >> 6, last = high >> 6;
        if (n < 32'768 && last - first + 1 > n / 4)
        {
            radix_sort<10, 2>(data, n);
            return sorted(data, n);
        }

        clear_occurrences(first, last);
        for (u32 i = 0; i != n; ++i) add_occurrence(data[i]);

        u32 previous = 0, keep = 0, increment = 0, answer = 0;
        for_each_distinct_descending(
            first,
            last,
            [&] [[gnu::always_inline]] (u32 x, bool repeated)
            {
                u32 d = previous - x;
                u32 next_keep = 1 + (keep & -u32{d == 1});
                u32 next_increment =
                    1 + (increment & -u32{d == 1}) + (keep & -u32{d == 2});
                keep = repeated ? next_increment + 1 : next_keep;
                increment = next_increment;
                previous = x;
                answer = max(answer, max(keep, increment));
            });
        return answer;
    }
};