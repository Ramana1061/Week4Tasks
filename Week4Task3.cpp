#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>

struct Control {
    int id;
    std::string type;
    std::string state;
};

void printControls(const std::vector<Control>& controls) {
    for (const auto& ctrl : controls) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << '\n';
    }
}

int main() {
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "button", "invisible"},
        {3, "button", "disabled"},
        {4, "slider", "visible"},
        {5, "slider", "disabled"},
        {6, "button", "invisible"},
        {7, "slider", "disabled"},
        {8, "button", "visible"},
        {9, "slider", "visible"},
        {10, "slider", "disabled"}
    };

    std::cout << "Original Control List:\n";
    printControls(controls);

    std::vector<Control> backupControls(controls.size());
    std::copy(controls.begin(), controls.end(), backupControls.begin());
    std::cout << "\nBackup Control List:\n";
    printControls(backupControls);

    std::fill(controls.begin(), controls.end(), Control{0, "", "disabled"});
    std::cout << "\nAfter std::fill: All states set to 'disabled'\n";
    printControls(controls);

    std::srand(static_cast<unsigned int>(std::time(0)));
    auto randomStateGenerator = []() {
        int randState = std::rand() % 3;
        switch (randState) {
            case 0: return "visible";
            case 1: return "invisible";
            case 2: return "disabled";
            default: return "visible";
        }
    };
    std::generate(controls.begin(), controls.end(), [&randomStateGenerator, i = 0]() mutable {
        return Control{i++, "button", randomStateGenerator()};
    });
    std::cout << "\nAfter std::generate: Randomized states for testing\n";
    printControls(controls);

    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& ctrl) {
        if (ctrl.type == "slider") {
            ctrl.state = "invisible";
        }
        return ctrl;
    });
    std::cout << "\nAfter std::transform: All sliders set to 'invisible'\n";
    printControls(controls);

    std::replace_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "disabled";
    }, Control{0, "", "enabled"});
    std::cout << "\nAfter std::replace_if: Replaced 'disabled' with 'enabled'\n";
    printControls(controls);

    controls.erase(std::remove_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    }), controls.end());
    std::cout << "\nAfter std::remove_if: Removed all 'invisible' controls\n";
    printControls(controls);

    std::reverse(controls.begin(), controls.end());
    std::cout << "\nAfter std::reverse: Control order reversed\n";
    printControls(controls);

    auto partitionIt = std::partition(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "\nAfter std::partition: Controls partitioned into visible and non-visible\n";
    std::cout << "Visible Controls:\n";
    printControls({controls.begin(), partitionIt});
    std::cout << "Non-visible Controls:\n";
    printControls({partitionIt, controls.end()});
}
