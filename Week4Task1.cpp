#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Control{
    int id;               // Unique ID    
    string type;     // "button" or "slider"    
    string state;    // "visible", "invisible", "disabled"
};

void displayControls(vector<Control> controls){
    for_each(controls.begin(),controls.end(),[](Control controls){
        cout<<"ID : "<<controls.id<<" Type : "<<controls.type<<" State : "<<controls.state<<endl;
    });
}

void findControl(vector<Control> controls,int x){
    auto it = find_if(controls.begin(),controls.end(),[x](Control controls){
        return controls.id == x;
    });
    if(it!=controls.end()){
        cout<<"Control found with id, Type : "<<it->type<<" State : "<<it->state<<endl;
    }
    else{
        cout<<"No control found with id "<<x;
    }
}

void findFirstInvisible(vector<Control> controls){
    auto it = find_if(controls.begin(),controls.end(),[](Control controls){
        return controls.state == "invisible";
    });
    if(it!=controls.end()){
        cout<<"First invisible found at Id : "<<it->id<<" Type "<<it->type<<" State : "<<it->state<<endl;
    }
    else{
        cout<<"No invisible state found..."<<endl;
    }
}

void consecutiveSameState(vector<Control> controls){
    auto it = adjacent_find(controls.begin(),controls.end(),[](Control a,Control b){
        return a.state == b.state;
    });
    if(it!=controls.end()){
        cout<<"Consecutive Same States found at \nId : "<<it->id<<" Type : "<<it->type<<" State : "<<it->state<<endl;
        cout<<"Id : "<<(it+1)->id<<" Type : "<<(it+1)->type<<" State : "<<(it+1)->state<<endl;
    }
    else{
        cout<<"No consecutive states found to be same..."<<endl;
    }
}

void countVisible(vector<Control> controls){
    int countV = count_if(controls.begin(),controls.end(),[](Control controls){
        return controls.state=="visible";
    });
    cout<<"There are "<<countV<<" visible states."<<endl;
}

void countSlidersDisabled(vector<Control> controls){
    auto countSliderDisable = count_if(controls.begin(),controls.end(),[](Control controls){
        return controls.type=="slider" && controls.state=="disabled";
    });
    cout<<"There are "<<countSliderDisable<<" sliders which are disabled."<<endl;
}

void SubrangesCompare(vector<Control> controls){
    bool equalSub = equal(controls.begin(),controls.begin()+4,controls.end()-5,[](Control a,Control b){
        return a.id==b.id && a.type==b.type && a.state==b.state;
    });
    cout<<(equalSub ? "Identical" : "Non-identical")<<endl;
}

int main(){
    vector<Control> controls = {
        {1,"button","visible"},
        {2,"slider","invisible"},
        {3,"button","disabled"},
        {4,"slider","visible"},
        {5,"button","invisible"},
        {6,"slider","disabled"},
        {7,"button","visible"},
        {8,"slider","invisible"},
        {9,"button","disabled"},
        {10,"slider","disabled"}
    };
    int choice;
    while(true){
        cout<<"Choose an option\n1 -> Display all the controls\n2 -> Find control with ID\n3 -> Find the first invisible control\n4 -> Check for consecutive controls with the same state\n5 -> Count the number of visible controls\n6 -> Count sliders that are disabled\n7 -> Compare two subranges of controls to check if they are identical\n0 -> Exit"<<endl;
        cin>>choice;
        if(choice==0){
            break;
        }
        
        switch(choice){
            case 1:
                displayControls(controls);
                break;
            case 2:
                cout<<"Enter id of controls : ";
                int x;
                cin>>x;
                findControl(controls,x);
                break;
            case 3:
                findFirstInvisible(controls);
                break;
            case 4:
                consecutiveSameState(controls);
                break;
            case 5:
                countVisible(controls);
                break;
            case 6:
                countSlidersDisabled(controls);
                break;
            case 7:
                SubrangesCompare(controls);
                break;
            default:
            cout<<"Enter a valid option.."<<endl;
                continue;
        }
    }
    
    return 0;
}