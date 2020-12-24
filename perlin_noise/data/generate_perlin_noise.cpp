
#include <iostream>
#include <fstream>

#include <math.h>

#include <vector>
#include <random>
#include <chrono>
#include <ctime>

// Define Pi with great precision and calculate it
// during compilation time
constexpr double pi() { return std::atan(1)*4; }

// Generate the a coordinate field
std::vector<std::vector<int>> get_coordinates(int N_x, int N_y)
{
	std::vector<std::vector<int>> coordinates (N_x * N_y);

	for(int i = 0; i < N_x; i++)
	{
		for(int j = 0; j < N_y; j++)
		{
			coordinates[i * N_y + j] = {i, j};
		}
	}

	return(coordinates);
}

// Return a 2D vector with a given `phi` argument
std::vector<double> get_gradient(double phi)
{
	std::vector<double> gradient{sin(phi), cos(phi)};

	return(gradient);
}

// Create a discrete vector field of vectors with randomly choosen
// arguments. Vectors are situated in each gridpoints.
std::vector<std::vector<double>> get_gradient_field(int N_x, int N_y)
{
	// Initialize the Mersenne-Twister RNG to choose
	// values from a uniform distribution between 0 and 2pi
  std::random_device Randomized;
  std::mt19937_64 Generate(Randomized());
  std::uniform_real_distribution<> Distribution(0, 2*pi());

  // Placeholder for the gradient field
  std::vector<std::vector<double>> gradient_field (N_x * N_y);

  // Generate the gradient field
  for(std::size_t i = 0; i < gradient_field.size(); ++i)
  {
  	double phi = Distribution(Generate);
  	gradient_field[i] = get_gradient(phi);
  }

  return(gradient_field);
}

// Calculate the dot product between the generated vector field in every
// corner of the grid cells.
std::vector<std::vector<double>> get_distance_vector_field(
													 int N_x, int N_y,
													 std::vector<std::vector<int>> const &coordinates)
{
	
}

// Write a 2D vector into a file with arbitrary variables
template <typename T>
void write_to_file(std::vector<std::vector<T>> const &table,
									 std::string filename)
{
  std::ofstream output_file;

  // Save generated gradient field
  output_file.open(filename);

  for(std::size_t i = 0; i < table.size(); ++i)
  {
  	output_file << table[i][0] << "," << table[i][1] << std::endl;
	}

  output_file.close();
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "ERROR!\n" << "------" << std::endl;
		std::cout << "NO DIMENSION FOR THE GRID (N_x AND N_y) WERE GIVEN!" << std::endl;
		std::cout << "Usage: ./generate_perlin_noise <N_x> <N_y>" << std::endl;
		std::cout << "Exiting..." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Currently does not check for valid input, please
	// try to give sensible arguments when execute
	int N_x = std::stoi(argv[1]);
	int N_y = std::stoi(argv[2]);
	auto coordinates = get_coordinates(N_x, N_y);
	auto gradient_field = get_gradient_field(N_x, N_y);
	//auto distance_vector_field = get_distance_vector_field(N_x, N_y,
	//																											 coordinates);

	write_to_file<int>(coordinates, "coordinates.txt");
	write_to_file<double>(gradient_field, "gradient_field.txt");

	return(0);
}