#include <iostream>
#include <vector>
#include <memory>
#include <string>
 
// --- Singleton Pattern ---
// HMISystem class ensures only one instance is available for managing the HMI state.
class HMISystem {
private:
    static HMISystem* instance;  // Static instance of the Singleton
    std::string mode;
 
    // Private constructor to prevent instantiation
    HMISystem() : mode("Day") {}
 
public:
    // Public method to access the single instance
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }
 
    // Getter and setter for mode (Day/Night)
    std::string getMode() const {
        return mode;
    }
 
    void setMode(const std::string& newMode) {
        mode = newMode;
    }
};
 
// Initialize static instance to nullptr
HMISystem* HMISystem::instance = nullptr;
 
 
// --- Factory Pattern ---
// Base class for controls (Button, Slider, etc.)
class Control {
public:
    virtual void render() = 0;  // Pure virtual function for rendering
    virtual ~Control() = default;
};
 
// Concrete Button class (Control)
class Button : public Control {
public:
    void render() override {
        std::cout << "Rendering Button." << std::endl;
    }
};
 
// Concrete Slider class (Control)
class Slider : public Control {
public:
    void render() override {
        std::cout << "Rendering Slider." << std::endl;
    }
};
 
// Factory class to create controls based on type
class ControlFactory {
public:
    static std::unique_ptr<Control> createControl(const std::string& controlType) {
        if (controlType == "Button") {
            return std::make_unique<Button>();
        }
        else if (controlType == "Slider") {
            return std::make_unique<Slider>();
        }
        else {
            return nullptr;
        }
    }
};
 
 
// --- Observer Pattern ---
// Abstract Observer class
class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() = default;
};
 
// Concrete Button class (Observer)
class ButtonObserver : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Button: Switching to Night Mode" << std::endl;
        }
        else {
            std::cout << "Button: Switching to Day Mode" << std::endl;
        }
    }
};
 
// Concrete Slider class (Observer)
class SliderObserver : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Slider: Switching to Night Mode" << std::endl;
        }
        else {
            std::cout << "Slider: Switching to Day Mode" << std::endl;
        }
    }
};
 
// Subject (HMI System) that notifies observers about mode changes
class HMISystemWithObservers {
private:
    std::vector<ModeObserver*> observers;
    std::string mode;
 
public:
    void attach(ModeObserver* observer) {
        observers.push_back(observer);
    }
 
    void setMode(const std::string& newMode) {
        mode = newMode;
        notify();
    }
 
    void notify() {
        for (auto observer : observers) {
            observer->update(mode);
        }
    }
};
 
 
// --- Strategy Pattern ---
// Abstract Strategy class for rendering
class RenderingStrategy {
public:
    virtual void render() const = 0;
    virtual ~RenderingStrategy() = default;
};
 
// Concrete 2D rendering strategy
class Rendering2D : public RenderingStrategy {
public:
    void render() const override {
        std::cout << "Rendering in 2D" << std::endl;
    }
};
 
// Concrete 3D rendering strategy
class Rendering3D : public RenderingStrategy {
public:
    void render() const override {
        std::cout << "Rendering in 3D" << std::endl;
    }
};
 
// Control class that uses a rendering strategy
class ControlWithRendering {
private:
    std::shared_ptr<RenderingStrategy> strategy;
 
public:
    void setStrategy(std::shared_ptr<RenderingStrategy> newStrategy) {
        strategy = newStrategy;
    }
 
    void render() const {
        strategy->render();
    }
};
 
 
int main() {
    // --- Singleton Example ---
    HMISystem* hmi = HMISystem::getInstance();
    std::cout << "Current HMI Mode (Singleton): " << hmi->getMode() << std::endl;
    hmi->setMode("Night");
    std::cout << "Updated HMI Mode (Singleton): " << hmi->getMode() << std::endl;
 
    // --- Factory Example ---
    auto button = ControlFactory::createControl("Button");
    button->render();
    auto slider = ControlFactory::createControl("Slider");
    slider->render();
 
    // --- Observer Example ---
    HMISystemWithObservers hmiWithObservers;
    ButtonObserver buttonObserver;
    SliderObserver sliderObserver;
 
    hmiWithObservers.attach(&buttonObserver);
    hmiWithObservers.attach(&sliderObserver);
 
    hmiWithObservers.setMode("Night");
    hmiWithObservers.setMode("Day");
 
    // --- Strategy Example ---
    ControlWithRendering control;
    control.setStrategy(std::make_shared<Rendering2D>());
    control.render();
 
    control.setStrategy(std::make_shared<Rendering3D>());
    control.render();
 
    return 0;
}