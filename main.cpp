#include <iostream>

#include "boids.random.hpp"
#include "boids.hpp"
#include "graphics.hpp"
#include "multiflock.hpp"
#include "rules.hpp"

int main() {
  std::cout << "-------Boid simulation: implemented with graphics-------"
            << '\n'
            << "Plase enter values for simulation parameters:" << '\n'
            << "Number of flocks (suggested value = 2):" << '\n'
            << "Number of boids for each flock (suggested value = 20):" << '\n'
            << "Distance of neighbours (suggested value = 180):" << '\n'
            << "Distance of collision (suggested value = 30):" << '\n'
            << "Separation rule (suggested value = 0.03):" << '\n'
            << "Alignment rule (suggested value = 0.001):" << '\n'
            << "Cohesion rule (suggested value = 0.02):" << '\n'
            << "Angle of view (suggested value = 180 degree):" << '\n';
  double angle{};
  double flock_number;
  double boids_number;
  double distance;
  double separation_distance;
  double separation;
  double alignment;
  double cohesion;
  std::cin >> flock_number >> boids_number >> distance >> separation_distance >>
      separation >> alignment >> cohesion >> angle;
  try {
    if (!std::cin.good()) throw std::runtime_error{"Invalid input"};

    if (flock_number < 0 || flock_number != static_cast<int>(flock_number))
      throw std::runtime_error{"Number of flock must be a positive integer"};
    if (boids_number < 0 || boids_number != static_cast<int>(boids_number))
      throw std::runtime_error{"Number of boids must be a positive integer"};
    if (distance < 0)
      throw std::runtime_error{"Invalid input: distance cannot be less than 0"};
    if (separation_distance < 0)
      throw std::runtime_error{
          "Invalid input: separation_distance cannot be less than 0"};
    if (separation < 0)
      throw std::runtime_error{
          "Invalid input: separation cannot be less than 0"};
    if (alignment < 0)
      throw std::runtime_error{
          "Invalid input: alignment cannot be less than 0"};
    if (cohesion < 0)
      throw std::runtime_error{"Invalid input: cohesion cannot be less than 0"};
    if (angle <= 0 || angle > 180)
      throw std::runtime_error{
          "Invalid input: angle must be between 0 and 180"};
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  Options simulation_options{distance, separation_distance, separation,
                             alignment, cohesion};
  MultiFlock multi_random = generate_multiflock(flock_number, boids_number,
                                                simulation_options, angle);
  graphics_simulation(multi_random);
  return 0;
}