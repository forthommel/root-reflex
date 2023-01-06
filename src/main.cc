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
    vector<MyObject> objs;

    tree.Branch("myObject", &obj);
    tree.Branch("myObjects", &objs);

    for (size_t i = 0; i < 10; ++i) {
      obj.setName("object#" + to_string(i));
      obj.setA(i * 2.);
      objs.clear();
      for (size_t j = 0; j < i; ++j)
        objs.emplace_back();
      tree.Fill();
    }

    tree.Write();
  }

  // step 2: read the tree
  {
    TFile file("my_file.root");
    auto* tree = file.Get<TTree>("events");
    MyObject* obj{nullptr};
    vector<MyObject>* objs{nullptr};
    tree->SetBranchAddress("myObject", &obj);
    tree->SetBranchAddress("myObjects", &objs);
    for (unsigned long long i = 0; i < tree->GetEntriesFast(); ++i) {
      tree->GetEntry(i);
      cout << obj->name() << ": " << obj->a() << ", " << obj->bSum() << ", objects collection size: " << objs->size()
           << endl;
    }
  }

  return 0;
}
