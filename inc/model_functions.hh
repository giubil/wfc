#ifndef MODEL_FUNCTIONS_HH
#define MODEL_FUNCTIONS_HH

#include "overlapping_model.hh"
#include "tile_model.hh"

Output create_output(const Model& model);

Result observe(const Model& model, Output* output, RandomDouble& random_double);

Result run(Output* output, const Model& model, size_t seed, size_t limit, jo_gif_t* gif_out);

Result find_lowest_entropy(const Model& model, const Output& output, RandomDouble& random_double,
                           int* argminx, int* argminy);


std::unique_ptr<Model> make_overlapping(const std::string& image_dir, const configuru::Config& config);

std::unique_ptr<Model> make_tiled(const std::string& image_dir, const configuru::Config& config);

#endif /* MODEL_FUNCTIONS_HH */