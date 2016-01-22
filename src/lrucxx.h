#include <stdlib.h>
#include <string>
#include "lruc.h"
#include <string.h>

using namespace std;

class LrucString{
public:
  LrucString(unsigned int bsize, unsigned int max){
    lruc = lruc_new(NULL, _hash_code, _compare, _destroy, sizeof(string), 0, bsize, max);
  }

  ~LrucString(){
    lruc_free(lruc);
  }

  int insert(string& v){
    lruc_node_t node = lruc_alloc_node(lruc);

    if(node == NULL){
      return 1;
    }

    string* p = G_LRUC_NODE_KEY(lruc, node, string*);

    //
    new (p) string;

    //
    *p = v;

    return lruc_insert_node(lruc, node);
  }

  string* find(string& v){
    return (string*) lruc_find(lruc,  &v);
  }

private:
  static unsigned int _hash_code(void* key){
    string* str = (string*) key;

    const unsigned char *p = (const unsigned char*) str->c_str();
    unsigned long h = 0, g;

    for(;*p;p++) {
      h = (h << 4) + (unsigned long)(*p);
      if ((g = (h & 0xF0000000UL))!=0)
        h ^= (g >> 24);
      h &= ~g;
    }

    return (int)h;

  }

  static int _compare(void* one, void* other){
    string* a = (string*)one;
    string* b = (string*)other;

    return strcmp(a->c_str(), b->c_str());
  }

  static void _destroy(void* key, void*){
    string* p = (string*)key;

    p->~string();
  }

private:
  lruc_t lruc;
};
