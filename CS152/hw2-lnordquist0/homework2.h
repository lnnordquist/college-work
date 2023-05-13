#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* Exercise 1
 *
 * flip: Flip the elements of an array in-place
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void flip(int *a, int len);

/* Exercise 2
 *
 * shift: Shift the elements of an array in-place to the right by one
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void shift(int *a, int len);

/* Exercise 3
 *
 * first_letter: Create an array of characters that contains
 *     the first letter of each word in a sentence
 *
 * sentence: the sentence
 * num_words: the length of the output array (out parameter)
 *
 * Returns: An array of characters
 */
char *first_letter(char *sentence, int *num_words);

/* Exercise 4
 *
 * count_zeros_and_runs: Count the number of zeros and the 
 *     number of runs of zeros in an array
 *
 * a: the array
 * len: the length of the array
 * num_zeros: the number of zeros (out parameter)
 * num_runs: the number of runs (out parameter)
 *
 * Returns: Nothing, returns number of zeros and runs as out parameters
 */
void count_zeros_and_runs(int *a, int len, int *num_zeros, int *num_runs);

/* Exercise 5
 *
 * saves_space: Determine whether or not the Null encoding of
 *     an array saves space
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: true if Null encoded array has fewer elements than the
 *     original, false otherwise
 */
bool saves_space(int *a, int len);

/* Exercise 6
 *
 * encode: Null encode an array
 *
 * a: the array
 * len: the length of the array
 * encoded_len: the length of the encoded array (out parameter)
 *
 * Returns: the Null encoded array and its length as an out parameter
 */
int *encode(int *a, int len, int *encoded_len);

/* Exercise 7
 *
 * decode: Decode a Null encoded array
 *
 * a: the array
 * len: the length of the array
 * decoded_len: the length of the decoded array (out parameter)
 *
 * Returns: the decoded array and its length as an out parameter
 */
int *decode(int *a, int len, int *decoded_len);