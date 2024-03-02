#include "pubsub.hpp"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    
    rclcpp::NodeOptions options;
    auto publisher_node = std::make_shared<StringPublisher>(options);
    auto subscriber_node = std::make_shared<StringSubscriber>(options);
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(publisher_node);
    executor.add_node(subscriber_node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}