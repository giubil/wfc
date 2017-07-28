#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

#include "overlapping_model.hh"
#include "tile_model.hh"
#include "make_pattern.hpp"
#include "model_functions.hh"

const auto kUsage = R"(
wfc.bin [-h/--help] [--gif] [job=samples.cfg, ...]
	-h/--help   Print this help
	--gif       Export GIF images of the process
	file        Jobs to run
)";

void run_and_write(const Options& options, const std::string& name, const configuru::Config& config, const Model& model, std::queue<Image> &frame_queue)
{
	const size_t limit       = config.get_or("limit",       0);
	const size_t screenshots = config.get_or("screenshots", 2);

	for (const auto i : irange(screenshots)) {
		for (const auto attempt : irange(10)) {
			(void)attempt;
			int seed = rand();

			Output output = create_output(model);

			jo_gif_t gif;

			if (options.export_gif) {
				const auto initial_image = model.image(output);
				const auto gif_path = emilib::strprintf("output/%s_%lu.gif", name.c_str(), i);
				const int gif_palette_size = 255; // TODO
				gif = jo_gif_start(gif_path.c_str(), initial_image.width(), initial_image.height(), 0, gif_palette_size);
			}

			const auto result = run(&output, model, seed, limit, options.export_gif ? &gif : nullptr, frame_queue);

			if (options.export_gif) {
				jo_gif_end(&gif);
			}

			if (result == Result::kSuccess) {
				const auto image = model.image(output);
				const auto out_path = emilib::strprintf("output/%s_%lu.png", name.c_str(), i);
				CHECK_F(stbi_write_png(out_path.c_str(), image.width(), image.height(), 4, image.data(), 0) != 0,
				        "Failed to write image to %s", out_path.c_str());
				break;
			}
		}
	}
}

void run_config_file(const Options& options, const std::string& path, std::queue<Image> &frame_queue)
{
	LOG_F(INFO, "Running all samples in %s", path.c_str());
	const auto samples = configuru::parse_file(path, configuru::CFG);
	const auto image_dir = samples["image_dir"].as_string();

	if (samples.count("overlapping")) {
		for (const auto& p : samples["overlapping"].as_object()) {
			LOG_SCOPE_F(INFO, "%s", p.key().c_str());
			const auto model = make_overlapping(image_dir, p.value());
			run_and_write(options, p.key(), p.value(), *model, frame_queue);
			p.value().check_dangling();
		}
	}

	if (samples.count("tiled")) {
		for (const auto& p : samples["tiled"].as_object()) {
			LOG_SCOPE_F(INFO, "Tiled %s", p.key().c_str());
			const auto model = make_tiled(image_dir, p.value());
			run_and_write(options, p.key(), p.value(), *model, frame_queue);
		}
	}
}

int	generation_thread(int argc, char* argv[], std::queue<Image> &frame_queue)
{
	loguru::init(argc, argv);

	Options options;

	std::vector<std::string> files;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			printf(kUsage);
			exit(0);
		} else if (strcmp(argv[i], "--gif") == 0) {
			options.export_gif = true;
			LOG_F(INFO, "Enabled GIF exporting");
		} else {
			files.push_back(argv[i]);
		}
	}

	if (files.empty()) {
		files.push_back("samples.cfg");
	}

	for (const auto& file : files) {
		run_config_file(options, file, frame_queue);
	}

	return 0;
}

void stbi_write_to_sf_image(void *context, void *data, int size)
{
	reinterpret_cast<sf::Image *>(context)->loadFromMemory(data, size);
}

int main(int argc, char* argv[])
{
	std::queue<Image>	frame_queue;

	std::thread	thread_generation(generation_thread, argc, argv, std::ref(frame_queue));

	sf::RenderWindow window(sf::VideoMode(1200, 1200), "My Window");

	int i = 0;

	while (window.isOpen())
	{
		sf::Event event;

		sf::Sprite frame_sprite;
		sf::Image frame_image;
		sf::Texture frame_texture;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//window.clear();
		if (!frame_queue.empty()) {
			window.clear();
			Image frame = frame_queue.front();
			stbi_write_png_to_func(&stbi_write_to_sf_image, &frame_image, frame.width(), frame.height(), 4, frame.data(), 0);
			frame_queue.pop();
			frame_texture.loadFromImage(frame_image);
			frame_sprite.setTexture(frame_texture, true);
			window.draw(frame_sprite);
			window.display();
			i++;
		}
		//window.draw(frame_sprite);
	}

	thread_generation.join();
}
