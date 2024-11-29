#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

void displayDynamicWidgets(vector<string> dynamicWidgets){
    for_each(dynamicWidgets.begin(),dynamicWidgets.end(),[](string dynamicWidgets){
        cout<<dynamicWidgets<<endl;
    });
}

void checkWidget(set<string> staticWidgets,string widget){
    auto it=staticWidgets.find(widget);
    if(it!=staticWidgets.end()){
        cout<<"Widget found : "<<widget<<endl;
    }
    else{
        cout<<"Widgrt not found..."<<endl;
    }
}

void combineWidgets(vector<string>& dynamicWidgets,set<string>& staticWidgets,vector<string>& allWidgets){
    cout<<"Combining containers....\n";
    copy(dynamicWidgets.begin(),dynamicWidgets.end(),back_inserter(allWidgets));
    copy(staticWidgets.begin(),staticWidgets.end(),back_inserter(allWidgets));
    displayDynamicWidgets(allWidgets);
}

void findWidget(vector<string> allWidgets,string widget){
    auto it = find(allWidgets.begin(),allWidgets.end(),widget);
    if(it != allWidgets.end()){
        cout<<"Widget found : "<<widget<<endl;
    }
    else{
        cout<<"Wiget not found...\n";
    }
}

int main(){
    vector<string> dynamicWidgets = {"Speedometer","Tachometer","Fuel Gauge","Temperature Gauge",
    "Pressure Gauge","Fuel Efficiency Gauge","Battery Charge Indicator"};
    set<string> staticWidgets = {"Logo","Branding Element","WarningLights","Alert Indicator","LED Indicator"};
    int choice;
    string widget;
    vector<string> allWidgets;
    while(true){
        cout<<"Choose a option..\n1 -> Display Dynamic widgets\n2 -> Check Widget...\n3 -> Combine both static and dynamic widgets\n4 -> Loacate specific Widget in combined wigets..\n0 -> Exit\n";
        cin>>choice;
        if(choice==0){
            break;
        }
        switch(choice){
            case 1:
                displayDynamicWidgets(dynamicWidgets);
                break;
            case 2:
                cout<<"Enter a specific static widget.\n";
                cin>>widget;
                checkWidget(staticWidgets,widget);
                break;
            case 3:
                combineWidgets(dynamicWidgets,staticWidgets,allWidgets);
                break;
            case 4:
                cout<<"Enter a specific widget.\n";
                cin>>widget;
                findWidget(allWidgets,widget);
                break;
            default:
                cout<<"Enter a valid option.."<<endl;
                continue;
        }
    }
}