#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class StringPublisher : public rclcpp::Node {
public:
    StringPublisher(rclcpp::NodeOptions options = rclcpp::NodeOptions()) : Node("string_publisher", options) {
        RCLCPP_INFO_STREAM(this->get_logger(), "use_intra_process_comms: " << (options.use_intra_process_comms() ? "true" : "false"));

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(100ms, std::bind(&StringPublisher::publish_message, this));
    }

private:
    void publish_message() {

        if(pub_cnt == 5) return;
        pub_cnt++;
        auto msg = std::make_unique<std_msgs::msg::String>();
        msg->data = "Hello, world!";
        RCLCPP_INFO(this->get_logger(), " pub msg ptr:     %p", (void *)&(msg->data));
        publisher_->publish(std::move(msg));
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    int pub_cnt = 0;
};

class StringSubscriber : public rclcpp::Node {
public:
    StringSubscriber(rclcpp::NodeOptions options = rclcpp::NodeOptions()) : Node("string_subscriber", options) {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "topic", 10, std::bind(&StringSubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const std_msgs::msg::String::UniquePtr msg) const {
        RCLCPP_INFO(this->get_logger(), " -> sub msg ptr: %p", (void *)&(msg->data));
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};