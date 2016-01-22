#include "../src/lrucxx.h"
#include <string>
#include <stdio.h>
#include <list>

int main(){
  LrucString lruc(17, 9);

  string last = "test";
  char buf[1024];

  lruc.insert(last);
  for(int x=0; x<1000; x++){
  for(int i=100; i<10000000; i++){
    sprintf(buf, "str%d", i);
  
    string str = buf;
    lruc.insert(str);

    //printf("%s\n", buf);

    string* x = lruc.find(last);

    if(x == NULL){
      printf("error!\n");
    }

    last = str;
  }
  }
}
