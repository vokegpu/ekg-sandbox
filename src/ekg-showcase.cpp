#include <iostream>

#include "application.hpp"
#include "ekg/io/text.hpp"
#include <ekg/os/ekg_opengl.hpp>
#include <ekg/draw/shape.hpp>

application_t app {};

void generate_char_sampler(ekg::sampler_t *p_sampler, std::string_view c, ekg::io::font_face_type font_face_type) {
  ekg::draw::font_renderer &f_renderer {ekg::draw::get_font_renderer(ekg::font::normal)};

  uint32_t previous_size {f_renderer.font_size};
  f_renderer.set_size(512);

  // 🐮
  // ✔

  ekg::io::font_face_t &typography_font_face {f_renderer.faces[font_face_type]};

  FT_Load_Char(
    typography_font_face.ft_face,
    ekg::utf_string_to_char32(c),
    FT_LOAD_RENDER | FT_LOAD_COLOR | FT_LOAD_DEFAULT
  );

  f_renderer.set_size(previous_size);

  ekg::sampler_allocate_info_t sampler_alloc_info {
    .p_tag = c.data()
  };

  sampler_alloc_info.w = static_cast<int32_t>(typography_font_face.ft_face->glyph->bitmap.width);
  sampler_alloc_info.h = static_cast<int32_t>(typography_font_face.ft_face->glyph->bitmap.rows);

  sampler_alloc_info.gl_wrap_modes[0] = GL_REPEAT;
  sampler_alloc_info.gl_wrap_modes[1] = GL_REPEAT;
  sampler_alloc_info.gl_parameter_filter[0] = GL_LINEAR;
  sampler_alloc_info.gl_parameter_filter[1] = GL_LINEAR;
  sampler_alloc_info.gl_internal_format = GL_RGBA;
  sampler_alloc_info.gl_format = GL_BGRA;
  sampler_alloc_info.gl_type = GL_UNSIGNED_BYTE;
  sampler_alloc_info.gl_generate_mipmap = GL_TRUE;
  sampler_alloc_info.p_data = typography_font_face.ft_face->glyph->bitmap.buffer;

  if (
      ekg::has(
        ekg::gpu_allocate_sampler(
          &sampler_alloc_info,
          p_sampler
        ),
        ekg::result::failed
      )
    ) {
    ekg::log() << "FAILED TO ALLOCATE SAMPLER ID: " << sampler_alloc_info.p_tag;
  };
}

void test_pixel_imperfect() {
  ekg::make(
    ekg::frame_t {
      .tag = "first frame",
      .rect = {500.0f, 200.0f, 200.0f, 200.0f},
      .drag_dock = ekg::dock::top,
      .resize_dock = ekg::dock::left | ekg::dock::bottom | ekg::dock::right
    }
  );

  ekg::theme().button.background = ekg::color<int32_t>(255, 255, 255, 100);

  ekg::button_t button {};
  
  button.tag = "0";
  button.text = "moo moo";
  button.text_dock = ekg::dock::left;
  button.dock = ekg::dock::left | ekg::dock::fill;
  ekg::make(button);
  
  button.tag = "bt-2";
  button.text = "owlf olwf";
  button.text_dock = ekg::dock::center;
  button.dock = ekg::dock::fill;
  ekg::make(button);
  
  button.tag = "1";
  button.text = "i meow u~";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::fill;
  ekg::button_t &meow = ekg::make(button);
  //meow.theme.text.w = 0.0f;
  //meow.theme.background.w = 0.0f;

  button.tag = "2";
  button.text = "ok";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::fill;
  ekg::make(button);

  button.tag = "2/1";
  button.text = "meow";
  button.dock = ekg::dock::bottom | ekg::dock::right;
  ekg::make(button);

  button.tag = "3";
  button.text = "meow";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::next | ekg::dock::fill;
  ekg::make(button);


  button.tag = "4";
  button.text = "meow";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::next | ekg::dock::fill;
  ekg::make(button);

  button.tag = "5";
  button.text = "meow";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::fill;
  ekg::make(button);

  button.tag = "3";
  button.text = "ok";
  button.dock = ekg::dock::bottom | ekg::dock::right | ekg::dock::next;

  ekg::pop();
}

