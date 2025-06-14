#include <iostream>

#include "application.hpp"
#include <ekg/gpu/opengl/gl.hpp>

application_t app {};

/*
void generate_char_sampler(ekg::sampler_t *p_sampler, std::string_view c, ekg::io::font_face_type font_face_type) {

  ekg::draw::font_renderer &f_renderer {ekg::draw::get_font_renderer(ekg::font::normal)};

  uint32_t previous_size {f_renderer.font_size};
  f_renderer.set_size(512);

  // 🐮
  // ✔

  ekg::io::font_face_t &typography_font_face {f_renderer.faces[font_face_type]};

  FT_Load_Char(
    typography_font_face.ft_face,
    ekg::utf8_to_utf32(c),
    FT_LOAD_RENDER | FT_LOAD_COLOR | FT_LOAD_DEFAULT
  );
  
}
*/

void test_pixel_imperfect() {

}

void test_widgets() {
  ekg::stack_t meow {
    .tag = "moo"
  };

  ekg::frame_t frame_template {
    .tag = "meows",
    .rect = {20.0f, 20.0f, 200.0f, 200.0f},
    .drag = ekg::dock::top,
    .resize = ekg::dock::left | ekg::dock::right | ekg::dock::bottom
  };

  auto &my_frame {ekg::make<ekg::frame_t>(frame_template)};
}

int32_t main(int32_t, char**) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetSwapInterval(0);

  app.p_sdl_win = {
    SDL_CreateWindow(
      "Pompom",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1280,
      720,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    )
  };

  SDL_Event sdl_event {};
  SDL_GLContext sdl_gl_context {SDL_GL_CreateContext(app.p_sdl_win)};
  glewInit();

  app.is_running = true;

  ekg::ft_library ft_library {};
  FT_Init_FreeType(&ft_library);

  ekg::runtime_properties_info_t runtime_properties_info {
    .default_font_path_text = "./comic-mono.ttf",
    .default_font_path_emoji = "./twemoji.ttf",
    .p_platform_base = new ekg::sdl2(app.p_sdl_win),
    .p_gpu_api = new ekg::opengl(),
    .ft_library = ft_library
  };

  ekg::runtime_t ekg_runtime {};
  ekg::init(
    runtime_properties_info,
    &ekg_runtime
  );

  ekg::gui.ui.redraw = true;
  ekg::flags_t resize {
    ekg::dock::left | ekg::dock::bottom | ekg::dock::right
  };

  ekg::dpi.auto_scale = true;
  ekg::dpi.scale = {0.0f, 0.0f, 800.0f, 600.0f};

  ekg::rgba_t<float> clear_color {0.3f, 0.22f, 0.7f, 1.0f};

  test_widgets();

  ekg::timing_t framerate {};
  uint64_t elapsed_frame_count {};
  uint64_t last_frame_count {1};

  while (app.is_running) {
    if (ekg::reset_if_reach(framerate, 1000)) {
      SDL_GL_SetSwapInterval(app.vsync);
      last_frame_count = elapsed_frame_count;
      elapsed_frame_count = 0;
    }

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT) {
        app.is_running = false;
      }

      ekg::sdl2_poll_event(sdl_event);
    }

    ekg::update();

    glClearColor(clear_color.x, clear_color.y, clear_color.z, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0.0f, 0.0f, ekg::dpi.viewport.w, ekg::dpi.viewport.h);

    ekg::gui.ui.dt = 1.0f / last_frame_count;
    ekg::render();

    SDL_GL_SwapWindow(app.p_sdl_win);

    ++elapsed_frame_count;

    if (app.vsync) {
      SDL_Delay(6);
    }
  }

  return 0;
}
