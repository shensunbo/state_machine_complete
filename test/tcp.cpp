#include <iostream>
#include <memory>
#include <string>

// 前向声明
class TCPState;
class TCPConnection;

// Context类
class TCPConnection {
private:
    std::shared_ptr<TCPState> state;
    std::string name;
    
public:
    TCPConnection(const std::string& connName);
    
    void setState(std::shared_ptr<TCPState> newState);
    std::string getName() const { return name; }
    
    // 暴露给客户端的操作
    void open();
    void acknowledge();
    void close();
    void transmit(const std::string& data);
    
    void displayStatus() const;
};

// State接口
class TCPState {
public:
    virtual ~TCPState() = default;
    virtual void open(TCPConnection& connection) {
        std::cout << "错误: 在当前状态下不能执行open操作\n";
    }
    virtual void acknowledge(TCPConnection& connection) {
        std::cout << "错误: 在当前状态下不能执行acknowledge操作\n";
    }
    virtual void close(TCPConnection& connection) {
        std::cout << "错误: 在当前状态下不能执行close操作\n";
    }
    virtual void transmit(TCPConnection& connection, const std::string& data) {
        std::cout << "错误: 在当前状态下不能执行transmit操作\n";
    }
    virtual std::string getStateName() const = 0;
};

// 具体状态：关闭状态
class TCPClosed : public TCPState {
public:
    static std::shared_ptr<TCPState> getInstance() {
        static auto instance = std::make_shared<TCPClosed>();
        return instance;
    }
    
    void open(TCPConnection& connection) override;
    std::string getStateName() const override { return "TCPClosed"; }
};

// 具体状态：监听状态
class TCPListen : public TCPState {
public:
    static std::shared_ptr<TCPState> getInstance() {
        static auto instance = std::make_shared<TCPListen>();
        return instance;
    }
    
    void acknowledge(TCPConnection& connection) override;
    void close(TCPConnection& connection) override;
    std::string getStateName() const override { return "TCPListen"; }
};

// 具体状态：已建立状态
class TCPEstablished : public TCPState {
public:
    static std::shared_ptr<TCPState> getInstance() {
        static auto instance = std::make_shared<TCPEstablished>();
        return instance;
    }
    
    void transmit(TCPConnection& connection, const std::string& data) override;
    void close(TCPConnection& connection) override;
    std::string getStateName() const override { return "TCPEstablished"; }
};

// TCPConnection实现
TCPConnection::TCPConnection(const std::string& connName) 
    : name(connName), state(TCPClosed::getInstance()) {}

void TCPConnection::setState(std::shared_ptr<TCPState> newState) {
    std::cout << "连接 " << name << " 状态变化: " 
              << state->getStateName() << " -> " << newState->getStateName() << std::endl;
    state = newState;
}

void TCPConnection::open() {
    state->open(*this);
}

void TCPConnection::acknowledge() {
    state->acknowledge(*this);
}

void TCPConnection::close() {
    state->close(*this);
}

void TCPConnection::transmit(const std::string& data) {
    state->transmit(*this, data);
}

void TCPConnection::displayStatus() const {
    std::cout << "连接 " << name << " 当前状态: " << state->getStateName() << std::endl;
}

// 具体状态实现
void TCPClosed::open(TCPConnection& connection) {
    std::cout << "打开连接，开始三次握手...\n";
    connection.setState(TCPListen::getInstance());
}

void TCPListen::acknowledge(TCPConnection& connection) {
    std::cout << "收到ACK，连接建立成功\n";
    connection.setState(TCPEstablished::getInstance());
}

void TCPListen::close(TCPConnection& connection) {
    std::cout << "关闭监听状态\n";
    connection.setState(TCPClosed::getInstance());
}

void TCPEstablished::transmit(TCPConnection& connection, const std::string& data) {
    std::cout << "传输数据: " << data << std::endl;
}

void TCPEstablished::close(TCPConnection& connection) {
    std::cout << "关闭已建立的连接\n";
    connection.setState(TCPClosed::getInstance());
}

// 使用示例
int main() {
    TCPConnection conn1("Connection-1");
    
    conn1.displayStatus();  // 连接 Connection-1 当前状态: TCPClosed
    
    conn1.open();           // 打开连接，开始三次握手...
    conn1.displayStatus();  // 连接 Connection-1 当前状态: TCPListen
    
    conn1.acknowledge();    // 收到ACK，连接建立成功
    conn1.displayStatus();  // 连接 Connection-1 当前状态: TCPEstablished
    
    conn1.transmit("Hello World!");  // 传输数据: Hello World!
    conn1.close();          // 关闭已建立的连接
    conn1.displayStatus();  // 连接 Connection-1 当前状态: TCPClosed
    
    return 0;
}