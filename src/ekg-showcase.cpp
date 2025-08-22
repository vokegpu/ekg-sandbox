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

void test_numbers() {
  ekg::slider_t slider {};

  slider.ranges.emplace_back().value.as<double>() = 64.0;
  ekg::assert(slider.ranges[0].value.get_type_info_hash() == ekg::ui::f64);
  ekg_log_low_level("f64: " << ekg::ui::f64);

  slider.ranges.emplace_back().value.as<float>() = 32.0f;
  ekg::assert(slider.ranges[1].value.get_type_info_hash() == ekg::ui::f32);
  ekg_log_low_level("f32: " << ekg::ui::f32);

  slider.ranges.emplace_back().value.as<uint64_t>() = 64;
  ekg::assert(slider.ranges[2].value.get_type_info_hash() == ekg::ui::u64);
  ekg_log_low_level("u64: " << ekg::ui::u64);

  slider.ranges.emplace_back().value.as<int64_t>() = 64;
  ekg::assert(slider.ranges[3].value.get_type_info_hash() == ekg::ui::i64);
  ekg_log_low_level("i64: " << ekg::ui::i64);

  slider.ranges.emplace_back().value.as<uint32_t>() = 32;
  ekg::assert(slider.ranges[4].value.get_type_info_hash() == ekg::ui::u32);
  ekg_log_low_level("u32: " << ekg::ui::u32);

  slider.ranges.emplace_back().value.as<int32_t>() = 32;
  ekg::assert(slider.ranges[5].value.get_type_info_hash() == ekg::ui::i32);
  ekg_log_low_level("i32: " << ekg::ui::i32);

  slider.ranges.emplace_back().value.as<uint16_t>() = 16;
  ekg::assert(slider.ranges[6].value.get_type_info_hash() == ekg::ui::u16);
  ekg_log_low_level("u16: " << ekg::ui::u16);

  slider.ranges.emplace_back().value.as<int16_t>() = 16;
  ekg::assert(slider.ranges[7].value.get_type_info_hash() == ekg::ui::i16);
  ekg_log_low_level("i16: " << ekg::ui::i16);

  slider.ranges.emplace_back().value.as<uint8_t>() = 8;
  ekg::assert(slider.ranges[8].value.get_type_info_hash() == ekg::ui::u8);
  ekg_log_low_level("u8: " << ekg::ui::u8);

  slider.ranges.emplace_back().value.as<int8_t>() = 8;
  ekg::assert(slider.ranges[9].value.get_type_info_hash() == ekg::ui::i8);
  ekg_log_low_level("i8: " << ekg::ui::i8);
}

