#include <TFile.h>
#include <TTree.h>

#include <iostream>

#include "MyObject.h"

using namespace std;

int main() {
  // step 1: write the tree
  {
    unique_ptr<TFile> file(TFile::Open("my_file.root", "recreate"));
    TTree tree("events", "events tree");

    MyObject obj;
    tree.Branch("myObject", &obj);

    for (size_t i = 0; i < 10; ++i) {
      obj.setA(i * 2.);
      tree.Fill();
    }

    tree.Write();
  }

  // step 2: read the tree
  {
    TFile file("my_file.root");
    auto* tree = file.Get<TTree>("events");
    MyObject* obj{nullptr};
    tree->SetBranchAddress("myObject", &obj);
    for (unsigned long long i = 0; i < tree->GetEntriesFast(); ++i) {
      tree->GetEntry(i);
      cout << obj->name() << ": " << obj->a() << ", " << obj->bSum() << endl;
    }
  }

  return 0;
}
