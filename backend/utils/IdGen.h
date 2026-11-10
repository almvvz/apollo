#pragma once

#include <string>

namespace idgen
{
// Returns a random hex string of the given byte length (string is 2x longer).
std::string randomHex(size_t numBytes);

// Current UTC time formatted as ISO-8601 (e.g. "2026-11-10T08:30:00Z").
std::string isoNow();
}  // namespace idgen
