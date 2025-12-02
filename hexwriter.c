#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to perform the hex string to binary file conversion
void write_hex_to_binary(const char *hex_string, const char *filename) {
  FILE *f = fopen(filename, "wb");
  if (f == NULL) {
    perror("Error opening output file");
    exit(EXIT_FAILURE);
  }

  const char *p = hex_string;
  unsigned int byte_val;
  int n_chars_read;

  // Iterate through the string, 2 characters (1 byte) at a time
  while (*p != '\0') {
    // Use sscanf to read two hex digits and store as an unsigned int
    if (sscanf(p, "%2x%n", &byte_val, &n_chars_read) != 1) {
      fprintf(stderr,
              "Invalid hex string at position %ld: expected hex digits\n",
              (long)(p - hex_string));
      fclose(f);
      exit(EXIT_FAILURE);
    }

    // Write the single byte to the file
    unsigned char byte_to_write = (unsigned char)byte_val;
    fwrite(&byte_to_write, sizeof(unsigned char), 1, f);

    // Advance the pointer by the number of characters consumed (n_chars_read)
    p += n_chars_read;
  }

  fclose(f);
  printf("Successfully wrote to %s\n", filename);
}

void print_usage(const char *program_name) {
  fprintf(stderr, "Usage: %s -h <hex_data> -o <output.bin>\n", program_name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  -h <hex_data>   The hexadecimal string to write to the "
                  "file (e.g., F3A102).\n");
  fprintf(stderr, "  -o <output.bin> The destination binary file name.\n");
}

int main(int argc, char *argv[]) {
  int opt;
  char *hex_data_str = NULL;
  char *output_filename = NULL;
  // optstring "h:o:" indicates that both -h and -o require an argument
  const char *options_string = "h:o:";

  // Parse command line arguments using getopt
  while ((opt = getopt(argc, argv, options_string)) != -1) {
    switch (opt) {
    case 'h':
      // optarg contains the argument for the option found
      hex_data_str = optarg;
      break;
    case 'o':
      output_filename = optarg;
      break;
    case '?':
      // getopt prints an error message for unknown options or missing arguments
      // by default
      print_usage(argv[0]);
      exit(EXIT_FAILURE);
    default:
      print_usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  // Check if both required values were provided
  if (hex_data_str == NULL || output_filename == NULL) {
    fprintf(
        stderr,
        "Error: Both -h (hex data) and -o (output file) flags are required.\n");
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  // Call the function to write the data
  write_hex_to_binary(hex_data_str, output_filename);

  return 0;
}
