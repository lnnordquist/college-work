#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


//Name: Lars Nordquist

/* References: none
   Help: Liam Lee Kitt
*/

/* Exercise 1
 *
 * flip: Flip the elements of an array in-place
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void flip(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    for(int i = 0; i<(len/2); i++) {
        int f = a[i];
        int l = a[len-1-i];
        a[i] = l;
        a[len-1-i] = f;
    }
    return;
}

/* Exercise 2
 *
 * shift: Shift the elements of an array in-place to the right by one
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void shift(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    int l = a[len-1];
    for(int i = len-1; i>0; i--) {
        a[i] = a[i-1];
    }
    a[0] = l;
}

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
char *first_letter(char *sentence, int *num_words) {
    assert(sentence != NULL);
    assert(num_words != NULL);

    *num_words = 0;
    for(int i = 0; sentence[i] != '\0'; i++) {
        if((sentence[i] == ' ')||(i==0)) {
            *num_words += 1;
        }
    }

    char *chars = (char *) malloc(sizeof(char) * *num_words);
    if (chars == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
    exit(1);
    }

    int k=1;
    chars[0] = sentence[0];
    for(int j=1; sentence[j] != '\0'; j++) {
        if(sentence[j] == ' ') {
            chars[k] = sentence[j+1];
            k++;
        }
    }
    printf("%s\n", chars);
    return chars;
}

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
void count_zeros_and_runs(int *a, int len, int *num_zeros, int *num_runs) {
    assert(a != NULL);
    assert(len > 0);
    assert(num_zeros != NULL);
    assert(num_runs != NULL);
    *num_zeros = 0;
    *num_runs = 0;
    for(int i = 0; i<len; i++) {
        if(a[i]==0){
            *num_zeros += 1;
            if(i==0){
                *num_runs +=1;
            }else if(a[i-1] != 0) {
                *num_runs += 1;
            }
        }
    }
    return;
}

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
bool saves_space(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    int runs = 0, zeros = 0;
    count_zeros_and_runs(a, len, &zeros, &runs);
    return (2*runs < zeros);
}

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
int *encode(int *a, int len, int *encoded_len) {
    assert(a != NULL);
    assert(len > 0);
    assert(encoded_len != NULL);

    int runs = 0, zeros = 0;
    count_zeros_and_runs(a, len, &zeros, &runs);
    *encoded_len = 2*runs + (len - zeros);

    int *encoded_a = (int *)malloc(sizeof(int) * *encoded_len);
    if (encoded_a == NULL) {
        fprintf(stderr, "Ran out of space in some function.\n");
        exit(1);
    }

    int k = 0;
    for(int i = 0; i<len; i++) {
        if(a[i]==0){
            if((i == 0)||(a[i-1] != 0)) {
                encoded_a[k] = 0;
                k++;
                encoded_a[k] = 1;
                if(a[i+1] != 0){
                    k++;
                }
            }else if(a[i+1] != 0){
                encoded_a[k] += 1;
                k++;
            }else{
                encoded_a[k] += 1;
            }
        }else {
            encoded_a[k] = a[i];
            k++;
        }
    }
    return encoded_a;
}

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
int *decode(int *a, int len, int *decoded_len) {
    assert(a != NULL);
    assert(len > 0);
    assert(decoded_len != NULL);

    *decoded_len = 0;

    for(int i = 0; i<len; i++){
        if((i != 0) && (a[i-1]==0)){
          *decoded_len += a[i]-1;
        }else{
            *decoded_len += 1;
        }
    }

    int *decoded_a = (int *)calloc(sizeof(int), *decoded_len);
    if (decoded_a == NULL) {
        fprintf(stderr, "Ran out of space in some function.\n");
        exit(1);
    }

   int n = 0;
    for(int j = 0; j<len; j++){
        if((j != 0) && (a[j-1]==0)){
            n += a[j]-1;
        }else{
            decoded_a[n] = a[j];
            n++;
        }
    }
    return decoded_a;
}