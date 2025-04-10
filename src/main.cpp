#include <chrono>
#include <cmath>
#include <cstdlib>

#include "SDL_events.h"

#include "config.hpp"
#include "fluid.hpp"
#include "graphics_handler.hpp"
#include "logger.hpp"
#include "platform_setup.hpp"

void setup() {
  Logger::init();
  setup_platform();
}

int main() {
  setup();

  GraphicsHandler<FLUID_HEIGHT, FLUID_WIDTH, CELL_SIZE> graphics(
      ARROW_HEAD_LENGTH, ARROW_HEAD_ANGLE, ARROW_DISABLE_THRESH_HOLD);
  Fluid<FLUID_HEIGHT, FLUID_WIDTH> fluid(PROJECTION_O, PROJECTION_N);

  SDL_Event event;

  {
    using namespace std::chrono;

    bool is_running = true;
    auto prev_time = high_resolution_clock::now();
    while (is_running) {
      while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
      }
      auto now = high_resolution_clock::now();
      auto passed_time = now - prev_time;
      auto passed_time_ns = duration_cast<nanoseconds>(passed_time);
      auto nano_seconds = passed_time_ns.count();
      float d_t = static_cast<float>(nano_seconds) / 1'000'000'000;

      auto fps = static_cast<uint32_t>(1 / d_t);

      Logger::log_fps(d_t);

      fluid.apply_external_forces(d_t);
      
      fluid.perform_projection();

      graphics.update(fluid);
      prev_time = now;
    }
  }

  return EXIT_SUCCESS;
}
