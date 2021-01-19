#include <iostream>

#include "GameDeck.h"

using namespace std;

int main()
{
  cout << "'make experiment' will run this main" << endl;

  GameDeck gd;

  gd.init();

  for (unsigned int i = 0; i < gd.NC; ++i) {
    cout << "cell" << (i + 1) << " size: " << gd.cell(i).size() << endl;
  }
  for (unsigned int i = 0; i < gd.NP; ++i) {
    cout << "pile" << (i + 1) << " size: " << gd.pile(i).size() << endl;
  }
  for (unsigned int i = 0; i < gd.NF; ++i) {
    cout << "foundation" << (i + 1) << " size: " << gd.foundation(i).size() << endl;
  }
  
  return 0;
}