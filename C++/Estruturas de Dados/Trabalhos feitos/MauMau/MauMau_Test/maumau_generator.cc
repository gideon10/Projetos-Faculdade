#include <bits/stdc++.h>
using namespace std;

typedef pair < int, int > ii;

int main()
{
  freopen("test_file", "w", stdout);
  
  bool achou;
  register int i;
  register int j;
  register int p = 100000;
  register int nj;
  ii t, cards[104];
  srand(time(0));
  
  printf("%d\n", p);  // partidas
  for (++p; --p; )
  {
    cerr << "Processing: " << p << endl;
    while ((nj = rand() % 10 + 1) == 1);  // qtde jogadores
    printf("%d\n", nj);
    
    while (--nj)
    {
      for (i = 0; i < 104; ++i)
      {
        t = ii(rand() % 13, rand() % 4);
        achou = 0;
        for (j = 0; j < i; ++j)
          if (t == cards[j])
          {
            if (achou)
              break;
            achou = 1;
          }
        if (j == i)
          cards[i] = t;
        else
          --i;
      }
      for (i = 104; i; --i)
        printf("%c%d ", cards[i].first + 65, cards[i].second);
      printf("\n");
    }
    printf("\n");
  }

  return 0;
}