void test_widgets() {
  ekg::make<ekg::stack_t>(
    {
      .tag = "moo"
    }
  );

  ekg::flags_t next_fill {ekg::dock::next | ekg::dock::fill};
  ekg::button_t bt {.tag = "x", .dock = next_fill, .checks = {{.text = "\tclikcka"}}};

  ekg::frame_t frame_template {
    .tag = "meows",
    .rect = {20.0f, 20.0f, 200.0f, 700.0f},
    .drag = ekg::dock::top,
    .resize = ekg::dock::left | ekg::dock::right | ekg::dock::bottom
  };

  ekg::button_t buttons {
    .tag = "to-click ><",
    .dock = next_fill,
    .checks = {{.text = "cliwck hewe"}}
  };

  buttons.rect.w = 200.0f;
  for (size_t it {}; it < 1; it++) {
    frame_template.rect.w = 600.0f;
    auto &my_frame {ekg::make<ekg::frame_t>(frame_template)};

    auto &entry = ekg::make<ekg::textbox_t>({.tag = "meow", .dock = next_fill, .rect = {.scaled_height = 16}});
    for (size_t it {}; it < 100; it++) {
      entry.text.push_back("meow-meow");
      entry.text.push_back("The quick brown fox jumps over the lazy dog;\nnisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit\neqndjqwbdiuqwybdihqwbdjhklbqwhkld");
    }

    ekg::make<ekg::slider_t>(
      {
        .tag = "meow amo miar",
        .dock = next_fill,
        .ranges = {
          {
            .value = 16.0f,
            .min = 20.0f,
            .max = 2000.0f,
            .dock = ekg::dock::left | ekg::dock::fill}
        }
      }
    );

    ekg::make<ekg::button_t>(buttons)
      .checks = {{.text = "amo vc", .box = ekg::dock::left}};

    auto &my = ekg::make<ekg::button_t>(buttons);

    my.checks = {
      {.text = "lcikc"},
      {.text = "lcikc", .dock = ekg::dock::left},
      {.text = "lcikc"},
      {.text = "lcikc"}
    };

    ekg::make<ekg::button_t>(buttons);

    auto &a = ekg::query<ekg::button_t>(my.at);
    auto &p = ekg::query<ekg::property_t>(a.property_at);
    ekg_log_low_level(p.at.flags);

    ekg::label_t mu {
      .tag = "pompom",
      .text = "oi eu sou uma vaca sabia",
      .dock = next_fill,
      .dock_text = ekg::dock::center
    };

    ekg::make<ekg::label_t>(mu);

    for (size_t it {}; it < 30; it++) {
      mu.text = "i like to meowmoo " + std::to_string(it);
      ekg::make<ekg::label_t>(mu);
    }

    ekg::make<ekg::scrollbar_t>({.tag = "oi eu queria miar e miar que nem uma vaca c"});
  }

  ekg::slider_t xx {};
  //meow.ranges.emplace_back().value<float>() = 32432.0f;
  //ekg_log_low_level(meow.ranges[0].value<float>());

  float b {36.0f};
  char*pb {(char*)(void*)&b};

  xx.ranges = {
    {
      .value = 34.0f,
      .min = 34.0f,
      .max = 34.0f,
      .dock = ekg::dock::left,
      .dock_text = ekg::dock::left
    }
  };

  //ekg_log_low_level("oi eu sou uma vaca " << meow.ranges[0].value.as<float>());
  //app.meows.push_back(meow);
  ekg::pop<ekg::frame_t>();

  auto &xxxx = ekg::make<ekg::popup_t>({.tag = "oi"});
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::label_t>(ekg::popup_t::separator);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::label_t>(ekg::popup_t::separator);
  ekg::make<ekg::button_t>(bt);
  ekg::pop<ekg::popup_t>();

  //ekg::popup_t &meows {ekg::make<ekg::popup_t>()};
  //ekg::make<ekg::button_t>(bt);
  //ekg::make<ekg::button_t>(bt);
  //ekg::pop<ekg::popup_t>();

  auto &moo = ekg::make<ekg::popup_t>({.tag = ">3<"});
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::pop<ekg::popup_t>();

  auto &meow = ekg::make<ekg::popup_t>({.tag = ">2<", .links = {{"moo", moo.at}, {"xoo", xxxx.at}}});
  //ekg::make<ekg::slider_t>({.tag ="muu", .dock = next_fill, .ranges = {{.value = 30.0f, .min = 20.0f, .max = 200.0f, .dock = ekg::dock::fill, .dock_text = ekg::dock::none}}});
  bt.tag = "xoo";
  ekg::make<ekg::button_t>(bt);
  bt.tag = "moo";
  ekg::make<ekg::label_t>(ekg::popup_t::separator);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::button_t>(bt);
  ekg::pop<ekg::popup_t>();

  auto &c = ekg::make<ekg::callback_t>(
    {
      .info = {.tag = "meow"},
      .lambda = [](ekg::info_t&) {
        ekg_log_low_level("meowomeowmeowmeowme");
      }
    }
  );

  app.test_popup_at = 
    ekg::make<ekg::popup_t>({.tag = ">1<", .links = {{"meow", meow.at}}}).at;
  
  bt.checks = {{.text = "pressiona", .box = ekg::dock::left}};
  ekg::make<ekg::button_t>(bt);

  bt.checks = {{.text = "oiiii"}};
  auto &bx = ekg::make<ekg::button_t>(bt);
  bx.checks[0].actions[ekg::action::active] = c.at;

  bt.checks = {{.text = "clickas"}};
  ekg::make<ekg::button_t>(bt);

  ekg::make<ekg::label_t>(ekg::popup_t::separator);

  bt.tag = "meow";
  auto &f = ekg::make<ekg::frame_t>({.dock = next_fill, {.h = 200.0f}, .resize = ekg::dock::left | ekg::dock::bottom | ekg::dock::right});
  ekg::make<ekg::button_t>(bt);
  ekg::make<ekg::slider_t>(
    {
      .tag = "meow",
      .dock = next_fill,
      .ranges = {
        {
          .value = 50.0f, .min = 0.0f, .max = 100.0f,
          .dock_text = ekg::dock::none,
          .dock = ekg::dock::fill | ekg::dock::left
        }
      }
    }
  );

  for (int i {}; i < 4; i++) {
    bt.dock = next_fill;
    ekg::make<ekg::button_t>(bt);
  }

  ekg::make<ekg::scrollbar_t>({});
  ekg::pop<ekg::frame_t>();

  ekg::make<ekg::scrollbar_t>({});
  ekg::pop<ekg::popup_t>();
}

void test_off() {
  size_t i {};
  ekg::text text {};

  text.push_back("oii\ntudobem");
  std::cout << text.length_of_lines() << std::endl;
  std::cout << text.length_of_chars() << std::endl;
  text.insert(0, "meow\nxu");

  for (size_t it {}; it < text.length_of_lines(); it++) {
    std::string charr {text.at(it)};
    std::cout << charr << std::endl;
  }
}

int32_t main(int32_t, char**) {
  test_off();
  test_numbers();

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
  ekg::dpi.scale = {0.0f, 0.0f, 1280.0f, 720.0f};

  ekg::rgba_t<float> clear_color {0.1f, 0.1f, 0.1f, 1.0f};
  test_widgets();

  ekg::timing_t framerate {};
  uint64_t elapsed_frame_count {};
  uint64_t last_frame_count {1};

  while (app.is_running) {
    if (ekg::reset_if_reach(framerate, 1000)) {
      SDL_GL_SetSwapInterval(app.vsync);
      last_frame_count = elapsed_frame_count;
      elapsed_frame_count = 0;
      ekg_log_low_level("fps: " << last_frame_count << " " << ekg::metrics.gpu_data_count);
      //ekg_log_low_level(app.meows[0].ranges[0].value<float>());
    }

    while (SDL_PollEvent(&sdl_event)) {
      ekg::sdl2_poll_event(sdl_event);

      if (sdl_event.type == SDL_QUIT) {
        app.is_running = false;
      }
    
      if (ekg::input("mouse-3")) {
        ekg::show(app.test_popup_at, ekg::input().interact);
        ekg_log_low_level("ayy cabron")
      }
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
