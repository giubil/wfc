#ifndef HELPERS_FUNCTIONS_HH
#define HELPERS_FUNCTIONS_HH

#include "definitions.hh"
#include "make_pattern.hpp"

double calc_sum(const std::vector<double>& a);

// Pick a random index weighted by a
size_t spin_the_bottle(const std::vector<double>& a, double between_zero_and_one);

PatternHash hash_from_pattern(const Pattern& pattern, size_t palette_size);

Pattern pattern_from_hash(const PatternHash hash, int n, size_t palette_size);

Image upsample(const Image& image);

PalettedImage load_paletted_image(const std::string& path);

// n = side of the pattern, e.g. 3.
PatternPrevalence extract_patterns(
	const PalettedImage& sample, int n, bool periodic_in, size_t symmetry,
	PatternHash* out_lowest_pattern);

Image scroll_diagonally(const Image& image);

const char* result2str(const Result result);

#endif /* HELPERS_FUNCTIONS_HH */
