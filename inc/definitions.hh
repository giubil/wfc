#ifndef DEFINITIONS_HH
#define DEFINITIONS_HH

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <configuru.hpp>
#include <emilib/irange.hpp>
#include <emilib/strprintf.hpp>
#include <loguru.hpp>
#include <stb_image.h>
#include <stb_image_write.h>

#include "arrays.hpp"

#define JO_GIF_HEADER_FILE_ONLY
#include <jo_gif.cpp>

using emilib::irange;

struct RGBA
{
	uint8_t r, g, b, a;
};

static_assert(sizeof(RGBA) == 4, "");
bool operator==(RGBA x, RGBA y);

using Bool              = uint8_t; // To avoid problems with vector<bool>
using ColorIndex        = uint8_t; // tile index or color index. If you have more than 255, don't.
using Palette           = std::vector<RGBA>;
using Pattern           = std::vector<ColorIndex>;
using PatternHash       = uint64_t; // Another representation of a Pattern.
using PatternPrevalence = std::unordered_map<PatternHash, size_t>;
using RandomDouble      = std::function<double()>;
using PatternIndex      = uint16_t;

const auto kInvalidIndex = static_cast<size_t>(-1);
const auto kInvalidHash = static_cast<PatternHash>(-1);

const bool   kGifSeparatePalette  = true;
const size_t kGifInterval         =  16; // Save an image every X iterations
const int    kGifDelayCentiSec    =   1;
const int    kGifEndPauseCentiSec = 200;
const size_t kUpscale             =   4; // Upscale images before saving

struct Options
{
	bool export_gif = false;
};

enum class Result
{
	kSuccess,
	kFail,
	kUnfinished,
};

const size_t MAX_COLORS = 1 << (sizeof(ColorIndex) * 8);

using Graphics = Array2D<std::vector<ColorIndex>>;

struct PalettedImage
{
	size_t                  width, height;
	std::vector<ColorIndex> data; // width * height
	Palette                 palette;

	ColorIndex at_wrapped(size_t x, size_t y) const
	{
		return data[width * (y % height) + (x % width)];
	}
};

// What actually changes
struct Output
{
	// _width X _height X num_patterns
	// _wave.get(x, y, t) == is the pattern t possible at x, y?
	// Starts off true everywhere.
	Array3D<Bool> _wave;
	Array2D<Bool> _changes; // _width X _height. Starts off false everywhere.
};

using Image = Array2D<RGBA>;

#endif /* DEFINITIONS_HH */