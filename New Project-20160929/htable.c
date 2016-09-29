#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include <stdlib.h>
struct htablerec {
  int capacity;
  int num_keys;
  char **keys;
};

static unsigned int htable_word_to_int(char *word) {
  unsigned int result = 0;

  while (*word != '\0') {
     result = (*word++ + 31 * result);
  }
  return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
  return i_key % h->capacity;
}

htable htable_new(int capacity) {
  int i;
  htable h = emalloc(sizeof(*h));
  h->capacity =capacity;
  h->num_keys = 0;
  h->keys = emalloc(capacity *sizeof(h->keys[0]));
  for(i=0;i<capacity;i++){
   h->keys[i]=NULL;   
  }
  return h;
    
    
}

void htable_free(htable h) {
  int i;
  for(i=0;i<h->capacity;i++){
      if(h->keys[i]!=NULL)
      free(h->keys[i]);
  }
  
  free(h->keys);
  free(h);
}

int htable_insert(htable h, char *key) {
     unsigned int i = htable_word_to_int(key);
     i = htable_hash(h,i);
     int k =0;
     
     if(h->keys[i] == NULL){
         h->keys[i] =emalloc( (strlen(key)+1)*sizeof(char));
         strcpy(h->keys[i],key);
         return 0;
     }
     if(strcmp(h->keys[i],key) ==0)
     return 0;
     
     while(1){
         i = (i+1)%h->capacity;
         
     if(h->keys[i] == NULL){
         h->keys[i] =emalloc( (strlen(key)+1)*sizeof(char));
         strcpy(h->keys[i],key);
         return 0;
     }
     if(strcmp(h->keys[i],key) ==0)
     return 0;
     
     k++;
     if(k>h->capacity)
     return -1;
         
     }
     
     

}

void htable_print(htable h, FILE *stream) {
    int i;
    
    for (i = 0; i < h->capacity; i++) {
      fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
    
}