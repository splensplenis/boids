#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>

#include "boids.random.hpp"
#include "boids.hpp"
#include "multiflock.hpp"
#include "rules.hpp"

//--------- Graphical simulation within enclosed ambient --------//
/*  Apply ambient constraints to a flock
    When the computed position of a boid isn't in the boundaries the boid bounce
   back elastically:
    - Its position is brought back on the edge the surpassed border
    - The component of the velocity in the direction of the trespass is inverted
   of sign */
inline void ApplyClosedAmbient(Flock& flock, const unsigned int width,
                               const unsigned int height) {
  std::vector<Boid> boids{flock.get_boids()};
  for (int i{}; i != flock.size(); ++i) {
    // check left border
    if (boids[i].position.x() < 0) {
      boids[i].position = Vector(0, boids[i].position.y());
      boids[i].velocity = Vector(-boids[i].velocity.x(), boids[i].velocity.y());
    }
    // check right border
    if (boids[i].position.x() > width) {
      boids[i].position = Vector(width, boids[i].position.y());
      boids[i].velocity = Vector(-boids[i].velocity.x(), boids[i].velocity.y());
    }
    // check upper border
    if (boids[i].position.y() < 0) {
      boids[i].position = Vector(boids[i].position.x(), 0);
      boids[i].velocity = Vector(boids[i].velocity.x(), -boids[i].velocity.y());
    }
    // check bottom border
    if (boids[i].position.y() > height) {
      boids[i].position = Vector(boids[i].position.x(), height);
      boids[i].velocity = Vector(boids[i].velocity.x(), -boids[i].velocity.y());
    }
  }
  // replace the flock with the new values
  flock = Flock(boids, flock.get_options(), flock.get_alpha());
}

inline void graphics_simulation(MultiFlock& more_flock) {
  const int width{640};
  const int height{480};
  double min_speed{50};
  double max_speed{250};

  double time_count{};
  std::ofstream file_output_stream{"data.txt"};
  if (!file_output_stream.is_open()) {
    throw std::runtime_error("Failed to open data.txt");
  }
  file_output_stream << "time" << '\t';
  for (int i{1}; i != more_flock.size() + 1; ++i) {
    file_output_stream << "flock" << i << " distance" << '\t' << '\t' << "flock"
                       << i << " speed" << '\t' << '\t';
  }
  file_output_stream << '\n';

  auto const delta_t{sf::milliseconds(1)};
  double const dt{delta_t.asSeconds()};
  int const fps = 60;
  int const steps_per_evolution{1000 / fps};

  sf::RenderWindow window(sf::VideoMode(width, height), "Boids!");
  window.setFramerateLimit(fps);

  sf::Texture texture;
  if (!texture.loadFromFile("image.png", sf::IntRect(6, 6, 5, 5))) {
    std::cout << "Cannot load boid graphics" << '\n';
  }
  sf::Sprite sprite{};
  sprite.setTexture(texture);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color::White);

    for (int i{0}; i != steps_per_evolution; ++i) {
      more_flock.evolve(dt, max_speed, min_speed, [](Flock& flock) {
        ApplyClosedAmbient(flock, width, height);
      });
    }

    for (auto& boid : more_flock.get_all_boids()) {
      sprite.setPosition((boid.position).x(), (boid.position).y());
      window.draw(sprite);
    }

    time_count += dt;
    auto distance_flock = more_flock.get_all_distance_mean_RMS();
    auto speed_flock = more_flock.get_all_speed_mean_RMS();

    file_output_stream << time_count * steps_per_evolution << '\t';
    for (int i{}; i != more_flock.size(); ++i) {
      file_output_stream << distance_flock[i].x() << " +/- "
                         << distance_flock[i].y() << '\t' << speed_flock[i].x()
                         << " +/- " << speed_flock[i].y() << '\t';
    }
    file_output_stream << '\n';

    window.display();
  }
}

#endif