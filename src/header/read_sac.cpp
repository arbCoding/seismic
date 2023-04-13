#include "read_sac.hpp"

// Here is where I'm going to put my actual definitions

namespace SAC
{

int word_position(int word_number)
{
  return (word_number * word_length);
}

std::array<char, word_length> read_next_word(std::ifstream* sac)
{
  char word[word_length] = {};
  sac->read((char*) &word, word_length);
  std::array<char, word_length> result;
  for (int i{0}; i < word_length; ++i)
  {
    result[static_cast<long unsigned int>(i)] = word[i];
  }
  return result;
}

// Literally just skips the the word by reading it into nothing
void skip_word(std::ifstream* sac)
{
  read_next_word(sac);
}

float read_next_float(std::ifstream* sac)
{
  char raw_word[word_length] = {};
  sac->read((char*) &raw_word, word_length);
  float word{};
  std::memcpy(&word, raw_word, 4);
  return word;
}

int read_next_int(std::ifstream* sac)
{
  char raw_word[word_length] = {};
  sac->read((char*) &raw_word, word_length);
  int word{};
  std::memcpy(&word, raw_word, 4);
  return word;
}

bool read_next_bool(std::ifstream* sac)
{
  std::array<char, word_length> one_word = read_next_word(sac);
  return static_cast<bool>(one_word[0]);
}

// Reads the sac data starting from the data_word and to npts
// It does it word by word (each word is a 4 byte float)
// Assumes evenly spaced data (standard file format)
std::vector<float> read_data(std::ifstream* sac, int npts)
{
  // Initialize and resize our data vector
  std::vector<float> data{};
  data.resize(static_cast<std::vector<float>::size_type>(npts));
  // Go to the start of the data.
  sac->seekg(word_position(data_word));
  // Do until the file is finished
  for (long unsigned int i{0}; i < data.size(); ++i)
  {
    data[i] = read_next_float(sac);
  }
  return data;
}

template <long unsigned int N>
std::array<char, N> read_words(std::ifstream* sac, int n_words)
{
  std::array<char, word_length> single_word;
  std::array<char, N> full_value;
  int destination_start{0};
  for (int words{0}; words < n_words; ++words)
  {
    single_word = read_next_word(sac);
    destination_start = words * word_length;
    std::copy(single_word.begin(), single_word.end(), full_value.begin() + destination_start);
  }
  return full_value;
}

// Explicit instantiation of template to make the linker/compiler behave
// This must be done for each expected case.
template std::array<char, word_length> read_words(std::ifstream* sac, int n_words = 1);
template std::array<char, 2 * word_length> read_words(std::ifstream* sac, int n_words = 2);
template std::array<char, 4 * word_length> read_words(std::ifstream* sac, int n_words = 4);

template <long unsigned int N>
void print_words(std::array<char, N> words)
{
  for (long unsigned int i{0}; i < sizeof(words); ++i)
  {
    std::cout << words[i] << '\t' << static_cast<int>(words[i]) << '\n'; 
  }
}

// Explicit instantiation of template to make linker/compiler behave!
template void print_words(std::array<char, word_length> words);
template void print_words(std::array<char, 2 * word_length> words);
template void print_words(std::array<char, 4 * word_length> words);

// Seems to work
// Checks to see if the value is -12345 (characters)
// Which is the SAC special value for unset
template <long unsigned int N>
bool is_set(std::array<char, N> words)
{
  // Need to search for the -12345 pattern
  for (long unsigned int i{0}; i < sizeof(words); ++i)
  {
    if (words[i] == '-')
    {
      return false;
    }
  }
  return true;
}

// Explicit instantiation of template to make linker/compiler behave!
template bool is_set(std::array<char, word_length> words);
template bool is_set(std::array<char, 2 * word_length> words);
template bool is_set(std::array<char, 4 * word_length> words);

}