void test_widgets() {
  app.loaded_sampler_list.emplace_back();
  app.loaded_sampler_list.emplace_back();

  ekg::sampler_t &check {app.loaded_sampler_list.at(0)};
  generate_char_sampler(&check, "✔", ekg::io::font_face_type::emojis);

  ekg::sampler_t &meow {app.loaded_sampler_list.at(1)};
  generate_char_sampler(&meow, "🐈", ekg::io::font_face_type::emojis);

  auto bla = ekg::frame_t {
    .tag = "bla",
    .rect = {500.0f, 200.0f, 200.0f, 200.0f},
    .drag_dock = ekg::dock::top,
    .resize_dock = ekg::dock::left | ekg::dock::bottom | ekg::dock::right

  };

  ekg::frame_t &oi = ekg::make(bla);
  oi.theme.layers[ekg::layer::background] = &meow;

  ekg::label_t label {};
  label.tag = "idk";
  label.text = "MEOW OWER MEOW";
  label.dock = ekg::dock::fill;
  label.text_dock = ekg::dock::center;
  ekg::make(label);

  ekg::button_t button {};
  button.tag = "bt1";
  button.text = "click hewe";
  button.dock = ekg::dock::fill | ekg::dock::next;
  ekg::make(button);

  ekg::checkbox_t checkbox {};
  checkbox.tag = "bt1";
  checkbox.text = "must meow ✔";
  checkbox.dock = ekg::dock::fill | ekg::dock::next;
  ekg::checkbox_t &mustmeow = ekg::make(checkbox);
  mustmeow.theme.layers[ekg::checkbox_t::box][ekg::layer::active] = &meow;

  for (uint32_t it {}; it < 64; it++) {
    checkbox.tag = "bt1";
    checkbox.text = "must meow ✔ " + std::to_string(it);
    checkbox.dock = ekg::dock::fill | ekg::dock::next;
    ekg::checkbox_t &mustmeow = ekg::make(checkbox);
    mustmeow.theme.layers[ekg::checkbox_t::box][ekg::layer::active] = &meow;
  }

  ekg::make(ekg::scrollbar_t {.tag = "oiimeowyou"});
  ekg::pop();

  ekg::frame_t &tweaks = ekg::make(bla);
  oi.theme.layers[ekg::layer::background] = &meow;

  checkbox.tag = "vsync";
  checkbox.text = "";
  ekg::checkbox_t &vsync = ekg::make(checkbox);

  vsync.value.move(&app.vsync);
  vsync.text.move(&app.fps);

  ekg::pop();
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
  ekg::vec3_t<float> clear_color {0.345234234f, 0.234234234f, 0.54645f};

  ekg::runtime_property_t ekg_runtime_property {
    .font_path = "./comic-mono.ttf",
    .font_path_emoji = "./twemoji.ttf",
    .p_gpu_api = new ekg::opengl(),
    .p_os_platform = new ekg::sdl(app.p_sdl_win)
  };

  ekg::runtime ekg_runtime {};
  ekg::init(&ekg_runtime, &ekg_runtime_property);

  ekg::viewport.redraw = true;
  ekg::flags_t resize {
    ekg::dock::left | ekg::dock::bottom | ekg::dock::right
  };

  ekg::dpi.auto_scale = false;
  ekg::dpi.scale = {0.0f, 0.0f, 800.0f, 600.0f};

  test_widgets();

  ekg::timing_t framerate {};
  uint64_t elapsed_frame_count {};
  uint64_t last_frame_count {1};

  while (app.is_running) {
    if (ekg::reset_if_reach(&framerate, 1000)) {
      SDL_GL_SetSwapInterval(app.vsync);
      app.fps = std::to_string(elapsed_frame_count) + ", " + std::to_string(ekg::viewport.dt);
      last_frame_count = elapsed_frame_count;
      elapsed_frame_count = 0;
      ekg::viewport.redraw = true;
    }

    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_QUIT) {
        app.is_running = false;
      }

      ekg::sdl_poll_event(sdl_event);
    }

    ekg::update();

    glClearColor(clear_color.x, clear_color.y, clear_color.z, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0.0f, 0.0f, ekg::viewport.w, ekg::viewport.h);

    ekg::viewport.dt = 1.0f / last_frame_count;
    ekg::render();

    SDL_GL_SwapWindow(app.p_sdl_win);

    ++elapsed_frame_count;

    if (app.vsync) {
      SDL_Delay(6);
    }
  }

  return 0;
}
