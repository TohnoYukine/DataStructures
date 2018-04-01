#pragma once
#include <iostream>
#include <iomanip>

namespace DataStructures
{
	template<size_t N, typename UnderlyingType = int>
	class Bitset
	{
	public:
		Bitset() : data{} {}
		bool operator[](size_t pos) const { return static_cast<bool>(data[pos / field_width] & mask(pos % field_width)); }
		Bitset& set(size_t pos) { data[pos / field_width] |= mask(pos%field_width); return *this; }
		Bitset& clear(size_t pos) { data[pos / field_width] &= ~mask(pos%field_width); return *this; }
		Bitset& flip(size_t pos) { data[pos / field_width] ^= mask(pos%field_width); return *this; }

	private:
		constexpr static size_t field_width = 8 * sizeof(UnderlyingType);
		UnderlyingType data[(N + field_width - 1) / field_width];

		inline constexpr static UnderlyingType mask(size_t pos) { return 1 << (field_width - pos - 1); }
	};

	template<size_t N, typename UnderlyingType = int>
	std::ostream& operator<<(std::ostream& out, const Bitset<N, UnderlyingType>& field)
	{
		out << std::noboolalpha;
		for (size_t i = 0; i < N; i++)
			out << field[i];
		return out;
	}
}