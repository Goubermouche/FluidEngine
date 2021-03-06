#include "pch.h"
#include "Hash.h"

constexpr auto GenerateCrc32Table() {
	constexpr uint32_t byteCount = 256;
	constexpr uint32_t iterationCount = 8;
	constexpr uint32_t polynomial = 0xEDB88320;

	auto crc32Table = std::array<uint32_t, byteCount>{};

	for (uint32_t byte = 0; byte < byteCount; ++byte) {
		uint32_t crc = byte;

		for (uint32_t i = 0; i < iterationCount; ++i) {
			uint32_t mask = -(crc & 1);
			crc = (crc >> 1) ^ (polynomial & mask);
		}

		crc32Table[byte] = crc;
	}

	return crc32Table;
}

static constexpr auto crc32Table = GenerateCrc32Table();
static_assert(
	crc32Table.size() == 256 &&
	crc32Table[1] == 0x77073096 &&
	crc32Table[255] == 0x2D02EF8D,
	"GenerateCrc32Table generated unexpected result."
);

namespace fe {
	uint32_t Hash::GenerateFNVHash(const char* str)
	{
		constexpr uint32_t FNV_PRIME = 16777619u;
		constexpr uint32_t OFFSET_BASIS = 2166136261u;

		const size_t length = strlen(str) + 1;
		uint32_t hash = OFFSET_BASIS;
		for (size_t i = 0; i < length; ++i)
		{
			hash ^= *str++;
			hash *= FNV_PRIME;
		}
		return hash;
	}

	uint32_t Hash::GenerateFNVHash(const std::string& string)
	{
		return GenerateFNVHash(string.c_str());
	}

	uint32_t Hash::CRC32(const char* str)
	{
		auto crc = 0xFFFFFFFFu;

		for (auto i = 0u; auto c = str[i]; ++i) {
			crc = crc32Table[(crc ^ c) & 0xFF] ^ (crc >> 8);
		}

		return ~crc;
	}

	uint32_t Hash::CRC32(const std::string& string)
	{
		return CRC32(string.c_str());
	}
}
