#ifndef EKG_TEST_APPLICATION_HPP
#define EKG_TEST_APPLICATION_HPP

#include <ekg/ekg.hpp>
#include <ekg/platform/sdl/sdl2.hpp>

extern struct application_t {
  SDL_Window *p_sdl_win {};
  std::string fps {};
  bool vsync {true};
  bool is_running {};
  std::vector<ekg::sampler_t> loaded_sampler_list {};
  std::vector<ekg::callback_t> loaded_task_list {};
  std::vector<ekg::slider_t> meows {};
  ekg::at_t test_popup_at {};
} app;

#endif
