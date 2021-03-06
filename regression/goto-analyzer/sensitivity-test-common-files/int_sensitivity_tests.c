#include <assert.h>

int main(int argc, char *argv[])
{
  // Test how well we can represent ints, and also that the transformers are
  // working correctly.
  int x=0;
  int y=0;
  if(argc>2)
  {
    y=1;
  }
  assert(x==0);
  assert(x==1);
  assert(x==y);

  assert(x<1);
  assert(x<-1);
  assert(x<y);

  assert(x>-1);
  assert(x>1);
  assert(x>y);

  assert(x!=1);
  assert(x!=0);
  assert(x!=y);

  assert(!(x==1));
  assert(!(x==0));
  assert(!(x==y));

  // Test how well we can represent an int when it has more than one possible
  // value
  assert(y<2);
  assert(y>2);
  assert(y==1);

  // Try copying a variable and then modifying the original
  int z=x;
  x=10;
  assert(z==0);
  assert(z==10);

  // Test how we treat assertions in unreachable code
  x=0;
  if(0)
  {
    assert(x==0);
    assert(x==1);
    assert(y==0);
  }

  return 0;
}
