/*
 * particle_filter.h
 *
 * 2D particle filter class.
 *  Created on: Dec 12, 2016
 *      Author: Tiffany Huang
 */

#ifndef PARTICLE_FILTER_H_
#define PARTICLE_FILTER_H_

#include "helper_functions.h"

struct Particle {
  int id;
  double x;
  double y;
  double theta;
  double weight;
  std::vector<int> associations;
  std::vector<double> sense_x;
  std::vector<double> sense_y;
};

class ParticleFilter {
  // Number of particles to draw
  int num_particles;

  // Flag, if filter is initialized
  bool is_initialized;

  // Vector of weights of all particles
  std::vector<double> weights;

 public:
  // Set of current particles
  std::vector<Particle> particles;

  // Constructor
  // @param num_particles Number of particles
  ParticleFilter() : num_particles(0), is_initialized(false) {}

  // Destructor
  ~ParticleFilter() {}

  /**
   * @details init Initializes particle filter by initializing particles to Gaussian distribution
   *          around first position (based on estimates of x, y, theta and their uncertainties from GPS)
   *          and all the weights to 1.
   *          Add random Gaussian noise to each particle.
   *
   * @todo Set the number of particles.
   * @param x Initial x position [m] (simulated estimate from GPS)
   * @param y Initial y position [m]
   * @param theta Initial orientation [rad]
   * @param std[] Array of dimension 3 [standard deviation of x [m], standard
   * deviation of y [m] standard deviation of yaw [rad]]
   */
  void init(double x, double y, double theta, double std[]);

  /**
   * prediction Predicts the state for the next time step
   *   using the process model.
   * @param delta_t Time between time step t and t+1 in measurements [s]
   * @param std_pos[] Array of dimension 3 [standard deviation of x [m],
   * standard deviation of y [m] standard deviation of yaw [rad]]
   * @param velocity Velocity of car from t to t+1 [m/s]
   * @param yaw_rate Yaw rate of car from t to t+1 [rad/s]
   */
  void prediction(double delta_t, double std_pos[], double velocity, double yaw_rate);

  /**
   * @brief Finds which observations correspond to which landmarks(likely by using a nearest-neighbors data association)
   *
   * @param predicted Vector of predicted landmark observations
   * @param observations Vector of landmark observations
   */
  void dataAssociation(std::vector<LandmarkObs> predicted, std::vector<LandmarkObs>& observations);

  /**
   * @brief updateWeights Updates the weights for each particle based on the likelihood of the observed measurements.
   *
   * @details The observations are given in the VEHICLE'S coordinate system. Your particles are located
   *          according to the MAP'S coordinate system. You will need to transform between the two systems.
   *          Keep in mind that this transformation requires both rotation AND translation (but no scaling).
   *          The following is a good resource for the theory:
   *            https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
   *          and the following is a good resource for the actual equation to implement
   *            look at equation 3.33 http://planning.cs.uiuc.edu/node99.html
   *
   * @todo Update the weights of each particle using a mult-variate Gaussian distribution.
   *       You can read more about this distribution here:
   *       https://en.wikipedia.org/wiki/Multivariate_normal_distribution
   *
   * @param sensor_range Range [m] of sensor
   * @param std_landmark[] Array of dimension 2 [Landmark measurement
   * uncertainty [x [m], y [m]]]
   * @param observations Vector of landmark observations
   * @param map Map class containing map landmarks
   */
  void updateWeights(double sensor_range,
                     double std_landmark[],
                     const std::vector<LandmarkObs>& observations,
                     const Map& map_landmarks);

  /**
   * resample Resamples from the updated set of particles to form the new set of particles.
   */
  void resample();

  /*
   * Set a particles list of associations, along with the associations
   * calculated world x,y coordinates This can be a very useful debugging tool
   * to make sure transformations are correct and assocations correctly
   * connected
   */
  Particle SetAssociations(Particle& particle,
                           const std::vector<int>& associations,
                           const std::vector<double>& sense_x,
                           const std::vector<double>& sense_y);

  std::string getAssociations(Particle best);
  std::string getSenseX(Particle best);
  std::string getSenseY(Particle best);

  /**
   * initialized Returns whether particle filter is initialized yet or not.
   */
  const bool initialized() const { return is_initialized; }
};

#endif /* PARTICLE_FILTER_H_ */
