#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

#ifndef _PRINT_BYTES
#define _PRINT_BYTES

using namespace Eigen;
using namespace std;

typedef unsigned char Scalar;
typedef Matrix<Scalar, 1, 784> ImageVector;

/**
 * @brief Loads file, checks for failure, and returns.
 * 
 * @param absolute_file_path 
 * @return FILE*
 */
FILE* load_file(string absolute_file_path);

/**
 * @brief Get the number of files in the training set, and sets FILE* f to the start of the raw data.
 * 
 * @param f 
 * @return uint32_t 
 */
uint32_t get_num_files(FILE* f);

/**
 * @brief This method allows me to print a digit to cout instead of using a rendering software.
 * It's hard to visualize the images from bytecode.
 * 
 * @param img 
 */
void print_img_vector(ImageVector* img);

/**
 * @brief This method loads an array of bytes (default is unsigned char) from the given absolute file path.
 * Currently expects encoding according to MNIST database, but this could change if necessary. Returns
 * a vector containing row vectors containing unsigned chars.
 * 
 * Note to self: This method allocates lots of memory. Figure out how to free it properly!
 * 
 * @param absolute_file_path 
 * @return vector<ImageVector*>* 
 */
vector<ImageVector*>* load_byte_array(string absolute_file_path, bool is_image_file);


#endif