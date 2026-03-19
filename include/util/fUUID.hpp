#pragma once

#include <array>
#include <cstdint>
#include <format>
#include <random>
#include <string>

/**

#include <iostream>

int main() {
	 for (int i = 0; i < 5; ++i) {
		  UUID id = UUID::generate();
		  std::cout << id.toString()
						<< "  (v" << static_cast<int>(id.version()) << ")\n";
	 }
}

**/
namespace zebra::util {


	class UUID {
	public:
		// --- Construction ---------------------------------------------------

		// Generate a random UUID v4
		static UUID generate() {
			UUID uuid;

			std::mt19937_64 rng{std::random_device{}()};
			std::uniform_int_distribution<uint64_t> dist;

			const uint64_t hi = dist(rng);
			const uint64_t lo = dist(rng);

			// Pack 128 bits into bytes
			for (int i = 0; i < 8; ++i) uuid.fBytes[i] = (hi >> (56 - i * 8)) & 0xFF;
			for (int i = 0; i < 8; ++i) uuid.fBytes[8 + i] = (lo >> (56 - i * 8)) & 0xFF;

			// RFC 4122 §4.4 — set version to 4 (0100xxxx in byte 6)
			uuid.fBytes[6] = (uuid.fBytes[6] & 0x0F) | 0x40;

			// RFC 4122 §4.4 — set variant to 10xxxxxx in byte 8
			uuid.fBytes[8] = (uuid.fBytes[8] & 0x3F) | 0x80;

			return uuid;
		}

		// --- Accessors ------------------------------------------------------

		// xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx  (canonical form)
		[[nodiscard]] std::string toString() const {
			return std::format(
				"{:02x}{:02x}{:02x}{:02x}-"
				"{:02x}{:02x}-"
				"{:02x}{:02x}-"
				"{:02x}{:02x}-"
				"{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}",
				fBytes[0], fBytes[1], fBytes[2], fBytes[3],
				fBytes[4], fBytes[5],
				fBytes[6], fBytes[7],
				fBytes[8], fBytes[9],
				fBytes[10], fBytes[11], fBytes[12],
				fBytes[13], fBytes[14], fBytes[15]
			);
		}

		[[nodiscard]] uint8_t version() const {
			return (fBytes[6] >> 4) & 0x0F; // high nibble of byte 6
		}

		[[nodiscard]] const std::array<uint8_t, 16> &bytes() const {
			return fBytes;
		}

		// --- Comparison -----------------------------------------------------

		auto operator<=>(const UUID &) const = default;

	private:
		std::array<uint8_t, 16> fBytes{};
	};
}
