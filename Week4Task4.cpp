#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Control{
    int id;
    string type;
    string state;
};

void sortControl(vector<Control>& controls1){
    sort(controls1.begin(),controls1.end(),[](Control A,Control B){
        return A.id<B.id;
    });
    cout<<"After Sorted using sort..\n";
    for_each(controls1.begin(),controls1.end(),[](Control controls1){
        cout<<controls1.id<<" "<<controls1.type<<" "<<controls1.state<<endl;
    });
}

void stableSort(vector<Control>& controls2){
    stable_sort(controls2.begin(),controls2.end(),[](Control a,Control b){
        return a.id<b.id;
    });
    cout<<"After Sorted using stable_sort..\n";
    for_each(controls2.begin(),controls2.end(),[](Control controls1){
        cout<<controls1.id<<" "<<controls1.type<<" "<<controls1.state<<endl;
    });
}

void lowerBound(vector<Control> controls1,int searchId){
    auto it=lower_bound(controls1.begin(),controls1.end(),searchId,[](Control con,int id){
        return con.id<id;
    });
    if(it!=controls1.end()){
        cout<<"Control found :\nId : "<<it->id<<" Type : "<<it->type<<" State : "<<it->state<<endl;
    }
    else{
        cout<<"No control found..\n";
    }
}

void upperBound(vector<Control>& controls2, int searchId2) {
    auto it = lower_bound(controls2.begin(), controls2.end(), searchId2, [](Control con, int id) {
        return con.id <id;
    });

    if (it != controls2.end()) {
        cout << "Control found:\nId: " << it->id << " Type: " << it->type << " State: " << it->state << endl;
    } else {
        cout << "No control found..\n";
    }
}

void mergeControls(vector<Control>& controls1,vector<Control>& controls2,vector<Control>& mergedControls){
    merge(controls1.begin(),controls1.end(),controls2.begin(),controls2.end(),mergedControls.begin(),[](Control a,Control b){
        return a.id<b.id;
    });
    cout<<"Both controls merged\n";
    for_each(mergedControls.begin(),mergedControls.end(),[](Control mergedControls){
        cout<<mergedControls.id<<" "<<mergedControls.type<<" "<<mergedControls.state<<endl;
    });
    
}

void inplaceMergeControls(vector<Control>& allControls){
    inplace_merge(allControls.begin(),allControls.begin()+5,allControls.end(),[](Control a,Control b){
        return a.id<b.id;
    });
    for_each(allControls.begin(),allControls.end(),[](Control allControls){
        cout<<allControls.id<<" "<<allControls.type<<" "<<allControls.state<<endl;
    });
}

void setUnion(vector<Control>& controls1, vector<Control>& controls2, vector<Control>& unionControls) {
    unionControls.resize(controls1.size() + controls2.size());
    auto it = set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), unionControls.begin(), [](Control a, Control b) {
        return a.id < b.id;
    });
    unionControls.resize(it - unionControls.begin());
    cout << "Union of controls:\n";
    for_each(unionControls.begin(), unionControls.end(), [](Control unionControls) {
        cout << unionControls.id << " " << unionControls.type << " " << unionControls.state << endl;
    });
}

void intersectionControl(vector<Control>& controls1,vector<Control>& controls2,vector<Control>& intersectionControls){
    intersectionControls.resize(controls1.size()+controls2.size());
    // auto it = set_intersection(controls1.begin(),controls1.end(),controls2.begin(),controls2.end(),back_inserter(intersectionControls));
    auto it = set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), intersectionControls.begin(), [](Control a, Control b) {
        return a.id < b.id;
    });
    intersectionControls.resize(it-intersectionControls.begin());
    cout<<"Intersection of controls\n";
    for_each(intersectionControls.begin(), intersectionControls.end(), [](Control intersectionControls) {
        cout << intersectionControls.id << " " << intersectionControls.type << " " << intersectionControls.state << endl;
    });
}

int main(){
    vector<Control> controls1 = {
        {1, "button", "visible"},
        {7, "slider", "visible"},
        {9, "button", "invisible"},
        {3, "slider", "invisible"},
        {5, "button", "disabled"}
    };

    std::vector<Control> controls2 = {
        {4, "button", "visible"},
        {2, "slider", "disabled"},
        {8, "button", "disabled"},
        {10, "slider", "visible"},
        {6, "slider", "invisible"}
    };
    
    //sort
    sortControl(controls1);
    //StableSort
    stableSort(controls2);
    //lower_bound
    cout<<"Enter an id to search.."<<endl;
    int searchId;
    cin>>searchId;
    lowerBound(controls1,searchId);
    upperBound(controls2,searchId);
    //merge
    vector<Control> mergedControl(size(controls1)+size(controls2));
    mergeControls(controls1,controls2,mergedControl);
    //inplacemerge
    vector<Control> allControls = controls1;
    allControls.insert(allControls.end(),controls2.begin(),controls2.end());
    inplaceMergeControls(allControls);
    //setUnion
    vector<Control> unionControls;
    setUnion(controls1,controls2,unionControls);
    //intersection
    vector<Control> intersectionControls;
    intersectionControl(controls1,controls2,intersectionControls);
    
    return 0;
}