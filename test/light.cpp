#include <iostream>
#include <memory>

// 前向声明
class LightState;
// class OffState;
// class OnState;

// Context类
class Light {
private:
    std::shared_ptr<LightState> currentState;
    
public:
    Light(): currentState(std::make_shared<OffState>()) {}
    void setState(std::shared_ptr<LightState> newState) {
        currentState = newState;
    }

    void pressSwitch() {
        currentState->handlePress(*this);
    }
    void displayStatus() const {
        std::cout << "当前状态: " << currentState->getStatus() << std::endl;
    }
};

// State接口
class LightState {
public:
    virtual ~LightState() = default;
    virtual void handlePress(Light& light) = 0;
    virtual std::string getStatus() const = 0;
};

// 具体状态：关闭状态
class OffState : public LightState {
public:
    void handlePress(Light& light) override {
        std::cout << "从关闭状态切换到开启状态\n";
        light.setState(std::make_shared<OnState>());
    }
    std::string getStatus() const override { return "关闭"; }
};

// 具体状态：开启状态  
class OnState: public LightState {
public:
    void OnState::handlePress(Light& light) override {
        std::cout << "从开启状态切换到关闭状态\n";
        light.setState(std::make_shared<OffState>());
    }
    std::string getStatus() const override { return "开启"; }
};

// 使用示例
int main() {
    Light light;
    
    light.displayStatus();  // 当前状态: 关闭
    
    light.pressSwitch();    // 从关闭状态切换到开启状态
    light.displayStatus();  // 当前状态: 开启
    
    light.pressSwitch();    // 从开启状态切换到关闭状态
    light.displayStatus();  // 当前状态: 关闭
    
    return 0;
}